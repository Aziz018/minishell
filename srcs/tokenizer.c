/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:51:08 by aelkheta          #+#    #+#             */
/*   Updated: 2024/06/10 18:10:15 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

int syntax_error(char *command)
{
	int i = 0;
	if (ft_strchr("<|>&;", command[i])) //<|>&;
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
	while(command[token->i] && ft_strchr(" \t\v", command[token->i]))
		token->i++;
	if (command[token->i] == '\0')
		return (NULL);
	token->index = token->i;
	if (ft_strchr("'\"[{(", command[token->i]))
	{
		char special = command[token->i];
		if (command[token->i] == '[')
			special = ']';
		else if (command[token->i] == '{')
			special = '}';
		else if (command[token->i] == '(')
			special = ')';
		
		// token->i++;
		while(command[++token->i] && command[token->i] == special);
			// token->i++;
		token->index = token->i;
		while(command[token->i] && command[token->i] != special)
			token->i++;
		if (!command[token->i])
		{
			write(2, "minishell: syntax error near unexpected token ';'\n", 51);
			data->syntax_error = true;
			return NULL;
		}
		while(command[++token->i] && ft_isalnum(command[token->i]));
		token_val = malloc((token->i - token->index) * sizeof(char) + 1);
		ft_strlcpy(token_val, &command[token->index], (token->i - token->index + 1));
		token->index = token->i;
		return (token_val);
	}
	if (command[token->i] && ft_strchr("<|>&;", command[token->i]))
	{
		// if (syntax_error(&command[token->i]))
		// 	return (NULL);
		if ((command[token->i] == '<' && command[token->i + 1] == '<') || (command[token->i] == '>' && command[token->i + 1] == '>') || (command[token->i] == '|' && command[token->i + 1] == '|') || (command[token->i] == '&' && command[token->i + 1] == '&'))
		{
			token_val = malloc(3 * sizeof(char));
			token_val[0] = command[token->i];
			token_val[1] = command[token->i + 1];
			token_val[2] = '\0';
			token->i += 2;
			token->index = token->i;
			return (token_val);
		}
		else
		{
			token_val = malloc(2 * sizeof(char));
			token_val[0] = command[token->i];
			token_val[1] = '\0';
			token->i++;
			token->index = token->i;
			return (token_val);
		}
	}
	while(command[token->i] && !ft_strchr(" \t\v<|>&;'\"", command[token->i])) // ft_isalnum(command[token->i])
		token->i++;
	token_val = malloc((token->i - token->index) * sizeof(char) + 1);
	ft_strlcpy(token_val, &command[token->index], (token->i - token->index + 1));
	token->index = token->i;
	return (token_val);
}


int set_token_type(t_token *token, int type)
{
    token->prev_type = type;
	token->type = type;
	return (type);
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
	else if (token->value[0] == ';')
		return (set_token_type(token, LIST));
	else if (token->prev_type == CMD || token->prev_type == ARG)
		return (set_token_type(token, ARG));
	else if (token->prev_type == RED_IN || token->prev_type == RED_OUT || token->prev_type == APP || token->prev_type == HER_DOC)
		return (set_token_type(token, FLE));
	else //if (token->prev_type == -1 || token->prev_type == PIPE || token->prev_type == RED_IN || token->prev_type == LIST)
		return (set_token_type(token, CMD));
	return (0);
}


// int get_token_type(t_token *token)
// {
// 	if (token->value[0] == '|' && token->value[1] == '\0')
// 	{
// 		// token->type = PIPE;
// 		// token->prev_type = PIPE;
// 		// // printf("type: ---------- PIPE\n");
// 		// return (PIPE);
// 		return (set_token_type(token, PIPE));
// 	}
// 	else if (token->value[0] == '>' && token->value[1] == '\0')
// 	{
// 		token->type = RED_OUT;
// 		token->prev_type = RED_OUT;
// 		// printf("type: ---------- RED_OUT\n");
// 		return(RED_OUT);
// 	}
// 	else if (token->value[0] == '>' && token->value[1] == '>' && token->value[2] == '\0')
// 	{
// 		token->type = APP;
// 		token->prev_type = APP;
// 		// printf("type: ---------- APP\n");
// 		return(APP);
// 	}
// 	else if (token->value[0] == '<' && token->value[1] == '\0')
// 	{
// 		token->type = RED_IN;
// 		token->prev_type = RED_IN;
// 		// printf("type: ---------- RED_IN\n");
// 		return(RED_IN);
// 	}
// 	else if (token->value[0] == '&' && token->value[1] == '\0')
// 	{
// 		token->type = BACK;
// 		token->prev_type = BACK;
// 		// printf("type: ---------- BACK\n");
// 		return(BACK);
// 	}
// 	else if (token->value[0] == '&' && token->value[1] == '&' && token->value[2] == '\0')
// 	{
// 		token->type = AND_OP;
// 		token->prev_type = AND_OP;
// 		// printf("type: ---------- AND_OP\n");
// 		return(AND_OP);
// 	}
// 	else if (token->value[0] == '|' && token->value[1] == '|' && token->value[2] == '\0')
// 	{
// 		token->type = OR_OP;
// 		token->prev_type = OR_OP;
// 		// printf("type: ---------- OR_OP\n");
// 		return(OR_OP);
// 	}
// 	else if (token->value[0] == ';')
// 	{
// 		token->type = LIST;
// 		token->prev_type = LIST;
// 		// printf("type: ---------- CMD\n");
// 		return(LIST);
// 	}
// 	else if (token->prev_type == CMD || token->prev_type == ARG)
// 	{
// 		token->type = ARG;
// 		token->prev_type = ARG;
// 		// printf("type: ---------- ARG\n");
// 		return(ARG);
// 	}
// 	else if (token->prev_type == RED_IN || token->prev_type == RED_OUT || token->prev_type == APP)
// 	{
// 		token->type = FLE;
// 		token->prev_type = FLE;
// 		// printf("type: ---------- FILE\n");
// 		return(FLE);
// 	}
// 	else if (token->prev_type == -1 || token->prev_type == PIPE || token->prev_type == RED_IN || token->prev_type == LIST)
// 	{
// 		token->type = CMD;
// 		token->prev_type = CMD;
// 		// printf("type: ---------- CMD\n");
// 		return(CMD);
// 	}
// 	return (0);
// }
