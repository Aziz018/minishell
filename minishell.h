/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:43:39 by aelkheta          #+#    #+#             */
/*   Updated: 2024/05/15 10:56:13 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

# define B_RED_COLOR "\033[1;31m"
# define N_RED_COLOR "\033[0;31m"
# define B_GREEN_COLOR "\033[1;32m"
# define N_GREEN_COLOR "\033[0;32m"
# define RESET_COLOR "\033[0m"

void	print_prompt(void);

#endif
