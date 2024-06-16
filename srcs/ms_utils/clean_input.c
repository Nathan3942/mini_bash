/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:00:51 by njeanbou          #+#    #+#             */
/*   Updated: 2024/06/14 15:59:41 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*clean_input(char *raw_input)
{
	char	*input;
	int		beg;
	int		len;

	if (raw_input == NULL || raw_input[0] == '\0')
		return (NULL);
	len = ft_strlen(raw_input);
	beg = 0;
	while (raw_input[beg] == ' ' || raw_input[beg] == '\t')
		beg++;
	if (raw_input[beg] == '\0')
		return (NULL);
	while (len > beg && (raw_input[len - 1] == ' '
			|| raw_input[len - 1] == '\t'))
		len--;
	input = (char *)malloc((len - beg + 1) * sizeof(char));
	if (!input)
		return (NULL);
	ft_strncpy(input, raw_input + beg, len - beg);
	return (input);
}
