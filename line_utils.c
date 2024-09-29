/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 23:59:13 by myakoven          #+#    #+#             */
/*   Updated: 2024/09/27 00:27:46 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static void	extend_cleanline(t_tools *tools, int add);

// returns len of variablien in line
int	copy_var(char *c_line, char *line, t_tools *tools)
{
	char	*var;
	char	*var_result;
	int		i;
	int		curr_cl_ind;

	var = NULL;
	curr_cl_ind = c_line - tools->cleanline;
	i = 1;
	while (!ft_isspace(line[i]) && isquote(line[i]) && !istoken(line[i])
		&& line[i] != "$")
		i++;
	if (i == 1)
		return (0);
	var = ft_substr(line, 1, i - 1);
	if (!var)
		error_exit(tools, 1);
	var_result = get_var(tools->env, var);
	free(var);
	if (!var_result)
		return (0);
	if (tools->cl_len < ft_strlen(var_result) + ft_strlen(tools->cleanline))
	{
		extend_cleanline(tools, ft_strlen(var_result));
		c_line = &(tools->cleanline[curr_cl_ind]);
	}
    ft_strlcpy(c_line, var_result, tools->cl_len - curr_cl_ind);
	return (i);
}

static void	extend_cleanline(t_tools *tools, int add)
{
	int		new_cl_len;
	char	*tmpold;

	new_cl_len = tools->cl_len + add;
	tmpold = tools->cleanline;
	tools->cleanline = ft_calloc(new_cl_len + 2, 1);
	if (!tools->cleanline)
		error_exit(tools, 1);
	tools->cl_len = new_cl_len;
	ft_strlcpy(tools->cleanline, tmpold, tools->cl_len);
	free(tmpold);
}