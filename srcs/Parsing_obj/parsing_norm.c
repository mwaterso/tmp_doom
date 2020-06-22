/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_norm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beduroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 15:50:43 by beduroul          #+#    #+#             */
/*   Updated: 2020/03/06 15:50:44 by beduroul         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		size_mtl_file(char *file)
{
	int i;

	i = -1;
	while (file[++i])
		if (file[i] == ' ')
			return (i);
	return (0);
}

void	loop_read2(t_line *list, t_object *new, t_input *data)
{
	if (ft_strnequ_word(list->line, "type", 4))
		sort_type(list->line, new);
	else if (ft_strnequ_word(list->line, "pos", 3))
		ft_sort_pos(list->line, new, data);
	else if (ft_strnequ_word(list->line, "rot", 3))
		ft_sort_rot(list->line, new);
}

void	free_new_lst(t_lst_mtl *new)
{
	ft_strdel(&(new->name));
	free(new);
	new = NULL;
}

void	free_object(t_object **obj, t_object *new)
{
	t_object		*tmp;
	t_object		*next;

	tmp = *obj;
	if (!obj)
		return ;
	while (tmp)
	{
		next = tmp->next;
		ft_strdel(&(tmp->file));
		ft_strdel(&(tmp->l_file));
		free_poly(&(tmp->poly));
		free(tmp);
		tmp = next;
	}
	*obj = NULL;
	ft_strdel(&(new->file));
	ft_strdel(&(new->l_file));
	if (new)
		free(new);
	new = NULL;
}

int            sort_tfdot_pos(char *line, t_fdot *dot, t_fdot pos)
{
    int        i;
    char    **tab;

    i = 0;
    while (!ft_isdigit(line[i]))
        i++;
    if (!(tab = ft_strsplit(line + i, ' ')))
        return (0);
    if (ft_avlen(tab) != 3)
        return (0);
    dot->x = ft_atof(tab[0]) + pos.x;
    dot->y = ft_atof(tab[1]) + pos.y;
    dot->z = ft_atof(tab[2]) + pos.z;
    free_tab(&tab);
    return (1);
}

int		parse_fobj2(t_line *list, t_file_obj *file, t_input *d, t_poly **poly)
{
	static char	*tmp;

	if (ft_strnequ_word(list->line, "mtllib ", 7))
		if (!(sort_mtl(d, list->line, file)))
			return (0);
	if (ft_strnequ_word(list->line, "v ", 2))
		if (!(sort_tfdot_pos(list->line, &(file->v[file->index.i++]), d->tmp_pos)))
			return (0);
	if (ft_strnequ_word(list->line, "vt ", 3))
		if (!(sort_t2d(list->line, &(file->vt[file->index.j++]))))
			return (0);
	if (ft_strnequ_word(list->line, "usemtl ", 7))
		tmp = list->line + 7;
	if (ft_strnequ_word(list->line, "vn ", 3))
		if (!(sort_tfdot(list->line, &(file->vn[file->index.k++]))))
			return (0);
	if (ft_strnequ_word(list->line, "f ", 2))
		if (!(sort_poly(list->line + 2, poly, *file, tmp)))
			return (0);
	return (1);
}
