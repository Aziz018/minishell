#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

void sig_handler(int signal)
{
    if (signal == SIGQUIT)
        return;
    if (signal == SIGINT)
        return;
}

int main(int ac, char **av, char **env)
{
    char *prompt;
    char *command;

    (void)ac;
    prompt = "┌──(aziz㉿hostname)-[~/Desktop/minishell]\n└─$ ";
    signal(SIGQUIT, sig_handler);
    signal(SIGINT, sig_handler);
    while (1)
    {
        command = readline(prompt);
        if (!command)
        {
            printf("\n");
            continue;
        }
        if (strcmp(command, "exit") == 0)
        {
            free(command);
            break;
        }
        free(command);
    }
    return 0;
}
