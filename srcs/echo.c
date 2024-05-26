/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:03:53 by aelkheta          #+#    #+#             */
/*   Updated: 2024/05/14 13:27:29 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>

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

int	main(int ac, char **av)
{
	int		i;
	bool	flag;

	i = 0;
	flag = false;
	if (ac > 1)
	{
		if (ft_strnstr("-n", av[1], 3))
		{
			flag = true;
			++i;
		}
		while (++i < ac)
		{
			printf("%s", av[i]);
			if (i + 1 != ac)
				printf(" ");
		}
	}
	if (!flag)
		printf("\n");
	return (0);
}
