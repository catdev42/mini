/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseredirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 19:16:34 by myakoven          #+#    #+#             */
/*   Updated: 2024/10/08 23:39:11 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

// ERROR MANAGEMENT:
// (print error message in parseexec(),
// give cursor to user in loop)
/*
parseexex()
{
if (peek redir)
parse_redirs
parse_exec
connect things
}
*/

struct cmd	*parseexec(char *start, char *end_of_exec, t_tools *tools)
{
	struct cmd	*ret;

	ret = NULL;
	if (peek(start, end_of_exec, tools, REDIR))
	{
		ret = parse_redirs(start, end_of_exec, tools); // check inside
		if (!ret)
			return (NULL);
	}
	if (!ret)
		ret = parseargv(start, end_of_exec, tools);
	// else
	// 	tools->lastredir->cmd = parseargv(start, end_of_exec, tools); // this is seg
	// tools->lastredir = NULL;
	return (ret);
}

struct cmd	*parse_redirs(char *start, char *end_of_exec, t_tools *tools)
{
	int				fd_in_or_out;
	int				mode;
	struct redircmd	*ret;

	ret = NULL;
	while (*start && start < end_of_exec)
	{
		mode = 0;
		fd_in_or_out = -1;
		if (isquote(*start))
			start += skip_quotes(start, 0);
		if (isredir(*start))
		{
			// fd_in_or_out = infile_or_outfile(start); // TODO !!!
			// mode = check_file_type(start, tools);    // TODO !!!
			// if (!mode)
			// 	return (NULL);
			if (start[1] == start[0])
				start++;
			createredir(++start, mode, fd_in_or_out, tools);
			if (!ret)
				ret = tools->lastredir;
		}
		start++;
	}
	parseargv(tools->s, tools->cmd_end, tools);
	tools->lastredir = NULL;
	return ((struct cmd *)ret);
}

struct cmd	*createredir(char *filestart, int mode, int fd, t_tools *tools)
{
	char	*end;

	end = NULL;
	end = get_token_end(filestart);
	if (tools->lastredir)
	{
		tools->lastredir->cmd = makeredir(filestart, end, mode, fd);
		tools->lastredir = (struct redircmd *)tools->lastredir->cmd;
	}
	else
		tools->lastredir = (struct redircmd *)makeredir(filestart, end, mode,
				fd);
	if (!tools->lastredir)
		error_exit(tools, 1); // EXITS PROGRAM ON OOM ERROR
	if (!tools->tree)
		tools->tree = (struct cmd *)tools->lastredir;
	return ((struct cmd *)tools->lastredir);
}

char	*get_token_end(char *namestart)
{
	int	i;

	i = 0;
	while (namestart[i] && !ft_isspace(namestart[i]))
	{
		if (isquote(namestart[i]))
			i = skip_quotes(namestart, i);
		i++;
	}
	return (&namestart[i]);
}
