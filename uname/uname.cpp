/*
PROGRAM NAME : uname v 0.1.0
AUTHOR : mateo-rfz
LICENSE : GPL-3


FLOW : print the standart output of sys/utsname.
*/
#include <iostream>
#include <sys/utsname.h>


#ifdef __OPENBSD__
#include <unistd.h>
#endif



#ifdef __linux__
#include <seccomp.h>
#endif



#define PROGRAM_NAME "uname"
#define VERSION "v 0.1.0"
#define AUTHOR "mateo-rfz"



//======> FLAGS
int sysName = 0;
int nodeName = 0;
int machine = 0; //system architecture
int release = 0;
int version = 0;







void 
usage() {
    std::cout << "Usage: [options]\n";
    std::cout << "-s: Show system name\n";
    std::cout << "-n: Show node name\n";
    std::cout << "-m: Show machine architecture\n";
    std::cout << "-r: Show release\n";
    std::cout << "-v: Show version\n";
    std::cout << "-a: Show all options\n";
    std::cout << "--help: Show this help message\n";
    std::cout << "--version: Show version\n";
    exit(0);
}






void 
argParser(int argc , char * argv[])
{
    if (argc > 1)
    {
    argv++;argc--; // skip program name
    }
    else 
    {
        sysName = 1;
        return;
    }

    while (argc != 0)
    {
        std::string parameter = std::string(*argv);
        if (parameter == "-s")
            sysName = 1;
        else if (parameter == "-n")
            nodeName = 1;
        else if (parameter == "-m")
            machine = 1;
        else if (parameter == "-r")
            release = 1;
        else if (parameter == "-v")
            version = 1;
        else if (parameter == "-a")
        {
            sysName = 1;
            nodeName = 1;
            machine = 1;
            release = 1;
            version = 1;
        }

        else if (parameter == "--help")
        {
            usage();
            exit(0);
        }
        else if (parameter == "--version")
        {
            std::cout << __VERSION__ << std::endl;
            exit(1);
        }

        else
        {
            std::cerr << "Invalid parameter: " << parameter << std::endl;
            exit(1);
        }


        argv++;argc--;

    }
}








int 
main(int argc , char * argv[])
{
#ifdef __OPENBSD__
    if (pledge("stdio" , NULL) != 0)
    {
        perror("pledge");
        return 1;
    }
#elif defined (__linux__)
    scmp_filter_ctx ctx = seccomp_init(SCMP_ACT_KILL);
    if (seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(uname), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(write), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(read), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(close), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(fstat), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(mmap), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(munmap), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(brk), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(arch_prctl), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(rt_sigaction), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(rt_sigprocmask), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(rt_sigreturn), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(set_tid_address), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(set_robust_list), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(prlimit64), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit), 0) ||
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit_group), 0)
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

    argParser(argc , argv);



    utsname u;
    if (uname(&u) == -1)
    {
        std::cerr << "ERROR IN `uname()`";
        return 1;
    }


    std::string buffer;
    if (sysName)
    {
        buffer += u.sysname;
        buffer += " ";
    }
    if (nodeName)
    {
        buffer += u.nodename;
        buffer += " ";
    }
    if (machine){
        buffer += u.machine;
        buffer += " ";
    }
    if (release){
        buffer += u.release;
        buffer += " ";
    }
    if (version){
        buffer += u.version;
        buffer += " ";
    }


    
    std::cout << buffer << std::endl;


    return 0;
}
