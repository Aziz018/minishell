/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:43:14 by aelkheta          #+#    #+#             */
/*   Updated: 2024/05/18 09:43:15 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
