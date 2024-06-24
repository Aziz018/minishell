/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:40:09 by aelkheta          #+#    #+#             */
/*   Updated: 2024/06/24 17:04:57 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

char *skip_white_spaces(char *command)
{
	while(*command && (*command == ' ' || *command == '\t' || *command == '\r' || *command == '\v'))
		command++;
	return (command);
}
void print_type(t_command *tokens)
{
	while (tokens != NULL)
	{
		printf("+---------------------------+\n");
		printf("| value: ----------- %s\n", tokens->value);
		if (tokens->type == CMD)
			printf("| type: ----------- CMD     |\n+---------------------------+\n\n");
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
		tokens = tokens->next;
		// t_command *ptr = tokens->next;
		// free(tokens->value);
		// free(tokens);
		// tokens = ptr;
	}
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
	// t_command *temp = tokens;
	t_command *ptr2 = ptr;
	ptr->args = NULL;
	while(ptr2 != NULL)
	{
		ptr2->args = NULL;
		if (ptr->type == CMD)
		{
			int i = 0;
			ptr2->args = malloc((get_args_size(ptr->next) + 2) * sizeof(char *)); // why + 2 one for the name of the command and ther other for NULL ptr
			ptr2->args[i++] = ft_strdup(ptr->value);
			ptr = ptr->next;
			while(ptr != NULL && ptr->type == ARG)
			{
				ptr2->args[i++] = ptr->value;
				ptr = ptr->next;
			}
			// if (ptr != NULL)
			ptr2->next = ptr;
			ptr2->args[i] = NULL;				
		}
		else if (ptr->type == RED_IN || ptr->type == RED_OUT || ptr->type == APP || ptr->type == HER_DOC)
		{
			if (!ptr->next || ptr->next->type != FLE)
			{
				printf("syntax error\n");
				return NULL;
			}
			ptr2->args = malloc((2) * sizeof(char *)); // why + 2 one for the name of the command and ther other for NULL ptr
			ptr = ptr->next;
			ptr2->next = ptr->next;
			ptr2->args[0] = ptr->value;
			ptr2->args[1] = NULL;
		}
		if (ptr2 != NULL)
			ptr2 = ptr2->next;

		// temp = ptr;
		// ptr = ptr->next;
		// temp->args = NULL;
		// if (!ptr)
		// 	break;
		// if (temp->type == CMD && ptr->type == ARG)
		// {
		// 	int i = 0;
		// 	temp->args = malloc((get_args_size(ptr) + 2) * sizeof(char *)); // why + 2 one for the name of the command and ther other for NULL ptr
		// 	temp->args[i++] = ft_strdup(temp->value);
		// 	while(ptr != NULL && ptr->type == ARG)
		// 	{
		// 		temp->args[i++] = ptr->value;
		// 		t_command *aziz = ptr->next;
		// 		free(ptr);
		// 		ptr = aziz;
		// 	}
		// 	temp->args[i] = NULL;
		// 	temp->next = ptr;
		// }
		// else if (temp->type == RED_OUT || temp->type == RED_IN || temp->type == APP || temp->type == HER_DOC)
		// {
		// 	temp->args = malloc(2 * sizeof(char *));
		// 	temp->args[0] = ptr->value;
		// 	temp->args[1] = NULL;
		// 	t_command *aziz = ptr->next;
		// 	free(ptr);
		// 	ptr = aziz;
		// 	temp->next = ptr;
		// }
	}
	return (tokens);
}

void print_list(t_command *tokens)
{
	int i = 0;

	while(tokens != NULL)
	{
		printf("=> node: %d\n+---------------------------+\n| token: ---------- %s\n", ++i, tokens->value);
		if (tokens->type == CMD)
			printf("| type: ----------- CMD     |\n+---------------------------+\n");
		else if (tokens->type == RED_OUT)
			printf("| type: ----------- RED_OUT |\n+---------------------------+\n");
		else if (tokens->type == RED_IN)
			printf("| type: ----------- RED_IN  |\n+---------------------------+\n");
		else if (tokens->type == APP)
			printf("| type: ----------- APP     |\n+---------------------------+\n");
		else if (tokens->type == HER_DOC)
			printf("| type: ----------- HER_DOC |\n+---------------------------+\n");
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
	printf("\nTokenising:\n\n");
	print_type(tokens);
	tokens = parser_command(tokens);
	printf("\n\n\nParsing:\n\n");
	print_list(tokens);


	// for execute commands

	// if (built_in_cmd(parsedcmd))
	// 	return (0);
	// exec_command(command);
    
	return (0);
}