#include <algorithm>
#include<iostream>
#include<vector>
#include<cmath>
#include<type_traits>

struct CameraFrame { int w, h; const unsigned char* buf; };
struct RosImage    { int w, h, step; const unsigned char* data; };  // step 为每行字节数，step >= w
struct VideoFrame  { int w, h; const unsigned char* yuv; };         // 只使用前 w*h 字节（Y 平面）

namespace virt {
class ImageSource {
public:
    virtual ~ImageSource() = default;
    virtual int width() const = 0;
    virtual int height() const = 0;
    virtual unsigned char at(int x, int y) const = 0;
};

class CameraSource : public ImageSource { public: explicit CameraSource(CameraFrame f):f_(f){}
    int width() const override{
        return f_.w;
    }
    int height()const override {
        return f_.h;
    }
    unsigned char at(int x,int y)const override{
        return f_.buf[y*width()+x];

    }
        private:
      CameraFrame f_; /* 实现三个虚函数 */ };

class RosSource    : public ImageSource { public: explicit RosSource(RosImage f):f_(f){}
    int width()const override{
        return f_.w;
    }
    int height()const override{
        return f_.h;
    }
    unsigned char at(int x,int y)const override{
        return f_.data[y*f_.step+x];
    }   
private:
  RosImage f_;           /* 同上 */ };
class VideoSource  : public ImageSource { public: explicit VideoSource(VideoFrame f):f_(f){}
   int width()const override{
    return f_.w;
   }
   int height()const override{
    return f_.h;
   }
   unsigned char at(int x,int y)const override{
      std::max(f_.yuv[y*width()+x]-16,0);
      return f_.yuv[y*width()+x];
   }
private:
   VideoFrame f_;       /* 同上 */ };

std::uint64_t preprocess(const ImageSource& src);
std::uint64_t preprocess(const ImageSource& src) {
    std::uint64_t sum = 0;
    for (int y = 0; y < src.height(); ++y) {
        for (int x = 0; x < src.width(); ++x) {
            sum += src.at(x, y);
        }
    }
    return sum;
}
}

namespace tmpl {
// Frame 为 CameraFrame、RosImage、VideoFrame 之一，直接使用上面的原始结构体，不需要再包装成类

template <typename Frame>
unsigned char at(const Frame& f,int x,int y);
template<>
unsigned char at<CameraFrame>(const CameraFrame& f,int x,int y){
    return f.buf[y*f.w + x];
}
template<>
unsigned char at<RosImage>(const RosImage& f,int x,int y){
    return f.data[y*f.step + x];
}
template<>
unsigned char at<VideoFrame>(const VideoFrame& f,int x,int y){
    std::max(f.yuv[y*f.w+x]-16,0);
    return f.yuv[y*f.w+x];
}
template <typename Frame>

std::uint64_t preprocess(const Frame& f){
    std::uint64_t sum = 0;int w=0,h=0;
    if constexpr(std::is_same_v<Frame,CameraFrame>){
        w=f.w;h=f.h;
    }
    else if constexpr(std::is_same_v<Frame,RosImage>){
        w=f.w;h=f.h;
    }
    else if constexpr(std::is_same_v<Frame, VideoFrame>){
        w=f.w;h=f.h;
    }
    for(int y=0;y<h;y++){
        for(int x=0;x<w;x++){
            sum+=at(f,x,y);
        }
    }
    return sum;
}

}




int main(){
   CameraFrame f;
   f.w = 1280;
   f.h = 1024;
   unsigned char buf[f.w*f.h];
   const unsigned char*buffer=buf;
   f.buf = buffer;
   virt::CameraSource src(f);
   auto a = virt::preprocess(src);
   std::cout<<a<<std::endl;
   auto b = tmpl::preprocess(f);
   std::cout<<b<<std::endl;

   
}