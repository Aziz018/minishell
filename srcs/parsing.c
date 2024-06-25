/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:40:09 by aelkheta          #+#    #+#             */
/*   Updated: 2024/06/25 21:49:19 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

char *skip_white_spaces(char *command)
{
	while(*command && (*command == ' ' || *command == '\t' || *command == '\r' || *command == '\v'))
		command++;
	return (command);
}

char *lexer(char *line)
{
	int i = 0;
	int j = 0;
	char *trimed_line = ft_strtrim(line, " \t\n\v");
	free(line);
	// printf("trimed: |%s|\n", trimed_line);
	char *unquoted_line = ft_calloc(ft_strlen(trimed_line) + 1, sizeof(char));
	while(trimed_line[i])
	{
		if (trimed_line[i] && (trimed_line[i] == '\'' || trimed_line[i] == '"') && (trimed_line[i + 1] == '\'' || trimed_line[i + 1] == '"'))
		{
			char quote = trimed_line[i];
			if (trimed_line[i + 1] == quote)
				i += 2;
		}
		else
			unquoted_line[j++] = trimed_line[i++];
	}
	free(trimed_line);
    unquoted_line[j] = '\0';
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
	if (type == CMD)
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

t_command *tokensizer(char *command_line)
{
	int i = 0;
	t_command *table = NULL;
	while(command_line[i])
	{
		char *token = get_token(command_line, &i);
		add_back_list(&table, new_node(0, token));
		// table.type = get_token_type(table.value);
	}
	print_list(table);
	clear_list(&table);
	return NULL;
}

int	parse_command(char *line)
{
	// printf("line befor lexer: %s\n", line);
	line = lexer(line);
	// printf("line after lexer: %s\n", line);
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