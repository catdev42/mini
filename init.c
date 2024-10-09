/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 21:35:52 by myakoven          #+#    #+#             */
/*   Updated: 2024/10/09 21:55:37 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

struct cmd	*makeexec(void)
{
	struct execcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = EXEC;
	return ((struct cmd *)cmd);
}
// redircmd(struct cmd *subcmd, char *file, char *efile, int mode, int fd)

struct cmd	*makeredir(char *file, char *efile, int mode, int fd)
{
	struct redircmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (0);
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = REDIR;
	cmd->cmd = NULL;
	cmd->file = file;
	cmd->efile = efile;
	// cmd->file = file;
	cmd->mode = mode;
	cmd->fd = fd;
	return ((struct cmd *)cmd);
}

struct cmd	*makepipe(struct cmd *left, struct cmd *right)
{
	struct pipecmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((struct cmd *)cmd);
}


