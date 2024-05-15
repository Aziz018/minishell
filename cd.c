/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:43:58 by aelkheta          #+#    #+#             */
/*   Updated: 2024/05/14 16:43:59 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && little[j] && (i + j) < len)
			j++;
		if (little[j] == '\0')
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}

char *get_pwd(char **env)
{
    int i;

    i = -1;
    while(env[++i] != NULL)
    {
        if (ft_strnstr(env[i], "PWD=", 4))
            return (env[i] + 4);
    }
    return NULL;
}

int main(int ac, char **av, char **env)
{
    char *path;
    bool flag;

    path = get_pwd(env);
    flag = false;
    if (ac == 2)
    {
        // printf("%s\n", path);
        if (chdir(av[1]) == 0)
            printf("done");
        else
            printf("not this time");
    }
    else if (ac > 2)
    {
        printf("cd: string not in pwd: %s", av[1]);
        return (1);
    }
    return (0);
}