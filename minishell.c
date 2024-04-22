#include "minishell.h"

void print_prompt()
{
    const char *prompt = "aziz@kali ~/desktop/minishell> ";
    const char *output_color = GREEN_COLOR;
    const char *reset_color = RESET_COLOR;
    write(1, output_color, ft_strlen(output_color));
    write(1, prompt, ft_strlen(prompt));
    write(1, reset_color, ft_strlen(reset_color));
}

int main()
{
    print_prompt();
    char *line = get_next_line(0);
    if (line == NULL || line[0] == '\0')
        return 0;
    while(line != NULL)
    {
        print_prompt();
        line = get_next_line(0);
        if (line == NULL || line[0] == '\0')
            return 0;
    }
    return 0;
}