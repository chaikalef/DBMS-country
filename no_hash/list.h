#ifndef _LIST_H_
#define _LIST_H_

typedef struct _country {
    char name[256];
    int population;
    int area;
    struct _country *next;
} country;

int add( country **list, char *name, int population, int area);
void delete(country **list, country *v);
country *find(country *list, char *name);
int count(country *list);
int sort_by_name(country **list);
int sort_by_area(country **list);
int sort_by_population(country **list);
void dump(country *list);
void print_country(country *p);
void clear(country *list);
country *load();
void save(country *list);

#endif // _LIST_H_