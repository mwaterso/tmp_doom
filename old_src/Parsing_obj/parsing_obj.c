/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beduroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 00:35:11 by beduroul          #+#    #+#             */
/*   Updated: 2020/02/17 00:35:13 by beduroul         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_index    obj_size(t_line *list)
{
	t_index index;

	index = (t_index){.i = 0, .j = 0, .k = 0};
	while (list)
	{
		if (ft_strnequ_word(list->line, "v ", 2))
			index.i++;
		if (ft_strnequ_word(list->line, "vt ", 3))
			index.j++;
		if (ft_strnequ_word(list->line, "vn ", 3))
			index.k++;
		list = list->next;
	}
	return (index);
}

int     mall_file(t_file_obj *file, t_line *list)
{
	t_index i;

	i = obj_size(list);
	if (!(file->v = (t_fdot *)malloc(sizeof(t_fdot) * i.i + 1)))
		return 0;
	if (!(file->vt = (t_2d *)malloc(sizeof(t_2d) * i.j + 1)))
		return 0;
	if (!(file->vn = (t_fdot *)malloc(sizeof(t_fdot) * i.k + 1)))
		return 0;
	return 1;
}

int			sort_tfdot_pos(char *line, t_fdot *dot, t_fdot pos)
{
	int		i;
	char	**tab;

	i = 0;
	while (!ft_isdigit(line[i]))
		i++;
	if (!(tab = ft_strsplit(line + i, ' ')))
		return (0);
	if (ft_avlen(tab) != 3)
		return (0);
	printf("POOOOOOdqsdqsdOOOOOOOOOOOOOS x %f POS y %f POS z %f\n", pos.x, pos.y, pos.z);
	dot->x = ft_atof(tab[0]) + pos.x;
	dot->y = ft_atof(tab[1]) + pos.y;
	dot->z = ft_atof(tab[2]) + pos.z;
	free_tab(&tab);
	return (1);
}

int     parse_file_obj(t_line *list, t_poly **poly, t_input *data, t_object *new)
{
	t_file_obj  file;
	t_index     index;
	char		*tmp;

	index = (t_index){.i = 0, .j = 0, .k = 0};
	file.lst = NULL;
	file.pos = data->obj->pos;
	if (!(mall_file(&file, list)))
		return 0;
   	while (list)
   	{
		   printf("IN LIST\n");
		if (ft_strnequ_word(list->line, "mtllib ", 7))
			sort_mtl(data, list->line, &file);
		if (ft_strnequ_word(list->line, "usemtl ", 7))
			tmp = list->line + 7;
		if (ft_strnequ_word(list->line, "v ", 2))
			sort_tfdot_pos(list->line, &(file.v[index.i++]), data->obj->pos);
		if (ft_strnequ_word(list->line, "vt ", 3))
			sort_t2d(list->line, &(file.vt[index.j++]));
		if (ft_strnequ_word(list->line, "vn ", 3))
			sort_tfdot(list->line, &(file.vn[index.k++]));
		if (ft_strnequ_word(list->line, "f ", 2))
			sort_poly(list->line + 2, poly, file, tmp);
		list = list->next;
   	}
	reverse_p(poly);
	(void)new;
   return 1;
}

int     p_obj_loop(t_poly **poly, t_input *data, int fd, t_object *new)
{
	t_line *list;
	int n_line;
	char *line;
	int i;

	i = 0;
	n_line = 0;
	list = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if(!(creat_elem_l(line, n_line, &list)))
			return 0;
		n_line++;
		ft_strdel(&line);
	}
	reverse_l(&list);
	ft_strdel(&line);
	if (!(i = parse_file_obj(list, poly, data, new)))
		return (0);
	return i;
}

t_poly *ft_pares_obj(char *file, t_input *data, t_object *new)
{
	int		fd;
	int 	i;
	t_poly	*poly;

	(void)data;
	(void)i;
	poly = NULL;
	if ((fd = open(file, O_RDONLY)) < 1)
		return (NULL);
	error_file(fd, file);
	if (!(i = p_obj_loop(&poly, data, fd, new)))
		return (NULL);
	close(fd);
	return (poly);
}
