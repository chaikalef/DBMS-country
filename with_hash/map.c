#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "map.h"
#define DBNAME "countries.csv"
#define MAP_SIZE 64
#define MAX_LINE_LENGTH 255

/* Функция, возвращающая значение хэша ключа.
Ключ это название страны. */
unsigned int hash(char *key) {
    unsigned int i, h = 0;

    for (i = 0; i < strlen(key); i++)
        h += key[i];

    return h % MAP_SIZE;
}

/* Функция, добавляющая элемент к хэш таблице */
void map_add(country **map, char *name, int population, int area) {
    unsigned int h = hash(name);

    country *line = find(map[h], name);

    if (line != NULL) {
        line->population = population;
        line->area = area;

    } else {
        if (add(&map[h], name, population, area) == 1)            
            printf("\nПроизошла ошибка при выделении памяти!\n");                   
    }
}

/* Функция, удаляющая страну с указанным названием из хеш таблицы */
void map_delete(country **map, char *name) {
    unsigned int h = hash(name);

    country *v = find(map[h], name);
    
    if (v != NULL)
        delete(&map[h], v);
    else
        printf("\nТакой страны нет!\n");
}

/* Функция, находящая страну с указанным названием в хеш таблице */
country *map_find(country **map, char *name) {
    unsigned int h = hash(name);

    country *v = map[h];
    
    return find(v, name);
}

/* Функция, печатающая на экране все записи хеш таблицы */
void map_dump(country **map) {
    int i;

    for (i = 0; i < MAP_SIZE; i++)
        dump(map[i]);
}

/* Функция, печатающая на экране одну запись хеш таблицы */
void map_view(country **map, char *name) {
    unsigned int h = hash(name);

    country *v = find(map[h], name);

    if (v != NULL)
        print_country(v);
    else
        printf("\nТакой страны нет!\n");        
}

/* Функция, создающая хэш таблицу */
country **map_create(void) {
    country **map = (country **)calloc(MAP_SIZE, sizeof(country *));
    return map;
}

/* Функция, удаляющая хэш таблицу */
void map_clear(country **map) {
    int i;

    for (i = 0; i < MAP_SIZE; i++)
        clear(map[i]);

    free(map);
}

/* Функция, загружающая таблицу из файла */
country **map_load() {
    char buf[MAX_LINE_LENGTH + 1], *parameters[3];
    int i, par_number;
    country **map = NULL;

    FILE *f = fopen(DBNAME, "r");

    map = map_create();

    buf[MAX_LINE_LENGTH] = '\0';
 
    if (f) {
        while (fgets(buf, MAX_LINE_LENGTH, f)) {
            par_number = 0;
            parameters[par_number++] = buf;
            i = 0;

            while (buf[i]) {
                if (buf[i] == ',') {
                    buf[i] = '\0';
                    parameters[par_number++] = &buf[i + 1];
                }
                i++;
            }
            if (par_number == 3)
                map_add(map, parameters[0], atoi(parameters[1]),
                atoi(parameters[2]));
        }
        fclose(f);
    }
    return map;
}

/* Функция, сохраняющая таблицу в файл */
void map_save(country **map) {
    int i;

    country *v;   

    FILE *f = fopen(DBNAME, "w");

    if (f) {
        for (i = 0; i < MAP_SIZE; i++) {
            v = map[i];

            while (v != NULL) {
                fprintf(f, "%s,%d,%d\n", v->name, v->population, v->area);
                v = v->next;
            }
        }
        fclose(f);
    }
}