/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:07:28 by spitul            #+#    #+#             */
/*   Updated: 2024/07/17 22:08:30 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env(t_tools *tools, char **env)
{
	char	**envp;
	int		len_pointers;
	int		i;

	i = 0;
	len_pointers = 0;
	while (env[len_pointers] != NULL)
		len_pointers++;
	envp = ft_calloc((len_pointers + 5), sizeof(char *));
	if (!envp)
		return (NULL);
	tools->env_len = len_pointers + 3;
	while (i < len_pointers && env[i])
	{
		envp[i] = ft_strdup(env[i]);
		if (!envp[i])
		{
			free_array(env, len_pointers);
			return (NULL);
		}
		i++;
	}
	return (envp);
}

char	*get_env_var(t_tools *tools, char *var)
{
	int		i;
	size_t	len;
	char	*pos;

	if (!var || !tools || !(tools->env))
		return (NULL);
	// exit(EXIT_FAILURE);
	//? myakoven i would prob just return null here
	// i think this should make us go to the next line probably,
	// instead of totally exit
	// edit: still thinking about this....
	pos = NULL;
	i = 0;
	len = ft_strlen(var);
	while (tools->env[i] && !pos)
	{
		pos = ft_strnstr(tools->env[i], var, len);
		i++;
	}
	if (*(pos + i) == '=')
		return (pos + len + 1);
	else
		return (NULL);
}
