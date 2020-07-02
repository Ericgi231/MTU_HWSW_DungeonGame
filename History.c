//Eric Grant
//ewgrant
//history of user actions

#include "History.h"
#include <stdlib.h>
#include <stdio.h>

//init action history
void historyInit(History* history){
    Node* node = malloc(sizeof(Node));
    node->next = NULL;
    history->first = node;
}

//add action to history
void historyAdd(History* history, Action action){
    //create current node and an empty node
    Node* node;
    Node* n = malloc(sizeof(Node));
    n->next = NULL;

    //loop through nodes starting at the head until a node with no next is found
    node = history->first;
    while (node->next != NULL)
    {
        node = node->next;
    }
    
    //add action to node and empty node to next
    node->action = action;
    node->next = n;
}

//print action history
void historyPrint(const History* history){
    Node* node;
    node = history->first;
    while (node->next != NULL)
    {
        printf("%s ", actionToString(node->action));
        node = node->next;
    }
    printf("\n");
}

//clear action history
void historyUninit(History* history){
    Node* temp;

    //clear head node and set next to new head, repeat until all nodes clear
    while (history->first != NULL)
    {
        temp = history->first;
        history->first = history->first->next;
        free(temp);
    }
}