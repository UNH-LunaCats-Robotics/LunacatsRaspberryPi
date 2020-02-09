#include "../Headers/RoadMap.h"

using namespace std;

vertex* newVertex(int id) {
    vertex* v = new vertex;
    v->id = id;
    v->index = 0;
    v->parent = 0;
    v->edges = nullptr;
    //v->d = INT_MAX;
    return v;
}

void addedge(vertex* v1, vertex* v2, double d) {
    edge* e = new edge;
    e->dest = v2;
    e->distance = d;
    //e->angle = a;

    e->next = v1->edges;
    v1->edges = e;
}

void pullup(roadmap* map, int i);
void pushdown(roadmap* map, int i);

roadmap* roadmap_create(int size) {
    roadmap* map = new roadmap;
    map->array = new vertex*[size];
    for(int i = 0; i < size; i++)
	map->array[i] = nullptr;
    map->count = 0;
    map->max = size;
    return map;
}

void roadmap_delete(roadmap* map) {
    if(map != nullptr) {
        delete[] map->array;
        delete map;
    }
}

int roadmap_size(roadmap* map) {
    return map->count;
}

int parent(int i) {
    return (i - 1) / 2;
}

void exchange(roadmap* map, int i, int j) {
    map->array[i]->index = j;
    map->array[j]->index = i;
    vertex* temp = map->array[i];
    map->array[i] = map->array[j];
    map->array[j] = temp;
}

int smallest(roadmap* map, int i) {
    vertex* v1 = map->array[i];
    vertex* v2;
    if((2 * i) + 1 < map->count)
        v2 = map->array[(2*i)+1];
    else
        v2 = v1;
    vertex* v3;
    if((2 * i) + 2 < map->count)
        v3 = map->array[(2*i)+2];
    else
        v3 = v1;

    if(v1->d <= v2->d && v1->d <= v3->d)
        return i;
    else if(v2->d <= v3->d)
        return (2 * i) + 1;
    else
        return(2 * i) + 2;
}

void roadmap_insert(roadmap* map, vertex* v) {
    if(map->count < map->max) {
        map->array[map->count] = v;
        map->array[map->count]->index = map->count;
        map->count++;
        pullup(map, map->count - 1);
    }
}

void pullup(roadmap* map, int i) {
    int j = parent(i);
    if(map->array[i]->d < map->array[j]->d) {
        exchange(map, i, j);
        pullup(map, j);
    }
}

void pushdown(roadmap* map, int i) {
    int s = smallest(map, i);
    if(s != i) {
        exchange(map, i, s);
        pushdown(map, s);
    }
}

vertex* roadmap_peek(roadmap* map) {
    return map->array[0];
}

vertex* roadmap_extract(roadmap* map) {
    if(map->count == 0)
        return nullptr;
    vertex* ret = map->array[0];
    map->count--;
    map->array[0] = map->array[map->count];
    map->array[0]->index = 0;
    map->array[map->count] = nullptr;
    if(map->count > 0)
        pushdown(map, 0);

    return ret;
}
