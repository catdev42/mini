/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:22:37 by myakoven          #+#    #+#             */
/*   Updated: 2024/10/09 22:54:02 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

/*
This description is wrong.
Input NULL or errline and/or errarg.
If errline is provided, an error is printed to the screen,
is errarg is provided, it is appended to the error string*/
int	print_error(const char *arg, const char *errline, const char *errarg)
{
	ft_putstr_fd("msh: ", 2);
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
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

/*
FOR EXITING!
0: CTRL D or EXIT SUCCESS
1: malloc
3: just exit(1) nothing printed
*/
int	error_exit(t_tools *tools, int error)
{
	clean_tools(tools);
	clear_history();
	if (error == 0)
		exit(0);
	else if (error == 1)
	{
		perror("msh:");
		exit(1);
	}
	else if (error == 2)
		exit(1);
	return (1);
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
