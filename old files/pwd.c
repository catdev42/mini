/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 14:13:16 by spitul            #+#    #+#             */
/*   Updated: 2024/07/20 23:07:35 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	pwd(t_tools *tools, cmd_t *cmd)
{
	char *pos;
	char cwd[2048];
	size_t i;

	i = 0;
	if (get_matrix_len(cmd->cmds) > 1)
		ft_putstr_fd("pwd: too many arguments\n", 2);
	pos = get_env_var(tools, "PWD");
	if (pos != NULL)
	{
		ft_putstr_fd(pos, 1);
		ft_putstr_fd("\n", 1);
	}
	else
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			ft_putstr_fd(cwd, 1);
			ft_putstr_fd("\n", 1);
		}
		else
			perror("pwd: error retrieving current directory:");
		// perror is needed here because the message has to be completed by errno
	}
}

/*
	Wanted to make a note on this for later:

	c4a6c10% pwd ok
	pwd: too many arguments

	After the have the 2d command array maybe we can stick it in there?

	void	pwd(t_tools *tools, char **cmd)?

	i have to change all my perrors to ft_putstr_fd(str, 2) - oops

*/
