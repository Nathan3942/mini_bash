/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 09:33:51 by njeanbou          #+#    #+#             */
/*   Updated: 2024/06/12 23:04:27 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void free_para(t_params *para)
// {
//     t_params *current;
//     t_params *next;
//     int i;

//     if (!para)
//         return;

//     current = para;
//     while (current != NULL)
//     {
//         next = current->next;

//         // Libérer l'array com
//         if (current->com)
//         {
//             i = 0;
//             while (current->com[i])
//             {
// 				printf("%s\n", para->com[i]);
//                 free(para->com[i]);
//                 i++;
//             }
//             free(para->com);
//         }

//         // Libérer le nœud actuel
//         free(current);
        
//         current = next;
//     }

// 	para = NULL; // Optionnel : mettre le pointeur à NULL après libération
// }

void free_para(t_params **para)
{
	int	i;

	i = 0;
    if (!(*para))
        return;
    if ((*para)->com)
    {
        while ((*para)->com[i])
        {
            free((*para)->com[i]);
            i++;
        }
        free((*para)->com);
    }
    if ((*para)->next)
    {
        free_para(&(*para)->next);
    }
    free(*para);
    *para = NULL;
}


// void	free_para(t_params **para)
// {
// 	int	i;

// 	i = 0;
// 	if (!(*para))
// 		return ;
// 	if (!(*para)->com)
// 	{
// 		free((*para));
// 		return ;
// 	}
// 	while ((*para)->com[i] != NULL)
// 	{
// 		free((*para)->com[i]);
// 		i++;
// 	}
// 	free_para(&(*para)->next);
// 	free((*para)->com);
// 	free((*para));
// }

void	free_all(t_params **para, t_put **put, t_data **data)
{
	free_para(para);
	if ((*put)->input != NULL)
		free((*put)->input);
	if ((*put)->output != NULL)
		free((*put)->output);
	free((*put));
	free((*data));
}
