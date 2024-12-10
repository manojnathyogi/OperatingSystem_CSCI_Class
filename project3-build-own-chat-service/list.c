//TeamM: Manoj Nath Yogi and Siddhartha Gautam

#include "list.h"

// Insert user into the user list
struct node* insertFirstU(struct node *head, int socket, char *username) {
    if (findU(head, username) == NULL) {
        struct node *link = (struct node*) malloc(sizeof(struct node));
        if (link == NULL) {
            perror("Failed to allocate memory for new user");
            exit(EXIT_FAILURE);
        }
        link->socket = socket;
        strcpy(link->username, username);
        link->dm_connections = NULL;
        link->next = head;
        head = link;
    } else {
        printf("Duplicate username: %s\n", username);
    }
    return head;
}

// Find user by username
struct node* findU(struct node *head, char* username) {
    struct node* current = head;
    while (current != NULL) {
        if (strcmp(current->username, username) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Delete user from the user list
struct node* deleteU(struct node *head, char *username) {
    struct node *current = head;
    struct node *previous = NULL;

    while (current != NULL && strcmp(current->username, username) != 0) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) { // User not found
        return head;
    }

    if (current == head) {
        head = head->next;
    }
    else {
        previous->next = current->next;
    }

    // Free DM connections
    struct node *dm = current->dm_connections;
    while(dm != NULL) {
        struct node *temp = dm;
        dm = dm->next;
        free(temp);
    }

    free(current);
    return head;
}

// List all users
void listUsers(struct node *head) {
    struct node *current = head;
    while (current != NULL) {
        printf("User: %s\n", current->username);
        current = current->next;
    }
}

// Insert room into the room list
struct room_node* insertFirstR(struct room_node *head, char *roomname) {
    if (findR(head, roomname) == NULL) {
        struct room_node *link = (struct room_node*) malloc(sizeof(struct room_node));
        if (link == NULL) {
            perror("Failed to allocate memory for new room");
            exit(EXIT_FAILURE);
        }
        strcpy(link->roomname, roomname);
        link->users = NULL;
        link->next = head;
        head = link;
    } else {
        printf("Duplicate room: %s\n", roomname);
    }
    return head;
}

// Find room by roomname
struct room_node* findR(struct room_node *head, char* roomname) {
    struct room_node* current = head;
    while (current != NULL) {
        if (strcmp(current->roomname, roomname) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Delete room from the room list
struct room_node* deleteR(struct room_node *head, char *roomname) {
    struct room_node *current = head;
    struct room_node *previous = NULL;

    while (current != NULL && strcmp(current->roomname, roomname) != 0) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) { // Room not found
        return head;
    }

    if (current == head) {
        head = head->next;
    }
    else {
        previous->next = current->next;
    }

    // Free users in the room
    struct node *user = current->users;
    while(user != NULL) {
        struct node *temp = user;
        user = user->next;
        free(temp);
    }

    free(current);
    return head;
}

// List all rooms, append to buffer
void listRooms(struct room_node *head, char *buffer) {
    struct room_node *current = head;
    while (current != NULL) {
        strcat(buffer, current->roomname);
        strcat(buffer, "\n");
        current = current->next;
    }
}

// Add user to a room
void addUserToRoom(struct room_node *room, struct node *user) {
    // Check if user is already in the room
    struct node *current = room->users;
    while(current != NULL) {
        if(strcmp(current->username, user->username) == 0) {
            // User already in the room
            return;
        }
        current = current->next;
    }

    // Add to the room's user list
    struct node *link = (struct node*) malloc(sizeof(struct node));
    if (link == NULL) {
        perror("Failed to allocate memory for user in room");
        exit(EXIT_FAILURE);
    }
    strcpy(link->username, user->username);
    link->socket = user->socket;
    link->dm_connections = NULL;
    link->next = room->users;
    room->users = link;
}

// Remove user from a room
void removeUserFromRoom(struct room_node *room, char *username) {
    struct node *current = room->users;
    struct node *previous = NULL;

    while (current != NULL && strcmp(current->username, username) != 0) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) { // User not found in room
        return;
    }

    if (current == room->users) {
        room->users = room->users->next;
    }
    else {
        previous->next = current->next;
    }

    free(current);
}

// List users in a room, append to buffer
void listUsersInRoom(struct room_node *room, char *buffer) {
    struct node *current = room->users;
    while(current != NULL) {
        strcat(buffer, current->username);
        strcat(buffer, "\n");
        current = current->next;
    }
}

// Connect two users via DM
bool connectUsers(struct node *head, char *user1, char *user2) {
    struct node *u1 = findU(head, user1);
    struct node *u2 = findU(head, user2);

    if(u1 == NULL || u2 == NULL) {
        return false;
    }

    // Check if already connected
    struct node *current = u1->dm_connections;
    while(current != NULL) {
        if(strcmp(current->username, user2) == 0) {
            // Already connected
            return false;
        }
        current = current->next;
    }

    // Add u2 to u1's DM connections
    struct node *link1 = (struct node*) malloc(sizeof(struct node));
    if (link1 == NULL) {
        perror("Failed to allocate memory for DM connection");
        exit(EXIT_FAILURE);
    }
    strcpy(link1->username, u2->username);
    link1->socket = u2->socket;
    link1->dm_connections = NULL;
    link1->next = u1->dm_connections;
    u1->dm_connections = link1;

    // Add u1 to u2's DM connections
    struct node *link2 = (struct node*) malloc(sizeof(struct node));
    if (link2 == NULL) {
        perror("Failed to allocate memory for DM connection");
        exit(EXIT_FAILURE);
    }
    strcpy(link2->username, u1->username);
    link2->socket = u1->socket;
    link2->dm_connections = NULL;
    link2->next = u2->dm_connections;
    u2->dm_connections = link2;

    return true;
}

// Disconnect two users via DM
bool disconnectUsers(struct node *head, char *user1, char *user2) {
    struct node *u1 = findU(head, user1);
    struct node *u2 = findU(head, user2);

    if(u1 == NULL || u2 == NULL) {
        return false;
    }

    // Remove u2 from u1's DM connections
    struct node *current = u1->dm_connections;
    struct node *previous = NULL;
    while(current != NULL && strcmp(current->username, user2) != 0) {
        previous = current;
        current = current->next;
    }

    if(current != NULL) {
        if(previous == NULL) {
            u1->dm_connections = current->next;
        }
        else {
            previous->next = current->next;
        }
        free(current);
    }

    // Remove u1 from u2's DM connections
    current = u2->dm_connections;
    previous = NULL;
    while(current != NULL && strcmp(current->username, user1) != 0) {
        previous = current;
        current = current->next;
    }

    if(current != NULL) {
        if(previous == NULL) {
            u2->dm_connections = current->next;
        }
        else {
            previous->next = current->next;
        }
        free(current);
    }

    return true;
}

// Check if two users are connected via DM
bool areConnected(struct node *head, char *user1, char *user2) {
    struct node *u1 = findU(head, user1);
    if(u1 == NULL) return false;

    struct node *current = u1->dm_connections;
    while(current != NULL) {
        if(strcmp(current->username, user2) == 0) {
            return true;
        }
        current = current->next;
    }
    return false;
}
