#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>







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

#if defined (__linux__)
    // set seccomp
#elif defined (__OpenBSD__)
    // set pledge ()
#endif



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


    if (Flag)
    {
        char * buffer = getcwd_logical(buffer);
        printf("%s\n" , buffer);
    }
    else 
    {
        char * path = getcwd(NULL , 0);
        printf("%s\n" , path);
    }
    
    return 0;
}






/*
 * getcwd () -> get currenct directory 
 *
 * RETURNS : 
 *      return char pointer of pwd 
 *      return NULL on error
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
    printf("%s" , "help mesg\n");
    exit(1);
}



static void 
version ()
{
    printf("%s %s\n" , "shell-stone-pwd version" , __VERSION);
    exit(1);
}
