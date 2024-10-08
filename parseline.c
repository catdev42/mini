/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 00:42:37 by myakoven          #+#    #+#             */
/*   Updated: 2024/10/08 01:19:14 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

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
	return (tools->tree);
}

/* Helper for parseline and pipe creation: determines where to attach the pipe */
struct cmd	*createpipe(struct cmd *left, struct cmd *right, t_tools *tools)
{
	if (tools->lastpipe)
	{
		tools->lastpipe->right = makepipe(left, right);
		tools->lastpipe = (struct pcmd *)tools->lastpipe->right;
	}
	else
		tools->lastpipe = (struct pcmd *)makepipe(left, right);
	if (!tools->lastpipe)
	{
		clean_execs(left, right);
		error_exit(tools, 1); // EXITS ENTIRE PROGRAM ON ALLOCATION ERROR!
	}
	if (!tools->tree)
		tools->tree = tools->lastpipe;
	return (tools->lastpipe);
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
		ret = getexec(start, end_of_exec, tools);
	else
		tools->lastredir->cmd = getexec(start, end_of_exec, tools);
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




// struct cmd	*parseline(char *cline, t_tools *tools)
// {
// 	struct cmd	*left;
// 	struct cmd	*right;

// 	tools->s = cline;
// 	while (peek(tools->s, tools->e_cline, tools, PIPE))
// 	{
// 		left = NULL;
// 		right = NULL;
// 		tools->cmd_end = peek(tools->s, tools->e_cline, tools, PIPE);
// 		left = parseexec(tools->s, tools->e_cline, tools);
// 		tools->s = tools->cmd_end + 1;
// 		if (peek(tools->s, tools->e_cline, tools, PIPE))
// 		{
// 			right = NULL;
// 			if (!tools->lastpipe)
// 				tools->lastpipe = (struct pcmd *)makepipe(left, NULL);
// 			else if (tools->lastpipe)
// 				tools->lastpipe->right = makepipe(left, NULL);
// 		}
// 		else
// 		{
// 			right = parseexec(tools->s, tools->e_cline, tools);
// 			if (tools->lastpipe)
// 			{
// 				tools->lastpipe->right = makepipe(left, right);
// 				tools->lastpipe = tools->lastpipe->right;
// 			}
// 			else
// 				tools->lastpipe = makepipe(left, right);
// 		}
// 		if (tools->tree)
// 			tools->tree = tools->lastpipe;
// 	}
// 	if (!tools->tree)
// 		tools->tree = parseexec(tools->s, tools->e_cline, tools);
// 	return (tools->tree);
// }

/*
// Uses tools->s, tools->p and tools->p_next
// Returns a pointer to the pipe struct with the left side command parsed
// and pointing to the next command parsed or and empty pipe	struct;
// */
// struct cmd	*decide_pipe_right(t_tools *tools)
// {
// 	struct execcmd	*ecmdLeft;
// 	struct execcmd	*ecmdRight;

// 	// while ((struct pipecmd *)tools->tree)
// 	// 	tools->p_next = !peek(tools->p + 1, tools, PIPE);
// 	if (!peek(tools->p + 1, tools->e_cline, tools, PIPE))
// 	{
// 		ecmdLeft = parseexec(tools->s, tools->p, tools);
// 		if (!ecmdLeft)
// 			return (0);
// 		ecmdLeft = parseexec(tools->p + 1, tools->e_cline, tools);
// 		if (!ecmdRight)
// 		{
// 			cleanexec(ecmdLeft); //TODO
// 			return (0);
// 		}
// 		return (makepipe(ecmdLeft, ecmdRight));
// 	}
// 	else
// 	{
// 		// tools->tracktree = makepipe(NULL, NULL); // CHECK TO DO
// 		return (makepipe(parseexec(tools->s, tools->p, tools), NULL));
// 	}
// }
