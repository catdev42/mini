/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:15:14 by myakoven          #+#    #+#             */
/*   Updated: 2024/09/27 00:42:01 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Can initialize 2 ints, 1 char and 1 string pointer
If something isnt necessary, pass in NULL
Used by clean_line()!
*/
void	init_zero(int *i, int *j, char *c, char **c_line)
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
	int i;

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
