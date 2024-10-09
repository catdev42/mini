/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:22:37 by myakoven          #+#    #+#             */
/*   Updated: 2024/10/09 23:16:26 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

/* RESET TOOLS: leave env var */
void	reset_tools(t_tools *tools)
{
	if (tools->line)
	{
		ft_bzero(tools->line, tools->line_capacity);
		free(tools->line);
	}
	tools->line = NULL;
	if (tools->cleanline)
	{
		ft_bzero(tools->cleanline, tools->cl_capacity);
		free(tools->cleanline);
	}
	if (tools->tree)
		tree_free(tools->tree);
	tools->tree = NULL;
	tools->cleanline = NULL;
	tools->cmd_end = NULL;
	tools->s = NULL;
	tools->lastpipe = NULL;
	tools->lastredir = NULL;
	tools->p = NULL;
	tools->p_next = NULL;
	tools->e_cline = NULL;
}

void	clean_tools(t_tools *tools)
{
	reset_tools(tools);
	if (tools->env)
		ft_freetab(tools->env, INT_MAX);
}

struct s_cmd	*clean_execs(struct s_cmd *first, struct s_cmd *second)
{
	struct s_redircmd	*rcmd;

	if (first)
	{
		if (first->type == REDIR)
		{
			rcmd = (struct s_redircmd *)first;
			free(rcmd);
		}
	}
	if (second)
	{
		if (first->type == REDIR)
		{
			rcmd = (struct s_redircmd *)second;
			free(rcmd);
		}
	}
	return (NULL);
}
