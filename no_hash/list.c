#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define DBNAME "countries.csv"
#define MAX_LINE_LENGTH 128

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
 *Ищет в списке пред. страну с заданным именем name. Возвращает указатель на
 *найденный элемент списка или NULL, если страна с таким названием отсутсвует
 *в списке.
 */
country *find_prev(country *list, char *name) {
    country *curr = list;
    country *prev = NULL;
    while (curr->next && strcmp(curr->name, name)) {
        prev = curr;
        curr = curr->next;
    } 
    return prev;
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

/*
 *Возвращает количество элементов в списке
 */
int count(country *list) {
    int cnt = 0;
    while (list) {
        list = list->next;
        cnt++;
    }
    return cnt;
}

/* Быстрая сортировка массива указателей на элементы списка */
void quick_sort(country **ca, int first, int last, cmp_func compare) {
    int i, j;
    country *v;
    country *p;

    i = first;
    j = last;
    v = ca[(first + last) / 2];

    do {
        while (compare(ca[i], v) < 0) i++;
        while (compare(ca[j], v) > 0) j--;
 
        if (i <= j) {
            if (compare(ca[i], ca[j]) > 0) {
                p = ca[j];
                ca[j] = ca[i];
                ca[i] = p;
            }
            i++; j--;
        }
    } while (i <= j);

    if (i < last)
        quick_sort(ca, i, last, compare);

    if (first < j)
        quick_sort(ca, first, j, compare);
}

int compare_name(country *v1, country *v2) {
    return (v1 && v2) ? strcmp(v1->name, v2->name) : 1;    
}

int compare_area(country *v1, country *v2) {
    return v1->area - v2->area;
}

int compare_population(country *v1, country *v2) {
    return v1->population - v2->population;
}

/*
 *Сортирует список по именам стран в алфавитном порядке методом пузырьковой
 *сортировки. Указатель на начало списка может измениться в результате   
 *сортировки
 */
int sort(country **list, cmp_func compare) {
    int cnt, i;
    country *p, **ca = NULL;

    cnt = count(*list);
    if (cnt < 2)
        return 0;
    
    /* выделяем память под массив указателей */
    ca = (country **)malloc(cnt*sizeof(country *));
    if (!ca)
        return 1;
 
    /* заполняем массив указателями на элементы списка */
    ca[0] = *list;
    for (i = 1; i < cnt; i++)
        ca[i] = ca[i-1]->next;

    quick_sort(ca, 0, cnt - 1, compare);

    /* заполняем список элементами из отсортированного массива */
    *list = NULL;
    while (cnt > 0) {
        ca[cnt - 1]->next = *list;
        *list = ca[cnt - 1];
        cnt--;
    }
    free(ca);
    return 0;
}

int sort_by_name(country **list) {
    return sort(list, compare_name);
}

int sort_by_area(country **list) {
    return sort(list, compare_area);
}

int sort_by_population(country **list) {
    return sort(list, compare_population);
}

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

void dump(country *list) {
    country *p = list;

    while (p != NULL) {
        print_country(p);
        p = p->next;
    }
}

/* Удаляет элемент списка list и освобождает выделенную по него память.
 *  Если элемент первый, изменяет указатель на список
 */
void delete(country **list, country *v) {
    country *del_next = find_prev(*list, v->name);
    
    if (del_next)
        del_next->next = v->next;
    else
        if (!compare_name(*list, v))
            *list = (*list)->next;
    
    free(v);
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

/* Загружает список стран из файла */
country *load() {
    char buf[MAX_LINE_LENGTH + 1];
    char *par[3];
    int cnt, pcount = 0;
    country *p, *list = NULL;
    FILE *f = fopen(DBNAME, "r");

    buf[MAX_LINE_LENGTH] = 0x00;
 
    if (f) {
        while (fgets(buf, MAX_LINE_LENGTH, f)) {
            pcount = 0;
            par[pcount++] = buf;
            cnt = 0;
            while (buf[cnt]) {
                if (buf[cnt] == ',') {
                    buf[cnt] = 0x00;
                    par[pcount++] = &buf[cnt + 1];
                }
                cnt++;
            }
            if (pcount == 3) {
                add(&list, par[0], atoi(par[1]), atoi(par[2]));
            }           
        }
        fclose(f);
    }
    return list;
}

/* Сохраняет список стран в файл */
void save(country *list) {
    FILE *f = fopen(DBNAME, "w+");
    country *p = list;

    if (f) {
        while (p != NULL) {
            fprintf(f, "%s,%d,%d\n", p->name, p->population, p->area);
            p = p->next;
        }

        fclose(f);
    }
}