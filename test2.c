/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:38:00 by aelkheta          #+#    #+#             */
/*   Updated: 2024/05/13 18:51:10 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

char	*get_current_dir(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i] != NULL)
	{
		if (strncmp(envp[i], "PWD=", 4) == 0)
			return (envp[i] + 4);
	}
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	char	*command;
	char	*input;
	char	*current_dir;
	pid_t	pid;

	prompt = NULL;
	command = NULL;
	input = NULL;
	current_dir = get_current_dir(envp);
	if (current_dir != NULL)
	{
		prompt = malloc(strlen(current_dir) + strlen("> ") + 1);
		if (prompt == NULL)
		{
			perror("malloc error");
			return (1);
		}
		sprintf(prompt, "%s> ", current_dir);
	}
	else
	{
		prompt = strdup("> ");
		if (prompt == NULL)
		{
			perror("strdup error");
			return (1);
		}
	}
	while ((input = readline(prompt)) != NULL)
	{
		command = malloc(strlen(input) + strlen("/bin/") + 1);
		if (command == NULL)
		{
			perror("malloc error");
			return (1);
		}
		sprintf(command, "/bin/%s", input);
		if (access(command, X_OK) == 0)
		{
			pid = fork();
			if (pid < 0)
			{
				perror("fork error");
				return (1);
			}
			if (pid == 0)
			{
				execl(command, input, NULL);
				perror("exec error");
				return (1);
			}
			else
			{
				wait(NULL);
			}
		}
		else
		{
			printf("minishell: command not found: %s\n", input);
		}
		add_history(input);
		free(input);
		free(command);
	}
	free(prompt);
	return (0);
}
