/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:40:09 by aelkheta          #+#    #+#             */
/*   Updated: 2024/06/26 11:10:54 by aelkheta         ###   ########.fr       */
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

char *lexer(char *line)
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
			else if (trimed_line[i + 1] == '"')
			{
				unquoted_line[j++] = trimed_line[i++];
				while(trimed_line[i] && trimed_line[i] != '\'')
					unquoted_line[j++] = trimed_line[i++];
				if (!unquoted_line[i])
					break;
				unquoted_line[j++] = trimed_line[i++];
			}
			else
				unquoted_line[j++] = trimed_line[i++];
		}
		else if (trimed_line[i] && trimed_line[i] == '"')
		{
			if (trimed_line[i + 1] == '"')
				i += 2;
			else if (trimed_line[i + 1] == '\'')
			{
				unquoted_line[j++] = trimed_line[i++];
				while(trimed_line[i] && trimed_line[i] != '"')
					unquoted_line[j++] = trimed_line[i++];
				if (!unquoted_line[i])
					break;
				unquoted_line[j++] = trimed_line[i++];
			}
			else
				unquoted_line[j++] = trimed_line[i++];
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
	// ft_substr()
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
		}
		if (command_line[j] == '<' || command_line[j] == '>' || command_line[j] == '|')
		{
			char special = command_line[j];
			while (command_line[j] && command_line[j] == special)
				j++;
			token_val = malloc((j - *i) * sizeof(char) + 1);
			ft_strlcpy(token_val, &command_line[*i], j - *i + 1);
			*i = j;
			// printf("token value: %s\n", token_val);
			// free(token_val);
			return (token_val);
		}
		while(command_line[j] &&  !ft_strchr(" \t\v<|>", command_line[j]))
			j++;
		token_val = malloc((j - *i) * sizeof(char) + 1);
		ft_strlcpy(token_val, &command_line[*i], j - *i + 1);
		*i = j;
		return (token_val);
		// printf("token value: %s\n", token_val);
		// free(token_val);
	}
	return (NULL);
}

void print_type(int type)
{
	if (type == -1)
		printf("| type: ----------- ERROR   |\n+---------------------------+\n");
	else if (type == CMD)
		printf("| type: ----------- CMD     |\n+---------------------------+\n");
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

void print_list(t_command *table)
{
	while (table != NULL)
	{
		printf("+---------------------------+\n");
		printf("| token: ---------- [%s]\n", table->value);
		print_type(table->type);
		table = table->next;
	}
}

int get_token_type(char *token)
{
	// int i = -1;
	// if (token[0] == '\'' || token[0] == '"')
		//return (CMD);
	if (token[0] == '|' && !token[1])
		return (PIPE);
	else if (token[0] == '>' && !token[1])
		return (RED_OUT);
	else if (token[0] == '<' && !token[1])
		return (RED_IN);
	else if (token[0] == '>' && token[1] == '>' && !token[2])
		return (APP);
	else if (token[0] == '<' && token[1] == '<' && !token[2])
		return (HER_DOC);
	else if ((token[0] != '\'' || token[0] != '"') && ft_strchr("<|&>", token[0]) && ft_strlen(token) > 2)
		return (-1);
	else
		return (CMD);
}

t_command *tokensizer(char *command_line)
{
	int i = 0;
	t_command *table = NULL;
	while(command_line[i])
	{
		char *token = get_token(command_line, &i);
		int type = get_token_type(token);
		add_back_list(&table, new_node(type, token));
	}
	print_list(table);
	clear_list(&table);
	return NULL;
}

int	parse_command(char *line)
{
	// printf("line befor lexer: %s\n", line);
	line = lexer(line);
	if (line != NULL && line[0])
		printf("line after lexer: %s\n", line);
	t_command *tokens = tokensizer(line);
	(void)tokens;
	free(line);
	return (0);
}	
	// t_command *tokens = tokenize_command(command); // this function is the lexical analyser of lexer (tokenizer) its separate the input into a set tokens
	// if (!tokens)
		// return 0;
	// printf("\nTokenising:\n\n");
	// print_type(tokens);
	// tokens = parser_command(tokens);
	// printf("\n\n\nParsing:\n\n");
	// print_list(tokens);


	// for execute commands

	// if (built_in_cmd(parsedcmd))
	// 	return (0);
	// exec_command(command);
    
// }