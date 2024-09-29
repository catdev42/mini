/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 20:17:05 by myakoven          #+#    #+#             */
/*   Updated: 2024/09/03 23:55:13 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* EXPAND $VAR OR NOT */

/*
index = location of the first letter of the variable
returns 1 if expand in quotes, 2 if expand without any quotes
returns 0 in case of single quotes, do not expand
*/
int	is_expand(char *line, int index)
{
	int	i;
	int	first_q;
	int	second_q;

	first_q = 0;
	second_q = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\"')
		{
			first_q = i;
			second_q = check_quotes(line, i);
			if (index > first_q && index < second_q)
				return (1);
		}
		else if (line[i] == '\'')
		{
			first_q = i;
			second_q = check_quotes(line, i);
			if (index > first_q && index < second_q)
				return (0);
		}
		i++;
	}
	return (2);
	// return 2 if the variable is not surrounded by quotes? not sure if a diff number is useful
}

/*
Mallocs a new string,
frees the previous full string and incorporates the expanded variable
*/
char	*connect_three(char *full_line, char *exp_var, int index, int vlen)
{
	int		expand_len;
	char	*newline;
	int		i;
	int		exp_var_len;

	exp_var_len = 0;
	i = -1;
	newline = NULL;
	expand_len = 0;
	exp_var_len = ft_strlen(exp_var);
	expand_len = exp_var_len + ft_strlen(full_line) - vlen;
	newline = ft_calloc(expand_len + 2, sizeof(char));
	while (newline && i < expand_len)
	{
		while (i++ < index)
			newline[i] = full_line[i];
		i--;
		while (i++ - index < exp_var_len)
			newline[i] = exp_var[i - index];
		i--;
		while (i++ < expand_len)
			newline[i] = full_line[i - index - exp_var_len + index + vlen];
	}
	free(full_line);
	return (newline);
}

/*
can split this into a find_var function and replace_var function*/
int	expand_command(char **line, t_tools *tools)
{
	int		i;
	char	*full_line;
	char	*expd;
	char	*variable_alloc;
	int		j;

	i = 0;
	full_line = *line;
	expd = NULL;
	while (full_line[i])
	{
		if (full_line[i] == '$')
		{
			i++;
			j = 0;
			while (full_line[i + j] && !ft_isspace(full_line[i + j]))
				j++;
			// j represents length, need to add +1 to include the dollar sign
			if (j == 0)
				continue ;
			variable_alloc = ft_substr(full_line, i, j);
			if (is_expand(full_line, i))
			{
				expd = get_var(tools->env, variable_alloc);
				if (expd)
				{
					full_line = connect_three(full_line, expd, i - 1, j + 1);
					i = i + ft_strlen(expd);
					if (!full_line)
					{
						free(variable_alloc);
						error_exit(tools, 1);
					}
				}
				else
					ft_bspace(&full_line[i - 1], j + 1);
			}
			free(variable_alloc);
		}
		else
			i++;
	}
	return (1);
}
