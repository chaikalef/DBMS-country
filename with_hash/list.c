#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

/* Pointer's type on function for elements comparing */
typedef int (* cmp_func)(country *v1, country *v2);

/*
 *Выделяет динамическую память для нового элемента списка list,
 *инициализирует поля и добавляет элемент в начало списка
 *Изменяет указатель на начало списка. Возвращает 0 если новый элемент
 *добавлен или 1 если не удалось выделить память для элемента.
 */
int add(country **list, char *name, int population, int area) {
    country *line = (country *)malloc(sizeof(country));
    
    if (line) {
        strcpy(line->name, name);
        line->population = population;
        line->area = area;
        line->next = *list;
        *list = line;

        return 0;
    }
    return 1;
}

/*
 *Удаляет элемент списка list и освобождает выделенную по него память.
 *Если элемент первый, изменяет указатель на список
 */
void delete(country **list, country *v) {
    country *p = *list;
    country *prev = NULL;

    while (p != NULL) {
        if (p == v) {
            if (prev)
                prev->next = p->next;            
            else
                *list = p->next;
    
            free(p);
            break;
        }
        prev = p;
        p = p->next;
    }
}

/*
 *Ищет в списке страну с заданным именем name. Возвращает указатель на
 *найденный элемент списка или NULL, если страна с таким названием отсутсвует
 *в списке.
 */
country *find(country *list, char *name) {
    country *line = list;

    while (line && strcmp(line->name, name))
        line = line->next;
    return line;
}

/* Функция вывода информации об одной стране из списка */
void print_country(country *p) {
    if (!p)
        return;
    printf("Название: %s \n", p->name);
    
    if (p->population)
        printf("Численность: %d \n", p->population);
    else
        printf("Численность: не указано\n");
    
    if (p->area)
        printf("Площадь: %d\n", p->area);
    else
        printf("Площадь: не указано\n");
}

/* Функция вывода информации всех странах из списка */
void dump(country *list) {
    country *p = list;

    while (p != NULL) {
        print_country(p);
        p = p->next;
    }
}

/*
 *Удаление всех элементов списка и
 *освобождение выделенной под эти элементы памяти
 */
void clear(country *list) {
    while (list) {
        delete(&list, list);
    }
}