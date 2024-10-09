/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseredirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 19:16:34 by myakoven          #+#    #+#             */
/*   Updated: 2024/10/09 23:39:52 by myakoven         ###   ########.fr       */
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
			if (mode == -1)
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
	if (fileordir == 0)
	{
		return (-1);
	}
	if (start[0] == '>' && fileordir == 2)
		print_error(filepath, "Is a directory", NULL);
	free(filepath);
	if (fileordir == 1 && start[0] == '>' && start[1] == '>')
		return (O_WRONLY | O_CREAT | O_APPEND);
	else if (fileordir == 1 && start[0] == '>')
		return (O_WRONLY | O_CREAT | O_TRUNC);
	else if (fileordir == 1 && start[0] == '<')
		return (O_RDONLY);
	else if (fileordir == 2 && start[0] == '<')
		return (O_RDONLY | O_DIRECTORY);
	// printf("NONE OF THE CONDITIONS WERE MET!");
	return (0);
	// else if (start[0] == '<' &&start[1] == '<')
	// 		; //HEREDOC?
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

/* Checks if a path is a file or directory File: 1; Dir: 2; Neither: 0*/
int	file_dir_noexist(const char *path, int fd_in_or_out)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
	{
		if (errno == ENOENT && fd_in_or_out == 1)
			return (1);
		/* this should be checked only with infiles*/
		print_error(path, strerror(errno), NULL);
		return (0);
	}
	if (S_ISREG(path_stat.st_mode))
	{
		return (1);
	}
	else if (S_ISDIR(path_stat.st_mode))
		return (2);
	else
		print_error(path, "Is neither a file nor a directory", NULL);
	return (0);
}

/* parseexex() > (peek redir) > parse_redirs > parse_exec > connect things */
