/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:22:37 by myakoven          #+#    #+#             */
/*   Updated: 2024/10/07 19:23:07 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

struct cmd	*clean_execs(struct cmd *first, struct cmd *second)
{
	struct redircmd	*rcmd;

	if (first)
	{
		if (first->type == REDIR)
		{
			rcmd = (struct redircmd *)first;
			free(rcmd->file);
			free(rcmd);
		}
	}
	if (second)
	{
		if (first->type == REDIR)
		{
			rcmd = (struct redircmd *)second;
			free(rcmd->file);
			free(rcmd);
		}
	}
	return (NULL);
}

/* RESET TOOLS: leave env var */
void	reset_tools(t_tools *tools)
{
	if (tools->line)
		free(tools->line);
	tools->line = NULL;
	if (tools->cleanline)
		free(tools->cleanline);
	tools->cleanline = NULL;
	// TODO
	// TODO
	// TODO
	// TODO
	// TODO
	// tools->lexed = NULL;
	// tools->lex_len = 0;
	// tools->num_pipes = 0;
}

/*
typedef struct s_tools
{
	int		env_len;
	char **env; // must free 2d

	char *line; // must free
	size_t	line_capacity;
	char *cleanline; // must free
	char *e_cline;   // null term of cleanline

	// do not free
	char	*s;
	char	*cmd_end;
	char	*p;
	char	*p_next;
	char	*r;

	size_t	cl_capacity;
	// int			num_pipes;
	struct cmd *tree; // must free
	// last empy pipe;
	struct pipecmd *lastpipe;
		// do not free/// it gets freed when tree is cleaned
	// // temp holder
	// struct cmd		*tracktree;

}			t_tools;
*/
