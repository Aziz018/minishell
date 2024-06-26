/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:43:39 by aelkheta          #+#    #+#             */
/*   Updated: 2024/06/29 20:06:07 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

# include "./colors.h"
# include "./libft/libft.h" 			// libft functions
# include <fcntl.h>						// for open sytem call and others system calls
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

typedef enum s_types
{
	CMD,
	RED_OUT,
	RED_IN,
	PIPE,
	LIST,
	BACK,
	ARG,
	OR_OP,
	AND_OP,
	FLE,
	APP,
	HER_DOC
} t_types;

# define TOKEN			0 //CMD 			0
	
# define EXEC 			1
# define RED_OUT 		2
# define RED_IN 		3
# define PIPE 			4
# define LIST 			5
# define BACK 			6
# define ARG 			7
# define OR_OP 			8
# define AND_OP 		9
# define FLE			10
# define APP			11
# define HER_DOC		12

typedef struct s_env
{
	char 				*value;
	struct s_env 		*next;
} t_env;

typedef struct s_command
{
	int					type;
	// char				*file;
	char				*value;
	char 				**args;
	struct s_command	*next;
}				t_command;

typedef struct s_data
{
	int 				i;
	int 				j;
	int					ac;
	t_env				*env;
	char				**av;
	char				*prompt;
	char 				*new_command;
	char  				*special_chars;
	char				**envirenment;
	bool				syntax_error; 			// boolean variable for syntax_error
}				t_data;

typedef struct s_token 
{
	int 				i;						// just a normal index for reading the input character by character
	int					prev_type;				// this variable for tracking the type of the previous node 
	int					index;					// to point to the location of the next token
	int 				type;					// for the type of the token PIPE REDER ...
	char 				*value;					// token value if it's a pipe the value is "|"
} t_token;

extern t_data *data;					// for use this global var from all files


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
// int				built_in_cmd(char **parsedcmd);


// general purpose utiles

char 			*skip_white_spaces(char *command);
char 			*skip_command(char *command);


// utiles for linked list: 

void			add_back_list(t_command **lst, t_command *new);
t_command		*new_node(int type, char *value);
void			clear_list(t_command **lst);

// parsing and toknizing functions

int				parse_command(char *command);
t_command 		*tokenize_command(char *commads);
char 			*get_token_value(t_token *token, char *commads);
// int 			get_token_type(t_token *token);
void			parentheses(char *command);
int 			check_syntax(char *command);


// parsing utiles

int 			ft_strisalnum(char *str);

int				exec_command(t_command *commands_list);
char	*ft_strnstr_l(const char *big, const char *little, size_t len);
char *get_env_element(char *env_var);
#endif
