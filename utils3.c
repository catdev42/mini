/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 20:33:23 by myakoven          #+#    #+#             */
/*   Updated: 2024/10/09 21:38:26 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

/*
Provide the pointer to line and the index you are currently on
Returns 0 is quotes aren't closed
And Index of second quote if they are closed
*/
int	check_quotes(char *line, int i)
{
	int	j;

	j = 1;
	if (!isquote(line[i]))
		return (i);
	while (line[i + j])
	{
		if (line[i] == line[i + j])
			return (i + j);
		j++;
	}
	print_error(NULL, UNCLOSED, NULL);
	return (0);
}

/*
Returns Index of CLOSING QUOTE if they are closed or END OF LINE
*/
int	skip_quotes(char *line, int i)
{
	int	j;

	j = 1;
	if (!isquote(line[i]))
		return (i);
	while (line[i + j])
	{
		if (line[i] == line[i + j])
			return (i + j);
		j++;
	}
	return (i + j);
}

int	infile_or_outfile(char *start)
{
	if (*start == '<')
		return (0);
	else if (*start == '>')
		return (1);
	return (-1);
}

/* Return the Mode necessary for opening the file or directory */
int	check_file_type(char *start, int fd_in_or_out, t_tools *tools)
{
	char	*filepath;
	int		fileordir;

	if (!start || fd_in_or_out < 0)
		return (0);
	filepath = get_redir_path(start, tools);
	fileordir = file_dir_noexist(filepath);
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

/* Checks if a path is a file or directory File: 1; Dir: 2; Neither: 0*/
int	file_dir_noexist(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
	{
		print_error(path, strerror(errno), NULL);
		return (0);
	}
	if (S_ISREG(path_stat.st_mode))
		return (1);
	else if (S_ISDIR(path_stat.st_mode))
		return (2);
	else
		print_error(path, "Is neither a file nor a directory", NULL);
	return (0);
}
