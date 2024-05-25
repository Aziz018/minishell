/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:42:13 by aelkheta          #+#    #+#             */
/*   Updated: 2024/05/25 14:01:55 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data *data = NULL;

void	print_minishell(void)
{
	printf("\n");
	printf("███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗\n");
	printf("████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║\n");
	printf("██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║\n");
	printf("██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║\n");
	printf("██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███");
	printf("████╗\n");
	printf("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══");
	printf("════╝\n");
	printf("\n");
}
void	print_prompt(void)
{
	char	*prompt;
	char	*output_color;
	char	*reset_color;

	prompt = "┌──(aziz㉿hostname)-[~/Desktop/minishell]\n└─$ ";
	output_color = GRN;
	reset_color = CRESET;
	write(1, output_color, ft_strlen(output_color));
	write(1, prompt, ft_strlen(prompt));
	write(1, reset_color, ft_strlen(reset_color));
}

int	exec_command(char *command)
{
	pid_t	pid;
	char	*cmd_path;
	char **parsedcmd = ft_split(command, ' ');
	if (command == NULL || command[0] == 0)
		return (0);
	cmd_path = ft_strjoin("/bin/", parsedcmd[0]);
	printf("command: %s <||> args: %s\n", parsedcmd[0], parsedcmd[1]);
	if (access(cmd_path, X_OK) == 0)
	{
		pid = fork();
		if (pid == -1)
			return (0);
		else if (pid == 0)
			execve(cmd_path, &parsedcmd[1], data->env);
		else
			wait(NULL);
	}
	else
		printf("%s: command not found\n", command);
	free_array(parsedcmd);
	free(cmd_path);
	return (0);
}

void	sig_handler(int signal)
{
	// char	*prompt;

	// prompt = "\n┌──(aziz㉿hostname)-[~/Desktop/minishell]\n└─$ ";
	if (signal == SIGQUIT)
		return ;
	// if (signal == SIGINT)
	// 	printf("\n%s", prompt);
}

void	print_char_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		printf("%s\n", array[i]);
}

int	built_in_cmd(char **parsedcmd)
{
	if (parsedcmd == NULL || parsedcmd[0] == 0)
		return (0);
	else if (!ft_strncmp("exit", parsedcmd[0], ft_strlen(parsedcmd[0])))
		exit(0);
	else if (!ft_strncmp("echo", parsedcmd[0], ft_strlen(parsedcmd[0])))
		echo(parsedcmd);
	else if (!ft_strncmp("pwd", parsedcmd[0], ft_strlen(parsedcmd[0])))
		pwd();
	else if (!ft_strncmp("cd", parsedcmd[0], ft_strlen(parsedcmd[0])))
		cd(parsedcmd[1]);
	else if (!ft_strncmp("env", parsedcmd[0], ft_strlen(parsedcmd[0])))
		env(data->env);
	else if (!ft_strncmp("export", parsedcmd[0], ft_strlen(parsedcmd[0])))
		export(parsedcmd);
	else
		return (0);
	free_array(parsedcmd);
	return (1);
}

void parentheses(char *command)
{
	data->i = -1;
	data->j = -1;
	while(command[++data->i])
	{
		if (command[data->i] == '(')
			++data->j;
		else
		{
			if (data->j == -1)
			{
				printf("minishell: syntax error near unexpected token `)'\n");
				return ;
			}
			if (command[data->i] == ')')
				--data->j;
		}
		if (data->j < -1)
		{
			printf("minishell: syntax error near unexpected token `)'\n");
			return ;
		}
	}
	if (data->j == -1)
		return ;
	char *line = readline("> ");
	data->new_command = ft_strjoin(command, line);
	free(line);
	free(command);
	parentheses(data->new_command);
}

char *get_token_value(t_token *token, char *commads)
{
	char *token_val = NULL;

	while(commads[token->i] && (commads[token->i] == ' ' || commads[token->i] == '\t' || commads[token->i] == '\v'))
		token->i++;
	token->index = token->i;
	while(commads[token->i] && commads[token->i] != ' ' && commads[token->i] != '\t' && commads[token->i] != '\v')
		token->i++;
	token_val = malloc((token->i - token->index) * sizeof(char) + 1);
	ft_strlcpy(token_val, &commads[token->index], (token->i - token->index + 1));
	while(commads[token->i] && commads[token->i] != ' ' && commads[token->i] != '\t' && commads[token->i] != '\v')
		token->i++;
	// if (commads[token->i] == '\0')
	// 	token->i = 0;
	token->index = token->i;
	return (token_val);
}

int get_token_type(t_token *token)
{
	if (token->value[0] == '|' && token->value[1] == '\0')
	{
		printf("type: ---------- PIPE\n");
		return (PIPE);
	}
	else if (token->value[0] == '>' && token->value[1] == '\0')
	{
		printf("type: ---------- RED_OUT\n");
		return (RED_OUT);
	}
	else if (token->value[0] == '<' && token->value[1] == '\0')
	{
		printf("type: ---------- RED_IN\n");
		return (RED_IN);
	}
	else if (token->value[0] == '&' && token->value[1] == '\0')
	{
		printf("type: ---------- BACK\n");
		return (BACK);
	}
	else if (token->value[0] == '&' && token->value[1] == '&' && token->value[2] == '\0')
	{
		printf("type: ---------- AND_OP\n");
		return (AND_OP);
	}
	else if (token->value[0] == '|' && token->value[1] == '|' && token->value[2] == '\0')
	{
		printf("type: ---------- OR_OP\n");
		return (OR_OP);
	}
	else
	{
		printf("type: ---------- CMD\n");
		return (CMD);
	}
	// else
	// {
	// 	printf("type: ---------- ARG\n");
	// 	return (ARG);
	// }
}

t_token *tokenizer_command(char *commads)
{
	t_token *token = (t_token *)malloc(sizeof(t_token));
	// int i = -1;
	token->i = 0;
	token->index = 0;
	if (commads[token->i] == 0)
		return NULL;
	while(commads[token->i])
	{
		// if (i == 0)
		{
			token->value = get_token_value(token, commads);
			printf("token: --------- %s\n", token->value);
			token->type = get_token_type(token);
			printf("\n");
		}
		if (token != NULL)
		{
			if (token->value != NULL)
				free(token->value);
			// free(tokens);
		}

	}
	return (token);
}

int	parse_command(char *command)
{


	t_token *tokens = tokenizer_command(command);

	// printf("token: --------- %s\n", tokens->value);
	// printf("type: ---------- %d\n", tokens->type);

	if (tokens != NULL)
	{
		// if (tokens->value != NULL)
		// 	free(tokens->value);
		free(tokens);
	}
	// char	**parsedcmd;

	// int i = -1;
	// int j = -1;
	
	// parsedcmd = ft_split(command, ' ');
	// while(parsedcmd[++i] != NULL)
	// {
	// 	j = 0;
	// 	if (parsedcmd[i][j] == '(' || parsedcmd[i][j] == ')')
	// 	{
	// 		parentheses(command);
	// 		j++;
	// 	}
	// 	// parsedcmd[i][0] == '|' || (parsedcmd[i][0] == '&' && parsedcmd[i][1] == '&') || parsedcmd[i][0] == '&' || parsedcmd[i][0] == '<' || parsedcmd[i][0] == '>'
		
	// 	if (i == 0 || ft_strchr("|&;", parsedcmd[i - 1][0]))
	// 		printf("command: ------ %s\n", parsedcmd[i]);
	// 	else if (ft_strchr("<>", parsedcmd[i - 1][0]))
	// 		printf("file: ------ %s\n", parsedcmd[i]);
	// 	else if (ft_strchr("<|&>", parsedcmd[i][0]))
	// 	{
	// 		if (parsedcmd[i][0] == '|')
	// 			printf("pipe: --------- %s\n", parsedcmd[i]);
	// 		else if (parsedcmd[i][0] == '&' && parsedcmd[i][1] == '&')
	// 			printf("and oprt: ----- %s\n", parsedcmd[i]);
	// 		else if (parsedcmd[i][0] == '<')
	// 			printf("red-in: ------- %s\n", parsedcmd[i]);
	// 		else if (parsedcmd[i][0] == '>')
	// 			printf("red-out: ------ %s\n", parsedcmd[i]);
	// 	}
	// 	else
	// 		printf("arg: ---------- %s\n", parsedcmd[i]);
	// }
	// free_array(parsedcmd);

	

			// cd ->-> && cat file | grep hello

	// printf("%s\n", command);
	// print_char_array(parsedcmd);

	// parsedcmd = ft_split(command, ' ');

	// if (built_in_cmd(parsedcmd, data))
	// 	return (0);
	// free_array(parsedcmd);
	// exec_command(command, data);
	return (0);
}

char	*get_prompt(void)
{
	
	char	*prompt1;
	char	*prompt2;
	char	*prompt3;
	char	*final_prompt;
	prompt1 = BBLU"┌──(aziz㉿aelkheta)-["COLOR_RESET;
	prompt2 = getcwd(NULL, 0);
	prompt3 = ft_strjoin(BWHT, prompt2);
	free(prompt2);
	prompt1 = ft_strjoin(prompt1, prompt3);
	free(prompt3);
	final_prompt = ft_strjoin(prompt1, BBLU"]\n└─$ "COLOR_RESET);
	free(prompt1);
	return (final_prompt);
}

void	init_minishell(int ac, char **av, char **env)
{
	data->ac = ac;
	data->env = env;
	data->av = av;
	data->prompt = get_prompt();
	data->new_command = NULL;
	
	//"┌──(aziz㉿aelkheta)-[/nfs/homes/aelkheta/Desktop/minishell]\n└─$ ";
}

int	main(int ac, char **av, char **env)
{
	char	*command;

	data = (t_data *)malloc(sizeof(t_data));
	init_minishell(ac, av, env);
	
	// prompt = "┌──(aziz㉿aelkheta)-[~/Desktop/minishell]\n└─$ ";
	// prompt = get_prompt();
	
	print_minishell();
	
	signal(SIGQUIT, sig_handler);
	// signal(SIGINT, sig_handler);
	command = readline(data->prompt);
	while (command != NULL)
	{
		parse_command(command);
		
		// free(command);
		command = readline(data->prompt);
	}
	free(data->new_command);
	free(data->prompt);
	return (0);
}
