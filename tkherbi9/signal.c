/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:43:10 by aelkheta          #+#    #+#             */
/*   Updated: 2024/05/18 09:43:11 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	sig_handler(int signal)
{
	if (signal == SIGQUIT)
		return ;
	if (signal == SIGINT)
		return ;
}

int	main(int ac, char **av, char **env)
{
	char	*prompt;
	char	*command;

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
			continue ;
		}
		if (strcmp(command, "exit") == 0)
		{
			free(command);
			break ;
		}
		free(command);
	}
	return (0);
}
