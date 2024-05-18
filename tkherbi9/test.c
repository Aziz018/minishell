/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:40:28 by aelkheta          #+#    #+#             */
/*   Updated: 2024/05/15 11:04:33 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s directory\n", argv[0]);
		return (1);
	}
	if (chdir(argv[1]) == -1)
	{
		perror("chdir");
		return (1);
	}
	printf("Changed directory to: %s\n", argv[1]);
	system("ls");
	return (0);
}
