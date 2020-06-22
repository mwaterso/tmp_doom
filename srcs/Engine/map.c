/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:42:01 by mwaterso          #+#    #+#             */
/*   Updated: 2020/06/18 17:32:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "doom.h"

void rev_moove(t_input *data, int way)
{
    printf("Rev moove\n");
    if (way == KEY_UP)
		mapmoveallp(data, (t_fdot){.x = 1, .y = 0, .z = 0});
    if (way == KEY_DOWN)
		mapmoveallp(data, (t_fdot){.x = -1, .y = 0, .z = 0});
    if (way == KEY_RIGHT)
		mapmoveallp(data, (t_fdot){.x = 0, .y = -1, .z = 0});
    if (way == KEY_LEFT)
		mapmoveallp(data, (t_fdot){.x = 0, .y = 1, .z = 0});
		//redefinevector(data->map);
}

void moove(t_input *data, int way)
{
    printf("moove\n");
    if (way == KEY_UP)
		  mapmoveallp(data, (t_fdot){.x = -1, .y = 0, .z = 0});
    if (way == KEY_DOWN)
		  mapmoveallp(data, (t_fdot){.x = 1, .y = 0, .z = 0});
    if (way == KEY_RIGHT)
		  mapmoveallp(data, (t_fdot){.x = 0, .y = 1, .z = 0});
    if (way == KEY_LEFT)
		  mapmoveallp(data, (t_fdot){.x = 0, .y = -1, .z = 0});
    if (check_colli(data->map))
        rev_moove(data, way);
		//redefinevector(data->map);
}

void mapmoveallp(t_input  *data, t_fdot way)
{
    t_object *obj;
    int i = -1;

    obj = data->obj;
    mapmovep(data->map, way);
    while(obj)
    {
      // while(++i < 4)
      //   printf("MOOVE   %f %f %f\n", obj->poly->rotx[i].x, obj->poly->rotx[i].y, obj->poly->rotx[i].z);
      mapmovep(obj->poly, way);
      obj->pos.x += way.x;
      obj->pos.y += way.x;
      obj->pos.z += way.x;
      obj->posrx.x += way.x;
      obj->posrx.y += way.x;
      obj->posrx.z += way.x;
      // i = -1;
      // while(++i < 4)
      //   printf("MOOVE   %f %f %f\n", obj->poly->rotx[i].x, obj->poly->rotx[i].y, obj->poly->rotx[i].z);
      // sleep(2);
      obj = obj->next;
    }

}

void mapmovep(t_poly *poly, t_fdot incr)
{
    int i;
    t_poly *gones;

    gones = poly;
    while(gones)
    {
		i = -1;
        while(++i < 3)
        {
			gones->dot[i].x += incr.x;
            gones->dot[i].y += incr.y;
            gones->dot[i].z += incr.z;
			gones->rotx[i].x += incr.x;
            gones->rotx[i].y += incr.y;
            gones->rotx[i].z += incr.z;
		    }
		gones->d = -(gones->a * gones->dot[0].x + gones->b * gones->dot[0].y + gones->c * gones->dot[0].z);
        gones = gones->next;
    }
}

void rot_sky(t_input *data, t_fdot rot)
{
  if (rot.y)
  {
    data->sky.i = data->angley == 0 ? data->sky.veci : ApplyMatPoint(define_yRotMat(data->angley), data->sky.veci);
    data->sky.j = data->angley == 0 ? data->sky.vecj : ApplyMatPoint(define_yRotMat(data->angley), data->sky.vecj);
  }
  else
  {
    if (rot.z == 1)
    {
      data->sky.veci = ApplyMatPoint(data->rotz, data->sky.veci);
      data->sky.vecj = ApplyMatPoint(data->rotz, data->sky.vecj);
    }
    else if (rot.z == -1)
    {
      data->sky.veci = ApplyMatPoint(data->minrotz, data->sky.veci);
      data->sky.vecj = ApplyMatPoint(data->minrotz, data->sky.vecj);
    }
  }
  //printf("i = %f %f %f\nj = %f %f %f\n", data->sky.i.x, data->sky.i.y, data->sky.i.z, data->sky.j.x, data->sky.j.y, data->sky.j.z);
}

void maprotp(t_poly *poly, t_fdot rot, t_input *data)
{
  int i;
  t_poly *gones;
  gones = poly;

    while(gones)
    {
    i = -1;
        while(++i < 3)
        {
		//printf("MAP: gones %d %f %f %f\n", gones->nbr_p, gones->rotx[i].x, gones->rotx[i].y, gones->rotx[i].z);
            if (rot.y)
            {
                    gones->dot[i] = data->angley == 0 ? gones->rotx[i] : ApplyMatPoint(define_yRotMat(data->angley), gones->rotx[i]);
                    //gones->vAB = ApplyMatPoint(define_yRotMat(data->angley), gones->vAB);
                   //gones->vBC = ApplyMatPoint(define_yRotMat(data->angley), gones->vBC);
          //          printf("roty\n");
            }
            else 
            {
                if (rot.z == 1)
                    gones->rotx[i] = ApplyMatPoint(data->rotz, gones->rotx[i]);
                else if (rot.z == -1)
                    gones->rotx[i] = ApplyMatPoint(data->minrotz, gones->rotx[i]);
                data->nbrtour = 1;
            }
                
		//printf("-------%d-------------------- gones %d %f %f %f\n", i, gones->nbr_p, gones->dot[i].x, gones->dot[i].y, gones->dot[i].z);
        }
       // printf("%p\n", gones);
        gones = gones->next;
    }
}

void maprotateallp(t_poly *poly, t_fdot rot, t_input *data)
{
  t_object *obj;

  obj = data->obj;
 // printf("ROTATE\n");
  while(obj)
  {
    maprotp(obj->poly, rot, data);
	  redefinevector(obj->poly);
    if (rot.y)
      obj->pos = ApplyMatPoint(define_yRotMat(data->angley), obj->posrx);
    else
    {
      if (rot.z == 1)
        obj->posrx = ApplyMatPoint(data->rotz,  obj->posrx);
      else if (rot.z == -1)
        obj->posrx = ApplyMatPoint(data->minrotz,  obj->posrx);
    }
    obj = obj->next;
  }
  maprotp(data->map, rot, data);
  rot_sky(data, rot);
	redefinevector(data->map);
}
