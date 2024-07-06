/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmd1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:43:58 by aelkheta          #+#    #+#             */
/*   Updated: 2024/06/27 17:13:19 by aelkheta         ###   ########.fr       */
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

void ft_perror(char *message)
{
	ft_putstr_fd(message, 2);
}

int	cd(char **args)
{
	// printf("affas\n");
	if (args[0] != NULL && args[1] != NULL)
	{
		ft_perror("cd: string not in pwd\n");
		return (0);
	}
	else if (args[0] != NULL && args[0][0] == '-' && args[0][1] == '\0')
	{
		args[0] = getenv("OLDPWD");
		printf("%s\n", args[0]);
		change_dir(args[0]);
		return (1);
	}
	else if (args[0] == NULL || (args[0][0] == '~' && args[0][1] == '\0'))
	{
		args[0] = getenv("HOME");
		change_dir(args[0]);
		return (1);
	}
	else if (args != NULL && change_dir(args[0]))
		return (1);
	else
	{
		if (errno == EACCES)
			printf("minishell: cd: %s Permission denied\n", args[0]);
		else if (errno == ENOENT)
			printf("minishell: cd: %s No such file or directory\n", args[0]);
		else if (errno == ENOTDIR)
			printf("minishell: cd: %s No such file or directory\n", args[0]);
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

// int	built_in_cmd(char **command)
// {
// 	if (command == NULL || command[0] == 0)
// 		return (0);
// 	else if (!ft_strncmp("exit", command, ft_strlen(command)))
// 		exit(0);
// 	else if (!ft_strncmp("echo", command, ft_strlen(command)))
// 		echo(command);
// 	else if (!ft_strncmp("pwd", command, ft_strlen(command)))
// 		pwd();
// 	else if (!ft_strncmp("cd", command, ft_strlen(command)))
// 		cd(command);
// 	else if (!ft_strncmp("env", command, ft_strlen(command)))
// 		env(data->env);
// 	else if (!ft_strncmp("export", command, ft_strlen(command)))
// 		export(command);
// 	else
// 		return (0);
// 	return (1);
// }
