/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:01:24 by njeanbou          #+#    #+#             */
/*   Updated: 2024/06/14 15:32:50 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	error_heredoc(char **input)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (input[i] != NULL)
	{
		if (input[i][0] == '|')
		{
			if (nb > 1)
				return (1);
			nb = 0;
		}
		if (ft_strequal(input[i], "<<") == 0)
			nb++;
		i++;
	}
	if (nb > 1)
		return (1);
	return (0);
}

static int error_red(char **input)
{
	int	i;

	i = 0;
	while (input[i] != NULL)
	{
		if (input[i][0] == '<' || input[i][0] == '>' || input[i][0] == '|')
		{
			if (input[i + 1] == NULL)
				return (1);
			if (input[i + 1][0] == '<' || input[i + 1][0] == '>'
				|| input[i + 1][0] == '|')
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_error(char **input, bool for_free)
{
	int	res;

	if (input == NULL || !input[0])
		res = 3;
	else if (input[0][0] == '<' || input[0][0] == '>' || input[0][0] == '|')
		res = 1;
	else if (error_heredoc(input) == 1)
		res = 4;
	else
		res = error_red(input);
	if (for_free == true && res != 3)
		ft_free_tab(input);
	return (res);
}

void	print_error(int error)
{
	if (error == 1)
		printf("minishell: syntax error near unexpected token\n");
	if (error == 3)
		printf("minishell: unclosed quote\n");
	if (error == 4)
		printf("minishell: two heredoc\n");
}
