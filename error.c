/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:22:37 by myakoven          #+#    #+#             */
/*   Updated: 2024/10/06 21:33:17 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

/*
This description is wrong.
Input NULL or errline and/or errarg.
If errline is provided, an error is printed to the screen,
is errarg is provided, it is appended to the error string*/
int	print_error(char *errline, char *errarg)
{
	ft_putstr_fd("msh: ", 2);
	// if (name)
	// {
	// 	ft_putstr_fd(errline, 2);
	// 	ft_putstr_fd(" ", 2);
	// }
	if (errline)
	{
		ft_putstr_fd(errline, 2);
		if (errarg)
		{
			// CHECK THIS with ` backticks and single quotes TODO TO DO
			ft_putstr_fd("`", 2);
			ft_putstr_fd(errarg, 2);
			ft_putstr_fd("\'", 2);
			// free(errarg); // this is NOT allocated
		}
		ft_putstr_fd("\n", 2);
	}
	return (0);
}

// int	print_error_errno(void)
// {
// 	// ft_putstr_fd("msh: ", 2);
// 	perror("msh");
// }

/*
1: malloc
2: quotes (changed behavior now, should delete)
3: control_D (changed behavior, should delete)
*/

int	error_exit(t_tools *tools, int error)
{
	clean_tools(tools);
	clear_history();
	if (error == 0)
	{
		exit(1);
	}
	else if (error == 1)
	{
		ft_putstr_fd("minishell: Problem with malloc", 2);
		exit(1);
	}
	else if (error == 2)
	{
		ft_putstr_fd("minishell: Unclosed quotes, please try again", 2);
		exit(1);
	}
	else if (error == 3)
	{
		// ft_putstr_fd("Control D was pressed", 2);
		exit(0);
	}
	return (1);
}
void	clean_tools(t_tools *tools)
{
	if (tools->env)
		ft_freetab(tools->env, INT_MAX);
	if (tools->line)
		free(tools->line);
	if (tools->cleanline)
	{
		ft_bzero(tools->cleanline, tools->cl_capacity);
		free(tools->cleanline);
	}
}

char	**free_array(char **res, int nb)
{
	int	i;

	i = 0;
	if (!res)
		return (NULL);
	while (i <= nb && res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);
	return (NULL);
}
