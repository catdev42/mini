/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:22:37 by myakoven          #+#    #+#             */
/*   Updated: 2024/10/09 14:28:42 by myakoven         ###   ########.fr       */
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
void	tree_free(struct cmd *node); 
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
	tools->cleanline = NULL;
	tools->cmd_end = NULL;
	tools->s = NULL;
	// if (tools->lastpipe)
	tools->lastpipe = NULL;
	// if (tools->lastredir)
	tools->lastredir = NULL;
	tools->p = NULL;
	tools->p_next = NULL;
	tools->e_cline = NULL;
	tree_free(tools->tree);
	tools->tree = NULL;
	// TODO
	// TODO
	// TODO
	// TODO
	// TODO
	// tools->lexed = NULL;
	// tools->lex_len = 0;
	// tools->num_pipes = 0;
}

static void	handle_exec(struct execcmd *cmd)
{
	// Don't have to free the argv or eargv
	free(cmd);
}

static void	handle_redir(struct redircmd *cmd)
{
	tree_free(cmd->cmd);
}

static void	handle_pipe(struct pipecmd *cmd)
{
	tree_free(cmd->left);
	tree_free(cmd->right);
}

void	tree_free(struct cmd *node)
{
	struct execcmd	*ecmd;
	struct redircmd	*rcmd;
	struct pipecmd	*pcmd;

	// ft_memset((void *)ecmd, 0, sizeof(*ecmd));
	// ft_memset((void *)rcmd, 0, sizeof(*rcmd));
	// ft_memset((void *)pcmd, 0, sizeof(*pcmd));
	ecmd = NULL;
	pcmd = NULL;
	rcmd = NULL;
	// *i = 1;
	if (node)
	{
		if (node->type == EXEC)
		{
			ecmd = (struct execcmd *)node;
			handle_exec(ecmd);
		}
		else if (node->type == REDIR)
		{
			rcmd = (struct redircmd *)node;
			handle_redir(rcmd);
		}
		else if (node->type == PIPE)
		{
			pcmd = (struct pipecmd *)node;
			handle_pipe(pcmd);
		}
		return ;
		// exit(1); // where is this returned and what happens to it
		// EXIT IS NEVER RETURNED
	}
	else
		return ;
}

/*
typedef struct s_tools
{
	int				env_len;
	char **env; // must free 2d

	char *line; // must free
	size_t			line_capacity;
	char *cleanline; // must free
	char *e_cline;   // null term of cleanline

	// do not free
	char			*s;
	char			*cmd_end;
	char			*p;
	char			*p_next;
	char			*r;

	size_t			cl_capacity;
	// int			num_pipes;
	struct cmd *tree; // must free
	// last empy pipe;
	struct pipecmd	*lastpipe;
		// do not free/// it gets freed when tree is cleaned
	// // temp holder
	// struct cmd		*tracktree;

}					t_tools;
*/
