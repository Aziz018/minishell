#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	*input;

	rl_initialize();
	input = readline("Enter your input: ");
	rl_replace_line("New text", 1);
	rl_redisplay();
	free(input);
	return (0);
}
