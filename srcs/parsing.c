/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:40:09 by aelkheta          #+#    #+#             */
/*   Updated: 2024/06/25 20:01:42 by aelkheta         ###   ########.fr       */
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
	printf("trimed: |%s|\n", trimed_line);
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

int	parse_command(char *line)
{
	printf("line befor lexer: %s\n", line);
	line = lexer(line);
	printf("line after lexer: %s\n", line);
	free(line);
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
    
	return (0);
}