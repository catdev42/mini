/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 20:17:05 by myakoven          #+#    #+#             */
/*   Updated: 2024/08/28 22:00:24 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(t_tools *tools)
{
	int		i;
	char	**lexed;
	int		comm_index;
	int		num_words;

	comm_index = 0;
	lexed = tools->lexed;
	/*EXPANDS THE VARIABLES IN EACH LINE*/
	i = 0;
	while (lexed[i])
	{
		while (ft_strchr(lexed[i], '$'))
			if (!expand_command(&lexed[i], tools))
				error_exit(tools, 1);
		i++;
	}
	/*ALLOCATE THE ARRAY OF COMMAND STRUCTS*/
	tools->parsed_commands = (t_parsed *)ft_calloc((tools->num_pipes + 1),
			sizeof(t_parsed *));
	tools->parsed_commands[tools->num_pipes + 1] = NULL;
	i = 0;
	return (1);
}

int	write_command_matrix(t_tools *tools, int command_index)
{
	char	*line;
	int		i;
	int		count;
	int		lexed_index;
	int		count_r;

	line = NULL;
	i = 0;
	lexed_index = 0;
	while (i < (tools->num_pipes + 1))
	{
		count_r = count_redirects(tools, i);
		tools->parsed_commands[i]->redir_tokens = (t_token *)(count_r + 1,
				sizeof(t_token));
		lexed_index = make_full_line(tools, i, lexed_index);
		line = tools->parsed_commands[i]->line;
		count = count_arguments(line);
		create_argv(tools, line, i);
		print_tab(tools->parsed_commands[i]->argv);
		if (!tools->lexed[lexed_index])
			break ;
		i++;
	}
}

char	*make_full_line(t_tools *tools, int c_index, int lexed_index)
{
	int		i;
	char	*command;
	char	*old_command;

	command = NULL;
	old_command = NULL;
	i = lexed_index;
	while (tools->lexed[i] && tools->lexed[i][0] != '|')
	{
		while (tools->lexed[i] && (!tools->lexed[i][0]))
			i++;
		if (istoken(tools->lexed[i][0]))
		{
			if (tools->lexed[i][0] == "|")
				break ;
			else
				/*should record the redirect into redirect array?*/
				handle_redirect(tools, c_index, i);
		}
		else if (!istoken(tools->lexed[i][0]))
		{
			command = ft_strjoin(command, tools->lexed[i]);
			if (command == NULL)
				error_exit(tools, 1);
			ft_bzero(tools->lexed[i], ft_strlen(tools->lexed[i]));
			if (old_command)
				free(old_command);
			old_command = command;
		}
		if (tools->lexed[i][0] != '|')
			i++;
	}
	tools->parsed_commands[c_index]->line = command;
	// keep pipes until redirects are recorded as well
	// ft_bzero(tools->lexed[i], ft_strlen(tools->lexed[i]));
	return (i + 1);
}

int	count_arguments(char *line)
{
	int		count;
	int		i;
	int		in_quotes;
	char	quote_char;

	count = 0;
	i = 0;
	in_quotes = 0;
	quote_char = '\0';
	while (line[i])
	{
		while (isspace(line[i]))
			i++;
		if (line[i] == '\0')
			break ;
		count++;
		while (line[i] && (!isspace(line[i]) || in_quotes))
		{
			if ((line[i] == '"' || line[i] == '\'') && !in_quotes)
			{
				in_quotes = 1;
				quote_char = line[i];
			}
			else if (line[i] == quote_char && in_quotes)
			{
				in_quotes = 0;
				quote_char = '\0';
			}
			i++;
		}
	}
	return (count);
}

char	**create_argv(t_tools *tools, char *line, int c_index)
{
	int		i;
	int		j;
	int		k;
	int		in_quotes;
	char	quote_char;

	i = 0;
	j = 0;
	k = 0;
	in_quotes = 0;
	quote_char = '\0';
	tools->parsed_commands[c_index]->argc = count_arguments(line);
	tools->parsed_commands[c_index]->argv = ft_calloc((tools->parsed_commands[c_index]->argc
				+ 1), sizeof(char *));
	while (line[i])
	{
		while (isspace(line[i]))
			i++;
		if (line[i] == '\0')
			break ;
		j = i;
		while (line[i] && (!isspace(line[i]) || in_quotes))
		{
			if ((line[i] == '"' || line[i] == '\'') && !in_quotes)
			{
				in_quotes = 1;
				quote_char = line[i];
			}
			else if (line[i] == quote_char && in_quotes)
			{
				in_quotes = 0;
				quote_char = '\0';
			}
			i++;
		}
		tools->parsed_commands[c_index]->argv[k] = strndup(&line[j], i - j);
		k++;
	}
	tools->parsed_commands[c_index]->argv[k] = NULL;
	return (tools->parsed_commands[c_index]->argv);
}

// DON'T NEED?

// char	**quotes_split(line)
// {
// 	int	i;
// char **matrix;
// 	i = 0;
// 	if (line[i] == "\"" || line[i] == "\'")

// }
// int	write_command_matrix(t_tools *tools)
// {
// }

// count words
// while (line[i])
// {
// 	while (ft_isspace())
// 		i++;
// 	if (line[i] == "\"" || line[i] == "\'")
// 	{
// 		i = check_quotes(line, i);
// 		count++;
// 	}
// }

// /* cleans the first spaces of a command and puts 0's at the end;
// returns 1 on sucess */
// int	spaces_cleanup(t_tools *tools)
// {
// 	int		i;
// 	int		j;
// 	int		len;
// 	char	**matrix;

// 	matrix = tools->lexed;
// 	i = 0;
// 	while (matrix[i])
// 	{
// 		j = 0;
// 		len = ft_strlen(matrix[i]);
// 		while (matrix[i][j])
// 		{
// 			if (matrix[i][j] == "\"")
// 				while ((matrix[i][j]) == "\"" && (matrix[i][j]) == "\"")
// 					j += 2;
// 			// j = 0;
// 			if (ft_isspace(matrix[i][j]))
// 				while (ft_isspace(matrix[i][j++]))
// 					;
// 			if (!ft_strlen(matrix[i]))
// 				break ;
// 		}
// 		if (j > 0)
// 		{
// 			ft_memmove(&matrix[i][0], &matrix[i][j], len - j);
// 			j = len - j;
// 			while (j < len)
// 				matrix[i][j++] = 0;
// 		}
// 		i++;
// 	}
// 	return (1);
// }
