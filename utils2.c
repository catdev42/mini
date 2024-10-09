/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:15:14 by myakoven          #+#    #+#             */
/*   Updated: 2024/10/09 21:55:10 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	get_matrix_len(char **matrix)
{
	int	i;

	if (!matrix || !*matrix)
		return (0);
	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

/* 	Allocates, checks the memory allocation,
		and returns the pointer to allocation.
	Calls error_exit in case of memory error  */
char	*safe_calloc(size_t nmemb, size_t size, t_tools *tools)
{
	char	*str;

	str = ft_calloc(nmemb, size);
	if (!str)
		error_exit(tools, 1);
	return (str);
}

/*
Can initialize 2 ints, 1 char and 1 string pointer
If something isnt necessary, pass in NULL
Used by clean_line()!
*/
void	init_zero(size_t *i, size_t *j, char *c, char **c_line)
{
	if (i)
		*i = 0;
	if (j)
		*j = 0;
	if (c)
		*c = 0;
	if (c_line)
		*c_line = NULL;
}

void	strip_quotes_final(char *start)
{
	int		i;
	char	quotechar;
	char	*firstquote;

	firstquote = 0;
	i = 0;
	quotechar = 0;
	while (start[i])
	{
		if (isquote(start[i]))
		{
			quotechar = start[i];
			firstquote = &start[i];
			i = skip_quotes(start, i);
			if (start[i] && start[i] == quotechar)
				i = i - remove_two(firstquote, &start[i]);
			quotechar = 0;
		}
		i++;
	}
}

char	*get_token_end(char *namestart)
{
	int	i;

	i = 0;
	while (namestart[i] && !ft_isspace(namestart[i]))
	{
		if (isquote(namestart[i]))
			i = skip_quotes(namestart, i);
		i++;
	}
	return (&namestart[i]);
}
