/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 20:26:33 by myakoven          #+#    #+#             */
/*   Updated: 2024/09/04 00:08:13 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "structs.h"

// /************************/
// /******* lexer.c ********/
// /************************/
// int		lexer(t_tools *tools);
// int		getlen_command(t_tools *tools, int i);
// int		getlen_redirect(t_tools *tools, int i);
// int		count_parts(t_tools *tools);

/************************/
/******* lexerchecks.c ********/
/************************/

int		check_quotes(char *line, int i);
char	*get_redir_error(char *line, int i, int goodtokens);
int		check_redirects(t_tools *tools);

#endif