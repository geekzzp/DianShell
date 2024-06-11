# include <stdio.h>
# include <stdlib.h>


int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "[ERROR] expected only one parameter, but got %d\n", argc-1);
        exit(-1);
    }

    // ensure it is a integer.
    for (int i = 0; argv[1][i] != '\0'; ++i) {
        if (argv[1][i] < '0' || argv[1][i] > '9') {
            if (argv[1][i] != '-') {
                fprintf(stderr, "[ERROR] expected integer parameter, but got %s\n", argv[1]);
                exit(-1);
            }
        }
    }

    int exit_code = atoi(argv[1]);
    printf("hello world!\n");
    exit(exit_code);
}