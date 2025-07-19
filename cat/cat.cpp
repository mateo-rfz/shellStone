#include <seccomp.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>


#define DEFAULT_BUFFER_SIZE 8192
/* 
use this size for buffer if kernel 
suggestion is wrong (if kernel suggestion < 1 use this macro)
*/


//standard output
#define STDOUT 1
#define STDERR 2


// need an argeparser
// add usage
// set flags
// add handler for open read write systemcalls





void
usage()
{
    ;
}







int 
main(int argc , char * argv[])
{
#ifdef __OPENBSD__
    if (pledge("stdio rpath") != 0) 
    {
    write(STDERR , "pledge\n" , 7);
    return 1;
    }


#elif __linux__
    scmp_filter_ctx ctx = seccomp_init(SCMP_ACT_KILL);
    if
    (seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(read), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(write), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(open), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(openat), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(access), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(close), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit_group), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(mmap), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(getpid), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(lseek), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(writev), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(fstat), 0))
    {
        write(STDERR , "seccomp error\n" , 13);
        return 1;
    }

    if (seccomp_load(ctx) < 0) 
    {
    write(STDERR , "seccomp load failed\n", 21);
    return 1;
    }

#endif


    char * path = argv[1];
    if (argc < 2) {write(STDERR , "ERROR Enter path like as cat /etc/hostname\n" , 43); return 1;}


    // check for file existence
    if (access(path, F_OK) != 0) 
    {
        write(STDERR , "cat: No such file or directory\n" , 31);
        return 1;
    }

    //check for file access
    int fd = open(path , O_RDONLY);
    if (fd == -1)
    {
        write(STDERR , "cat: Permission denied\n" , 23);
        return 1;
    }



    struct stat st;

    fstat(fd , &st);


    size_t bufferSize = st.st_blksize;
    if (bufferSize < 1)
        bufferSize = DEFAULT_BUFFER_SIZE;
 

    char * buffer[bufferSize];
    


    ssize_t bytesRead;
    while ((bytesRead = read(fd, buffer, bufferSize)) > 0) {
        write(STDOUT, buffer, bytesRead);
    }





#ifdef __linux__
    seccomp_release(ctx);
#endif


    close(fd);

    return 0;
}
