/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseargv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 19:16:34 by myakoven          #+#    #+#             */
/*   Updated: 2024/10/09 21:59:38 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

struct s_cmd	*parseargv(char *start, char *end, t_tools *tools)
{
	struct s_execcmd	*ecmd;
	int					i;
	int					index;

	ecmd = NULL;
	ecmd = (struct s_execcmd *)makeexec();
	i = 0;
	index = 0;
	if (!ecmd)
		error_exit(tools, 1);
	while (start[i] && (&start[i] < end))
	{
		while (start[i] && isspace(start[i]))
			i++;
		if (start[i] && istoken(start[i]))
			i = skip_token(start, i);
		else
		{
			ecmd->argv[index] = &start[i];
			i = skip_token(start, i);
			ecmd->eargv[index++] = &start[i + 1];
		}
		i++;
	}
	if (tools->lastredir)
		tools->lastredir->cmd = (struct s_cmd *)ecmd;
	return ((struct s_cmd *)ecmd);
}

/* Returns the index of the last character of the token,
	just like skip quote is index of the second quote */
int	skip_token(char *start, int i)
{
	while (start[i] && !isspace(start[i]))
	{
		if (isquote(start[i]))
			i = skip_quotes(start, i);
		i++;
	}
	return (i - 1);
}
