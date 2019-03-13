#ifndef _MAP_H_
#define _MAP_H_

country **map_create(void);
void map_clear(country **map);
void map_add( country **map, char *name, int population, int area);
void map_delete(country **map, char *name);
country *map_find(country **map, char *name);
void map_dump(country **map);
country **map_load();
void map_save(country **map);
void map_view(country **map, char *name);

#endif // _MAP_H_