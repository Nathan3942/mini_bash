/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:31:24 by ichpakov          #+#    #+#             */
/*   Updated: 2024/05/28 14:21:27 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* close_file
*   ferme un fichier seulement si il existe.
*/
void	close_file(int fd)
{
	if (fd > 0)
		close(fd);
}

/* open_file :
*   prends un fichier et sa nature en parametre.
*   Esayes d'ouvrir le fichier avec les droits
*   necessaire a sa nature. Renvoie son fd si tout functionne.
*/
int	open_file(char *file, int in_or_out)
{
	int	ret;

	if (in_or_out == 0)
		ret = open(file, O_RDONLY, 0777);
	if (in_or_out == 1)
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (in_or_out == 2)
		ret = open(file, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (ret == -1)
		exit(0);
	return (ret);
}
