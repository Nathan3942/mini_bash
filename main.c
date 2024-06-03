/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:52:31 by njeanbou          #+#    #+#             */
/*   Updated: 2024/06/03 19:29:31 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*get_input()
{
	char	*raw_input;
	char	*input;

	raw_input = readline("minishell$ ");
	input = clean_input(raw_input);
	free(raw_input);
	return (input);
}

void	init_data(t_params **para, t_put **put, t_data **data)
{
	*para = (t_params *)malloc (sizeof(t_params));
	*put = (t_put *) malloc (sizeof(t_put));
	*data = NULL;
    *data = malloc(sizeof(t_data));
	(*put)->input = NULL;
	(*put)->output = NULL;
}

void	loop_shell(t_params *para, t_env *lstenv, t_put *put, t_data *data)
{
	int	error;
	char *input;

	while (1)
	{
		input = NULL;
		input = get_input();
		if (input != NULL)
		{
			init_data(&para, &put, &data);
			add_history(input);
			error = set_para(&para, input, &lstenv, &put);
			if (error == 0 && para->com[0] != NULL)
			{
				print_all(&para, &lstenv, &put);
				add_var_status(&lstenv, ms_exec_loop(data, para, put, &lstenv));
			}
			else
				print_error(error);
			if (ft_strequal(para->com[0], "exit") == 0 && printf("exit\n"))
				ms_exit(para, put, &lstenv, &data);
			free_all(&para, &put, &data);
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_params	*para;
	t_env		*lstenv;
	t_put		*put;
	t_data		*data;
	char		*input;

	if (argc > 1 && argv[1] == NULL)
		exit(EXIT_FAILURE);
	lstenv = set_env(env);
	loop_shell(para, lstenv, put, data);
	return (0);
}
