/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:40:09 by aelkheta          #+#    #+#             */
/*   Updated: 2024/06/26 17:51:35 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

char *skip_white_spaces(char *command)
{
	while(*command && (*command == ' ' || *command == '\t' || *command == '\r' || *command == '\v'))
		command++;
	return (command);
}
int check_unqoted(char *line)
{
	int i = 0;
	// printf("line: %s\n", line);
	while(line[i])
	{
		if (line[i] == '\'')
		{
			while(line[++i] && line[i] != '\'');
			if (!line[i])
				return (1);
			i++;
		}
		else if (line[i] == '"')
		{
			while(line[++i] && line[i] != '"');
			if (!line[i])
				return (1);
			i++;
		}
		else
			i++;
	}
	return (0);
}

char *lexer_command(char *line)
{
	int i = 0;
	int j = 0;
	char *trimed_line = ft_strtrim(line, " \t\n\v");
	free(line);
	char *unquoted_line = ft_calloc(ft_strlen(trimed_line) + 1, sizeof(char));
	while(trimed_line[i])
	{
		if (trimed_line[i] && trimed_line[i] == '\'')
		{
			if (trimed_line[i + 1] == '\'')
				i += 2;
			else //if (trimed_line[i + 1] == '"')
			{
				unquoted_line[j++] = trimed_line[i++];
				while(trimed_line[i] && trimed_line[i] != '\'')
					unquoted_line[j++] = trimed_line[i++];
				if (!trimed_line[i])
					break;
				unquoted_line[j++] = trimed_line[i++];
			}
			// else
			// 	unquoted_line[j++] = trimed_line[i++];
		}
		else if (trimed_line[i] && trimed_line[i] == '"')
		{
			if (trimed_line[i + 1] == '"')
				i += 2;
			else //if (trimed_line[i + 1] == '\'')
			{
				unquoted_line[j++] = trimed_line[i++];
				while(trimed_line[i] && trimed_line[i] != '"')
					unquoted_line[j++] = trimed_line[i++];
				if (!trimed_line[i])
					break;
				unquoted_line[j++] = trimed_line[i++];
			}
			// else
			// 	unquoted_line[j++] = trimed_line[i++];
		}
		else
			unquoted_line[j++] = trimed_line[i++];
	}
	free(trimed_line);
    unquoted_line[j] = '\0';
	if (check_unqoted(unquoted_line))
	{
		printf("syntax error\n");
		free(unquoted_line);
		unquoted_line = NULL;
	}
	return (unquoted_line);
}
char *get_token(char *command_line, int *i)
{
	int j = 0;
	char *token_val = NULL;
	j = *i;
	while(command_line[*i])
	{
		while(command_line[j] && ft_strchr(" \t\v", command_line[j]))
			j++;
		*i = j;
		if (command_line[j] == '\'' || command_line[j] == '"')
		{
			char quote = command_line[j++];
			while(command_line[j] && command_line[j] != quote)
				j++;
			if (command_line[j] == quote)
				j++;
		}
		if (command_line[j] == '<' || command_line[j] == '>' || command_line[j] == '|')
		{
			char special = command_line[j];
			while (command_line[j] && command_line[j] == special)
				j++;
			token_val = malloc((j - *i) * sizeof(char) + 1);
			ft_strlcpy(token_val, &command_line[*i], j - *i + 1);
			*i = j;
			return (token_val);
		}
		while(command_line[j] && !ft_strchr(" \t\v<|>", command_line[j]))
		{
			if (command_line[j] == '\'' || command_line[j] == '"')
			{
				char quote = command_line[j];
				while(command_line[++j] && command_line[j] != quote);
				if (command_line[j] == quote)
					j++;
			}		
			if (command_line[j])
				j++;
		}
		token_val = malloc((j - *i) * sizeof(char) + 1);
		ft_strlcpy(token_val, &command_line[*i], j - *i + 1);
		*i = j;
		return (token_val);
	}
	return (NULL);
}

void print_type(int type)
{
	if (type == -1)
		printf("| type: ----------- ERROR   |\n+---------------------------+\n");
	else if (type == TOKEN)
		printf("| type: ----------- TOKEN   |\n+---------------------------+\n");
	else if (type == RED_OUT)
		printf("| type: ----------- RED_OUT |\n+---------------------------+\n");
	else if (type == RED_IN)
		printf("| type: ----------- RED_IN  |\n+---------------------------+\n");
	else if (type == APP)
		printf("| type: ----------- APP     |\n+---------------------------+\n");
	else if (type == HER_DOC)
		printf("| type: ----------- HER_DOC |\n+---------------------------+\n");
	else if (type == PIPE)
		printf("| type: ----------- PIPE    |\n+---------------------------+\n\n");
	else if (type == LIST)
		printf("| type: ----------- LIST    |\n+---------------------------+\n\n");
	else if (type == BACK)
		printf("| type: ----------- BACK    |\n+---------------------------+\n\n");
	else if (type == ARG)
		printf("| type: ----------- ARG     |\n+---------------------------+\n\n");
	else if (type == OR_OP)
		printf("| type: ----------- OR_OP   |\n+---------------------------+\n\n");
	else if (type == AND_OP)
		printf("| type: ----------- AND_OP  |\n+---------------------------+\n\n");
	else if (type == FLE)
		printf("| type: ----------- FLE     |\n+---------------------------+\n\n");
}

void print_args(char **args)
{
	int i = 0;
	while(args != NULL && *args)
	{
		printf("	+---------------------------+\n");
		printf("	| arg[%d]: --------- [%s]\n", i++, *args++);
		printf("	+---------------------------+\n");
	}
}

void print_list(t_command *table)
{
	while (table != NULL)
	{
		printf("+---------------------------+\n");
		printf("| token: ---------- [%s]\n", table->value);
		print_type(table->type);
		print_args(table->args);
		table = table->next;
	}
}

int get_token_type(char *token)
{
	if (token[0] == '|' && !token[1])
		return (PIPE);
	if (token[0] == '|' && token[1] == '|' && !token[2])
		return (OR_OP);
	else if (token[0] == '>' && !token[1])
		return (RED_OUT);
	else if (token[0] == '<' && !token[1])
		return (RED_IN);
	else if (token[0] == '>' && token[1] == '>' && !token[2])
		return (APP);
	else if (token[0] == '<' && token[1] == '<' && !token[2])
		return (HER_DOC);
	else if (token[0] == '&' && !token[1])
		return (BACK);	
	else if (token[0] == '&' && token[1] == '&' && !token[2])
		return (AND_OP);
	else if (ft_strchr("<|&>", token[0]) && ft_strlen(token) > 2)
		return (-1);
	else
		return (TOKEN);
}

t_command *tokenzer_command(char *command_line)
{
	int i = 0;
	t_command *table = NULL;
	if (!command_line)
		return NULL;
	while(command_line[i])
	{
		char *token = get_token(command_line, &i);
		int type = get_token_type(token);
		add_back_list(&table, new_node(type, token));
	}
	free(command_line);
	return table;
}

t_command *free_node(t_command *_tokens_list)
{
	t_command *ptr = _tokens_list->next;
	free(_tokens_list->value);
	free(_tokens_list);
	_tokens_list = NULL;
	return (ptr);
}
int get_args_size(t_command *list)
{
	int i = 0;
	while(list != NULL && list->type == TOKEN)
	{
		list = list->next;
		i++;
	}	
	return (i);
}

t_command *parser_command(t_command *_tokens_list)
{
	t_command *head = NULL;
	t_command *list_command;
	int i;
	
	while(_tokens_list != NULL)
	{
		list_command = new_node(_tokens_list->type, ft_strdup(_tokens_list->value));
		list_command->args = NULL;
		if (_tokens_list->type == TOKEN)
		{
			i = 0;
			int size = get_args_size(_tokens_list);
			list_command->args = malloc((size + 1) * sizeof(char *));
			while(_tokens_list != NULL && _tokens_list->type == TOKEN)
			{
				list_command->args[i++] = ft_strdup(_tokens_list->value);
				_tokens_list = free_node(_tokens_list);
			}
			list_command->args[i] = NULL;
		}
		else if (_tokens_list->type == RED_IN || _tokens_list->type == RED_OUT || _tokens_list->type == APP || _tokens_list->type == HER_DOC)
		{
			_tokens_list = free_node(_tokens_list);
			if (!_tokens_list)
			{
				printf("syntax error\n");
				free_node(list_command);
				clear_list(&head);
				return (NULL);
			}
			list_command->args = malloc(2 * sizeof(char *));
			list_command->args[0] = ft_strdup(_tokens_list->value);
			list_command->args[1] = NULL;
			_tokens_list = free_node(_tokens_list);
		}
		else
		{
			list_command->value = ft_strdup(_tokens_list->value);
			_tokens_list = free_node(_tokens_list);
			if (!_tokens_list)
			{
				printf("syntax error\n");
				free_node(list_command);
				clear_list(&head);
				return (NULL);
			}
		}
		add_back_list(&head, list_command);
	}
	return (head);
}

t_command *expander_command(t_command *list)
{
	int i;
	t_command *head = list;

	while(list != NULL)
	{
		i = 0;
		if (list->type == -1)
		{
			printf("syntax error\n");
			clear_list(&head);
			return (NULL);
		}	
		while(list->args != NULL && list->args[i] != NULL)
		{
			int j = 0;
			int k = 0;
			char *argument = ft_calloc((ft_strlen(list->args[i]) + 1), sizeof(char));
			while(list->args[i][j])
			{
				if (list->args[i][j] == '\'' || list->args[i][j] == '"')
				{
					char quote = list->args[i][j++];
					while(list->args[i][j] && list->args[i][j] != quote)
						argument[k++] = list->args[i][j++];
					j++;
				}
				else
					argument[k++] = list->args[i][j++];
			}
			free(list->args[i]);
			list->args[i] = argument;
			i++;
		}
		list = list->next;
	}
	return (head);
}

int	parse_command(char *line)
{
	// printf("line befor lexer: %s\n", line);
	line = lexer_command(line);
	// if (line != NULL && line[0])
		// printf("line after lexer: %s\n", line);
	t_command *tokens_list = tokenzer_command(line);
	// print_list(tokens_list);
	t_command *list = parser_command(tokens_list);
	// print_list(list);
	list = expander_command(list);
	print_list(list);
	clear_list(&list);
	return (0);
}	

	// for execute commands

	// if (built_in_cmd(parsedcmd))
	// 	return (0);
	// exec_command(command);
    
// }