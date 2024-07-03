/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:58:16 by ichpakov          #+#    #+#             */
/*   Updated: 2024/07/02 18:14:25 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void exec_signal(int signal)
{
		if (signal == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}

void handler_signal(int signal)
{
    if (signal == SIGINT)
    {
        ft_putstr_fd("\n", STDOUT_FILENO);
        rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
    }
}