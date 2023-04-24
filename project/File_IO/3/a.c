// 多次打开同一文件
// 有不同文件描述符，指向不同文件表（所以位置偏移量会不同），但不同文件表指向同一inode节点
// 内存中只会存在一个动态文件，并不会出现多份动态文件
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main(){
    int fd1,fd2,fd3;
    int ret;

    fd1 = open("./test_file",O_RDWR|O_CREAT);
    if(-1==fd1){
        perror("open error 1");
        exit(-1);
    }

    fd2 = open("./test_file",O_RDWR|O_CREAT);
    if(-1==fd2){
        perror("open error 2");
        close(fd1);
        exit(-1);
    }
    fd3 = open("./test_file",O_RDWR|O_CREAT);
    if(-1==fd3){
        perror("open error 3");
        close(fd1);
        close(fd2);
        exit(-1);
    }
    printf("%d %d %d\n",fd1,fd2,fd3);
    close(fd1);
    close(fd2);
    close(fd3);
    exit(0);
}