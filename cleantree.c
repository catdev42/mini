/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleantree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:22:37 by myakoven          #+#    #+#             */
/*   Updated: 2024/10/09 22:50:19 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static void	handle_exec(struct s_execcmd *cmd)
{
	free(cmd);
}

static void	handle_redir(struct s_redircmd *cmd)
{
	tree_free(cmd->cmd);
}

static void	handle_pipe(struct s_pipecmd *cmd)
{
	tree_free(cmd->left);
	tree_free(cmd->right);
}

void	tree_free(struct s_cmd *node)
{
	struct s_execcmd	*ecmd;
	struct s_redircmd	*rcmd;
	struct s_pipecmd	*pcmd;

	ecmd = NULL;
	pcmd = NULL;
	rcmd = NULL;
	if (node && node->type == EXEC)
	{
		ecmd = (struct s_execcmd *)node;
		handle_exec(ecmd);
	}
	else if (node && node->type == REDIR)
	{
		rcmd = (struct s_redircmd *)node;
		handle_redir(rcmd);
	}
	else if (node && node->type == PIPE)
	{
		pcmd = (struct s_pipecmd *)node;
		handle_pipe(pcmd);
	}
	return ;
}
