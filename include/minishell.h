/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 20:12:04 by myakoven          #+#    #+#             */
/*   Updated: 2024/10/09 22:56:20 by myakoven         ###   ########.fr       */
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

void			walking(struct s_cmd *cmd);

/************************/
/******** main.c ********/
/************************/
int				shell_loop(t_tools *tools);
void			new_line(void);
void			handle_signals(int sig);
void			init_sa(struct sigaction *sa);
void			checkexit(t_tools *tools);

/************************/
/******* init.c ********/
/************************/
struct s_cmd	*makeexec(void);
struct s_cmd	*makeredir(char *file, char *efile, int mode, int fd);
struct s_cmd	*makepipe(struct s_cmd *left, struct s_cmd *right);
// void		init_tools(t_tools *tools);

/************************/
/*******  env.c  ********/
/************************/
char			**copy_env(t_tools *tools, char **env);
char			*get_var(char **env, char *var);
// char	*get_env_var(t_tools *tools, char *var);

/************************/
/******* syntax.c ********/
/************************/
int				valid_quotes(char *line);
int				valid_redirects(char *line);

/************************/
/******** line.c ********/
/************************/
int				copy_quotes(char *c_line, char *line, t_tools *tools);
int				copy_pipe(char *c_line, char *line, int current_line_index);
int				copy_redirect(char *c_line, char *line, int current_line_index);
char			*clean_line(char *line, int linelen, t_tools *tools);
int				copy_spaces(char *c_line, char *line);

/******** line_utils.c ********/
int				copy_var(char *c_line, char *line, t_tools *tools);
void			remove_useless_quotes(char *cline);
int				remove_two(char *first, char *second);

/************************/
/******* parse ********/
/************************/
struct s_cmd	*parseline(char *cline, t_tools *tools);
char			*peek(char *line, char *end, int token);
struct s_cmd	*parseexec(char *start, char *end_of_exec, t_tools *tools);
struct s_cmd	*createpipe(struct s_cmd *left, struct s_cmd *right,
					t_tools *tools);

struct s_cmd	*parse_redirs(char *start, char *end_of_exec, t_tools *tools);
struct s_cmd	*createredir(char *filestart, int mode, int fd, t_tools *tools);
char			*get_redir_path(char *redir, t_tools *tools);

struct s_cmd	*parseargv(char *start, char *end, t_tools *tools);
int				skip_token(char *start, int i);

/************************/
/******* utils.c ********/
/************************/
int				print_tab(char **envp);
int				valid_line(char *line);
int				istoken(char c);
int				isquote(char c);
int				isredir(char c);
/* int		skip_spaces(char *s);
void	ft_bspace(void *s, size_t n); */

/******* utils2.c ********/
int				get_matrix_len(char **matrix);
char			*safe_calloc(size_t nmemb, size_t size, t_tools *tools);
void			init_zero(size_t *i, size_t *j, char *c, char **c_line);
void			strip_quotes_final(char *start);
char			*get_token_end(char *namestart);

/******* UTILS3.C *******/
int				check_quotes(char *line, int i);
int				skip_quotes(char *line, int i);
int				infile_or_outfile(char *start);
int				check_file_type(char *start, int fd_in_or_out, t_tools *tools);
int				file_dir_noexist(const char *path, int fd_in_or_out);

/************************/
/******* ERROR.C ********/
/************************/
int				error_exit(t_tools *tools, int error);
void			clean_tools(t_tools *tools);
char			**free_array(char **res, int nb);
int				print_error(const char *arg, const char *errline,
					const char *errarg);

/************************/
/******* CLEAN.C ********/
/************************/
void			reset_tools(t_tools *tools);
void			clean_tools(t_tools *tools);
struct s_cmd	*clean_execs(struct s_cmd *first, struct s_cmd *second);

void			tree_free(struct s_cmd *node);

#endif

/************************/
/******* built_ins.c ********/
/************************/
// void	pwd(t_tools *tools, cmd_t *cmd); //TODO
// void	pwd(t_tools *tools);

// int		check_quotes(char *line, int i);
// char	*get_redir_error(char *line, int i, int goodtokens);
// int		check_redirects(t_tools *tools);
