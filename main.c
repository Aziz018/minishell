#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char *input;

    // Read a line of input
    input = readline("Enter your input: ");

    // If the input is not empty
    if (input) {
        // Display the input
        printf("You entered: %s\n", input);

        // Add the input to history
        add_history(input);

        // Free the memory allocated by readline
        free(input);
    }

    // Clear the entire history list
    rl_clear_history();

    return 0;
}

