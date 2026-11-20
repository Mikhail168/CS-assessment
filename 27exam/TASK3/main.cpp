#include<iostream>
#include<fstream>
#include<vector>
enum direct{up,down,left,right};


void DFS(int r,int c,const std::vector<std::string>& map,std::vector<std::vector<bool>>& visited,int &cell){
    int y = map.size();
    int x = map[0].size();
    int directr[4]={-1,0,1,0};
    int directc[4]={0,1,0,-1};
    for(int i=0;i<4;i++){
        int nextr=r+directr[i];int nextc=c+directc[i];
        if(nextr<0||nextc<0||nextr>=y||nextc>=x)
          continue;
        else if(map[nextr][nextc]=='#')
          continue;
        else if(visited[nextr][nextc]==true)
          continue;
        else{
            visited[nextr][nextc] = true;
            ++cell;
            DFS(nextr,nextc,map,visited,cell);
        }
        

    }
    //std::cout<<cell<<std::endl;//调试用代码

}
struct point{
    int r,c;int f,g,h;
};
struct node{
    point pos;
    std::vector<node*>  npos;
    node* parentpos;
};
node* createNode(int y,int x){
    node* pNew=new node;
    *pNew={};
    pNew->pos.r=y;pNew->pos.c=x;
    return pNew;
}
int geth(point pos,point end,int cost){
    int x=((end.c>pos.c)?(end.c-pos.c):(pos.c-end.c));
    int y=((end.r>pos.r)?(end.r-pos.r):(pos.r-end.r));
    return cost*(x+y);
}
void Astar(int r,int c,int r2,int c2,const std::vector<std::string>& map,std::vector<std::vector<bool>>& visited){
    for(int i=0;i<(int)map.size();i++){
        for(int j=0;j<(int)map[0].size();j++){
            visited[i][j]=false;
        }
    }
    visited[r][c] = true;
    int cost=1;int varcost=0;
    int findend=0;int totalcost=1;
    point begin={r,c};point end={r2,c2};
    node* rootpos=createNode(begin.r,begin.c);
    node* currentpos=rootpos;
    node* childpos=NULL;

    std::vector<node*>buff;
    std::vector<node*>::iterator it;
    std::vector<node*>::iterator itmin;

    while(1){
        for(int i =0;i<4;i++){
            childpos=createNode(currentpos->pos.r,currentpos->pos.c);
            if(childpos->pos.r<0||childpos->pos.r>=(int)map.size()||childpos->pos.c<0||childpos->pos.c>=(int)map[0].size()){
               delete childpos;
               continue;
            }
            switch(i){
                case up:
                  childpos->pos.r--;
                  if(childpos->pos.r<0||childpos->pos.r>=(int)map.size()||childpos->pos.c<0||childpos->pos.c>=(int)map[0].size()){
                    delete childpos;
                    continue;
                  }
                  else{
                    if(map[childpos->pos.r][childpos->pos.c]=='2'||map[childpos->pos.r][childpos->pos.c]=='3'||map[childpos->pos.r][childpos->pos.c]=='4'||map[childpos->pos.r][childpos->pos.c]=='5'||map[childpos->pos.r][childpos->pos.c]=='6'||map[childpos->pos.r][childpos->pos.c]=='7'||map[childpos->pos.r][childpos->pos.c]=='8'||map[childpos->pos.r][childpos->pos.c]=='9'){
                      varcost=map[childpos->pos.r][childpos->pos.c]-'0';
                      childpos->pos.g +=varcost;
                    }
                    else if(map[childpos->pos.r][childpos->pos.c]=='G'||map[childpos->pos.r][childpos->pos.c]=='S'){
                        childpos->pos.g +=cost;
                    }
                    else{
                      childpos->pos.g +=cost;
                    }
                  }
 
                  break;
                case down:
                  childpos->pos.r++;
                  if(childpos->pos.r<0||childpos->pos.r>=(int)map.size()||childpos->pos.c<0||childpos->pos.c>=(int)map[0].size()){
                    delete childpos;
                    continue;
                  }
                  else{
                    if(map[childpos->pos.r][childpos->pos.c]=='2'||map[childpos->pos.r][childpos->pos.c]=='3'||map[childpos->pos.r][childpos->pos.c]=='4'||map[childpos->pos.r][childpos->pos.c]=='5'||map[childpos->pos.r][childpos->pos.c]=='6'||map[childpos->pos.r][childpos->pos.c]=='7'||map[childpos->pos.r][childpos->pos.c]=='8'||map[childpos->pos.r][childpos->pos.c]=='9'){
                      varcost=map[childpos->pos.r][childpos->pos.c]-'0';
                      childpos->pos.g = currentpos->pos.g + varcost;
                    }
                    else if(map[childpos->pos.r][childpos->pos.c]=='G'||map[childpos->pos.r][childpos->pos.c]=='S'){
                        childpos->pos.g = currentpos->pos.g + cost;
                    }
                    else{
                      childpos->pos.g = currentpos->pos.g + cost;
                    }
                  } 
                  break;
                case left:
                  childpos->pos.c--;
                  if(childpos->pos.r<0||childpos->pos.r>=(int)map.size()||childpos->pos.c<0||childpos->pos.c>=(int)map[0].size()){
                    delete childpos;
                    continue;
                  }
                  else{
                    if(map[childpos->pos.r][childpos->pos.c]=='2'||map[childpos->pos.r][childpos->pos.c]=='3'||map[childpos->pos.r][childpos->pos.c]=='4'||map[childpos->pos.r][childpos->pos.c]=='5'||map[childpos->pos.r][childpos->pos.c]=='6'||map[childpos->pos.r][childpos->pos.c]=='7'||map[childpos->pos.r][childpos->pos.c]=='8'||map[childpos->pos.r][childpos->pos.c]=='9'){
                      varcost=map[childpos->pos.r][childpos->pos.c]-'0';
                      childpos->pos.g = currentpos->pos.g + varcost;
                    }
                    else if(map[childpos->pos.r][childpos->pos.c]=='G'||map[childpos->pos.r][childpos->pos.c]=='S'){
                        childpos->pos.g = currentpos->pos.g + cost;
                    }
                    else{
                      childpos->pos.g = currentpos->pos.g + cost;
                    }
                  } 
                  break;
                case right:
                  childpos->pos.c++;
                  if(childpos->pos.r<0||childpos->pos.r>=(int)map.size()||childpos->pos.c<0||childpos->pos.c>=(int)map[0].size()){
                    delete childpos;
                    continue;
                  }
                  else{
                    if(map[childpos->pos.r][childpos->pos.c]=='2'||map[childpos->pos.r][childpos->pos.c]=='3'||map[childpos->pos.r][childpos->pos.c]=='4'||map[childpos->pos.r][childpos->pos.c]=='5'||map[childpos->pos.r][childpos->pos.c]=='6'||map[childpos->pos.r][childpos->pos.c]=='7'||map[childpos->pos.r][childpos->pos.c]=='8'||map[childpos->pos.r][childpos->pos.c]=='9'){
                      varcost=map[childpos->pos.r][childpos->pos.c]-'0';
                      childpos->pos.g = currentpos->pos.g + varcost;
                    }
                    else if(map[childpos->pos.r][childpos->pos.c]=='G'||map[childpos->pos.r][childpos->pos.c]=='S'){
                        childpos->pos.g = currentpos->pos.g + cost;
                    }
                    else{
                      childpos->pos.g = currentpos->pos.g + cost;
                    }
                  } 
                  break;
            }
            if((map[childpos->pos.r][childpos->pos.c]=='.'||map[childpos->pos.r][childpos->pos.c]=='2'||map[childpos->pos.r][childpos->pos.c]=='3'||map[childpos->pos.r][childpos->pos.c]=='4'||map[childpos->pos.r][childpos->pos.c]=='5'||map[childpos->pos.r][childpos->pos.c]=='6'||map[childpos->pos.r][childpos->pos.c]=='7'||map[childpos->pos.r][childpos->pos.c]=='8'||map[childpos->pos.r][childpos->pos.c]=='9'||map[childpos->pos.r][childpos->pos.c]=='G') && visited[childpos->pos.r][childpos->pos.c]==false){
               childpos->pos.h=geth(childpos->pos,end,cost);
               childpos->pos.f=childpos->pos.g+childpos->pos.h;
               currentpos->npos.push_back(childpos);
               childpos->parentpos=currentpos;
               buff.push_back(childpos);
            }
            else{
                delete childpos;
            }
        }
        it=buff.begin();
        itmin=buff.begin();
        if(buff.empty()){
            break;
        }
        for(;it!=buff.end();it++){
            itmin=(((*itmin)->pos.f<(*it)->pos.f)?itmin:it);
        }
        currentpos=*itmin;
        visited[currentpos->pos.r][currentpos->pos.c]=true;
        buff.erase(itmin);
        if(end.r==currentpos->pos.r&&end.c==currentpos->pos.c){
            break;
        }
        if(buff.size()==0){
            findend=-1;
            break;
        }
    }
    if(findend==-1){
        std::cout<<"终点未找到或不可达\n";
    }
    else{
        std::cout<<"终点已找到\n";
        while(currentpos){
            if(map[currentpos->pos.r][currentpos->pos.c]=='.'){
                totalcost+=cost;
                currentpos=currentpos->parentpos;
                continue;
            }
            if(map[currentpos->pos.r][currentpos->pos.c]=='2'||map[currentpos->pos.r][currentpos->pos.c]=='3'||map[currentpos->pos.r][currentpos->pos.c]=='4'||map[currentpos->pos.r][currentpos->pos.c]=='5'||map[currentpos->pos.r][currentpos->pos.c]=='6'||map[currentpos->pos.r][currentpos->pos.c]=='7'||map[currentpos->pos.r][currentpos->pos.c]=='8'||map[currentpos->pos.r][currentpos->pos.c]=='9'){
                totalcost+=map[currentpos->pos.r][currentpos->pos.c]-'0';
                currentpos=currentpos->parentpos;
                continue;
            }
            currentpos=currentpos->parentpos;
        }
        std::cout<<"cost:"<<totalcost<<std::endl;
    }
    
}

