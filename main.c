/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 20:51:01 by myakoven          #+#    #+#             */
/*   Updated: 2024/09/30 16:05:03 by myakoven         ###   ########.fr       */
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
	init_tools(&tools);
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
		if (tools->line)
			free(tools->line);
		tools->line = readline("minishell: ");
		checkexit(tools);
		global_signal = 0;
		if (valid_line(tools->line))
			add_history(tools->line);
		else
			continue ;
		// if (!validquotes(tools->line, tools))
		// 	continue ;
		tools->cleanline = clean_line(tools->line, ft_strlen(tools->line),
				tools);
		if (!tools->cleanline)
			continue;
		
		// if (!tools->cleanline)
		// 	error_exit(tools, 1);
		ft_putstr_fd(tools->cleanline, 1);
		ft_putstr_fd("\n", 1);
		// if (lexer(tools))
		// {
		// 	printf("%s\n", tools->line);
		// 	print_tab(tools->lexed);
		// 	parser(tools);
		// }
		if (global_signal == SIGTERM) // TODO? or done
			break ;
	}
	clean_tools(tools);
	return (0);
}

// Note: Built this into line.c -> copy_quotes()

// int	validquotes(char *line, t_tools *tools)
// {
// 	int		i;
// 	char	quote_char;

// 	i = 0;
// 	while (line[i])
// 	{
// 		if (isquote(line[i]))
// 		{
// 			quote_char = line[i];
// 			i++;
// 			while (line[i] && line[i] != quote_char)
// 				i++;
// 			if (!line[i])
// 			{
// 				print_error("unclosed quotes, please try again", NULL);
// 				new_line();
// 				return (0);
// 			}
// 		}
// 		else
// 			i++;
// 	}
// 	return (1);
// }

/* Liretally checks if exit was typed into the line as the first command */
int	checkexit(t_tools *tools)
{
	if (!tools->line || (!strncmp(tools->line, "exit", 4)
			&& (ft_isspace(tools->line[5]) || tools->line[5] == 0)))
		error_exit(tools, 3);
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
