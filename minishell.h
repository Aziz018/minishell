/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:43:39 by aelkheta          #+#    #+#             */
/*   Updated: 2024/05/25 13:58:39 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define CMD 		0

# define EXEC 		1
# define RED_OUT 	2
# define RED_IN 	3
# define PIPE 		4
# define LIST 		5
# define BACK 		6
# define ARG 		7
# define OR_OP 		8
# define AND_OP 	9

# define MAX_ARGS 	15

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
	int 		i;
	int 		j;
	int			ac;
	char		**av;
	char		**env;
	char		*prompt;
	char 		*new_command;
	
}				t_data;

typedef struct s_token 
{
	int			index;		// to point to the location of the next token
	int 		type;		// for the type of the token PIPE REDER ...
	char 		*value;		// token value if it's a pipe the value is "|"
	int 		i;
} t_token;

extern t_data *data;					// for use this global var from all files

#include "colors.h" 					// for colors
# include "libft/libft.h" 				// libft functions

# include <errno.h> 					// for errors specification
# include <stdio.h> 					// for printf
# include <stdlib.h> 					// for malloc and free
# include <signal.h> 					// for kill and signal handling
# include <unistd.h> 					// for system calls
# include <dirent.h> 					// for directory handling
# include <stdbool.h> 					// for boolean vars
# include <sys/types.h> 				// 
# include <sys/wait.h> 					// for wating child process to terminate execution
# include <readline/history.h> 			// readline GNU library
# include <readline/readline.h> 		// readline GNU library

// # include <termios.h>
// # include <sys/stat.h>

void			print_prompt(void);
void			free_array(char **array);
int				cd(char *path);
char			*get_prompt(void);
void			pwd(void);
int				env(char **env);
int				echo(char **cmd);
int				export(char **cmd);

#endif
