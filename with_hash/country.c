#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "map.h"

// '_' -> ' '
void undecorate_name(char *name) {
    int cnt;
    while (name[cnt]) {
        if (name[cnt] == '_')
            name[cnt] = ' ';
        cnt++;
    }
}

int main(int argc, char *argv[]) {
    /* Загрузка списка */
    country **map = map_load();

    char *cmd = (char*)malloc(11 *sizeof(char));
    char *name = (char*)malloc(41 *sizeof(char));

    unsigned int population;
    unsigned int area;

    cmd[10] = '\0';
    name[40] = '\0';    

    printf("\n  ВАС ПРИВЕТСТВУЕТ СУБД \"СТРАНЫ\"\n");
    while (1) {
        printf("\nВведите команду с параметрами через пробел: \n");
        scanf("%s", cmd);

        if (strcmp(cmd, "add") == 0) {
            scanf("%s", name);
            undecorate_name(name);
            printf("Введите население (целое число): ");
            scanf("%d", &population);
            printf("Введите площадь (целое число): ");
            scanf("%d", &area);
            map_add(map, name, population, area);
            printf("Успешно выполнено \n");
        } 
        else if (strcmp(cmd, "del") == 0) {
            scanf("%s", name);
            undecorate_name(name);
            map_delete(map, name);
            printf("Успешно выполнено \n"); 
        } 
        else if (strcmp(cmd, "dump") == 0) {
            printf("Вывод всех стран\n");
            map_dump(map);
            printf("Успешно выполнено \n");
        } 
        else if (strcmp(cmd, "view") == 0) {
            scanf("%s", name);
            undecorate_name(name);
            map_view(map, name);
            printf("Успешно выполнено \n");
        } 
        else if (strcmp(cmd, "save") == 0) {
            printf("Сохранение\n");
            map_save(map);
            printf("Успешно выполнено \n");
        } 
        else if (strcmp(cmd, "quit") == 0) {
            printf("Сохранение\n");
            map_save(map);
            printf("Выход\n");
            break;
        } 
        else if (strcmp(cmd, "help") == 0) {
            printf("Варианты команд: add, del, dump, view, save, quit, help\n");
            printf("Для команды add (Добавление) введите следующие параметры:\n");
            printf("Название, Численность, Площадь\n");
            printf("Для команды delete(Удаление) введите следующие параметры:\n");
            printf("Название\n");
            printf("Для команды view (Просмотр) введите следующие параметры:\n");
            printf("Название\n");
        } 
        else {
            printf("Ошибка: нет такой команды. Попробуйте help\n");
        }
    }

    free(cmd);
    free(name);

    map_clear(map);

    return 0;
}