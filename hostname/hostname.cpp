#include <iostream>
#include <unistd.h>
#include <pwd.h>
#include <string>
#include <cstring>


#define NAME_LENGTH 256


void 
usage ()
{
    puts("im here");
}



bool superUserChecker ()
{
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
                puts("Have an Error");
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