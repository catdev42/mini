/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseexec_old.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 19:16:34 by myakoven          #+#    #+#             */
/*   Updated: 2024/10/09 21:59:56 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

// ERROR MANAGEMENT:
// (print error message in parseexec(),
// give cursor to user in loop)

struct s_cmd	*parseexec(char *start, char *end_of_exec, t_tools *tools)
{
	struct s_execcmd	*ecmd;
	struct s_redircmd	*rcmd;
	struct s_cmd		*ret;
	int				i;

	i = 0;
	// ecmd = NULL;
	rcmd = NULL;
	ret = NULL;
	ecmd = makeexec();
	ret = (struct s_cmd *)ecmd;
	tools->tracktree = ecmd;
	// while (peek(&start[i], end_of_exec, tools, REDIR))
	// {
	// 	rcmd = parseredir(&start[i], end_of_exec, tools);
	// TODO (5 redirs, redir 0, 1, 2, etc)
	// 	i++;
	// 	rcmd = NULL;
	// }
	while (1)
	{
		if (istoken(start[i]))
		{
			if (start[i] == '<' && start[i + 1] == '<')
				; // HEREDOC TO DO
			else if (start[i] == '<')
				tools->tracktree = getredir(INPUT, &start[i + 1], tools);
			else if (start[i] == '>' && start[i + 1] == '>')
				tools->tracktree = getredir(OUTFILE_APPEND, &start[i + 1],
						tools);
			else if (start[i] == '>')
				tools->tracktree = getredir(OUTFILE, &start[i + 1], tools);
			else if (start[i] == '|' || start[i] == 0)
				break ;
			if (!tools->tracktree)
				return (0)
		}
		i++;
	}
	getexecargv(start, end_of_exec, tools);
	return (ret);
}


struct s_cmd	*getredir(int token, char *namestart, t_tools *tools)
{
	int		i;
	char	*filename;

	i = 0;
	while (namestart[i] && !ft_isspace(namestart[i]))
	{
		if (isquote(namestart[i]))
			i = skip_quotes(namestart, i);
		i++;
	}
	filename = ft_substr(namestart, 0, i);
	if (!filename)
		error_exit(tools, 1);
	strip_quotes_final(filename);
	if (!check_file_type(filename, token, tools))
		;
	makeredir(tools->tracktree, filename, O_RDONLY |);
	ft_bspace(namestart, i);
}

// Function to check if a path is a file or directory
int	check_file_type(const char *path, int redirtype, t_tools *tools)
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
		printf("%s is a file\n", path);
	}
	else if (S_ISDIR(path_stat.st_mode))
	{
		printf("%s is a directory\n", path);
	}
	else
	{
		printf("%s is neither a file nor a directory\n", path);
		return (0);
			// Indicate failure for non-regular files and non-directories
	}
	return (1); // Indicate success
}

struct s_cmd	*parseredir(char *start, char *end_of_exec, t_tools *tools)
{
	struct s_redircmd	*rcmd;
	int				i;
	int				term;
	int				j;

	term = 0;
	i = 0;
	while (start[i] != '<' || start[i] != '>')
		i++;
	if (start[i] == '<')
	{
		j = 0;
		while (start[i + j])
		{
			if (start[i + j] == '\'' || start[i + j] == '"')
				j = skip_quotes(start, i + j) - i;
			if (ft_isspace(start[i + j]))
				break ;
			j++;
		}
		term = i + j;
		// TODO HEREDOC
		// TODO CHECK FOR DIRECTORY
		// DO NOT DELETE THIS NOTE
		// if (start[i + 1] == '<')
		// 	; /*TODO HEREDOC*/
		// else
		// struct cmd * makeredir(struct cmd *subcmd, char *file,
		// char *efile, int mode, int fd)
		rcmd = (struct s_redircmd *)(makeredir(NULL, &start[++i], &start[term],
					O_WRONLY | O_TRUNC | O_CREAT, 0));
	}
}
