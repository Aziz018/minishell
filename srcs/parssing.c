/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:40:09 by aelkheta          #+#    #+#             */
/*   Updated: 2024/06/11 13:31:17 by aelkheta         ###   ########.fr       */
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
	commads = skip_white_spaces(commads);
	if (commads[token.i] == '\0')
		return NULL;
	while(commads[token.i])
	{
		{
			// printf("\ncommads[%d]: %d\n", token.i, commads[token.i]);
			
			token.value = get_token_value(&token, commads);
			if (!token.value)
				break;
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
	
	// if (data->syntax_error)
	// {
	// 	clear_list(&tokens);
	// 	return (0);
	// }
	
	while(ptr != NULL)
	{
		temp = ptr;
		ptr = ptr->next;
		temp->args = NULL;
		if (!ptr)
			break;
		if (temp->type == CMD)
		{
			if (ptr->type == ARG)
			{
				int i = 0;
				temp->args = malloc((get_args_size(ptr) + 2) * sizeof(char *));
				temp->args[i++] = temp->value;
				while(ptr != NULL && ptr->type == ARG)
				{
					temp->args[i++] = ptr->value;
					t_command *aziz = ptr->next;
					free(ptr);
					ptr = aziz;
				}
				// printf("\n\n============ i ==== %d ===============\n\n", i);
				temp->args[i] = NULL;
			}
			temp->next = ptr;
		}
		else if (temp->type == RED_OUT || temp->type == RED_IN || temp->type == APP)
		{
			temp->args = malloc(2 * sizeof(char *));
			temp->args[0] = ptr->value;
			temp->args[1] = NULL;
			t_command *aziz = ptr->next;
			free(ptr);
			ptr = aziz;
			// ptr = ptr->next;
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
		printf("=> node: %d\n+---------------------------+\n| token: ---------- %s\n", ++i, tokens->value);
		if (tokens->type == CMD)
		{
			// int i = 0;
			printf("| type: ----------- CMD     |\n+---------------------------+\n");
			print_args(tokens);
			printf("\n");
		}
			
		if (tokens->type == RED_OUT)
			printf("| type: ----------- RED_OUT |\n+---------------------------+\n\n");
		if (tokens->type == RED_IN)
			printf("| type: ----------- RED_IN  |\n+---------------------------+\n\n");
		if (tokens->type == APP)
			printf("| type: ----------- APP     |\n+---------------------------+\n\n");
			
		if ((tokens->type == RED_OUT || tokens->type == RED_IN || tokens->type == APP) && tokens->args != NULL)
		{
			printf("	+---------------------------+\n");
			printf("	| arg[%d]: ----------- [%s]\n", 1, tokens->args[0]);
			printf("	+---------------------------+\n");
			printf("\n");
			free(tokens->args[0]);
			free(tokens->args);
		}
		
		if (tokens->type == PIPE)
			printf("| type: ----------- PIPE    |\n+---------------------------+\n\n");
		if (tokens->type == LIST)
			printf("| type: ----------- LIST    |\n+---------------------------+\n\n");
		if (tokens->type == BACK)
			printf("| type: ----------- BACK    |\n+---------------------------+\n\n");
		if (tokens->type == ARG)
			printf("| type: ----------- ARG     |\n+---------------------------+\n\n");
		if (tokens->type == OR_OP)
			printf("| type: ----------- OR_OP   |\n+---------------------------+\n\n");
		if (tokens->type == AND_OP)
			printf("| type: ----------- AND_OP  |\n+---------------------------+\n\n");
		if (tokens->type == FLE)
			printf("| type: ----------- FLE     |\n+---------------------------+\n\n");
		if (tokens->type == HER_DOC)
			printf("| type: ----------- HER_DOC |\n+---------------------------+\n\n");
		t_command *tmp = tokens;
		tokens = tokens->next;
		// free(tmp->value);
		free(tmp);
		// tokens = tmp;
	}



		// for debuging:
	
	// while(tokens != NULL)
	// {
	// 	printf("=> node: %d\n+---------------------------+\n| token: ---------- %s\n", ++i, tokens->value);
	// 	if (tokens->type == CMD)
	// 		printf("| type: ----------- CMD     |\n+---------------------------+\n\n");
	// 	if (tokens->type == RED_OUT)
	// 		printf("| type: ----------- RED_OUT |\n+---------------------------+\n\n");
	// 	if (tokens->type == RED_IN)
	// 		printf("| type: ----------- RED_IN  |\n+---------------------------+\n\n");
	// 	if (tokens->type == PIPE)
	// 		printf("| type: ----------- PIPE    |\n+---------------------------+\n\n");
	// 	if (tokens->type == LIST)
	// 		printf("| type: ----------- LIST    |\n+---------------------------+\n\n");
	// 	if (tokens->type == BACK)
	// 		printf("| type: ----------- BACK    |\n+---------------------------+\n\n");
	// 	if (tokens->type == ARG)
	// 		printf("| type: ----------- ARG     |\n+---------------------------+\n\n");
	// 	if (tokens->type == OR_OP)
	// 		printf("| type: ----------- OR_OP   |\n+---------------------------+\n\n");
	// 	if (tokens->type == AND_OP)
	// 		printf("| type: ----------- AND_OP  |\n+---------------------------+\n\n");
	// 	if (tokens->type == FLE)
	// 		printf("| type: ----------- FLE     |\n+---------------------------+\n\n");
	// 	if (tokens->type == APP)
	// 		printf("| type: ----------- APP     |\n+---------------------------+\n\n");
	// 	t_command *tmp = tokens->next;
	// 	free(tokens->value);
	// 	free(tokens); 
	// 	tokens = tmp;	
	// 	// tokens = tokens->next;
	// }

}

int	parse_command(char *command)
{
	
	t_command *tokens = tokenizer_command(command); // this function is the lexical analyser of lexer (tokenizer) its separate the input into a set tokens
	if (!tokens)
		return 0;
	tokens = parser_command(tokens);
	print_list(tokens);



	// for execute commands

	// char **parsedcmd = ft_split(command, ' ');

	// if (built_in_cmd(parsedcmd))
	// 	return (0);
	// free_array(parsedcmd);
	// exec_command(command);
    
	return (0);
}