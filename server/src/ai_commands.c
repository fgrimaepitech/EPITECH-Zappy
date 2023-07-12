/*
** EPITECH PROJECT, 2023
** ai_commands.c
** File description:
** ai_commands
*/

#include "../include/server.h"

void send_task_response_2(server_t *server, task_t *task, char *cmd)
{
    if (strstr(cmd, "Take"))
        take_command(server, task->client, cmd);
    if (strcmp(cmd, "Eject") == 0)
        eject_command(server, task->client);
    if (strstr(cmd, "Broadcast")) {
        broadcast_command(server, task->client, cmd); return;
    }
    if (strcmp(cmd, "Incantation") == 0) {
        incantation_command(task->client, server); return;
    }
    if (strcmp(cmd, "Respawn") == 0) {
        respawn_task(server); return;
    }
    if (strcmp(cmd, "LifeCycle") == 0) {
        life_cycle_command(server, task->client); return;
    }
    if (strcmp(cmd, "Fork") == 0) {
        fork_command(task->client, server); return;
    }
}

void send_task_response(server_t *server, task_t *task, char *cmd)
{
    if (strcmp(cmd, "Forward") == 0) {
        forward_command(server, task->client);
        send_new_player_pos(task->client, server);
    }
    if (strcmp(cmd, "Right") == 0) {
        right_command(task->client); send_new_player_pos(task->client, server);
    }
    if (strcmp(cmd, "Left") == 0) {
        left_command(task->client); send_new_player_pos(task->client, server);
    }
    if (strcmp(cmd, "Inventory") == 0) {
        inventory_command(task->client);
    }
    if (strcmp(cmd, "Look") == 0) {
        look_command(server, task->client);
    }
    if (strstr(cmd, "Set"))
        set_command(server, task->client, cmd);
    send_task_response_2(server, task, cmd);
}

void forward_command(server_t *server, client_t *client)
{
    if (client->player->state == INCANTATION) return;
    int *pos = create_tuple(client->player->x, client->player->y);
    if (client->player->orientation == 'N')
        pos[1]--;
    if (client->player->orientation == 'E')
        pos[0]++;
    if (client->player->orientation == 'S')
        pos[1]++;
    if (client->player->orientation == 'W')
        pos[0]--;
    move_player(client->player, server->game->map, pos, server);
    send(client->socket, "ok\n", 3, 0);
}

void right_command(client_t *client)
{
    if (client->player->state == INCANTATION) return;
    if (client->player->orientation == 'N')
        client->player->orientation = 'E';
    if (client->player->orientation == 'E')
        client->player->orientation = 'S';
    if (client->player->orientation == 'S')
        client->player->orientation = 'W';
    if (client->player->orientation == 'W')
        client->player->orientation = 'N';
    send(client->socket, "ok\n", 3, 0);
}

void left_command(client_t *client)
{
    if (client->player->state == INCANTATION) return;
    if (client->player->orientation == 'N')
        client->player->orientation = 'W';
    if (client->player->orientation == 'E')
        client->player->orientation = 'N';
    if (client->player->orientation == 'S')
        client->player->orientation = 'E';
    if (client->player->orientation == 'W')
        client->player->orientation = 'S';
    send(client->socket, "ok\n", 3, 0);
}