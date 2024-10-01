/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checksyntax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 21:45:41 by myakoven          #+#    #+#             */
/*   Updated: 2024/10/01 21:46:06 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_redir_error(char *line, int i, int goodtokens)
{
	int	j;

	j = 0;
	while (istoken(line[i + goodtokens + j]))
		j++;
	return (ft_substr(line, (i + goodtokens), j)); ///this is malloc, and has to be ree, would like to avoid that
}

int	check_redirects(t_tools *tools)
{
	// int	len;
	int	i;

	// len = ft_strlen(tools->line);
	i = 0;
	while (tools->line[i])
	{
		if (tools->line[i] == '\"' || tools->line[i] == '\'')
			i = check_quotes(tools->line, i) + 1;
		if (istoken(tools->line[i]))
		{
			if (ft_strncmp(&tools->line[i], "<<|", 3)
				|| ft_strncmp(&tools->line[i], ">>>", 3))
				return (print_error(UNEXP, get_redir_error(tools->line, i, 2)));
			else if (ft_strncmp(&tools->line[i], ">>>>", 4))
				return (print_error(UNEXP, get_redir_error(tools->line, i, 3)));
			else if (ft_strncmp(&tools->line[i], "||", 2)
				|| ft_strncmp(&tools->line[i], "><", 2)
				|| ft_strncmp(&tools->line[i], "<>", 2))
				return (print_error(UNEXP, get_redir_error(tools->line, i, 1)));
		}
		i++;
	}
	return (0);
}
/*
	"<<|",
	"<<<<",
	">>>",
	"||",
	";;",
	"><",
	"<>",
	*/