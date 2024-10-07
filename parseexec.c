/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseexec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 19:16:34 by myakoven          #+#    #+#             */
/*   Updated: 2024/10/07 16:46:38 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

// ERROR MANAGEMENT:
// (print error message in parseexec(),
// give cursor to user in loop)

struct cmd	*parseexec(char *start, char *end_of_exec, t_tools *tools)
{
}

struct cmd	*getredir(int token, char *namestart, t_tools *tools)
{
	int i;
	char *filename;

	i = 0;
	while (namestart[i] && !ft_isspace(namestart[i]))
	{
		if (isquote(namestart[i]))
			i = skip_quotes(namestart, i);
		i++;
	}
	filename = ft_substr(namestart, 0, i);
	if (!filename)
		error_exit(tools, 1);
	strip_quotes_final(filename);
	if (!check_file_type(filename, token, tools))
		;
	makeredir(tools->tracktree, filename, O_RDONLY |);
	ft_bspace(namestart, i);
}