/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 00:42:37 by myakoven          #+#    #+#             */
/*   Updated: 2024/10/02 17:18:16 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

struct cmd	*parseline(char *cline, t_tools *tools)
{
	// int	pipe;
	// pipe = peek(tools, PIPE);
	// if (pipe)
	// 	;
	// return (ret);
	tools->s = cline;
	while (1)
	{
		tools->p = peek(tools->s, tools->e_cline, tools, PIPE);
		if (tools->p)
			decide_pipe_right(tools);
		else
			break ;
		tools->s = tools->p + 1;
		tools->p = NULL;
	}
	parseexec(tools->s, tools->e_cline, tools);
}

/*
Uses tools->s, tools->p and tools->p_next
Returns a pointer to the pipe struct with the left side command parsed
and pointing to the next command parsed or and empty pipe	struct;
*/
struct cmd	*decide_pipe_right(t_tools *tools)
{
	// while ((struct pipecmd *)tools->tree)
	// 	tools->p_next = !peek(tools->p + 1, tools, PIPE);
	if (!peek(tools->p + 1, tools->e_cline, tools, PIPE))
	{
		return (makepipe(parseexec(tools->s, tools->p, tools),
				parseexec(tools->p + 1, tools->e_cline, tools)));
	}
	else
	{
		tools->tracktree = makepipe(NULL, NULL);
		return (makepipe(parseexec(tools->s, tools->p, tools),
				tools->tracktree));
	}
}

struct cmd	*parseexec(char *start, char *end_of_exec, t_tools *tools)
{
	struct execcmd	*ecmd;
	struct redircmd	*rcmd;
	struct cmd		*ret;
	int				i;

	i = 0;
	ecmd = NULL;
	rcmd = NULL;
	ret = NULL;
	ecmd = makeexec();
	if (peek(start, end_of_exec, tools, REDIR))
	{
		rcmd = parseredir(start, end_of_exec, tools); // TODO
		i++;
	}
}

struct cmd	*parseredir(char *start, char *end_of_exec, t_tools *tools)
{
	struct redircmd	rcmd;
	int				i;

	i = 0;
	while (start[i] != '<' || start[i] != '>')
		i++;
	if (start[i] == '<')
	{
		// if (start[i + 1] == '<')
		// 	; /*TODO HEREDOC*/
		// else

		// struct cmd * makeredir(struct cmd *subcmd, char *file, 
		// char *efile, int mode, int fd)
		
		rcmd = makeredir( &start[++i])
	}
}

char	*peek(char *line, char *end, t_tools *tools, int token)
{
	char *tokenaddress;
	int i;
	char tokenchar;

	tokenaddress = 0;
	i = 0;
	tokenchar = 0;
	if (token == PIPE)
	{
		tokenchar = '|';
		i = 0;
		while (line[i] && line[i] != '|')
		{
			if (isquote(line[i]))
				i = skip_quotes(line, i);
			if (line[i] == '|')
			{
				tokenaddress = &line[i];
			}
			i++;
		}
	}
	if (token == REDIR)
	{
		i = 0;
		while (line[i] && isredir(line[i]) && &line[i] < end)
		{
			if (isquote(line[i]))
				i = skip_quotes(line, i);
			if (isredir(line[i]))
				tokenaddress = &line[i];
			i++;
		}
	}

	return (tokenaddress);
}