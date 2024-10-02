/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 21:45:41 by myakoven          #+#    #+#             */
/*   Updated: 2024/10/02 20:02:42 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_redir_error(char *line, int i);
static int	check_pipes(char *line);
static int	check_last_redir(char *line);
static int	check_pipes(char *line);

int	valid_redirects(char *line)
{
	int		i;
	bool	hasalpha;
	int		first_token_index;

	first_token_index = 0;
	hasalpha = 0;
	i = 0;
	while (line[i])
	{
		if (!check_pipes(line))
			return (print_error(UNEXP, "|"));
		
		if (line[i] == '\"' || line[i] == '\'')
		{
			hasalpha = 1;
			i = skip_quotes(line, i) + 1;
		}
		if (line[i] && istoken(line[i]))
		{
			hasalpha = 0;
			if (line[i + 1] && line[i + 1] == line[i] && line[i] != '|')
				i++;
			if (line[i + 1])
				i++;
			while (line[i] && !istoken(line[i]))
			{
				if (!ft_isspace(line[i]) && !istoken(line[i]))
					hasalpha = 1;
				i++;
			}
			if (!hasalpha && istoken(line[i]))
				return (print_error(UNEXP, (get_redir_error(line, i))));
		}
		if (line[i])
			i++;
	}
	if (!check_last_redir(line))
			return (print_error(UNEXP, "newline"));
	return (1);
}

int	valid_quotes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (isquote(line[i]))
		{
			if (!check_quotes(line, i))
				return (0);
			i = skip_quotes(line, i);
		}
		i++;
	}
	return (1);
}

static char	*get_redir_error(char *line, int i)
{
	int	j;

	j = 0;
	while (istoken(line[i + j]) && j < 2)
		j++;
	if (istoken(line[i] == '|'))
		j = 1;
	if (istoken(line[i]) != istoken(line[i + 1]))
		j = 1;
	line[i + j] = 0;
	return (&line[i]);
}

static int	check_last_redir(char *line)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (line[i] && i >= 0 && ft_isspace(line[i]))
		i--;
	if (line[i] == '<' || line[i] == '>')
		return (0);
	return (1);
}

// returns zero if syntax error with pipes in beginning or end
static int	check_pipes(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] == '|')
		return (0);
	i = ft_strlen(line) - 1;
	while (line[i] && i >= 0 && ft_isspace(line[i]))
		i--;
	if (line[i] == '|')
		return (0);
	return (1);
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

/*


int	valid_redirects(t_tools *tools)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
			i = check_quotes(line, i) + 1;
		if (istoken(line[i]))
		{
			if (ft_strncmp(&line[i], "<<|", 3))
				return (print_error(UNEXP, "|"));
			else if (ft_strncmp(&line[i], ">>>", 3))
				return (print_error(UNEXP, ">"));
			// else if (ft_strncmp(&line[i], ">>>>", 4))
			// 	return (print_error(UNEXP, ">>"));
			// else if (ft_strncmp(&line[i], "|||", 2))
			// 	return (print_error(UNEXP, "||"));
			else if (ft_strncmp(&line[i], "||", 2))
				return (print_error(UNEXP, "|"));
			else if (ft_strncmp(&line[i], "><", 2))
				return (print_error(UNEXP, "<"));
			// else if (ft_strncmp(&line[i], "><<", 2))
			// 	return (print_error(UNEXP, "<<"));
			// else if (ft_strncmp(&line[i], "><<<", 2))
			// 	return (print_error(UNEXP, "<<<"));
			// else if (ft_strncmp(&line[i], "<>>>", 2))
			// 	return (print_error(UNEXP, ">>"));
			// else if (ft_strncmp(&line[i], "<>>", 2))
			// 	return (print_error(UNEXP, ">"));
			else if (ft_strncmp(&line[i], "<>", 2))
				return (print_error(UNEXP, ">"));
		}
		i++;
	}
	return (1);
}

int	valid_redirects(t_tools *tools)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
			i = check_quotes(line, i) + 1;
		if (istoken(line[i]))
		{
			if (ft_strncmp(&line[i], "<<<", 2))
				return (print_error(UNEXP, "<"));
			if (ft_strncmp(&line[i], "<<|", 2))
				return (print_error(UNEXP, "|"));
			else if (ft_strncmp(&line[i], ">>>", 2))
				return (print_error(UNEXP, ">"));
			else if (ft_strncmp(&line[i], "||", 2))
				return (print_error(UNEXP, "|"));
			else if (ft_strncmp(&line[i], "><", 1))
				return (print_error(UNEXP, "<"));
			else if (ft_strncmp(&line[i], "<>", 1))
				return (print_error(UNEXP, ">"));
		}
		i++;
	}
	return (1);
}


// int	valid_redirects(char *line)
// {
// 	int	i;

// 	i = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == '\"' || line[i] == '\'')
// 			i = check_quotes(line, i) + 1;
// 		if (istoken(line[i]))
// 		{
// 			if (ft_strncmp(&line[i], "<<<", 3))
// 				return (get_redir_error(line, i, 2));
// 			else if (ft_strncmp(&line[i], "<<|", 3))
// 				return (get_redir_error(line, i, 2));
// 			else if (ft_strncmp(&line[i], ">>>", 3))
// 				return (get_redir_error(line, i, 2));
// 			else if (ft_strncmp(&line[i], "||", 2))
// 				return (get_redir_error(line, i, 1));
// 			else if (ft_strncmp(&line[i], "><", 2))
// 				return (get_redir_error(line, i, 1));
// 			else if (ft_strncmp(&line[i], "<>", 2))
// 				return (get_redir_error(line, i, 1));
// 		}
// 		i++;
// 	}
// 	return (1);
// }
// TODO CHECK if there are words between tokens

// static char	*get_redir_error(char *line, int i, int goodtokens)
// {
// 	int	j;

// 	j = 0;
// 	while (istoken(line[i + goodtokens + j]) & j < 2)
// 		j++;
// 	if (istoken(line[i + goodtokens] == '|'))
// 		j = 1;
// 	if (istoken(line[i + goodtokens]) != istoken(line[i + goodtokens + 1]))
// 		j = 1;
// 	line[i + goodtokens + j] = 0;
// 	return (line[i + goodtokens]);
// }
*/