/*
PROGRAM NAME : hostname v 0.1.0
AUTHOR : mateo-rfz
LICENSE : GPL-3


FLOW : show hostname and change hsotname(only for root)
*/




#include <iostream>
#include <unistd.h>
#include <pwd.h>
#include <string>


//program Info
#define PROGRAM_NAME "hostname"
#define AUTHOR "mateo-rfz"
#define VERSION "v 0.1.0"


#define NAME_LENGTH 256


void 
usage ()
{
    //help mesg
    puts("im here");
}



bool superUserChecker ()
{
    //check if user uid == 0 run as root user and return true
    return getuid() == 0;
}



int
main(int argc , char * argv[])
{
    //parse with shellstone parser
        

    if (argc > 1)
    {
        if (superUserChecker())
        {
            std::string name = argv[1];
            
            if (sethostname(name.c_str() , name.length()) != 0)
            {   
                puts("Error : error in change hostname");
            }
        }
        else
        {
            puts("Need to be super user for change hostname");
        }
    }
    else 
    {
        char name[NAME_LENGTH];
        gethostname(name , NAME_LENGTH);
        puts(name);
    }

    return 0;
}