/*
PROGRAM NAME : echo v 0.1.1
AUTHOR : mateo-rfz
LICENSE : GPL-3


FLOW : Prints the arguments to standard output.
*/
#include <iostream>
#include <string>


#ifdef __linux__
#include <seccomp.h>
#endif

#ifdef __OPENBSD__
#include <unistd.h>
#endif


#define PROGRAM_NAME "echo"
#define VERSION "v 0.1.1"
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
#ifdef __OPENBSD__
    if (pledge("stdio" , NULL) != 0)
    {
        perr("pledge");
        return 1;
    }
#elif defined (__linux__)
    scmp_filter_ctx ctx = seccomp_init(SCMP_ACT_KILL);
    if (seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(read), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(write), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit_group), 0) ||


    //system calls used by iostream , string
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(fstat), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(mmap), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(munmap), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(brk), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(close), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(arch_prctl), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(rt_sigaction), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(rt_sigprocmask), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(rt_sigreturn), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(set_tid_address), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(set_robust_list), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(prlimit64), 0)
    ) {
        perror("seccomp_rule_add");
        seccomp_release(ctx);
        return 1;
    }


    if (seccomp_load(ctx) < 0) {
        perror("seccomp_load");
        seccomp_release(ctx);
        return 1;
    }

    seccomp_release(ctx);

#endif




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