/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptit_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:02:34 by ichpakov          #+#    #+#             */
/*   Updated: 2024/06/11 15:07:39 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_exec(t_params *cmds, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = cmds->com;
	path = get_path(s_cmd[0], env);
	execve(path, s_cmd, env);
	ft_putstr_fd("error: command not found: ", 2);
	ft_putendl_fd(s_cmd[0], 2);
	exit(0);
}


static int	ms_redir_exec(t_data *data, t_params *cmds, t_put *puts, t_env **env)
{
	int		status;

 	if (cmds->inp_red == entre1 || cmds->inp_red == entre2)
 		ms_input(data, puts);
 	if (cmds->out_red == PIPE)
 	{
 		if (pipe(data->p_fd) == -1)
 			return (exec_error(0));
 	}
 	data->pid = fork();
 	if (data->pid == 0)
 	{
 		if (cmds->out_red == PIPE)
 		{
 			if ((dup2(data->p_fd[1], STDOUT_FILENO) == -1 || close(data->p_fd[0]) == -1
				|| close(data->p_fd[1]) == -1))
                return(exec_error(0));
 		}
 		else if (cmds->out_red == sortie1)
 			ms_output(data, puts, 1);
 		else if (cmds->out_red == sortie2)
 			ms_output(data, puts, 2);
		ms_exec_class(cmds, env, &data);
 		exec_error(2);
 	}
	waitpid(data->pid, &status, 0);
	if (cmds->out_red == PIPE)
 	{
 		if (dup2(data->p_fd[0], STDIN_FILENO) == -1 || close(data->p_fd[0]) == -1
				|| close(data->p_fd[1]) == -1)
 			return (exec_error(0));
 	}
	return (WIFEXITED(status) && WEXITSTATUS(status));
}

static void	supp_heredoc(t_data *data, t_env **env, t_put *puts)
{
	char	**rm;
	int		i;

	i = 1;
	rm = malloc (3 * sizeof(char *));
	rm[0] = "rm";
	rm[1] = puts->input;
	rm[2] = NULL;
	data->pid = fork();
	if (data->pid == 0)
		execve(get_path("rm", get_env(env)), rm, get_env(env));
	else
		waitpid(data->pid, 0, 0);
	free(rm);
}

int	ms_exec_loop(t_data *data, t_params *cmds, t_put *puts, t_env **env)
{
	t_params	*t_cmds;
	int			status;
	int			saved_stdin;

	saved_stdin = dup(STDIN_FILENO);
	t_cmds = cmds;
	while (t_cmds != NULL)
	{
		status = ms_redir_exec(data, t_cmds, puts, env); //renvoie l'etat du resultat 
		t_cmds = t_cmds->next;
	}
	dup2(saved_stdin, STDIN_FILENO);
	if (cmds->inp_red == entre2)
		supp_heredoc(data, env, puts);
	return (status);
}
