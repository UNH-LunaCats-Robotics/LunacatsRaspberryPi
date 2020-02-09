struct vertex {
    double x;
    double y;
    //edges
    struct edge* edges;

    //Info for Dijkstra
    int id;
    int d;
    int parent;
    int index; //Might shift to heap specific struct

    //For use in linked lists
    struct vertex* next;
};

struct edge {
    vertex* dest;
    double distance;
    double angle;

    struct edge* next;
};

struct roadmap {
    struct vertex** array;
    int count;
    int max;
};

vertex* newVertex(int id);

void addedge(vertex* v1, vertex* v2, double d);

roadmap* roadmap_create(int size);
void roadmap_delete(roadmap* map);
int roadmap_size(roadmap* map);
void roadmap_insert(roadmap* map, vertex* v);
vertex* roadmap_peek(roadmap* map);
vertex* roadmap_extract(roadmap* map);
