/*
PROGRAM NAME : echo v 0.1.0
AUTHOR : mateo-rfz
LICENSE : GPL-3


FLOW : Prints the arguments to standard output.
*/
#include <iostream>
#include <string>

#define PROGRAM_NAME "echo"
#define VERSION "v 0.0.1"
#define AUTHOR "mateo-rfz"

void
usage()
{
    std::cout << "Usage: " << PROGRAM_NAME << " [-n] [STRING...]\n";
    std::cout << "  -n         do not output the trailing newline\n";
    std::cout << "  -h, --help     display this help and exit\n";
    std::cout << "  -v, --version  output version information and exit\n";
}

int 
main(int argc, char* argv[])
{
    bool nflag = false;

    argc--; // skip program name
    argv++;

    // Handle options
    while (argc > 0 && *argv != nullptr)
    {
        std::string arg = *argv;

        if (arg == "--help" || arg == "-h")
        {
            usage();
            return 0;
        }
        else if (arg == "--version" || arg == "-v")
        {
            std::cout << PROGRAM_NAME << " " << VERSION << " by " << AUTHOR << "\n";
            return 0;
        }
        else if (arg == "-n")
        {
            nflag = true;
            argv++; argc--;
        }
        else
        {
            break; 
        }
    }



    std::string buffer = "";

    while (argc > 0 && *argv != nullptr)
    {
        buffer = buffer + *argv;
        argv++; argc--;
        if (argc > 0)
            buffer = buffer + " ";
    }

    std::cout << buffer;
    if (!nflag)
        std::cout << std::endl;

    return 0;
}
