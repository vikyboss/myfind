// A mini implementation of find command that lists all files and directories
// Resources:
// * http://stackoverflow.com/questions/3284552/how-to-remove-a-non-empty-directory-in-c
// * Man pages
// Thu Apr  6 20:28:04 EDT 2017: Initial
// Thu Apr  6 21:18:15 EDT 2017: Added ignore_path_names support
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/stat.h>
#include <limits.h>

int find_recurs_print(const char *dname, const char **ignore_pnames)
{
    char pname[PATH_MAX];

    DIR *dirp = opendir(dname);
    if (!dirp) {
        perror("opendir");
        return 1;
    }

    printf("%s\n", dname);

    struct dirent *dp;
    while ((dp = readdir(dirp)) != NULL) {
        if (!strcmp(dp->d_name, ".."))
            continue;
        if (!strcmp(dp->d_name, "."))
            continue;

        sprintf(pname, "%s/%s", dname, dp->d_name);

        bool ignore = false;
        for (int i = 0; ignore_pnames[i] != NULL; ++i) {
            if (!strcmp(pname, ignore_pnames[i])) {
                ignore = true; 
                printf("!!! ignoring %s !!!\n", ignore_pnames[i]);
                break;
            }
        }
#if 0
        // using pointers
        char **igds = ignore_pnames;
        char *i;
        while ((i = *igds++) != NULL) {
            if (!strcmp(pname, i)) {
                ignore = true; 
                printf("ignoring %s\n", i);
                break;
            }
        }
#endif
        if (ignore)
            continue;

        struct stat st;
        if (stat(pname, &st) == -1) {
            perror("stat");
            return 1;
        }
        if (S_ISDIR(st.st_mode)) {
            find_recurs_print(pname, ignore_pnames);
        }
        else {
            printf("%s\n", pname);
        }
    }

    if (closedir(dirp) == -1) {
        perror("closedir");
        return 1;
    }

    return 0;
}

int main(int argc, char **argv)
{
    if (argc < 1+1) {
        fprintf(stderr, "Try '%s --help' for more information.\n", argv[0]);
        return 1;
    }

    if (!strcmp(argv[1], "--help")) {
        printf( "Usage: %s <dir_name> [ignore_path_names...]\n"
                "options:\n"
                "  dir_name: directory to list files and directory names from\n"
                "  ignore_path_names: optional space separated list of sub paths of dir_name,\n"
                "                     if the dir_name itself is provided as an option, that option is silently ignored\n"
                , argv[0]);
        return 0;
    }

    char **ignore_pnames = malloc(sizeof(char *) * (argc-2+1)); // +1 for NULL sentinel
    if (!ignore_pnames) {
        perror("malloc");
        return 1;
    }

    for (int i = 2; i < argc; ++i)
        ignore_pnames[i-2] = argv[i];
    ignore_pnames[argc-2] = NULL; // set sentinel

    find_recurs_print(argv[1], (const char **)ignore_pnames);

    free(ignore_pnames);

    return 0;
}
