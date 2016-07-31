#include "map.h"

Point * init_point(unsigned int pos)
{
    Point * point = (Point *)malloc(sizeof(Point));
    point->pos = pos; 
    point->prev = NULL;
    point->next = NULL;
    return point;
}

Link * init_link(float score)
{
    Link * link = (Link *)malloc(sizeof(Link));
    link->score = score; 
    link->p = (Point **)malloc(2 * sizeof(Point *));
    link->p[0] = NULL;
    link->p[1] = NULL;
    return link;
}

void delete_point(Point * point)
{
    if(point != NULL){
        if(point->prev != NULL)
            point->prev->next = point->next;
        if(point->next != NULL)
            point->next->prev = point->prev;
        free(point);
    }
}

void delete_link(Link * link)
{
    if(link != NULL){
        if(link->p[0] != NULL)
            delete_point(link->p[0]);
        if(link->p[1] != NULL)
            delete_point(link->p[1]);
        free(link);
    }
}

void print_link(Link * link)
{
    if(link != NULL){
        printf(
            "%u\t%u\t%f\n",
            link->p[0]->pos,
            link->p[1]->pos,
            link->score
        );
    }
}

// Comparison function for sorting by left-side (genome A)
static int cmp_by_a(const void * p1, const void * p2)
{
    unsigned int a = (* (Link **) p1)->p[0]->pos;
    unsigned int b = (* (Link **) p2)->p[0]->pos;
    return a - b;
}

// Comparison function for sorting by right-side (genome B)
static int cmp_by_b(const void * p1, const void * p2)
{
    unsigned int a = (* (Link **) p1)->p[1]->pos;
    unsigned int b = (* (Link **) p2)->p[1]->pos;
    return a - b;
}

// Read data and build synteny datastructure
Link * load(char * filename){
    FILE * f = fopen(filename, "r");
    size_t size = BUFFER_SIZE;
    char * line = (char *) malloc(size * sizeof(char));
    unsigned int apos, bpos;
    float score;
    unsigned int N = 0;

    // Count number of rows in the input data file
    while (fgets(line, size, f) && !feof(f)) { N++; }
    rewind(f);

    // A temporary array of links
    Link ** links = (Link **)malloc(N * sizeof(Link *));
    
    for(size_t i = 0; fgets(line, size, f) && !feof(f); i++) {
        if (!sscanf (line, "%d %d %f", &apos, &bpos, &score)) {
            fprintf(stderr, "Could not process the following line:\n%s", line);
            exit(EXIT_FAILURE);
        }
        links[i] = init_link(score);
        links[i]->p[0] = init_point(apos);
        links[i]->p[1] = init_point(bpos);
        links[i]->p[0]->parent = links[i];
        links[i]->p[1]->parent = links[i];
    }

    // Sort by link[i]->p[0]->pos
    qsort(links, N, sizeof(Link *), cmp_by_a);
    for(size_t i = 0; i < N; i++){
        if(i != 0){
            links[i]->p[0]->prev = links[i-1]->p[0];
        }
        if(i != (N-1)){
            links[i]->p[0]->next = links[i+1]->p[0];
        }
    }
    links[0]->p[0]->prev = links[N-1]->p[0];
    links[N-1]->p[0]->next = links[0]->p[0];

    // Sort by link[i]->p[1]->pos
    qsort(links, N, sizeof(Link *), cmp_by_b);
    for(size_t i = 0; i < N; i++){
        if(i != 0){
            links[i]->p[1]->prev = links[i-1]->p[1]; 
        }
        if(i != (N-1)){
            links[i]->p[1]->next = links[i+1]->p[1];
        }
    }
    links[0]->p[1]->prev = links[N-1]->p[1];
    links[N-1]->p[1]->next = links[0]->p[1];
    
    return links[0];
}
