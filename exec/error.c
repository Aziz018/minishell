#include "../libraries/minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (s == NULL || fd < 0)
		return ;
	len = 0;
	while (s[len])
		len++;
	write(fd, s, len);
}

void	ft_error_2(void)
{
	perror("\033[31mError");
	exit(127);
}

void	ft_error(char *av)
{
	if (ft_strcmp(av, "") == 0)
	{
		ft_putstr_fd("zsh: permission denied: ", 2);
		write(2, "\n", 1);
		exit(126);
	}
	else if (ft_strcmp(av, ".") == 0)
	{
		ft_putstr_fd(".: not enough arguments", 2);
		write(2, "\n", 1);
		exit(1);
	}
	else
	{
		ft_putstr_fd("zsh: command not found: ", 2);
		ft_putstr_fd(av, 2);
		write(2, "\n", 1);
		exit(127);
	}
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (0);
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}