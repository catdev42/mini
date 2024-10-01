/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:15:14 by myakoven          #+#    #+#             */
/*   Updated: 2024/10/01 17:35:05 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/*
CHECKS IF THE COMMAND IS EMPTY
Returns 1 if there is anything except spaces in a line
*/
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

/* WHY DOES THIS EXIST? */
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

/*
Provide the pointer to line and the index you are currently on
Returns 0 is quotes aren't closed
And Index of second quote if they are closed
*/

int	check_quotes(char *line, int i)
{
	int	j;

	j = 1;
	if (!isquote(line[i]))
		return (i);
	while (line[i + j])
	{
		if (line[i] == line[i + j])
			return (i + j);
		j++;
	}
	print_error(UNCLOSED, NULL);
	return (0);
}

/*
Provide the pointer to beginning of line and the index you are currently on.
Returns Index of CLOSING QUOTE if they are closed
Only use to find next quote when you KNOW that the quotes are closed
If the quotes are NOT closed, returns the index of the initial quote
*/

int	skip_quotes(char *line, int i)
{
	int	j;

	j = 1;
	if (!isquote(line[i]))
		return (i);
	while (line[i + j])
	{
		if (line[i] == line[i + j])
			return (i + j);
		j++;
	}
	// print_error(UNCLOSED, NULL);
	return (i);
}
