#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "schedule.h"

//
// Created by Luiz Henrique S.S on 05/03/2023.
//

/*O intuito dessa atividade é fazer uma agenda telefonica que seja persistente
e guarde os valores em um arquivo .txt e .bin*/



int main (void)
{
    int end = 0;
    int option;
    char string[45];
    node *list = NULL;
    node *new = NULL;
    do
    {
        menu();
        scanf("%d",&option);
        switch (option)
        {
            case 1:
                new = newContact();
                insertInOrder(&list,new);
                printf("Contato inserido com sucesso!\n");
            break;
            case 2:
                printf("Digite o nome do contato de que deseja alterar: ");
                scanf(" %[^\n]",string);
                deleteByName(&list,string);
                new = newContact();
                insertInOrder(&list,new);
            case 3:
                printf("Digite o nome do contato que deseja apagar: ");
                scanf(" %[^\n]",string);
                deleteByName(&list,string);
                printf("Contato deletado com sucesso!\n");
            break;
            case 4:
                saveFileTxt(&list);
                printf("Agenda salva em .txt com sucesso!\n");
            break;
            case 5:
                saveFileBin(&list);
                printf("Agenda salva em .bin com sucesso!\n");
            break;
            case 6:
                loadFileTxt(&list);
            break;
            case 7:
                loadFileBin(&list);
            break;
            case 8:
                showList(list);
            break;
            case 0:
                end = 1;
            break;
        }
    }while(!end);
    return 0;
}