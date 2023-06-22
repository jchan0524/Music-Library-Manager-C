//
//  proj1.h
//  Cisc361
//
//  Created by Justin chan on 9/15/21.
//  Copyright © 2021 Justin chan. All rights reserved.
//

#ifndef proj1_h
#define proj1_h

struct node {
    char *artist;
    char *song;
    int year;
    int time;
    struct node* next;
    struct node* prev;
};
struct node *head = NULL;


#endif /* proj1_h */
