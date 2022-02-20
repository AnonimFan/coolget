#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

void help(FILE *stream)
{
    fprintf(stream, "coolget help: \n");
    fprintf(stream, "    <url>: can be ftp, sftp, http, https, telnet\n");
    fprintf(stream, "    <file>: shall have the requested files file extension\n");
    exit(1);
}

void interrupt(int num)
{
    signal(SIGINT, interrupt);
    printf("[WARN]: recived signal %d (SIGINT)\n", num);
}

int eputs(const char *str);

// deletes the file that we are trying to download
int fix_fopen_failure(const char *path)
{
    if (path == NULL) {
        eputs("fix_fopen_failure() was unable to fix fopen() failure");
        return 1;
    }
    char *shit = malloc(345345);

    #ifdef _UNIX
    sprintf(shit, "rm -rf %s", path);
    #elif _WIN32
    sprintf(shit, "del %s", path);
    #endif
    system(shit);
    return 0;
}

// puts unsigned intiger to stdout
int eputu(unsigned int num)
{
    printf("%d\n", num);
    return 0;
}

// puts for errors
int eputs(const char *str)
{
    printf("[ERROR]: %s\n", str);
    return 0;
}

// puts for information
int iputs(const char *str)
{
    printf("[INFO]: %s\n", str);
    return 0;
}

// puts for notes
int nputs(const char *str)
{
    printf("[NOTE]: %s\n", str);
    return 0;
}


void get_file(const char *url, const char *path)
{
    CURL *ezhan = curl_easy_init();
    if (ezhan == NULL) {
        eputs("curl easy handle was not initalized");
        nputs("curl_easy_init() failed");
        //iputs("this is reported");
        exit(1);
    }
    curl_easy_setopt(ezhan, CURLOPT_URL, url);

    FILE *file = fopen(path, "w");
    if (file == NULL) {
        eputs("file handle was not initalized");
        iputs("trying to fix error");
        if (fix_fopen_failure(path) != 0) {
            perror("fopen() failed");
            exit(1);
        }
    }
    curl_easy_setopt(ezhan, CURLOPT_WRITEDATA, file);
    curl_easy_perform(ezhan);
    curl_easy_cleanup(ezhan);
    fclose(file);
}



int main(int argc, char *argv[])
{
    signal(SIGINT, interrupt);
    if (argc < 3) {
        fprintf(stderr, "[ERROR]: no url and output file is provided\n");
        fprintf(stderr, "[USAGE]: %s <url> <output file>\n", argv[0]);
        return 1;
    }

    if (argc == 2 && !strcmp(argv[1], "--help")) {
        help(stderr);
    }

    if (argc == 2) {
        fprintf(stderr, "[ERROR]: no output file is provided\n");
        fprintf(stderr, "[USAGE]: %s %s <output file>", argv[0], argv[1]);
        return 1;
    }

    if (argc == 3) {
        if (strstr(argv[1], "https://") == NULL && strstr(argv[1], "http://") == NULL
            && strstr(argv[1], "sftp://") == NULL && strstr(argv[1], "ftp://") == NULL
            && strstr(argv[1], "telnet://") == NULL) {
            eputs("specified URL does not contain an internet protocol");
            return 1;
        }
        fprintf(stdout, "[INFO]: downloading file %s from %s\n", argv[2], argv[1]);
        clock_t start, end;
        start = clock();
        get_file(argv[1], argv[2]);
        end = clock() - start;
        double time_took = ((double) (end)) / CLOCKS_PER_SEC;
        fprintf(stdout, "[INFO]: downloaded file %s\n", argv[2]);
        fprintf(stdout, "[PROFILE]: downloading took %f seconds\n", time_took);
    }

    return 0;
}
