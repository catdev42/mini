/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 00:42:37 by myakoven          #+#    #+#             */
/*   Updated: 2024/10/01 17:35:47 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

struct cmd	*parseline(char *line, t_tools *tools)
{
	// int	pipe;
	// pipe = peek(tools, PIPE);
	// if (pipe)
	// 	;
	// return (ret);
}

char	*peek(char *start, t_tools *tools, int token)
{
	char *tokenaddress;
	int i;
	char tokenchar;

	tokenaddress = 0;
	i = 0;
	tokenchar = 0;
	if (token == PIPE)
	{
		tokenchar = '|';
		i = 0;
		while (start[i] && start[i] != '|')
		{
			if (isquote(start[i]))
				i = skip_quotes(start, i);
			if (start[i] == '|')
				tokenaddress = &start[i];
			i++;
		}
	}
	if (token == REDIR)
	{
		i = 0;
		while (start[i] && isredir(start[i]))
		{
			if (isquote(start[i]))
				i = skip_quotes(start, i);
			if (isredir(start[i]))
				tokenaddress = &start[i];
			i++;
		}
	}

	return (tokenaddress);
}