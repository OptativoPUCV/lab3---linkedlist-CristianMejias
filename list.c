#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList()
{
  List* lista = (List*) malloc(sizeof(List));
  lista->head = NULL;
  lista->tail = NULL;
  lista->current = NULL;
  return lista;
}

void * firstList(List * list)
{
  list->current = list->head;
  if (list->current != NULL)
    return list->current->data;
  return NULL;
}

void * nextList(List * list)
{
  if (list->current)
    list->current = list->current->next;
  
  if (list->current)
    return list->current->data;
  return NULL;
}

void * lastList(List * list)
{
  if (list->tail != NULL)
  {
    list->current = list->tail;
    return list->tail->data;
  }
  return NULL;
}

void * prevList(List * list)
{
  if (list->current)
    list->current = list->current->prev;
  if (list->current)
    return list->current->data;
  return NULL;
}

void pushFront(List * list, void * data) 
{
  Node*  nodoN = createNode(data);
  if (list->head == NULL)
  {
    list->head = nodoN;
    list->tail = nodoN;
    return;
  }
  nodoN->next = list->head;
  list->head->prev = nodoN;
  list->head = nodoN;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data)
{
  Node* nodoN = createNode(data);
  /*
  if (list->head == list->current)
    pushFront(list, data);
    ---------------------REVISAR
  */
  
  if(list->current == list->head)
  {
    nodoN->prev = list->current;
    nodoN->next = nextList(list);
    list->head->next = nodoN;
  }
  
  if (list->current == list->tail)
    {
      nodoN->prev = list->tail;
      list->tail->next = nodoN;
      list->tail = nodoN;
    }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) 
{
  if (list->current == list->head)
  {
    list->head = list->head->next;
    list->head->prev = NULL;
    list->current = list->head;
  }
  list->head->next->prev = NULL;
  free(list->current);
  list->current = firstList(list);
  return list->current->data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}