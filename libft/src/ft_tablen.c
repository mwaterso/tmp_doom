/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_tablen.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: beduroul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/26 14:37:11 by beduroul     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/26 14:37:17 by beduroul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

int     ft_tablen(void **tab)
{
    int index;
    index = 0;
    while (tab[index])
        index++;
    return (index);
}