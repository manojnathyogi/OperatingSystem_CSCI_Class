//TeamM: Manoj Nath Yogi and Siddhartha Gautam

#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// User linked list node
struct node {
    char username[30];
    int socket;
    struct node *next;
    struct node *dm_connections; // List of DM connections
};

// Room linked list node
struct room_node {
    char roomname[30];
    struct room_node *next;
    struct node *users; // List of users in the room
};

// User management functions
struct node* insertFirstU(struct node *head, int socket, char *username);
struct node* findU(struct node *head, char* username);
struct node* deleteU(struct node *head, char *username);
void listUsers(struct node *head);

// Room management functions
struct room_node* insertFirstR(struct room_node *head, char *roomname);
struct room_node* findR(struct room_node *head, char* roomname);
struct room_node* deleteR(struct room_node *head, char *roomname);
void listRooms(struct room_node *head, char *buffer);
void addUserToRoom(struct room_node *room, struct node *user);
void removeUserFromRoom(struct room_node *room, char *username);
void listUsersInRoom(struct room_node *room, char *buffer);

// DM management functions
bool connectUsers(struct node *head, char *user1, char *user2);
bool disconnectUsers(struct node *head, char *user1, char *user2);
bool areConnected(struct node *head, char *user1, char *user2);

#endif // LIST_H
