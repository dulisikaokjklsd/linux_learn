// O_TRUNC 打开时清空现有文件 
// O_APPEND 续写
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(void)
{
    char buff[4];
    int fd1 = open("./test", O_RDONLY | O_TRUNC | O_APPEND);
    if(-1==fd1){
        perror("open error");
        exit(-1);
    }
    memset(buff,0x55,sizeof(buff));
    write(fd1,buff,4);
    close(fd1);
    return 0;
}