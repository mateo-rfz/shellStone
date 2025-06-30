#include <string>







extern int minimalFlags[3];
// minimalFlags: flags used during argument parsing
// [0] = help requested (--help / -h)
// [1] = version requested (--version / -v)
// [2] = invalid parameter detected


extern std::string parameter;



void
minimalChecker (int argc , char * argv[])
{
    int flag = 0;
    for (int i = 1 ; i < argc ; i++)
    {
        std::string arg = argv[i];

        if (arg[0] != '-' && flag == 0)
        {
            parameter = argv[i];
            flag = 1;
        }
        else if (arg == "--help" || arg == "-h")
        {
            minimalFlags[0] = 1;
        } 
        else if (arg == "--version" || arg == "-v")
        {
            minimalFlags[1] = 1;
        } 
        else
        {
            minimalFlags[2] = 1;
            break;
        }
    }
}


