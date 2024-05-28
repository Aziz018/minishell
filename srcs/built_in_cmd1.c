/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmd1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:43:58 by aelkheta          #+#    #+#             */
/*   Updated: 2024/05/28 14:25:59 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

int change_dir(char *path)
{
	if (chdir(path))
		return 0;
	free(data->prompt);
	data->prompt = get_prompt();
	return (1);
}

int	cd(char *path)
{
	if (path != NULL && path[0] == '-' && path[1] == '\0')
	{
		path = getenv("OLDPWD");
		printf("%s\n", path);
		change_dir(path);
		return (1);
	}
	else if (path == NULL || (path[0] == '~' && path[1] == '\0'))
	{
		path = getenv("HOME");
		change_dir(path);
		return (1);
	}
	else if (path != NULL && change_dir(path))
		return (1);
	else
	{
		if (errno == EACCES)
			printf("minishell: cd: %s Permission denied\n", path);
		else if (errno == ENOENT)
			printf("minishell: cd: %s No such file or directory\n", path);
		else if (errno == ENOTDIR)
			printf("minishell: cd: %s No such file or directory\n", path);
	}
	return (0);
}

int	env(t_env *env)
{
	while (env != NULL)
	{
		printf("%s\n", env->value);
		env = env->next;
	}
	return (0);
}

void echo_it(char **cmd, int i)
{
	while (cmd[i] != NULL)
	{
		printf("%s", cmd[i]);
		printf(" ");
		i++;
	}
}

int	echo(char **cmd)
{
	int		i;
	bool	flag;

	i = 1;
	flag = false;
	if (!ft_strncmp("-n", cmd[i], ft_strlen(cmd[i])))
	{
		flag = true;
		++i;
	}
	if (cmd[i][0] == '$' && cmd[i][1] != '$' && cmd[i][1] != ' ')
	{
		char *path = getenv(&cmd[i][1]);
		if(!path)
		{
			printf("\n");
			return (0);
		}
		printf("%s\n", path);
		return (0);
	}
	echo_it(cmd, i);
	if (!flag)
		printf("\n");
	return (0);
}
int	built_in_cmd(char **parsedcmd)
{
	if (parsedcmd == NULL || parsedcmd[0] == 0)
		return (0);
	else if (!ft_strncmp("exit", parsedcmd[0], ft_strlen(parsedcmd[0])))
		exit(0);
	else if (!ft_strncmp("echo", parsedcmd[0], ft_strlen(parsedcmd[0])))
		echo(parsedcmd);
	else if (!ft_strncmp("pwd", parsedcmd[0], ft_strlen(parsedcmd[0])))
		pwd();
	else if (!ft_strncmp("cd", parsedcmd[0], ft_strlen(parsedcmd[0])))
		cd(parsedcmd[1]);
	else if (!ft_strncmp("env", parsedcmd[0], ft_strlen(parsedcmd[0])))
		env(data->env);
	else if (!ft_strncmp("export", parsedcmd[0], ft_strlen(parsedcmd[0])))
		export(parsedcmd[1]);
	else
		return (0);
	free_array(parsedcmd);
	return (1);
}