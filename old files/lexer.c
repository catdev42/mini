/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:07:28 by spitul            #+#    #+#             */
/*   Updated: 2024/07/23 20:37:49 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// returns 0 on unclosed quotes, and a 1 on success
int	lexer(t_tools *tools)
{
	int	lex_i;
	int	i;
	int	len;

	i = 0;
	lex_i = 0;
	tools->lex_len = count_parts(tools);
	if (tools->lex_len == 0)
		return (0);
	tools->lexed = ft_calloc((tools->lex_len + 2), sizeof(char *));
	if (!tools->lexed)
		error_exit(tools, 1);
	while (lex_i < tools->lex_len && tools->line[i])
	{
		if (tools->line[i] && !istoken(tools->line[i]))
			len = getlen_command(tools, i);
		else if (tools->line[i] == '<' || tools->line[i] == '>')
			len = getlen_redirect(tools, i);
		else if (tools->line[i] == '|')
			len = 1;
		tools->lexed[lex_i] = ft_substr(tools->line, i, len);
		i += len;
		lex_i++;
	}
	return (1);
}

int	getlen_command(t_tools *tools, int i)
{
	int	og_index;

	og_index = i;
	while (tools->line[i])
	{
		if (isquote(tools->line[i]))
			i = check_quotes(tools->line, i); // now points to the last quote
		else if (istoken(tools->line[i]))
		{
			break ;
		}
		i++;
	}
	return (i - og_index);
}

int	getlen_redirect(t_tools *tools, int i)
{
	int	og_index;

	og_index = i;
	i++;
	while (tools->line[i])
	{
		if ((i - og_index) == 1 && tools->line[i] == tools->line[i - 1])
			i++;
		else if (tools->line[i] == '\"' || tools->line[i] == '\'')
		{
			i = check_quotes(tools->line, i);
			break ;
		}
		else if (!ft_isspace(tools->line[i]) && ft_isspace(tools->line[i + 1])
			&& (ft_isprint(tools->line[i]) && (i > og_index)))
		{
			while (ft_isspace(tools->line[i + 1]))
				i++;
			break ;
		}
		else if (i - og_index > 1 && istoken(tools->line[i + 1]))
			break ;
		else
			i++;
	}
	return (i - og_index + 1);
}

int	count_parts(t_tools *tools)
{
	int	i;
	int	redirs;

	i = 0;
	redirs = 0;
	if (!check_redirects(tools))
		return (0);
	while (tools->line[i])
	{
		if (tools->line[i] == '\"' || tools->line[i] == '\'')
		{
			i = check_quotes(tools->line, i);
			if (i == 0)
				return (0);
		}
		else if (tools->line[i] == '<' || tools->line[i] == '>')
		{
			if (tools->line[i + 1] == tools->line[i])
				i++;
			redirs++;
		}
		else if (tools->line[i] == '|')
			tools->num_pipes++;
		i++;
	}
	return (tools->num_pipes * 2 + 1 + redirs * 2);
}
