/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:01:24 by njeanbou          #+#    #+#             */
/*   Updated: 2024/04/30 10:47:17 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_error(char **input)
{
	int	i;

	i = 0;
	if (input == NULL)
		return (3);
	if (!input[0])
		return (2);
	if (input[0][0] == '<' || input[0][0] == '>' || input[0][0] == '|')
		return (1);
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

void	print_error(int error)
{
	if (error == 1)
		printf("minishell: syntax error near unexpected token\n");
	if (error == 3)
		printf("minishell: unclosed quote\n");
}
