/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 20:51:01 by myakoven          #+#    #+#             */
/*   Updated: 2024/10/08 18:34:56 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

volatile sig_atomic_t	global_signal = 0;

int	main(int argc, char **argv, char **env)
{
	t_tools				tools;
	struct sigaction	sa;

	if (argc > 1 || argv[1])
		ft_putstr_fd("This program does not accept arguments\n", 2);
	ft_memset(&tools, 0, sizeof(t_tools)); // init tools to zero
	tools.env = copy_env(&tools, env);
	if (!tools.env)
		return (error_exit(&tools, 1));
	init_sa(&sa);
	shell_loop(&tools);
	print_tab(tools.env);
	clear_history();
	return (0);
}

int	shell_loop(t_tools *tools)
{
	while (1)
	{
		if (global_signal == SIGTERM) // TODO? or done
			break ;
		reset_tools(tools);
		tools->line = readline("minishell: ");
		checkexit(tools); // We have to make our own exit builtin?
		global_signal = 0;
		if (!valid_line(tools->line))
			continue ;
		add_history(tools->line);
		if (!valid_quotes(tools->line) || !valid_redirects(tools->line))
			continue ;
		tools->cleanline = clean_line(tools->line, ft_strlen(tools->line),
				tools);
		if (!tools->cleanline)
			continue ;
		if (!parseline(tools->cleanline, tools))
			continue ;
		ft_putstr_fd(tools->cleanline, 1); // testing
		ft_putstr_fd("\n", 1);             // testing
		walking(tools->tree, 0);
		// execution(tools->tree, tools);
		if (global_signal == SIGTERM) // TODO? or done
			break ;
	}
	clean_tools(tools);
	return (0);
}

// check the entire line for quotes with 0 returns if its not valid and 1 if it is
int	valid_quotes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (isquote(line[i]))
		{
			if (!check_quotes(line, i))
				return (0);
			i = skip_quotes(line, i);
		}
		i++;
	}
	return (1);
}

// CHECK IF THIS SHOULD BE A BUILTIN??? TODO TO DO
/* Liretally checks if exit was typed into the line as the first command */
void	checkexit(t_tools *tools)
{
	if (!tools->line || (!strncmp(tools->line, "exit", 4)
			&& (ft_isspace(tools->line[5]) || tools->line[5] == 0)))
		error_exit(tools, 0);
}

void	new_line(void)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_signals(int sig)
{
	if (sig == SIGINT)
	{
		new_line();
		global_signal = SIGINT;
	}
	else if (sig == SIGTERM)
		global_signal = SIGTERM;
}

void	init_sa(struct sigaction *sa)
{
	sa->sa_handler = handle_signals;
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = 0;
	if (sigaction(SIGINT, sa, NULL) == -1)
	{
		global_signal = SIGINT;
		perror("sigaction");
		exit(1);
	}
}
