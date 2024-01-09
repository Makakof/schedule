#ifndef CONTATO_H
#define CONTATO_H

typedef struct node
{
    char name[45];
    char sex[2];
    char telephone[15];
    int age;
    struct node *next;
}node;

#endif