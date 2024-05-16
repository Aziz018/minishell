#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char *input;

    rl_initialize();

    input = readline("Enter your input: ");

    rl_replace_line("New text", 1);

    rl_redisplay();

    free(input);

    return 0;
}
