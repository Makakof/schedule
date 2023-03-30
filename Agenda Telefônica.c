#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "schedule.h"

//
// Created by Luiz Henrique S.S on 05/03/2023.
//

/*O intuito dessa atividade é fazer uma agenda telefonica que seja persistente
e guarde os valores em um arquivo .txt e .bin*/


node* newContact()
{
    node *new;
    new = (node *) malloc(sizeof(node));

    printf("Qual o nome do contato: \n");
    scanf(" %[^\n]",new->name);
    printf("Qual o sexo do contato? Digite M para masculino e F para feminino: \n");
    scanf(" %s",new->sex);
    printf("Qual o telefone do contato? \n");
    scanf(" %[^\n]",new->telephone);
    printf("Qual a idade do contato? \n");
    scanf("%d",&new->age);
    new->next = NULL;

    return new;
}

void insertInOrder(node **list, node *new)
{
    node *p,*q;
    q = *list;
    p = NULL;

    while(q != NULL && strcmp(new->name,q->name) > 0)
    {
        p = q;
        q = q->next;
    }

    if(q == NULL)
    {
        if(p == NULL)
        {
            *list = new;
        }
        else
        {
            p->next = new;
        }
    }
    else
    {
        if(p == NULL)
        {
            new->next = q;
            *list = new;
        }
        else
        {
            new->next = q;
            p->next = new;
        }
    }
}

void deleteByName(node **list,char string[45])
{
    node *q,*p;
    q = *list;
    p = NULL;

    while(q != NULL && strcmp(string, q->name) > 0)
    {
        p = q;
        q = q->next;
    }
    if(q != NULL)
    {
        if(p != NULL)
        {
            p->next = q->next;
        }
        else
        {
            *list = q->next;
        }
        free(q);
    }
}

void showList(node *list)
{
    printf("\n");
    node *q;
    printf("Os contatos da agenda são: \n");
    for(q = list;q != NULL;q = q->next)
    {
        printf("Nome: %s\n",q->name);
        printf("Sexo: %s\n",q->sex);
        printf("Telefone: %s\n",q->telephone);
        printf("Idade: %d anos\n",q->age);
        printf("\n");

    }
    printf("\n");
}

void loadFileTxt(node **list)
{
    FILE *file;
    node *new;
    file = fopen("contatos.txt","r");
    if(file == NULL)
    {
        printf("Erro ao abrir aquivo contatos.txt!\n");
        return 1;
    }
    while(!feof(file))
    {
        new = (node *) malloc(sizeof(node));
        fscanf(file,"%[^;];%[^;];%[^;];%d\n",new->name,new->sex,new->telephone,&new->age);
        new->next = NULL;
        insertInOrder(list,new);
    }
    fclose(file);
}

void loadFileBin(node **list)
{
    FILE *file;
    node *new;
    file = fopen("contatos.bin","rb");
    if(file == NULL)
    {
        printf("Erro ao abrir aquivo contatos.bin!\n");
        return 1;
    }
    /*Faço uma leitura antes do laço para poder colocar o insert no inicio do laço
    isso impede de que na ultima vez lixo da memória seja inserido na lista, uma vez que
    ele verifica primeiro se acabou o arquivo antes de inserir*/
    new = (node *) malloc(sizeof(node));
    fread(new, sizeof(node), 1, file);
    new->next = NULL;
    while(!feof(file))
    {
        insertInOrder(list,new);
        new = (node *) malloc(sizeof(node));
        fread(new, sizeof(node), 1, file);
        new->next = NULL;
    }
    fclose(file);

}

void saveFileTxt(node **list)
{
    FILE *file;
    node *q;
    file = fopen("contatos.txt","w");
    if(file == NULL)
    {
        printf("Erro ao abrir aquivo contatos.txt!\n");
        return 1;
    }
    for(q = *list;q != NULL;q=q->next)
    {
        fprintf(file,"%s;%s;%s;%d\n",q->name,q->sex,q->telephone,q->age);
    }
    fclose(file);
}

void saveFileBin(node **list)
{
    FILE *file;
    node *q;
    file = fopen("contatos.bin","wb");
    if(file == NULL)
    {
        printf("Erro ao abrir aquivo contatos.bin!\n");
        return 1;
    }
    for(q = *list;q != NULL;q=q->next)
    {
        //fprintf(file,"%s;%s;%s;%d\n",q->name,q->sex,q->telephone,q->age);
        fwrite(q, sizeof(node), 1, file);
    }
    fclose(file);
}


void menu()
{
    printf("\n");
    printf("*******************************\n");
    printf("1-INSERIR CONTATO\n");
    printf("2-ALTERAR CONTATO\n");
    printf("3-EXCLUIR CONTATO\n");
    printf("4-SALVAR AGENDA EM .txt\n");
    printf("5-SALVAR AGENDA EM .bin\n");
    printf("6-CARREGAR AGENDA EM .txt\n");
    printf("7-CARREGAR AGENDA EM .bin\n");
    printf("8-MOSTRAR AGENDA\n");
    printf("0-SAIR\n");
    printf("*******************************\n");
    printf("Digite a opção desejada: ");
}

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