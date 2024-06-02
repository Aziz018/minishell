/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:40:09 by aelkheta          #+#    #+#             */
/*   Updated: 2024/06/02 12:05:24 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

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

char *skip_white_spaces(char *command)
{
	while(*command && (*command == ' ' || *command == '\t' || *command == '\r' || *command == '\v'))
		command++;
	return (command);
}

char *skip_command(char *command)
{
	while(*command && ft_isalnum(*command))
		command++;
	command = skip_white_spaces(command);
	if (*command == ';')
		command++;
	return (command);
}

int check_syntax(char *command)
{
	// int i = -1;
	// int stack[100];

	while(*command)
	{
		command = skip_white_spaces(command);
		if (!*command)
			break;
		if (*command == ';')
			printf("minishell: syntax error near unexpected token `%c'\n", *command);
		command = skip_command(command);
		if (!*command)
			break;
		
		printf("%s\n", command);
		
		if (*command == ';')
		{
			command = skip_white_spaces(command);
			if (!*command)
				break;
			else if (*command == ';')
				printf("minishell: syntax error near unexpected token `%c'\n", *command);
		}
		command++;
	}
	return (0);
}

int	parse_command(char *command)
{
	// if (!check_syntax(command))
	// {
	// 	// printf("%s\n", command);
	// 	return 0;
	// }
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