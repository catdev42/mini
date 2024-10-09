/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 20:12:04 by myakoven          #+#    #+#             */
/*   Updated: 2024/10/09 21:50:09 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
/* Keep on top */
# include <readline/history.h>
# include <readline/readline.h>
/* Keep on top */
# include "../libft/libft.h"
# include "builtins.h"
# include "structs.h"
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <unistd.h>

# define UNEXP "syntax error near unexpected token "
# define UNCLOSED "unclosed quotes "

// volatile sig_atomic_t	global_signal = 0;

void		walking(struct cmd *cmd);
/************************/
/******** main.c ********/
/************************/
int			shell_loop(t_tools *tools);
void		new_line(void);
void		handle_signals(int sig);
void		init_sa(struct sigaction *sa);
void		checkexit(t_tools *tools);

/************************/
/******* init.c ********/
/************************/
// void		init_tools(t_tools *tools);

/************************/
/*******  env.c  ********/
/************************/
char		**copy_env(t_tools *tools, char **env);
char		*get_var(char **env, char *var);
// char	*get_env_var(t_tools *tools, char *var);

/************************/
/******* syntax.c ********/
/************************/
int			valid_quotes(char *line);
int			valid_redirects(char *line);

/************************/
/******** line.c ********/
/************************/
int			copy_quotes(char *c_line, char *line, t_tools *tools);
int			copy_pipe(char *c_line, char *line, int current_line_index);
int			copy_redirect(char *c_line, char *line, int current_line_index);
char		*clean_line(char *line, int linelen, t_tools *tools);
int			copy_spaces(char *c_line, char *line);

/******** line_utils.c ********/
int			copy_var(char *c_line, char *line, t_tools *tools);
void		remove_useless_quotes(char *cline);
int			remove_two(char *first, char *second);

/************************/
/******* parseline.c ********/
/************************/
struct cmd	*parseline(char *cline, t_tools *tools);
// struct cmd	*decide_pipe_right(t_tools *tools);
char		*peek(char *line, char *end, t_tools *tools, int token);
struct cmd	*parseexec(char *start, char *end_of_exec, t_tools *tools);
struct cmd	*createpipe(struct cmd *left, struct cmd *right, t_tools *tools);

struct cmd	*parse_redirs(char *start, char *end_of_exec, t_tools *tools);
struct cmd	*createredir(char *filestart, int mode, int fd, t_tools *tools);
char		*get_token_end(char *namestart);
char		*get_redir_path(char *redir, t_tools *tools);

struct cmd	*parseargv(char *start, char *end, t_tools *tools);
int			skip_token(char *start, int i);
/************************/
/****  makestruct.c  ****/
/****** allocation ******/
struct cmd	*makeexec(void);
struct cmd	*makeredir(char *file, char *efile, int mode, int fd);
// struct cmd	*makeredir(struct cmd *subcmd, char *filename, int mode,
// int fd);
// struct cmd	*makeredir(struct cmd *subcmd, char *file, char *efile,
// int mode, int fd);
struct cmd	*makepipe(struct cmd *left, struct cmd *right);

/************************/
/******* utils.c ********/
/************************/
int			print_tab(char **envp);
int			valid_line(char *line);
int			istoken(char c);
int			isquote(char c);
int			isredir(char c);
// int		skip_spaces(char *s);
// void		ft_bspace(void *s, size_t n);

/******* utils2.c ********/
int			get_matrix_len(char **matrix);
char		*safe_calloc(size_t nmemb, size_t size, t_tools *tools);
void		init_zero(size_t *i, size_t *j, char *c, char **c_line);
void		strip_quotes_final(char *start);
char		*get_token_end(char *namestart);

/******* utils3.c ********/
int			check_quotes(char *line, int i);
int			skip_quotes(char *line, int i);
int			infile_or_outfile(char *start);
int			check_file_type(char *start, int fd_in_or_out, t_tools *tools);
int			file_dir_noexist(const char *path);
/************************/
/******* error.c ********/
/************************/
int			error_exit(t_tools *tools, int error);
void		clean_tools(t_tools *tools);
char		**free_array(char **res, int nb);
int			print_error(const char *arg, const char *errline,
				const char *errarg);

/************************/
/******* cleaning.c ********/
/************************/
struct cmd	*clean_execs(struct cmd *first, struct cmd *second);
void		reset_tools(t_tools *tools);

/************************/
/******* built_ins.c ********/
/************************/
// void	pwd(t_tools *tools, cmd_t *cmd); //TODO
// void	pwd(t_tools *tools);

// int		check_quotes(char *line, int i);
// char	*get_redir_error(char *line, int i, int goodtokens);
// int		check_redirects(t_tools *tools);
#endif