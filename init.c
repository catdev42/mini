/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 21:35:52 by myakoven          #+#    #+#             */
/*   Updated: 2024/10/01 14:55:30 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// TODO
void	init_tools(t_tools *tools)
{
	ft_memset(tools, 0, sizeof(t_tools));
	// tools->line = NULL;
	// tools->cleanline
	// tools->env = NULL;
	// tools->env_len = 0;
	// tools->lexed = NULL;
	// tools->lex_len = 0;
	// tools->num_pipes = 0;
	// tools->parsed_commands = NULL;
}

/* must clean tools first */
void	reset_tools(t_tools *tools)
{
	free(tools->line);
	tools->line = NULL;

	//TODO
	//TODO
	//TODO
	//TODO
	//TODO

	
	// tools->lexed = NULL;
	// tools->lex_len = 0;
	// tools->num_pipes = 0;
}


