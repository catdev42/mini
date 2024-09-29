/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserredirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 20:17:05 by myakoven          #+#    #+#             */
/*   Updated: 2024/08/18 19:58:21 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redirect(t_tools *tools, int cmd_index, int lexed_index)
{
	int			i;
	t_parsed	**redirects;
	t_token		*tokens;

	redirects = tools->parsed_commands[cmd_index]->redirects;
	tokens = tools->parsed_commands[cmd_index]->redir_tokens;
	if (tokens == NULL)
		tokens = i = 0;
	while (tokens[i])
		i++;
	tokens[i] = get_token(tools->lexed[lexed_index]);
	while ()
}
//TODO

int	count_redirects(t_tools *tools, int cmd_index)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (tools->lexed[i][0] != "|")
	{
		if (tools->lexed[i][0] == "<" || tools->lexed[i][0] == ">")
			count++;
		i++;
	}
	return (count);
}

/* parser should record the redirect or command as it appears */

t_token	get_token(char *redirect)
{
	if (strcmp(redirect, ">") == 0)
		return (GREAT);
	if (strcmp(redirect, ">>") == 0)
		return (GREAT_GREAT);
	if (strcmp(redirect, "<") == 0)
		return (LESS);
	if (strcmp(redirect, "<<") == 0)
		return (LESS_LESS);
	if (strcmp(redirect, "<<<") == 0)
		return (LESS_LESS_LESS);
	return (NONE);
}