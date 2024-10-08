/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseredirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 19:16:34 by myakoven          #+#    #+#             */
/*   Updated: 2024/10/08 01:23:28 by myakoven         ###   ########.fr       */
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

struct cmd	*parse_redirs(char *start, char *end_of_exec, t_tools *tools)
{
	int				fd_in_or_out;
	int				mode;
	struct redircmd	*ret;

	ret = NULL;
	while (*start && *start < end_of_exec)
	{
		mode = 0;
		fd_in_or_out = -1;
		if (isquote(*start))
			start += skip_quotes(start, 0);
		if (isredir(*start))
		{	
			fd_in_or_out = infile_or_outfile(start); // TODO !!!
			mode = check_file_type(start, tools);    // TODO !!!
			if (!mode)
				return (NULL);
			if (start[1] == start[0])
				start++;
			createredir(++start, mode, fd_in_or_out, tools); // malloc error exits TODO
			if (!ret)
				ret = tools->lastredir;
		}
		start++;
	}
	return ((struct cmd *)ret);
}

struct cmd	*createredir(char *filestart, int mode, int fd, t_tools *tools)
{
	char	*end;

	end = NULL;
	end = get_token_end(filestart, tools);
	if (tools->lastredir)
	{
		tools->lastredir->cmd = makeredir(filestart, end, mode, fd);
		tools->lastredir = (struct redircmd *)tools->lastredir->cmd;
	}
	else
		tools->lastredir = (struct redircmd *)makeredir(filestart, end, mode,
				fd);
	if (!tools->lastredir)
		error_exit(tools, 1); //EXITS PROGRAM ON OOM ERROR
	if (!tools->tree)
		tools->tree = tools->lastredir;
	return (tools->lastredir);
}

char	*get_token_end(char *namestart, t_tools *tools)
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









// struct cmd	*makeredir(struct cmd *subcmd, char *filename, int mode,
// int fd);

// struct cmd	*getredir(char *redirlocation, t_tools *tools)
// {
// 	int		i;
// 	char	*filename;
// 	int		token;
// 	int		mode;

// 	mode = 0;
// 	i = 0;
// 	token = gettoken(redirlocation);
// 	if (redirlocation[0] == redirlocation[1])
// 		redirlocation++;
// 	redirlocation++;
// 	filename = get_token_end(redirlocation);
// 	// while (redirlocation[i] && !ft_isspace(redirlocation[i]))
// 	// {
// 	// 	if (isquote(redirlocation[i]))
// 	// 		i = skip_quotes(redirlocation, i);
// 	// 	i++;
// 	// }
// 	// filename = ft_substr(redirlocation, 0, i);
// 	if (!filename)
// 		error_exit(tools, 1);
// 	strip_quotes_final(filename);
// 	if (!check_file_type(filename, token, tools))
// 		// returns mode? or just file or dir?
// 		; // ERROR MANAGEMENT
// 	makeredir(NULL, filename, check_file_type(filename, token, tools), );
// 	ft_bspace(redirlocation, i);
// }

// int	gettoken(char *start)
// {
// 	int	i;

// 	i = 0;
// 	if (start[i] == '<' && start[i + 1] == '<')
// 		return (INPUT); // HEREDOC TO DO
// 	else if (start[i] == '<')
// 		return (INPUT);
// 	else if (start[i] == '>' && start[i + 1] == '>')
// 		return (OUTFILE_APPEND);
// 	else if (start[i] == '>')
// 		return (OUTFILE);
// 	return (0)
// }

// struct cmd	*getredir(int token, char *namestart, t_tools *tools)
// {
// 	int i;
// 	char *filename;

// 	i = 0;
// 	while (namestart[i] && !ft_isspace(namestart[i]))
// 	{
// 		if (isquote(namestart[i]))
// 			i = skip_quotes(namestart, i);
// 		i++;
// 	}
// 	filename = ft_substr(namestart, 0, i);
// 	if (!filename)
// 		error_exit(tools, 1);
// 	strip_quotes_final(filename);
// 	if (!check_file_type(filename, token, tools))
// 		;
// 	makeredir(tools->tracktree, filename, O_RDONLY |);
// 	ft_bspace(namestart, i);
// }