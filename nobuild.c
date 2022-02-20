#define NOBUILD_IMPLEMENTATION
#include "./nobuild.h"

#define UNIX_CFLAGS "-Wall", "-Wextra", "-pedantic", "-std=c11", "-I/usr/include", "-ggdb", "-O2"
#define UNIX_LDFLAGS "-L/usr/lib", "-lcurl"


int main(int argc, char **argv)
{
    GO_REBUILD_URSELF(argc, argv);
    #ifdef _UNIX
    CMD("cc", "-c", UNIX_CFLAGS, "coolget.c");
    CMD("cc", "-o", "coolget", LDFLAGS);
    #elif _WIN32
    // CMD("cl.exe", "/c");
    #endif
}
