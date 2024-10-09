/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseredirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 19:16:34 by myakoven          #+#    #+#             */
/*   Updated: 2024/10/09 17:47:52 by myakoven         ###   ########.fr       */
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
static int	infile_or_outfile(char *start);

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
	// 	tools->lastredir->cmd = parseargv(start, end_of_exec, tools);
	// this is seg
	// tools->lastredir = NULL;
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
static int	infile_or_outfile(char *start)
{
	if (*start == '<')
		return (0);
	else if (*start == '>')
		return (1);
	return (-1);
}

int	check_file_type(char *start, int fd_in_or_out, t_tools *tools)
{
	if (start)
	if (fd_in_or_out == 1)
	{
		if (file_dir_noexist())
		return (O_WRONLY | O_CREAT | O_TRUNC);
		return (O_WRONLY | O_CREAT | O_APPEND);
	}
}

/* 
Function to check if a path is a file or directory 
File: 1
Dir: 2
none: 0
*/
int	file_dir_noexist(const char *path, int redirtype, t_tools *tools)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
	{
		perror("msh");
		// if (errno == ENOENT) {
		//     print_error(path, does not exist\n", path);
		// } else if (errno == EACCES) {
		//     fprintf(stderr, "Error: Permission denied for %s\n", path);
		// } else {
		//     fprintf(stderr, "Error: Unable to access %s\n", path);
		// }
		return (0); // Indicate failure
	}
	if (S_ISREG(path_stat.st_mode))
	{
		// printf("%s is a file\n", path);
		return 1;
	}
	else if (S_ISDIR(path_stat.st_mode))
	{
		// printf("%s is a directory\n", path);
		return (2)
	}
	else
	{
		printf("%s is neither a file nor a directory\n", path);
		return (0);
			// Indicate failure for non-regular files and non-directories
	}
	// return (-1); // Indicate nonesense
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
	// if (!tools->tree)
	// 	tools->tree = (struct cmd *)tools->lastredir;
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
