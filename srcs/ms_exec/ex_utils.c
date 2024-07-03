/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:31:24 by ichpakov          #+#    #+#             */
/*   Updated: 2024/06/19 16:50:01 by njeanbou         ###   ########.fr       */
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

int	check_exe(t_params **cmds)
{
	t_params	*head;
	int			i;

	i = -1;
	head = *cmds;
	while (head != NULL)
	{
		i++;
		printf("%s\n", head->com[0]);
		if (ft_strequal(head->com[0], "./minishell") == 0 && i > 0)
			return (1);
		head = head->next;
	}
	return (0);
}

pid_t	ft_getpid(void) {
    pid_t pid;

    // Appel système pour obtenir le PID
    __asm__ ("mov $20, %%eax\n\t"  // 20 est un numéro d'appel système pour getpid() sur x86
             "int $0x80\n\t"       // Appel au noyau via l'interruption 0x80
             "mov %%eax, %0"       // Récupérer la valeur de retour dans pid
             : "=r" (pid)          // Sortie : pid
             :                     // Pas d'entrée
             : "%eax"              // Utilisation du registre %eax
            );

    return pid;
}