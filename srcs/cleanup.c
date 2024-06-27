/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:27:48 by aelkheta          #+#    #+#             */
/*   Updated: 2024/06/27 16:54:30 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

void	free_array(char **array)
{
	int	i;

	i = -1;
	while (array != NULL && array[++i] != NULL)
		free(array[i]);
	free(array);
}
