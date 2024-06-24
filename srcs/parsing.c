/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:40:09 by aelkheta          #+#    #+#             */
/*   Updated: 2024/06/24 11:31:26 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

char *skip_white_spaces(char *command)
{
	while(*command && (*command == ' ' || *command == '\t' || *command == '\r' || *command == '\v'))
		command++;
	return (command);
}

t_command *tokenize_command(char *commads)
{
	t_token token;
	t_command *head = NULL;
	token.i = 0;
	token.index = 0;
	commads = skip_white_spaces(commads);
	if (commads[token.i] == '\0')
		return NULL;
	while(commads[token.i])
	{
		token.value = get_token_value(&token, commads);
		if (!token.value)
			break;
		token.type = get_token_type(&token);		
		add_back_list(&head, new_node(token.type, token.value));
	}
	return (head);
}

int get_args_size(t_command *token)
{
	int i = 0;
	while(token != NULL && token->type == ARG)
	{
		token = token->next;
		i++;
	}
	return (i);
}

void print_args(t_command *token)
{
	int i = 0;
	
	while(token->args != NULL && token->args[i] != NULL)
	{
		printf("	+---------------------------+\n");
		printf("	| arg[%d]: ------------- [%s]\n", i, token->args[i]);
		printf("	+---------------------------+\n");
		free(token->args[i]);
		i++;
	}
	if (token->args != NULL)
		free(token->args);
}

t_command *parser_command(t_command *tokens)
{
	t_command *ptr = tokens;
	t_command *temp = tokens;
	temp->args = NULL;
	while(ptr != NULL)
	{
		temp = ptr;
		ptr = ptr->next;
		temp->args = NULL;
		if (!ptr)
			break;
		if (temp->type == CMD && ptr->type == ARG)
		{
			int i = 0;
			temp->args = malloc((get_args_size(ptr) + 2) * sizeof(char *)); // why + 2 one for the name of the command and ther other for NULL ptr
			temp->args[i++] = ft_strdup(temp->value);
			while(ptr != NULL && ptr->type == ARG)
			{
				temp->args[i++] = ptr->value;
				t_command *aziz = ptr->next;
				free(ptr);
				ptr = aziz;
			}
			temp->args[i] = NULL;
			temp->next = ptr;
		}
		else if (temp->type == RED_OUT || temp->type == RED_IN || temp->type == APP || temp->type == HER_DOC)
		{
			temp->args = malloc(2 * sizeof(char *));
			temp->args[0] = ptr->value;
			temp->args[1] = NULL;
			t_command *aziz = ptr->next;
			free(ptr);
			ptr = aziz;
			temp->next = ptr;
		}
	}
	return (tokens);
}

void print_list(t_command *tokens)
{
	int i = 0;

	while(tokens != NULL)
	{
		if (tokens->type == -1)
		{
			printf("minishell: syntax error near unexpected token `%s`\n", tokens->value);
			clear_list(&tokens);
			return ;
		}
		printf("=> node: %d\n+---------------------------+\n| token: ---------- %s\n", ++i, tokens->value);
		if (tokens->type == CMD)
			printf("| type: ----------- CMD     |\n+---------------------------+\n");
		else if (tokens->type == RED_OUT)
			printf("| type: ----------- RED_OUT |\n+---------------------------+\n\n");
		else if (tokens->type == RED_IN)
			printf("| type: ----------- RED_IN  |\n+---------------------------+\n\n");
		else if (tokens->type == APP)
			printf("| type: ----------- APP     |\n+---------------------------+\n\n");
		else if (tokens->type == HER_DOC)
			printf("| type: ----------- HER_DOC |\n+---------------------------+\n\n");
		else if (tokens->type == PIPE)
			printf("| type: ----------- PIPE    |\n+---------------------------+\n\n");
		else if (tokens->type == LIST)
			printf("| type: ----------- LIST    |\n+---------------------------+\n\n");
		else if (tokens->type == BACK)
			printf("| type: ----------- BACK    |\n+---------------------------+\n\n");
		else if (tokens->type == ARG)
			printf("| type: ----------- ARG     |\n+---------------------------+\n\n");
		else if (tokens->type == OR_OP)
			printf("| type: ----------- OR_OP   |\n+---------------------------+\n\n");
		else if (tokens->type == AND_OP)
			printf("| type: ----------- AND_OP  |\n+---------------------------+\n\n");
		else if (tokens->type == FLE)
			printf("| type: ----------- FLE     |\n+---------------------------+\n\n");
		print_args(tokens);
		t_command *tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
}

int	parse_command(char *command)
{
	
	t_command *tokens = tokenize_command(command); // this function is the lexical analyser of lexer (tokenizer) its separate the input into a set tokens
	if (!tokens)
		return 0;
	tokens = parser_command(tokens);
	print_list(tokens);


	// for execute commands

	// if (built_in_cmd(parsedcmd))
	// 	return (0);
	// exec_command(command);
    
	return (0);
}