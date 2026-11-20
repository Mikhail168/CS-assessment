#!/bin/bash
build(){
  (
   executable=$(find /home -name "app" -type f -executable 2>/dev/null | head -n 1)
   if [ -n "$executable" ];then
      echo "文件已存在，已跳过编译，若要更新请执行./run.sh update"
   else
      mkdir -p build
      cd build
      cmake ..
      cmake --build .
    fi
  )
}
run(){
  (
    cd build 
    ./app "$@"
  )
}

clean(){
  (
   cd build
   cmake --build . --target clean
  )
}
update(){
  (
    cd build
    cmake --build . --target clean
    
    cmake ..
    cmake --build .
  )
}
help(){
  echo "./run.sh build 构建可执行文件"
  echo "./run.sh run --arg1 arg2 运行可执行文件（可传参）"
  echo "./run.sh clean 删除可执行文件"
  echo "./run.sh update 更新可执行文件"
  echo "./run.sh -help 帮助界面"
  
}



command=${1:-help}
case "$command" in
     build)
       build;;
     run)
       shift
        if [ "${1:-}" = "--" ];then
          shift
        fi
          run "$@"
       ;;
     clean)
       clean;;
     update)
       update;;
     -help)
       help;;
     *)
       exit 1;;
esac
      
