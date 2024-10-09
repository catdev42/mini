/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseredirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 19:16:34 by myakoven          #+#    #+#             */
/*   Updated: 2024/10/09 21:24:54 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

struct cmd	*parseexec(char *start, char *end_of_exec, t_tools *tools)
{
	struct cmd	*ret;

	ret = NULL;
	if (peek(start, end_of_exec, tools, REDIR))
	{
		ret = parse_redirs(start, end_of_exec, tools);
		if (!ret)
			return (NULL);
	}
	if (!ret)
		ret = parseargv(start, end_of_exec, tools);
	return (ret);
}

struct cmd	*parse_redirs(char *start, char *end_of_exec, t_tools *tools)
{
	int			fd_in_or_out;
	int			mode;
	struct cmd	*ret;

	ret = NULL;
	while (*start && start < end_of_exec)
	{
		mode = 0;
		fd_in_or_out = -1;
		if (isquote(*start))
			start += skip_quotes(start, 0);
		if (isredir(*start))
		{
			fd_in_or_out = infile_or_outfile(start);
			mode = check_file_type(start, fd_in_or_out, tools); // TODO !!!
			if (!mode)
				return (NULL);
			if (start[1] == start[0])
				start++;
			createredir(++start, mode, fd_in_or_out, tools);
			if (!ret)
				ret = (struct cmd *)tools->lastredir;
		}
		start++;
	}
	parseargv(tools->s, end_of_exec, tools);
	tools->lastredir = NULL;
	return ((struct cmd *)ret);
}

/* allocates a filename/path: must be freed */
char	*get_redir_path(char *redir, t_tools *tools)
{
	int		i;
	char	*filename;
	int		start;

	i = 0;
	while (redir[i] && isredir(redir[i]))
	{
		i++;
	}
	start = i;
	while (redir[i] && !ft_isspace(redir[i]))
	{
		if (isquote(redir[i]))
			i = skip_quotes(redir, i);
		i++;
	}
	filename = ft_substr(redir, start, i);
	if (!filename)
		error_exit(tools, 1);
	strip_quotes_final(filename);
	return (filename);
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
		error_exit(tools, 1);
	return ((struct cmd *)tools->lastredir);
}

/* parseexex() > (peek redir) > parse_redirs > parse_exec > connect things */
