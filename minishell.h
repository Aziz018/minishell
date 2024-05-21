/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:43:39 by aelkheta          #+#    #+#             */
/*   Updated: 2024/05/20 12:49:18 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define B_RED_COLOR "\033[1;31m" // ANSI color
# define N_RED_COLOR "\033[0;31m" // ANSI color
# define B_GREEN_COLOR "\033[1;32m" // ANSI color
# define N_GREEN_COLOR "\033[0;32m" // ANSI color
# define RESET_COLOR "\033[0m" // ANSI color
# define YELLOW "\e[1;93m"
# define BLUE "\e[1;94m"

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_data
{
	int 	ac;
	char	**av;
	char	**env;
	char	*prompt;
}			t_data;

# include <dirent.h> // for directory handling
# include <errno.h> // for errors specification
# include <signal.h> // for kill and signal handling
# include <stdbool.h> // for boolean vars
# include <stdio.h> // for printf
# include <stdlib.h> // for malloc and free
# include <sys/types.h> //
# include <unistd.h> // for system calls

// # include <termios.h>
// # include <sys/stat.h>

# include "libft/libft.h" // libft functions
# include <readline/history.h> // readline GNU library
# include <readline/readline.h> // readline GNU library
# include <sys/wait.h>
// for wating child process to terminate execution

void		print_prompt(void);
void		free_array(char **array);
int			cd(char *path, t_data *data);
char		*get_prompt(void);
void		pwd();
int			env(char **env);
int			echo(char **cmd);
int			export(t_data *data, char **cmd);


#endif
