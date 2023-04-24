// perror
// strerror
// errno
//exit、_exit()
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
int main()
{
    int fd1 = open("./test_file", O_RDONLY);
    if (-1 == fd1)
    {
        // printf("ERROR: %s\n", strerror(errno));
        perror("error");
        // _exit()是系统调用，exit()是C库函数用法一样
        // exit(-1);
        _exit(-1);
    }
    close(fd1);
    exit(0);
    // _exit(0);
}