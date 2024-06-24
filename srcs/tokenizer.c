/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:51:08 by aelkheta          #+#    #+#             */
/*   Updated: 2024/06/24 19:42:03 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

int set_token_type(t_token *token, int type)
{
    token->prev_type = type;
	token->type = type;
	return (type);
}

int syntax_error(char *command)
{
	int i = 0;
	if (ft_strchr("<|>&;", command[i]))
	{
		char special = command[i];
		while(command[++i] && ft_strchr(" \t\v", command[i])); // ++i to skip the char and start from the char after
		if (command[i] == special || (ft_strchr("<|>", special) && !command[i]))
		{
			data->syntax_error = true;
			write(2, "minishell: syntax error near unexpected token ';'\n", 51);
			return (1);
		}
	}
	return (0);
}

char *get_token_value(t_token *token, char *command)
{
	char *token_val = NULL;
	if (token->index == 0)
		token->prev_type = -1;
	while(command[token->i] && ft_strchr(" \t\v\n", command[token->i]))
		token->i++;
	if (command[token->i] == '\0')
		return (NULL);
	token->index = token->i;
	if (command[token->i] == '\'' || command[token->i] == '"')
	{
		while(command[token->i] && (command[token->i] == '\'' || command[token->i] == '"'))
			token->i++;
		token->index = token->i;
		while(command[token->i] && command[token->i] != '\'' && command[token->i] != '"')
			token->i++;
		token_val = malloc((token->i - token->index) * sizeof(char) + 1);
		ft_strlcpy(token_val, &command[token->index], (token->i - token->index + 1));
		while (command[token->i] && !ft_strchr("'\"", command[token->i]))
			token->i++;
		token->index = token->i;
		return (token_val);
	}
	// token->index = token->i;
	if (command[token->i] == ';')
	{
		token->i++;
		return (ft_strdup(";"));
	}
	if (command[token->i] && ft_strchr("<|>&;", command[token->i]))
	{
		char special = command[token->i];
		// while(command[token->i] && command[token->i] == command[token->index])
		// 	token->i++;
		while(command[token->i] && command[token->i] == special && token->i - token->index < 2)
			token->i++;
		token_val = malloc((token->i - token->index) * sizeof(char) + 1);
		ft_strlcpy(token_val, &command[token->index], (token->i - token->index + 1));				
		token->index = token->i;
		return (token_val);
	}
	while(command[token->i] && !ft_strchr(" \t\v\n<|>&;", command[token->i])) // ft_isalnum(command[token->i])
		token->i++;
	token_val = malloc((token->i - token->index) * sizeof(char) + 1);
	ft_strlcpy(token_val, &command[token->index], (token->i - token->index + 1));
	token->index = token->i;
	return (token_val);
}

int get_token_type(t_token *token)
{
	if (token->value[0] == '|' && token->value[1] == '\0')
		return (set_token_type(token, PIPE));
	else if (token->value[0] == '>' && token->value[1] == '\0')
		return (set_token_type(token, RED_OUT));
	else if (token->value[0] == '>' && token->value[1] == '>' && token->value[2] == '\0')
		return (set_token_type(token, APP));
	else if (token->value[0] == '<' && token->value[1] == '<' && token->value[2] == '\0')
		return (set_token_type(token, HER_DOC));
	else if (token->value[0] == '<' && token->value[1] == '\0')
		return (set_token_type(token, RED_IN));
	else if (token->value[0] == '&' && token->value[1] == '\0')
		return (set_token_type(token, BACK));
	else if (token->value[0] == '&' && token->value[1] == '&' && token->value[2] == '\0')
		return (set_token_type(token, AND_OP));
	else if (token->value[0] == '|' && token->value[1] == '|' && token->value[2] == '\0')
		return (set_token_type(token, OR_OP));
	else if (token->value[0] == ';' && token->value[1] == '\0')
		return (set_token_type(token, LIST));
	else if (token->prev_type == CMD || token->prev_type == ARG)
		return (set_token_type(token, ARG));
	else if (token->prev_type == RED_IN || token->prev_type == RED_OUT || token->prev_type == APP || token->prev_type == HER_DOC)
		return (set_token_type(token, FLE));
	else if (ft_strisalnum(token->value) && (token->prev_type == -1 || token->prev_type == PIPE || token->prev_type == FLE))
		return (set_token_type(token, CMD));
	// else
	// 	return (-1);
	return (0);
}

