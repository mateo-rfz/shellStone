#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>


#define STDOUT 1
#define STDERR 2


int
main(int argc , char * argv[])
{
    if (argc < 2) 
    {
        write(STDERR , "Enter valid arguments\n" , 22);
        return 1;
    }
    
    char * path = argv[1];
    if (access(path , F_OK) == -1)
    {
        write(STDERR , "No such file or directory\n" , 26);
        return 1;
    }
    if (access(path , R_OK) == -1)
    {
        write(STDERR , "You can't read this file\n" , 25);
        return 1;
    }

    struct stat st;
    stat(path , &st);

    const int buff_size = st.st_size;
    
    int fd = 0;
    if ((fd = open(path , O_RDONLY)) < 0)
    {
        write(STDERR , "Open file faild\n" , 17);
        return 1;
    }

    char * buffer = malloc(buff_size);
    if (read(fd , buffer , buff_size) < 0)
    {
        write(STDERR , "Read file faild\n" , 16);
        return 1;
    }
    if (write(STDOUT , buffer , buff_size) < 0)
    {
        write(STDOUT , "Faild to write in output\n" , 25);
        return 1;
    }
    
    return 0;
}

