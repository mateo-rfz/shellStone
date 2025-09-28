/*
PROGRAM NAME : pwd v 0.1.0
AUTHOR : mateo-rfz
LICENSE : GPL-3


FLOW : pwd - print working directory
*/
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#if defined (__linux__)
#include <seccomp.h>
#endif





#define __VERSION "v0.1"
#define __AUTHOR "mateo-rfz" 

const char * PROGRAM_NAME;




char * getcwd_logical (char * buffer);
static void usage () ;
static void version ();







static int 
str_comp (char * s1 , char * s2)
{
    while (*s1 != '\0' || *s2 != '\0')
    {
        if (*s1 != *s2)
            return 1;

        s1++;s2++;
    }

    return 0;
}






int 
main (int argc , char * argv[])
{
    PROGRAM_NAME = argv[0];

    /* Flag -> logical flag 
     * default is 1
     */
    int Flag = 1;
    
    argv++; // skip Program-name
    while (*argv != NULL)
    {
        if (str_comp(*argv , "--version") == 0 || str_comp(*argv , "-v") == 0)
            version ();
        
        else if (str_comp(*argv, "--help") == 0 || str_comp(*argv , "-h") == 0)
            usage ();
        
        else if (str_comp(*argv , "-P") == 0)
            Flag = 1;

        else if (str_comp (*argv , "-L") == 0)
            Flag = 0;


        else 
            usage();

        argv++;
    }

#if defined (__linux__)
    if (Flag == 1) {
        scmp_filter_ctx ctx = seccomp_init(SCMP_ACT_KILL);

        seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(read), 0);
        seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(write), 0);
        seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(close), 0);
        seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit), 0);
        seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit_group), 0);
        seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(brk), 0);
        seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(mmap), 0);
        seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(munmap), 0);
        seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(mprotect), 0);
        seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(arch_prctl), 0);
        seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(fstat), 0);
        seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(getrandom), 0);

        if (seccomp_load(ctx) < 0) {
            perror("seccomp_load");
            seccomp_release(ctx);
            return 1;
        }
        seccomp_release(ctx);
    }

#elif defined (__OpenBSD__)
    if (pledge ("stdio rpath" , NULL) == -1)
    {
        perror("%s" , "pledge");
        exit(1);
    }
#endif


    if (Flag == 1)
    {
        char * buffer = getcwd_logical(NULL);
        if (!buffer) {
            fprintf(stderr, "PWD not set\n");
            exit(1);
        }
        printf("%s\n" , buffer);
    } else {
        char * path = getcwd(NULL , 0);
        if (!path) {
            perror("getcwd");
            exit(1);
        }
        printf("%s\n" , path);
        free(path);
    }
    
    return 0;
}






/*
 * getcwd_logical () -> get currenct logical directory 
 *
 * RETURNS : 
 *      return char pointer of pwd 
 *      return NULL on error
 *
 * INPUTS : 
 *      
 */
char * 
getcwd_logical (char * buffer)
{
    buffer = getenv("PWD");
    if (buffer == NULL)
        return NULL;
    if (buffer[0] != '/')
        return NULL;

    return buffer;
}





static void
usage () 
{
    printf("%s - print working directory\n\nProgram-options : \n\t-v , --version\tShow version\n\t-h , --help\tDisplay this help and exit\n\t-L\t\tLogical path\n\t-P\t\tPath\n" , PROGRAM_NAME);
    exit(1);
}



static void 
version ()
{
    printf("%s %s\n" , "shell-stone-pwd version" , __VERSION);
    exit(1);
}

