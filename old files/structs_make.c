/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_make.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:07:28 by myakoven          #+#    #+#             */
/*   Updated: 2024/10/09 22:00:19 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

struct s_cmd	*makeexec(void)
{
	struct s_execcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = EXEC;
	return ((struct s_cmd *)cmd);
}

struct s_cmd	*makeredir(struct s_cmd *subcmd, char *filename, int mode, int fd)
{
	struct s_redircmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (0);
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = REDIR;
	cmd->cmd = subcmd;
	// cmd->file = file;
	// cmd->efile = efile;
	cmd->file = filename;
	cmd->mode = mode;
	cmd->fd = fd;
	return ((struct s_cmd *)cmd);
}

struct s_cmd	*makepipe(struct s_cmd *left, struct s_cmd *right)
{
	struct s_pipecmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((struct s_cmd *)cmd);
}
