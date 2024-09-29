/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 20:00:21 by myakoven          #+#    #+#             */
/*   Updated: 2024/09/09 21:09:22 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "minishell.h"

// enum e_tokentype
// {
// 	NONE,
// 	PIPE,
// 	INPUT,
// 	HEREDOC,
// 	OUTFILE,
// 	OUTFILE_APPEND,
// };

/* Type of node */
# define EXEC 1
# define REDIR 2
# define PIPE 3

# define MAXARGS 20

/* one for each command with its own redirects and argc*/
// typedef struct s_parsed_command
// {
// 	char		*line;
// 	int			argc;
// 	char		**argv;
// 	char		**redirects;
// 	t_token		*redir_tokens;
// }				t_parsed;

struct			cmd
{
	int			type;
};

struct			execcmd
{
	int			type;
	char		*argv[20];
	char		*eargv[20];
};

struct			redircmd
{
	int			type;
	// pointer to next thing redir or exec
	struct cmd	*cmd;
	// pointer to filename
	char		*file;
	// pointer to end of the file name for nullify
	char		*efile;
	// 0 for read, 1 for write and truncate, 2 for append?
	int			mode;
	// fd of the opened file?
	int			fd;
};

struct			pipecmd
{
	int			type;
	// execute first
	struct cmd	*left;
	// pipe into - this can also become the next pipe's left side
	struct cmd	*right;
};

typedef struct s_tools
{
	int			env_len;
	char		**env;
	
	char		*line;
	
	char 		*cleanline;
	int 		cl_len;
	// char		**lexed;
	// int			lex_len;
	int			num_pipes;
	// t_parsed	**parsed_commands;
}				t_tools;

// typedef struct line_saver
// {
// 	char	**line_pointers;
// 	int		*line_lengths;
// }

#endif