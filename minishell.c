#include "minishell.h"

int main()
{
    char *line = get_next_line(0);
    // if (line == NULL || line[0] == '\0')
    //     return 0;
    printf("%s %d\n", line, line[0]);
    while(line != NULL || line[0] == '\0')
    {
        line = get_next_line(0);
        printf("%s %d\n", line, line[0]);

    }
    return 0;
}