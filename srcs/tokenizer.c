/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:51:08 by aelkheta          #+#    #+#             */
/*   Updated: 2024/05/29 11:59:01 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

char *get_token_value(t_token *token, char *commads)
{
	char *token_val = NULL;
	if (token->index == 0)
		token->prev_type = -1;
	while(commads[token->i] && (commads[token->i] == ' ' || commads[token->i] == '\t' || commads[token->i] == '\v'))
		token->i++;	
	token->index = token->i;
	if (commads[token->i] == '"')
	{
		token->i++;
		while(commads[token->i] != '"')
			token->i++;
		// token->i++;
	}
	else if (commads[token->i] == '\'')
	{
		token->i++;
		while(commads[token->i] && commads[token->i] != '\'')
			token->i++;
		// token->i++;
	}
	while(commads[token->i] && commads[token->i] != ' ' && commads[token->i] != '\t' && commads[token->i] != '\v')
		token->i++;
	token_val = malloc((token->i - token->index) * sizeof(char) + 1);
	ft_strlcpy(token_val, &commads[token->index], (token->i - token->index + 1));
	token->index = token->i;
	return (token_val);
}


int get_token_type(t_token *token)
{
	if (token->value[0] == '|' && token->value[1] == '\0')
	{
		token->type = PIPE;
		token->prev_type = PIPE;
		// printf("type: ---------- PIPE\n");
		return (PIPE);
	}
	else if (token->value[0] == '>' && token->value[1] == '\0')
	{
		token->type = RED_OUT;
		token->prev_type = RED_OUT;
		// printf("type: ---------- RED_OUT\n");
		return(RED_OUT);
	}
	else if (token->value[0] == '>' && token->value[1] == '>' && token->value[2] == '\0')
	{
		token->type = APP;
		token->prev_type = APP;
		// printf("type: ---------- APP\n");
		return(APP);
	}
	else if (token->value[0] == '<' && token->value[1] == '\0')
	{
		token->type = RED_IN;
		token->prev_type = RED_IN;
		// printf("type: ---------- RED_IN\n");
		return(RED_IN);
	}
	else if (token->value[0] == '&' && token->value[1] == '\0')
	{
		token->type = BACK;
		token->prev_type = BACK;
		// printf("type: ---------- BACK\n");
		return(BACK);
	}
	else if (token->value[0] == '&' && token->value[1] == '&' && token->value[2] == '\0')
	{
		token->type = AND_OP;
		token->prev_type = AND_OP;
		// printf("type: ---------- AND_OP\n");
		return(AND_OP);
	}
	else if (token->value[0] == '|' && token->value[1] == '|' && token->value[2] == '\0')
	{
		token->type = OR_OP;
		token->prev_type = OR_OP;
		// printf("type: ---------- OR_OP\n");
		return(OR_OP);
	}
	else if (token->prev_type == CMD || token->prev_type == ARG)
	{
		token->type = ARG;
		token->prev_type = ARG;
		// printf("type: ---------- ARG\n");
		return(ARG);
	}
	else if (token->prev_type == RED_OUT || token->prev_type == RED_IN || token->prev_type == APP)
	{
		token->type = FLE;
		token->prev_type = FLE;
		// printf("type: ---------- FILE\n");
		return(FLE);
	}
	else if (token->prev_type == -1 || token->prev_type == PIPE)
	{
		token->type = CMD;
		token->prev_type = CMD;
		// printf("type: ---------- CMD\n");
		return(CMD);
	}
	return (0);
}
