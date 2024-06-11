# include <stdio.h>
# include <time.h>
# include <stdlib.h>
# include "prompt.h"

void welcome() {
    const char* dian_str = DIAN_SHELL;
    srand(time(NULL));
    for (int i = 0; dian_str[i] != '\0'; i++) {
        int color = 31 + rand() % 7;
        printf("\033[%dm%c\033[0m", color, dian_str[i]);
    }
    printf(WELCOME);
}

void print_prompt() {
    // TODO: display present working directory here.
    printf(PROMPT_ARROW);
}