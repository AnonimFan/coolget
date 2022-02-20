#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    const char *url = "https://ftp.gnu.org/gnu/grep";
    const char *prefix = "ftp://";
    if(!strstr(url, prefix)) {
            printf("fukah\n");
    }
    return 0;
}
