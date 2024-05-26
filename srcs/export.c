/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:44:22 by aelkheta          #+#    #+#             */
/*   Updated: 2024/05/18 18:03:31 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export(char *exprt_var, char **env)
{
	int	i;

	i = -1;
	while (env[++i] != NULL)
	{
		if (ft_strncmp(exprt_var, env[i], ft_strlen(env[i])) == 0)
			modify_env_var(env[i]);
	}
	// printf("%s\n", env[i]);
}
