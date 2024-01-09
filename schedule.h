#ifndef SHEDULE_H
#define SHEDULE_H
#include "contato.h"

node* newContact();
void insertInOrder(node **list, node *new);
void deleteByName(node **list,char string[45]);
void showList(node *list);
void loadFileTxt(node **list);
void loadFileBin(node **list);
void saveFileTxt(node **list);
void saveFileBin(node **list);
void menu();

#endif