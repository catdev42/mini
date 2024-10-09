#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

void print_error(const char *path, const char *message, const char *extra) {
    if (extra) {
        fprintf(stderr, "Error: %s: %s (%s)\n", path, message, extra);
    } else {
        fprintf(stderr, "Error: %s: %s\n", path, message);
    }
}

/* Checks if a path is a file or directory File: 1; Dir: 2; Neither: 0 */
int file_dir_noexist(const char *path, int fd_in_or_out) {
    struct stat path_stat;

    if (stat(path, &path_stat) != 0) {
        if (errno == ENOENT && fd_in_or_out == 1) {

            return (1);
        }
        /* this should be checked only with infiles */
        print_error(path, strerror(errno), NULL);
        return (0);
    }

    if (S_ISREG(path_stat.st_mode)) {
        return (1);
    } else if (S_ISDIR(path_stat.st_mode)) {
        return (2);
    } else {
        print_error(path, "Is neither a file nor a directory", NULL);
    }

    return (0);
}

int main() {
    const char *path = "test.txt"; // Change this to test different paths
    int result = file_dir_noexist(path, 0);
    printf("Result: %d\n", result); // Should print 1 if test.txt is a file
    return 0;
}