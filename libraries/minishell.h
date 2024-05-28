/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:43:39 by aelkheta          #+#    #+#             */
/*   Updated: 2024/05/28 10:40:36 by aelkheta         ###   ########.fr       */
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
# define FLE		10
# define APP		11

# define MAX_ARGS 	15


typedef struct s_env
{
	char 			*value;
	struct s_env 	*next;
} t_env;

typedef struct s_command
{
	int					type;
	char				*file;
	char				*value;
	char 				**args;
	struct s_command	*next;
}				t_command;

typedef struct s_data
{
	int 		i;
	int 		j;
	int			ac;
	char		**av;
	t_env		*env;
	char		*prompt;
	char 		*new_command;
	
}				t_data;

typedef struct s_token 
{
	int 		i;
	int			prev_type;
	int			index;		// to point to the location of the next token
	int 		type;		// for the type of the token PIPE REDER ...
	char 		*value;		// token value if it's a pipe the value is "|"
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

// buit-in commands:

int				cd(char *path);
char			*get_prompt(void);
void			pwd(void);
int				env(t_env *env);
int				echo(char **cmd);
int				export(char *cmd);

// utiles for linked list: 

void			add_back_list(t_command **lst, t_command *new);
void			clear_list(t_command **lst, void (*del)(int));
t_command	*new_node(int type, char *value);

#endif
