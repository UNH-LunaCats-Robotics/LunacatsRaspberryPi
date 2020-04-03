#include "../Headers/Dijkstra.h"

vertex* dijkstra(vertex** vertices, int count) {
    vertices[0]->d = 0;

    roadmap* map = roadmap_create(count);
    for(int i = 0; i < count; i++)
        roadmap_insert(map, vertices[i]);

    while(roadmap_size(map) > 0) {
	    //printf("%i\n", roadmap_size(map));
        vertex* u = roadmap_extract(map);
	    //printf("%i\n", roadmap_size(map));
	//printf("%i, %i, %f\n", u->id, u->index, u->d);
        if(u->id == 1)
            break;
	//printf("past break\n");
        edge* e = u->edges;
        while(e != nullptr) {
            if(e->dest->finished == 0 && e->dest->d > u->d + e->distance) {
		    //printf("edit: %i\n", e->dest->id);
                e->dest->d = u->d + e->distance;
                roadmap_pullup(map, e->dest->index);
                e->dest->parent = u->id;
            }
            e = e->next;
        }
	//printf("past while\n");
        u->finished = 1;
    }

    for(int i = 0; i < 100; i++) {
	//printf("%i <- %i\n", vertices[i]->id, vertices[i]->parent);
    }

    vertex* path = vertices[1];
    while(path->parent != -1) {
        vertices[path->parent]->next = path;
        path = vertices[path->parent];
    }

    roadmap_delete(map);
    
    return path;
}
