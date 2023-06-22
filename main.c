
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proj1.h"

#define BUFFERSIZE 128

/*
 This function adds nodes to the linked list
 */
void add_node(char *song, char *artist, int year, int time)
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));

    newNode->song = malloc(strlen(song) + 1);
    strcpy(newNode->song, song);
    newNode->artist = malloc(strlen(artist) + 1);
    strcpy(newNode->artist, artist);

    newNode->time = time;
    newNode->year = year;
    newNode->next = NULL;

    if (head == NULL)
    {
        newNode->prev = NULL;
        head = newNode;
        return;
    }
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
/*
 This function removes nodes from the list
 */
void remove_node(char *artist)
{
    struct node *tmp = head;
    if (head == NULL)
    {
        return;
    }

    while (tmp != NULL)
    {

        if (strcmp(tmp->artist, artist) == 0)
        {
            if (tmp->prev == NULL && tmp->next == NULL)
            {
                head = NULL;

                free(tmp->artist);
                free(tmp->song);
                free(tmp);
            }
            else if (tmp->prev == NULL)
            {
                tmp->next->prev = NULL;
                head = tmp->next;
                free(tmp->artist);
                free(tmp->song);
                free(tmp);
            }
            else if (tmp->next == NULL)
            {
                // tmp->prev = tmp;
                tmp->prev->next = NULL;
                free(tmp->artist);
                free(tmp->song);
                free(tmp);
            }

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
/*
 This function prints the list forwards
 */
void print_forwards(struct node *head)
{
    struct node *current_node = head;
    while (current_node != NULL)
    {
        printf("artist: %s, song: %s, time: %d, year: %d \n", current_node->artist, current_node->song, current_node->time, current_node->year);
        current_node = current_node->next;
    }
}
/*
 This function prints the list backwards
 */
void print_backward(struct node *head)
{
    struct node *current_node = head;
    while (current_node->next != NULL)
    {
        current_node = current_node->next;
    }

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
    char buffer[BUFFERSIZE];
    char song_buff[BUFFERSIZE];
    char artist_buff[BUFFERSIZE];
    char year_buff[BUFFERSIZE];
    char time_buff[BUFFERSIZE];

    while (1)
    {
        printf("Enter 'a' to add\nEnter 'r' to remove\nEnter 'fp' to print forwards\nEnter 'bp' to print backwards\nEnter 'f' to End");
        fgets(buffer, BUFFERSIZE, stdin);

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
        else if (strcmp("r\n", buffer) == 0)
        {
            printf("artist to be removed:");
            fgets(artist_buff, BUFFERSIZE, stdin);
            remove_node(artist_buff);
        }
        else if (strcmp("fp\n", buffer) == 0)
        {
            print_forwards(head);
        }
        else if (strcmp("bp\n", buffer) == 0)
        {
            print_backward(head);
        }
        else
        {
            printf("Enter a valid character\n");
        }
    }
    return 0;
}
