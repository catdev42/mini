/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 00:42:37 by myakoven          #+#    #+#             */
/*   Updated: 2024/10/08 18:53:01 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	nullify(char *cline); // FIX THIS TO BE MORE PRECISE MAYBE?

struct cmd	*parseline(char *cline, t_tools *tools)
{
	struct cmd	*left;
	struct cmd	*right;

	tools->s = cline;
	while (peek(tools->s, tools->e_cline, tools, PIPE))
	{
		left = NULL;
		right = NULL;
		tools->cmd_end = peek(tools->s, tools->e_cline, tools, PIPE);
		left = parseexec(tools->s, tools->e_cline, tools);
		if (!left)
			return (NULL);
		// ERROR MANAGEMENT:
		// (print error message in parseexec(),
		// give cursor to user in loop)
		tools->s = tools->cmd_end + 1;
		if (peek(tools->s, tools->e_cline, tools, PIPE))
			right = NULL;
		else
		{
			right = parseexec(tools->s, tools->e_cline, tools);
			if (!right)
				return (clean_execs(left, NULL));
			// ERROR MANAGEMENT:
			// (print error message in parseexec(),
			// give cursor to user in loop)
		}
		createpipe(left, right, tools);
		// pipe creation (exits from there if malloc error)
	}
	if (!tools->tree)
		tools->tree = parseexec(tools->s, tools->e_cline, tools);
	nullify(tools->cleanline); // TODO FIX THIS
	return (tools->tree);
}
void	nullify(char *cline)
{
	int	i;

	i = 0;
	while (cline[i])
	{
		if (isspace(cline[i]))
			cline[i] = 0;
		else
			i = skip_token(cline, i);
		i++;
	}
}

/* Helper for parseline and pipe creation: determines where to attach the pipe */
struct cmd	*createpipe(struct cmd *left, struct cmd *right, t_tools *tools)
{
	if (tools->lastpipe)
	{
		tools->lastpipe->right = makepipe(left, right);
		tools->lastpipe = (struct pipecmd *)tools->lastpipe->right;
	}
	else
		tools->lastpipe = (struct pipecmd *)makepipe(left, right);
	if (!tools->lastpipe)
	{
		clean_execs(left, right);
		error_exit(tools, 1); // EXITS ENTIRE PROGRAM ON ALLOCATION ERROR!
	}
	if (!tools->tree)
		tools->tree = (struct cmd *)tools->lastpipe;
	return ((struct cmd *)tools->lastpipe);
}

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
	else
		tools->lastredir->cmd = parseargv(start, end_of_exec, tools);
	return (ret);
}

char	*peek(char *line, char *end, t_tools *tools, int token)
{
	char	*tokenaddress;
	int		i;
	char	tokenchar;

	tokenaddress = 0;
	i = 0;
	tokenchar = 0;
	if (token == PIPE && tools->line)
	{
		tokenchar = '|';
		i = 0;
		while (line[i]) //&& line[i] != '|')
		{
			if (isquote(line[i]))
				i = skip_quotes(line, i);
			if (line[i] == '|')
			{
				tokenaddress = &line[i];
				break ;
			}
			i++;
		}
	}
	else if (token == REDIR && tools->line)
	{
		i = 0;
		while (line[i] && &line[i] < end) // isredir(line[i]) &&
		{
			if (isquote(line[i]))
				i = skip_quotes(line, i);
			if (isredir(line[i]))
			{
				tokenaddress = &line[i];
				break ;
			}
			i++;
		}
	}
	return (tokenaddress);
}
