/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 13:40:16 by mwaterso          #+#    #+#             */
/*   Updated: 2020/06/21 12:39:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "doom.h"

void printobj(t_object *obj, t_input *data)
{
	int i;
	int ret;
	t_poly *po;
	i = -1;
	int j;
	po = obj->poly;
    while (po)
	{
		i++;

		separate_points(po);
		
		ret = Projxy(po, data);

		if (ret)
		{
			po->isvisible = 1;

			poly_toboxes(data, po);
		}

		
		po = po->next;
	}
	//printf("%p		%p\n", data->im.tab, data->im.ad);
	//mlx_put_image_to_window(data->mlx_ad, data->win_ad, data->im.ad, 0, 0);
}
void damage_mob(t_object *obj)
{
	if(obj->type != ENEMI)
		return;

	obj->hp -= 10;
	if(obj->hp <= 0)
		obj->exist = 0;
	printf("Shoot %d\n", obj->hp);
}

void get_objpo(t_object *objects, t_input *data)
{
//	printf("printing objects..\n");
	int i;
	i = -1;
	while (objects)
	{
		//printf("a\n");
		while (objects && !objects->exist)
			objects = objects->next;
		if(!objects)
			return;
		++i;
		printobj(objects, data);
		//printf("b\n");
		//printf("print obj %d\n", i);
		thread_start(data, objects->poly);

		objects = objects->next;
	}
}