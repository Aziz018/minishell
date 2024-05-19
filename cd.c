/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:43:58 by aelkheta          #+#    #+#             */
/*   Updated: 2024/05/19 15:17:40 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(char *path, t_data *data)
{
	bool	flag;

	flag = false;
	(void) data;
	if (chdir(path) == 0)
		return (1);
	else
	{
		if (errno == EACCES)
			printf("minishell: cd: %s Permission denied\n", path);
		else if (errno == ENOENT)
			printf("minishell: cd: %s Not such file or directory\n", path);
		else if (errno == ENOTDIR)
			printf("minishell: cd: %s Not such file or directory\n", path);
	}
	return (0);
}
void	pwd()
{
	char *cwd = getcwd(NULL, 0);
	printf("%s\n", cwd);
	free(cwd);
}
