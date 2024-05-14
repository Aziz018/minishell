/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:40:28 by aelkheta          #+#    #+#             */
/*   Updated: 2024/05/13 15:58:16 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	char *input;
	char *prompt = "┌──(aziz㉿hostname)-[~/Desktop/minishell]\n└─$ ";

	input = readline(prompt);
	while (input != NULL)
	{
		printf("\nYou entred; %s\n", input);
		add_history(input);
		free(input);
		input = readline(prompt);
	}
	int history_count = history_length;
	printf("Total history entries: %d\n", history_count);

	rl_clear_history();
}