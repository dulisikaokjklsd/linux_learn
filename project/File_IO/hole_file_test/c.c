#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char buff[1024];
    char buff2[8192];
    int fd, fd1;
    int ret;
    fd = open("./hole_file", O_WRONLY | O_CREAT | O_EXCL,
              S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (-1 == fd)
    {
        perror("open error");
        exit(-1);
    }
    //  读写头偏移到4096处
    ret = lseek(fd, 4096, SEEK_SET);
    if (-1 == ret)
    {
        perror("lseek error");
        close(fd);
        exit(-1);
    }
    memset(buff, 'a', sizeof(buff));

    for (int i = 0; i < 4; i++)
    {
        ret = write(fd, buff, sizeof(buff));
        if (-1 == ret)
        {
            perror("write error");
            close(fd);
            exit(-1);
        }
    }

    fd1 = open("./test_file", O_RDWR | O_CREAT,
               S_IRWXU | S_IRGRP | S_IROTH);
    if (-1 == fd1)
    {
        perror("open2 error");
        close(fd);
        exit(-1);
    }

    ret = read(fd, buff2, sizeof(buff2));
    if (-1 == fd)
    {
        perror("read error");
        close(fd);
        close(fd1);
        exit(-1);
    }

    ret = write(fd1, buff2, sizeof(buff2));
    if (-1 == fd)
    {
        perror("write2 error");
        close(fd);
        close(fd1);
        exit(-1);
    }

    close(fd);
    close(fd1);
    exit(0);
}