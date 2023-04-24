// 使用dup函数实现续写
// 还有一个dup2,第二个参数可以指定复制的文件的标志符（前提是未被占用）
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int main()
{
    int fd1, fd2;
    int ret;
    char buff1[4] = {0x11, 0x22, 0x33, 0x44};
    char buff2[4] = {0xAA, 0xBB, 0xCC, 0xDD};

    fd1 = open("./test_file", O_RDWR | O_CREAT | O_APPEND,
               S_IRWXU | S_IRGRP | S_IROTH);
    if (-1 == fd1)
    {
        perror("open error 1");
        exit(-1);
    }

    fd2 = dup(fd1);
    for (int i = 0; i < 4; i++)
    {
        int a, b;
        a = write(fd1, buff1, sizeof(buff1));
        if (-1 == a)
        {
            perror("write error 1");
            close(fd1);
            close(fd2);
            exit(-1);
        }

        b = write(fd2, buff2, sizeof(buff2));
        if (-1 == b)
        {
            perror("write error 2");
            close(fd1);
            close(fd2);
            exit(-1);
        }
    }

    int lsk = lseek(fd1,0,SEEK_SET);
    if(-1==lsk){
        perror("lssek error");
            close(fd1);
            close(fd2);
            exit(-1);
    }
    memset(buff1,0,sizeof(buff1));
    for(int i=0;i<8;i++){
        int rd = read(fd1,buff1,sizeof(buff1));
        if(-1==rd){
            perror("read error");
            close(fd1);
            close(fd2);
            exit(-1);
        }
        printf("%x%x%x%x  ",buff1[0],buff1[1],buff1[2],buff1[3]);
    }

    close(fd1);
    close(fd2);
    exit(0);   
}