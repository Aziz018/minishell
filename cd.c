/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:43:58 by aelkheta          #+#    #+#             */
/*   Updated: 2024/05/19 15:02:14 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd(char **env)
{
	int	i;

	i = -1;
	while (env[++i] != NULL)
	{
		if (ft_strnstr(env[i], "PWD=", 4))
			return (env[i] + 4);
	}
	return (NULL);
}

int	cd(char *path, t_data *data)
{
	bool	flag;

	// char	*path;
	flag = false;
	(void) data;
	if (chdir(path) == 0)
	{
		// data->prompt = get_prompt();
		// free(data->prompt);
		// printf("%s\n", data->prompt);
		return (1);
	}
	else
	{
		if (errno == EACCES)
			printf("minishell: cd: %s Permission denied\n", path);
		else if (errno == ENOENT)
			printf("minishell: cd: %s Not such file or directory\n", path);
		else if (errno == ENOTDIR)
			printf("minishell: cd: %s Not such file or directory\n", path);
		// else
		// printf("minishell: cd failed\n");
	}
	return (0);
}
