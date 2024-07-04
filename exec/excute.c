#include "../libraries/minishell.h"

char	*function(char **env)
{
	int		i;
	char	*path_from_envp;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH", ft_strlen("PATH")) == 0)
			break ;
		i++;
	}
	if (!env[i])
		return (NULL);
	path_from_envp = ft_substr(env[i], ft_strlen("PATH="), ft_strlen(env[i]));
	return (path_from_envp);
}

char	*slash(char *mycmdargs)
{
	if (access(mycmdargs, F_OK) == 0)
		return (mycmdargs);
	else
	{
		ft_putstr_fd("zsh: no such file or directory: ", 2);
		ft_putstr_fd(mycmdargs, 2);
		write(2, "\n", 1);
		return (mycmdargs);
	}
}

char	*without_slash(char **env, char *mycmdargs)
{
	t_path	path;

	path.path_from_envp = function(env);
	if (!(path.path_from_envp))
		ft_error(mycmdargs);
	path.mypaths = ft_split(path.path_from_envp, ':');
	free(path.path_from_envp);
	path.i = 0;
	while (path.mypaths[path.i])
	{
		path.part_path = ft_strjoin(path.mypaths[path.i], "/");
		path.path = ft_strjoin(path.part_path, mycmdargs);
		free(path.part_path);
		if (access(path.path, F_OK) == 0)
			return (path.path);
		free(path.path);
		path.i++;
	}
	path.i = -1;
	while (path.mypaths[++path.i])
		free(path.mypaths[path.i]);
	free(path.mypaths);
	return (0);
}

char	*search_path(char *mycmdargs, char **env)
{
	if (ft_strchr(mycmdargs, '/') != 0)
		return (slash(mycmdargs));
	else
		return (without_slash(env, mycmdargs));
}

void	ft_excute(char **av, char **env)
{
	char	**mycmdargs;
	char	*path;
	int		i;

	i = -1;
	// if (ft_strcmp(av, "") == 0 || ft_strcmp(av, ".") == 0
	// 	|| ft_strcmp(&av[ft_strlen(av) - 1], " ") == 0)
	// 	ft_error(av);
	// else
	// {

	mycmdargs = av;//ft_split(av, ' ');
	path = search_path(mycmdargs[0], env);
	if (!path)
	{
		while (mycmdargs[++i])
			free(mycmdargs[i]);
		free(mycmdargs);
		//ft_error(av);
	}
	if (execve(path, mycmdargs, env) == -1)
		exit(127);
	// }
}
