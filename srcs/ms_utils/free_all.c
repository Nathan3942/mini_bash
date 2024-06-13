/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 09:33:51 by njeanbou          #+#    #+#             */
/*   Updated: 2024/06/13 15:09:21 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void free_para(t_params **para)
{
    t_params *current;
    t_params *next;
    int i;

    if (!para || !*para)
        return;

    current = *para;
    while (current != NULL)
    {
        next = current->next;
        if (current->com)
        {
            i = 0;
            while (current->com[i])
            {
                free((*para)->com[i]);
                i++;
            }
            free((*para)->com);
        }
        free(current);
        current = next;
    }
	*para = NULL;
}

// void free_para(t_params **para)
// {
// 	int	i;

// 	i = 0;
//     if (!(*para))
//         return;
//     if ((*para)->com)
//     {
// 		printf("free\n");
//         while ((*para)->com[i])
//         {
//             free((*para)->com[i]);
//             i++;
//         }
//         free((*para)->com);
//     }
//     // Recursively free the next node
//     if ((*para)->next)
//     {
//         free_para(&(*para)->next);
//     }
//     // Free the current node
//     free(*para);
//     *para = NULL; // Optional: set pointer to NULL after freeing
// }


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
    // if (!(*data))
    //     printf("data\n");
}
