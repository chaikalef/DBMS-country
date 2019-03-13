#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

int main(int argc, char *argv[]) {
    country *list;

    /* Loading the list */
    list = load();

    /* 
    *strcmp(const char *str1, const char *str2) 
    *returns 0, if str1 == str2
    */
    if (argc > 1) {
        if (strcmp(argv[1], "add") == 0) {
            if (argc > 2 && argc < 6) {
                printf("Добавление страны \"%s\"\n", argv[2]);
                if (add(&list,  
                        argv[2],
                        (argc > 3)? atoi(argv[3]):0,
                        (argc > 4)? atoi(argv[4]):0)) {
                    printf("Произошла ошибка\n");
                }
                
                else {
                    printf("Добавление страны \"%s\" успешно завершилось\n", argv[2]);
                    print_country(list);
                }
            }
            else {
                printf("Произошла ошибка\n");
                printf("Вы ввели %d аргументов, а необходимо 5\n", argc);
                printf("Пример ввода: add <name> <population> <area>\n");
            }
        }
        else if (strcmp(argv[1], "delete") == 0) {
            if (argc == 3) {
                printf("Удаление страны \"%s\"\n", argv[2]);
                country* tmp = find(list, argv[2]);
                if (tmp) {
                    delete(&list, tmp);
                    printf("Удаление страны \"%s\" успешно завершилось\n", argv[2]);
                }
                else {
                    printf("Нет страны \"%s\"\n", argv[2]);
                }
                  
            }
            else
                printf("Пример ввода: delete <name>\n");
        }
        else if  (strcmp(argv[1], "dump") == 0) {
            if ((argc == 2)
                || !strcmp(argv[2], "-n") && !sort_by_name(&list)
                || !strcmp(argv[2], "-a") && !sort_by_area(&list)
                || !strcmp(argv[2], "-p") && !sort_by_population(&list))
                dump(list);
            else {
                 printf("Произошла ошибка\n");
                 printf("Неверно указан параметр %s\n", argv[2]);
                 printf("Используйте (-n, -a, -p)\n");
            }   
        }
        else if (strcmp(argv[1], "view") == 0) {
            if (argc == 3) {
                country *tmp = find(list, argv[2]);
                if (tmp)
                    print_country(tmp);
                else{
                    printf("Нет страны \"%s\"\n", argv[2]);
                }
            } 
            else
                printf("Произошла ошибка\nПример ввода: view <name>\n");
        }
        else if (strcmp(argv[1], "count") == 0)
            printf("Количество всех стран: %d\n", count(list));
        else{
            printf("Неизвестная команда \"%s\"\n", argv[1]);
            printf("Используйте: <dump, delete, count, view, add>\n");
        }
    }
        
    save(list);

    /* Deleting the list */
    clear(list);

    return 0;
}