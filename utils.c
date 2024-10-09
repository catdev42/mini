/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:15:14 by myakoven          #+#    #+#             */
/*   Updated: 2024/10/09 21:50:32 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 	CHECKS IF THE COMMAND LINE IS EMPTY
	Returns 1 if there is anything except spaces in a line */
int	valid_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (1);
		i++;
	}
	return (0);
}

/* PRINTS A 2D ARRAY */
int	print_tab(char **envp)
{
	size_t	i;

	i = 0;
	if (!envp || !*envp)
		return (0);
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (1);
}

int	istoken(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
int	isredir(char c)
{
	return (c == '<' || c == '>');
}

int	isquote(char c)
{
	return (c == '\'' || c == '\"');
}

/*
int	copy_quotes(char *c_line, char *line, t_tools *tools)
{
	char	quote_char;
	int		i;
	int		j;

	i = 0;
	j = 0;
	quote_char = line[i];
	c_line[j++] = line[i++];
	while (line[i] && line[i] != quote_char)
	{
		if (quote_char == '\"' && line[i] == '$' && line[i - 1] != '\'')
			copy_var(&c_line[j], &line[i], tools); // TODO TODO TO DO
	}
	c_line[j++] = line[i++];
	i = i + copy_spaces(&c_line[j], &line[i]);
	return (i);
}

// Returns the number of spaces to skip -> add this to current index
int	skip_spaces(char *s)
{
	int	i;

	i = 0;
	if (!s || !*s)
		return (0);
	while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
		i++;
	return (i);
}

//WHY DOES THIS EXIST?
void	ft_bspace(void *s, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *)s;
	i = 0;
	while (i < n && p[i])
	{
		p[i++] = ' ';
	}
}

*/
