/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:43:58 by aelkheta          #+#    #+#             */
/*   Updated: 2024/05/22 19:07:07 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(char *path, t_data *data)
{
	if (path == NULL)
	{
		char *home = getenv("HOME");
		if (home != NULL)
		{
			chdir(home);
			free(data->prompt);
			data->prompt = get_prompt();
		}
	}
	if (chdir(path) == 0)
	{
		free(data->prompt);
		data->prompt = get_prompt();
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
	}
	return (0);
}
void	pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	printf("%s\n", cwd);
	free(cwd);
}

int	env(char **env)
{
	int	i;

	i = -1;
	while (env[++i] != NULL)
		printf("%s\n", env[i]);
	return (0);
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
	while (cmd[i] != NULL)
	{
		printf("%s", cmd[i]);
		printf(" ");
		i++;
	}
	if (!flag)
		printf("\n");
	return (0);
}

// void modify_env_var(char *var, )
// {
	
// }


// int join_str(char **env, char **cmd)
// {
// 	int len;
// 	char **new_env;
	
// 	len = -1;
// 	while(env[++len] != NULL);
// 	new_env = malloc((len + 1) * sizeof(char *));
// 	if (!new_env)
// 		return (0);
// 	len = -1;
// 	while(env[++len])
// 	{
// 		// new_env[len] = malloc((env[len] + 1) * sizeof(char));
// 		new_env[len] = ft_strdup(env[len]);
// 	}
// 	new_env[len] = ft_strdup(cmd[1]);
// 	new_env[++len] = NULL;
// 	return (1);
// }

int	export(t_data *data, char **cmd)
{
	// int	i;

	// i = 0;
	if (cmd[1] == NULL)
	{
		env(data->env);
		return (0);
	}
	// while (env[++i] != NULL)
	// {
		// if (ft_strncmp(exprt_var, env[i], ft_strlen(env[i])) == 0)
		// 	modify_env_var(env);
	// }
	// join_str(data->env, cmd);
	// printf("%s\n", env[i]);
	return (0);
}
