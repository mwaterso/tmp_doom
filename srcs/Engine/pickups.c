
#include "../include/doom.h"

void add_item(t_input *data, int id)
{
    if (id == 0)
        data->data_hud->inventory.slot_two++;
    else if (id == 1)
        data->data_hud->inventory.slot_one++;
    else if (id == 2)
        data->data_hud->inventory.slot_three++;
    else if (id == 3)
        data->data_hud->total_ammo += 30;
}

void hit_player(t_input *data)
{
    data->data_hud->health_bar.health -= 20 * data->data_hud->diff;
    if (data->data_hud->health_bar.health <= 0)
        dead_anim(data->data_hud);
}

void collobj(t_object *obj, t_input *data)
{
    if(obj->type == ENEMI)
        hit_player(data);
    else if(obj->type == POTION)
    {
        add_item(data, 0);
        obj->exist = 0;
    }
    else if(obj->type == ARMOR)
    {
        add_item(data, 1);
        obj->exist = 0;
    }
    else if (obj->type == MUN)
    {
        add_item(data, 2);
        obj->exist = 0;
    }
    else if (obj->type == SCEN)
    {
        add_item(data, 2);
        obj->exist = 0;
    }
    else if (obj->type == CHEST)
    {
        add_item(data, 2);
        obj->exist = 0;
    }
    else if (obj->type == KEY)
    {
        add_item(data, 3);
        obj->exist = 0;
    }
}

void agro(t_object *obj, t_input *data)
{
    t_fdot dir;
    dir = normalise_vec((t_fdot){-obj->pos.x, -obj->pos.y, -obj->pos.z});
    dir.x *= data->data_hud->diff;
    dir.y *= data->data_hud->diff;
    dir.z *= data->data_hud->diff;
    mapmovep(obj->poly, dir);

}

void check_obj(t_object *object, t_input *data)
{
    t_object *obj;

    obj = object;
    while (obj)
    {
        if (obj->hp <= 0 && obj->type == ENEMI)
            obj->exist = 0;
        if (getpow3ddist(obj->pos) <= 10 && obj->type == ENEMI)
            agro(obj, data);
        if (getpow3ddist(obj->pos) <= 0.25)
            collobj(obj, data);
        obj = obj->next;
        while(obj && !obj->exist)
            obj = obj->next;
    }
}
