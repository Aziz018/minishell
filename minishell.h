/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:43:39 by aelkheta          #+#    #+#             */
/*   Updated: 2024/05/22 19:04:27 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define EXEC 1
# define RDRC 2
# define PIPE 3
# define LIST 4
# define BACK 5

# define MAX_ARGS 15

typedef struct s_command
{
	int			type;
}				t_command;

typedef struct s_exec
{
	int			type;
	char		*argv[MAX_ARGS];
	char		*eargv[MAX_ARGS];
}				t_exec;

typedef struct s_redirec
{
	int			type;
	t_command	*cmd;
	char		*file;
	char		*efile;
	int			mode;
	int			fd;
}				t_redirec;

typedef struct s_pipe
{
	int			type;
	t_command	*left;
	t_command	*right;

}				t_pipe;

typedef struct s_listcmd
{
	int			type;
	t_command	*left;
	t_command	*right;

}				t_listcmd;

typedef struct s_data
{
	int			ac;
	char		**av;
	char		**env;
	char		*prompt;
}				t_data;

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

# define B_RED_COLOR "\033[1;31m" // ANSI color
# define N_RED_COLOR "\033[0;31m" // ANSI color
# define B_GREEN_COLOR "\033[1;32m" // ANSI color
# define N_GREEN_COLOR "\033[0;32m" // ANSI color
# define RESET_COLOR "\033[0m" // ANSI color

void			print_prompt(void);
void			free_array(char **array);
int				cd(char *path, t_data *data);
char			*get_prompt(void);
void			pwd(void);
int				env(char **env);
int				echo(char **cmd);
int				export(t_data *data, char **cmd);

#endif
