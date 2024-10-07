/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseexec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 19:16:34 by myakoven          #+#    #+#             */
/*   Updated: 2024/10/07 20:24:21 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

// ERROR MANAGEMENT:
// (print error message in parseexec(),
// give cursor to user in loop)

struct cmd	*parseexec(char *start, char *end_of_exec, t_tools *tools)
{
	char			*curr_redir;
	struct redircmd	*temp_rcmd;
	struct cmd		*ret;

	curr_redir = NULL;
	temp_rcmd = NULL;
	ret = NULL;
	while (peek(start, end_of_exec, tools, REDIR))
	{
		curr_redir = peek(start, end_of_exec, tools, REDIR);
		temp_rcmd = getredir(curr_redir, tools);
		// ERROR MANAGEMENT TODO
		// can this be inside getredir?
		if (tools->lastredir)
		{
			tools->lastredir->cmd = temp_rcmd;
			tools->lastredir = tools->lastredir->cmd;
		}
		else
			tools->lastredir = temp_rcmd;
		if (!ret)
			ret = tools->lastredir;
	}
	if (!ret)
		ret = getexec(start, end_of_exec, tools);
	else
		tools->lastredir->cmd = getexec(start, end_of_exec, tools);
	return (ret);
}

struct cmd	*getredir(char *redirlocation, t_tools *tools)
{
	int		i;
	char	*filename;
	int		token;

	i = 0;
	token = gettoken(redirlocation);
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

int	gettoken(char *start)
{
	int	i;

	i = 0;
	if (start[i] == '<' && start[i + 1] == '<')
		; // HEREDOC TO DO
	else if (start[i] == '<')
		return (INPUT);
	else if (start[i] == '>' && start[i + 1] == '>')
		return (OUTFILE_APPEND);
	else if (start[i] == '>')
		return (OUTFILE);
	return (0)
}

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