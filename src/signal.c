/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:30:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/09/09 21:31:06 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handler_sig_int(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		exit_status = 130;
		rl_redisplay();
	}
}
void	handler_sig_quit(int sig)
{
	if (sig == SIGQUIT)
	{
		exit_status = 131;
		rl_on_new_line();
		rl_redisplay();
	}
}
int	exit_func(void)
{
	return (EXIT_SUCCESS);
}

void	init_signals(void)
{
	rl_event_hook = exit_func;
	signal(SIGINT, handler_sig_int);
	signal(SIGQUIT, handler_sig_quit);
}
