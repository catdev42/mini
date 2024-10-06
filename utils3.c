/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 20:33:23 by myakoven          #+#    #+#             */
/*   Updated: 2024/10/06 20:51:09 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	strip_quotes_final(char *start)
{
	int		i;
	char	quotechar;
	char	*firstquote;
	char	*secondquote;
	bool	removequotes;

	removequotes = 1;
	firstquote = 0;
	secondquote = 0;
	i = 0;
	quotechar = 0;
	while (start[i])
	{
		if (isquote(start[i]))
		{
			quotechar = start[i];
			firstquote = &start[i];
			i++;
			while (start[i] && start[i] != quotechar)
				i++;
			if (start[i] && start[i] == quotechar)
			{
				secondquote = &start[i];
				remove_two(firstquote, secondquote);
				i -= 2;
			}
			quotechar = 0;
		}
		i++;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t i;

	if (dest == src)
		return (dest);
	if (dest > src)
	{
		i = n - 1;
		while (i + 1)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dest);
}