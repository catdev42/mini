/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseredirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 19:16:34 by myakoven          #+#    #+#             */
/*   Updated: 2024/10/09 23:07:03 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

struct s_cmd	*parseexec(char *start, char *end_of_exec, t_tools *tools)
{
	struct s_cmd	*ret;

	ret = NULL;
	if (peek(start, end_of_exec, REDIR))
	{
		ret = parse_redirs(start, end_of_exec, tools);
		if (!ret)
			return (NULL);
	}
	if (!ret)
		ret = parseargv(start, end_of_exec, tools);
	return (ret);
}

struct s_cmd	*parse_redirs(char *start, char *end_of_exec, t_tools *tools)
{
	int				fd_in_or_out;
	int				mode;
	struct s_cmd	*ret;

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
				ret = (struct s_cmd *)tools->lastredir;
		}
		start++;
	}
	parseargv(tools->s, end_of_exec, tools);
	tools->lastredir = NULL;
	return ((struct s_cmd *)ret);
}

/* Return the Mode necessary for opening the file or directory */
int	check_file_type(char *start, int fd_in_or_out, t_tools *tools)
{
	char	*filepath;
	int		fileordir;

	if (!start || fd_in_or_out < 0)
		return (0);
	filepath = get_redir_path(start, tools);
	// printf("\n %s \n", filepath);
	fileordir = file_dir_noexist(filepath, fd_in_or_out);
	if (start[0] == '>' && fileordir == 2)
		print_error(filepath, "Is a directory", NULL);
	free(filepath);
	if (fileordir == 0)
		return (0);
	if (fileordir == 1 && start[0] == '>' && start[1] == '>')
		return (O_WRONLY | O_CREAT | O_APPEND);
	else if (fileordir == 1 && start[0] == '>')
		return (O_WRONLY | O_CREAT | O_TRUNC);
	// else if (start[0] == '<' &&start[1] == '<')
	// 		; //HEREDOC?
	else if (fileordir == 1 && start[0] == '<')
		return (O_RDONLY);
	else if (fileordir == 2 && start[0] == '<')
		return (O_RDONLY | O_DIRECTORY);
	return (0);
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

struct s_cmd	*createredir(char *filestart, int mode, int fd, t_tools *tools)
{
	char	*end;

	end = NULL;
	end = get_token_end(filestart);
	if (tools->lastredir)
	{
		tools->lastredir->cmd = makeredir(filestart, end, mode, fd);
		tools->lastredir = (struct s_redircmd *)tools->lastredir->cmd;
	}
	else
		tools->lastredir = (struct s_redircmd *)makeredir(filestart, end, mode,
				fd);
	if (!tools->lastredir)
		error_exit(tools, 1);
	return ((struct s_cmd *)tools->lastredir);
}

/* parseexex() > (peek redir) > parse_redirs > parse_exec > connect things */
