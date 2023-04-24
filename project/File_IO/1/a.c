// 读读写写偏移偏移啥的
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
    int fd1, fd2;
    ssize_t r_sign, w_sign;
    char buff[1024];
    fd1 = open("./src_file",O_RDONLY);
    if(-1==fd1){
        printf("open file 1 error\n");
        return -1;
    }
    lseek(fd1,500,SEEK_SET);
    r_sign = read(fd1,buff,1024);
    printf("r_sign: %ld", r_sign);
    close(fd1);
    fd2 = open("./kkk",O_WRONLY|O_CREAT,S_IRWXU|S_IRGRP|S_IROTH);
    if(-1==fd2){
        printf("open file 2 error\n");
        return -1;
    }
    w_sign = write(fd2,buff,1024);
    printf("w_sign: %ld", w_sign);
    close(fd2);
    return 0;
}