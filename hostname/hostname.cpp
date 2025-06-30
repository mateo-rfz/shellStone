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

#include "../lib/stoneParser.hpp"


//program Info
#define PROGRAM_NAME "hostname"
#define AUTHOR "mateo-rfz"
#define VERSION "v 0.1.0"


#define NAME_LENGTH 256



// minimalFlags: flags used during argument parsing
// [0] = help requested (--help / -h)
// [1] = version requested (--version / -v)
// [2] = invalid parameter detected
int minimalFlags[3] = {0, 0, 0};
std::string parameter;




void 
usage ()
{
    std::cout << PROGRAM_NAME << " " << VERSION << " by " << AUTHOR << "\n";
    std::cout << "Usage:\n";
    std::cout << "  " << PROGRAM_NAME << "            # Show current hostname\n";
    std::cout << "  " << PROGRAM_NAME << " <name>     # Set hostname (requires root)\n";
    std::cout << "  " << PROGRAM_NAME << " --help     # Show this help message\n";
    std::cout << "  " << PROGRAM_NAME << " --version  # Show program version\n";
}



bool 
superUserChecker ()
{
    // Returns true if the program is running with root privileges (UID 0).
    return getuid() == 0;
}



int
main(int argc , char * argv[])
{
    minimalChecker(argc , argv);
    if (minimalFlags[2] == 1)
    {
        std::cerr << "Error: Invalid parameter passed.\n";
        return 1;
    }

    if (minimalFlags[0] == 1)
    {
        usage();
        return 0;
    }
    else if (minimalFlags[1] == 1)
    {
       std::cout << "hostname " << VERSION << std::endl;
       return 0;
    }
        



    if (!parameter.empty())
    {
        if (superUserChecker())
        {
            if (sethostname(parameter.c_str() , parameter.length()) != 0)
            {   
                std::cerr << "sethostname failed";
                return 1;
            }
        }
        else
        {
            std::cout << "Need to be super user for change hostname" << std::endl;
            return 1;
        }
    }
    else 
    {
        char name[NAME_LENGTH];
        gethostname(name , NAME_LENGTH);
        std::cout << name << std::endl;
    }

    return 0;
}