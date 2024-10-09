/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:53:30 by spitul            #+#    #+#             */
/*   Updated: 2024/10/09 13:57:50 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct execcmd	t_execcmd;
typedef struct pipecmd	t_pipecmd;
typedef struct redircmd	t_redircmd;
typedef struct cmd		t_cmd;
void					print_cmd(t_execcmd *ecmd);
void					print_redir(t_redircmd *rcmd);
void					print_pipe(t_pipecmd *pcmd);

void	walking(struct cmd *cmd)
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
	if (cmd)
	{
		if (cmd->type == 1)
		{
			ecmd = (t_execcmd *)cmd;
			print_cmd(ecmd);
		}
		else if (cmd->type == 2)
		{
			rcmd = (t_redircmd *)cmd;
			print_redir(rcmd);
		}
		else if (cmd->type == 3)
		{
			pcmd = (t_pipecmd *)cmd;
			print_pipe(pcmd);
		}
		else
			return;
			// exit(1); // where is this returned and what happens to it
			// EXIT IS NEVER RETURNED
	}
}

void	print_cmd(t_execcmd *cmd)
{
	printf("node %d. \n", cmd->type);
	printf("we are in an exec struct\n");
	printf("ecmd: %p\n\n", cmd->argv);
	// free(cmd);
	// (*i)++;
}
void	print_redir(t_redircmd *cmd)
{
	printf("node %d. \n", cmd->type);
	printf("redir cmd: %d\n", cmd->fd);
	// (*i)++;
	walking(cmd->cmd);
	// free(cmd);

}

void	print_pipe(t_pipecmd *cmd)
{
	printf("node %d. \n", cmd->type);
	printf("pipe cmd\n");
	// (*i)++;
	walking(cmd->left);
	walking(cmd->right);
	// free(cmd);
}





// void	walking(t_cmd *cmd)
// {
// 	struct execcmd	*ecmd;
// 	struct redircmd	*rcmd;
// 	struct pipecmd	*pcmd;

// 	// ft_memset((void *)ecmd, 0, sizeof(*ecmd));
// 	// ft_memset((void *)rcmd, 0, sizeof(*rcmd));
// 	// ft_memset((void *)pcmd, 0, sizeof(*pcmd));
// 	ecmd = NULL;
// 	pcmd = NULL;
// 	rcmd = NULL;
// 	*i = 1;
// 	if (cmd)
// 	{
// 		if (cmd->type == 1)
// 		{
// 			ecmd = (t_execcmd *)cmd;
// 			print_cmd(ecmd);
// 		}
// 		else if (cmd->type == 2)
// 		{
// 			rcmd = (t_redircmd *)cmd;
// 			print_redir(rcmd);
// 		}
// 		else if (cmd->type == 3)
// 		{
// 			pcmd = (t_pipecmd *)cmd;
// 			print_pipe(pcmd);
// 		}
// 		else
// 			exit(1); // where is this returned and what happens to it
// 	}
// }

// void	print_cmd(t_execcmd *ecmd)
// {
// 	printf("node %d. \n", *i);
// 	printf("we are in an exec struct\n");
// 	printf("ecmd: %p\n\n", ecmd->argv);
// 	(*i)++;
// }
// void	print_redir(t_redircmd *rcmd)
// {
// 	printf("node %d. \n", *i);
// 	printf("redir cmd: %d\n", rcmd->fd);
// 	(*i)++;
// 	walking(rcmd->cmd);
// }

// void	print_pipe(t_pipecmd *pcmd)
// {
// 	printf("node %d. \n", *i);
// 	printf("pipe cmd\n");
// 	(*i)++;
// 	walking(pcmd->left);
// 	walking(pcmd->right);
// }
