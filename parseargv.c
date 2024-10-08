/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseargv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 19:16:34 by myakoven          #+#    #+#             */
/*   Updated: 2024/10/08 14:19:44 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

struct cmd	*parseargv(char *start, char *end, t_tools *tools)
{
	struct execcmd	*ecmd;
	int				i;
	int				index;

	ecmd = NULL;
	ecmd = (struct execcmd *)makeexec();
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
	return ((struct cmd *)ecmd);
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
