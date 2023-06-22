
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proj1.h"

#define BUFFERSIZE 128

/*
 function to add a node to the linked list
 */
void add_node(char *song, char *artist, int year, int time)
{
    // Allocate memory for the new node
    struct node *newNode = (struct node *)malloc(sizeof(struct node));

    // Allocate memory for the song and copy it to the node
    newNode->song = malloc(strlen(song) + 1);
    strcpy(newNode->song, song);

    // Allocate memory for the artist and copy it to the node
    newNode->artist = malloc(strlen(artist) + 1);
    strcpy(newNode->artist, artist);

    // This will be the last node, so set its next pointer to NULL
    newNode->time = time;
    newNode->year = year;

    // This will be the last node, so set its next pointer to NULL
    newNode->next = NULL;

    // If the list is empty, make the new node the head
    if (head == NULL)
    {
        newNode->prev = NULL;
        head = newNode;
        return;
    }
    // IF the list is not empty, traverse to the end and link the new node
    else
    {
        struct node *tmp = head;
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }

        tmp->next = newNode;
        newNode->prev = tmp;
        return;
    }
}
// Function to remove nodes from the list based on the artist name
void remove_node(char *artist)
{
    struct node *tmp = head;

    // If the list is empty, just return
    if (head == NULL)
    {
        return;
    }

    // Traverse through the list
    while (tmp != NULL)
    {

        // If the current node's artist matches the given artist
        if (strcmp(tmp->artist, artist) == 0)
        {
            // If it's the only node in the list
            if (tmp->prev == NULL && tmp->next == NULL)
            {
                head = NULL;
                free(tmp->artist);
                free(tmp->song);
                free(tmp);
            }
            // If it's the first node in the list
            else if (tmp->prev == NULL)
            {
                tmp->next->prev = NULL;
                head = tmp->next;
                free(tmp->artist);
                free(tmp->song);
                free(tmp);
            }
            // If it's the last node in the list
            else if (tmp->next == NULL)
            {
                tmp->prev->next = NULL;
                free(tmp->artist);
                free(tmp->song);
                free(tmp);
            }

            // If it's somewhere in the middle
            else
            {
                tmp->prev->next = tmp->next;
                tmp->next->prev = tmp->prev;

                free(tmp->artist);
                free(tmp->song);
                free(tmp);
            }
        }
        tmp = tmp->next;
    }
}

// Function to print the list from the head to the end
void print_forwards(struct node *head)
{
    struct node *current_node = head;
    while (current_node != NULL)
    {
        printf("artist: %s, song: %s, time: %d, year: %d \n", current_node->artist, current_node->song, current_node->time, current_node->year);
        current_node = current_node->next;
    }
}

// Function to print the list from the end to the head
void print_backward(struct node *head)
{
    struct node *current_node = head;
    // Move to the end of the list
    while (current_node->next != NULL)
    {
        current_node = current_node->next;
    }

    // Traverse backwards printing each node
    while (current_node != NULL)
    {
        printf("artist: %s, song: %s, time: %d, year: %d \n", current_node->artist, current_node->song, current_node->time, current_node->year);
        current_node = current_node->prev;
    }
}

/*
 Main function of the program controls the input - 'a' to add, 'r' to remove 'fp' to forward print, 'bp' to reverse print, and 'f' to end
 when adding the user enters a song string, a artist string, a year int, and a time int
 */
int main(int argc, char *argv[])
{
    // Buffer arrays to store user input
    char buffer[BUFFERSIZE];
    char song_buff[BUFFERSIZE];
    char artist_buff[BUFFERSIZE];
    char year_buff[BUFFERSIZE];
    char time_buff[BUFFERSIZE];

    // Infinite loop to keep the program running until the user decides to exit 
    while (1)
    {
        printf("Enter 'a' to add\nEnter 'r' to remove\nEnter 'fp' to print forwards\nEnter 'bp' to print backwards\nEnter 'f' to End");
        fgets(buffer, BUFFERSIZE, stdin);

        // If the user enters 'f', free memory and end the program
        if (strcmp("f\n", buffer) == 0)
        {
            while (head != NULL)
            {
                free(head->song);
                free(head->artist);
                free(head);
                head = head->next;
            }
            break;
        }
        // If the user enters 'a', prompt for details and add a node to the list
        else if (strcmp("a\n", buffer) == 0)
        {
            printf("song: ");
            fgets(song_buff, BUFFERSIZE, stdin);

            printf("artist: ");
            fgets(artist_buff, BUFFERSIZE, stdin);

            printf("year: ");
            (fgets(year_buff, BUFFERSIZE, stdin));
            int year = atoi(year_buff);

            printf("time: ");
            fgets(time_buff, BUFFERSIZE, stdin);
            int time = atoi(time_buff);

            add_node(song_buff, artist_buff, year, time);
        }
        // If the user enters 'r', prompt for an artist's name and remove nodes with matching artists from the list
        else if (strcmp("r\n", buffer) == 0)
        {
            printf("artist to be removed:");
            fgets(artist_buff, BUFFERSIZE, stdin);
            remove_node(artist_buff);
        }
        // If the user enters 'fp', print the list forwards
        else if (strcmp("fp\n", buffer) == 0)
        {
            print_forwards(head);
        }
        // If the user enters 'bp', print the list backwards
        else if (strcmp("bp\n", buffer) == 0)
        {
            print_backward(head);
        }
        // If the user enters an invalid command, promp them to enter a valid one
        else
        {
            printf("Enter a valid character\n");
        }
    }
    return 0;
}
