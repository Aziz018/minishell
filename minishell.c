/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:42:13 by aelkheta          #+#    #+#             */
/*   Updated: 2024/05/15 11:05:50 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt(void)
{
	char	*prompt;
	char	*output_color;
	char	*reset_color;

	prompt = "┌──(aziz㉿hostname)-[~/Desktop/minishell]\n└─$ ";
	output_color = N_GREEN_COLOR;
	reset_color = RESET_COLOR;
	write(1, output_color, ft_strlen(output_color));
	write(1, prompt, ft_strlen(prompt));
	write(1, reset_color, ft_strlen(reset_color));
}

int	check_command(char *command, char **av, char **env)
{
	pid_t	pid;
	char	*cmd_path;

	cmd_path = ft_strjoin("/bin/", command);
	if (access(cmd_path, X_OK) == 0)
	{
		pid = fork();
		if (pid == -1)
			return (0);
		else if (pid == 0)
			execve(cmd_path, av, env);
		else
			wait(NULL);
	}
	else
		printf("%s: command not found\n", command);
	free(cmd_path);
	return (0);
}

void	print_minishell(void)
{
	printf("\n");
	printf("███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗\n");
	printf("████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║\n");
	printf("██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║\n");
	printf("██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║\n");
	printf("██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███");
	printf("████╗\n");
	printf("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══");
	printf("════╝\n");
	printf("\n");
}

void sig_handler(int signal)
{
	char *prompt;

	prompt = "\n┌──(aziz㉿hostname)-[~/Desktop/minishell]\n└─$ ";
    if (signal == SIGQUIT)
        return;
    if (signal == SIGINT)
        printf("\n%s", prompt);
}

int	main(int ac, char **av, char **env)
{
	char	*prompt;
	char	*command;

	(void)ac;
	prompt = "┌──(aziz㉿hostname)-[~/Desktop/minishell]\n└─$ ";
	print_minishell();
	signal(SIGQUIT, sig_handler);
	signal(SIGINT, sig_handler);
	while (1)
	{
		command = readline(prompt);
		if (command == NULL)
			break;
		if (ft_strnstr("exit", command, ft_strlen(command)))
			exit(0);
		check_command(command, av, env);
		free(command);
	}
	return (0);
}