void initializer(){
   int x=0,y=0;
   int r=0,c=0,r2=0,c2=0;
   int wall=0;
   std::cout<<"请输入地图宽的大小： \n";
   std::cin>>y;
   std::cout<<"请输入地图长的大小： \n";
   std::cin>>x;
   std::ifstream f1;
   f1.open("sample.in",std::ios::in);
    std::vector<std::string> map(y);
    std::cout<<"地图示意：\n";
    for (int i = 0; i < y; ++i) {
        std::getline(f1, map[i]);
        std::cout << map[i] << "\n";
    }
   f1.close();
   if(map[y-1][x-1]=='#'||map[y-1][x-1]=='.'||map[y-1][x-1]=='S'||map[y-1][x-1]=='G'||map[y-1][x-1]=='2'||map[y-1][x-1]=='3'||map[y-1][x-1]=='4'||map[y-1][x-1]=='5'||map[y-1][x-1]=='6'||map[y-1][x-1]=='7'||map[y-1][x-1]=='8'||map[y-1][x-1]=='9'){
     for(int i=0;i<y;i++){
      for(int j=0;j<x;j++){
        if(map[i][j]=='#'){
          ++wall;
        }
        if(map[i][j]=='S'){
            r=i;c=j;
        }
        if(map[i][j]=='G'){
            r2=i;c2=j;
        }
      }
    }
    std::cout<<"起点坐标："<<c<<" "<<r<<std::endl;
    std::cout<<"终点坐标："<<c2<<" "<<r2<<std::endl;
    std::vector<std::vector<bool>> visited(y, std::vector<bool>(x, false));
    visited[r][c] = true;int cell=1;
    int i = map.size();
    int j = map[0].size();
    DFS(r,c,map,visited,cell);
    std::cout << "reachable cells: " << cell << std::endl;
    int reg=i*j-cell-wall;
    //std::cout<<i*j<<std::endl;
    //std::cout<<wall<<std::endl;
    std::cout<<"regions:"<<reg<<std::endl;

    Astar(r,c,r2,c2,map,visited);
   }
   else{
      std::cout<<"地图输入无效\n";
   }
}


int main(){

    initializer();

}