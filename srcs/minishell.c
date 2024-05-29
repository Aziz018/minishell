/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:42:13 by aelkheta          #+#    #+#             */
/*   Updated: 2024/05/29 10:56:49 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

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
			execve(cmd_path, &parsedcmd[1], NULL);
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
	char	*prompt;

	prompt = get_prompt();
	if (signal == SIGQUIT)
		return ;
	if (signal == SIGINT)
		printf("\n%s", prompt);
	free(prompt);
}

void	print_char_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		printf("%s\n", array[i]);
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

t_command *tokenizer_command(char *commads)
{
	t_token token;
	t_command *head = NULL;
	token.i = 0;
	token.index = 0;
	if (commads[token.i] == 0)
		return NULL;
	while(commads[token.i])
	{
		{
			// printf("\ncommads[%d]: %d\n", token.i, commads[token.i]);
			
			token.value = get_token_value(&token, commads);
			token.type = get_token_type(&token);
			
			add_back_list(&head, new_node(token.type, token.value));
			
			while(commads[token.i] == ' ')
				token.i++;
			
			// free(token.value);
			
			// token.type = get_token_type(&token);
			// new_node(token->type, token->value);
			// printf("token: --------- %s\n", token.value);
			// printf("type: ---------- %d\n", token.type);
			// token->type = get_token_type(token);
			// printf("\n");
		}
		// if (token != NULL)
		// {
			// if (token.value != NULL)
			// 	free(token.value);
			// free(token);
		// }
	}
	return (head);
}

int	parse_command(char *command)
{

	while(*command && (*command == ' ' || *command == '\t' || *command == '\v'))
		command++;
	// printf("commnd: %s\n", command);
	t_command *tokens = tokenizer_command(command);
	while(tokens != NULL)
	{
		printf("token: ---------- %s\n", tokens->value);
		if (tokens->type == 0)
			printf("type: ----------- CMD\n\n");
		if (tokens->type == 2)
			printf("type: ----------- RED_OUT\n\n");
		if (tokens->type == 3)
			printf("type: ----------- RED_IN\n\n");
		if (tokens->type == 4)
			printf("type: ----------- PIPE\n\n");
		if (tokens->type == 5)
			printf("type: ----------- LIST\n\n");
		if (tokens->type == 6)
			printf("type: ----------- BACK\n\n");
		if (tokens->type == 7)
			printf("type: ----------- ARG\n\n");
		if (tokens->type == 8)
			printf("type: ----------- OR_OP\n\n");
		if (tokens->type == 9)
			printf("type: ----------- AND_OP\n\n");
		if (tokens->type == 10)
			printf("type: ----------- FLE\n\n");
		if (tokens->type == 11)
			printf("type: ----------- APP\n\n");
		t_command *tmp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = tmp;	
	}
	// t_parse *parser = parser_command();
	// printf("token: --------- %s\n", tokens->value);
	// printf("type: ---------- %d\n", tokens->type);

	if (tokens != NULL)
	{
		// if (tokens->value != NULL)
		// 	free(tokens->value);
		free(tokens);
	}


	
	// this for parsing 

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

			// cd ->-> && cat file | grep hello

	// printf("%s\n", command);
	// print_char_array(parsedcmd);


	// for execute commands

	// char **parsedcmd = ft_split(command, ' ');

	// if (built_in_cmd(parsedcmd))
	// 	return (0);
	// free_array(parsedcmd);
	// exec_command(command);
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

void	add_back(t_env **lst, t_env *new)
{
	t_env	*temp;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

t_env	*lstnew(char *content)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->value = content;
	new_node->next = NULL;
	return (new_node);
}


t_env *creat_env(char **env)
{
	t_env *head = NULL;
	int i = -1;
	while(env[++i] != NULL)
		add_back(&head, lstnew(env[i]));
	return (head);
}

void	init_minishell(int ac, char **av, char **env)
{
	data->ac = ac;
	data->env = creat_env(env);
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
	print_minishell();
	
	signal(SIGQUIT, sig_handler);
	signal(SIGINT, sig_handler);
	
	command = readline(data->prompt);
	while (command != NULL)
	{
		parse_command(command);
		
		// free(command);
		add_history(command);
		command = readline(data->prompt);
	}
	clear_history();
	free(data->new_command);
	free(data->prompt);
	return (0);
}
