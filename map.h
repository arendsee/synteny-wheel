#ifndef __MAP_H__
#define __MAP_H__

#include <stdio.h>
#include <stdlib.h>

// Buffer size for a single row of data from the input file
#define BUFFER_SIZE 1024

/**
 * A location on a genome
 *
 * NOTE: Genomes are assumed to be circular. The highest Point is adjacent to
 * the lowest. Therefore every Point structure will have non-NULL prev and next
 * values (at least in the final datastructure).
 *
 * Fields:
 * pos - the position on a genome
 * prev - the previous point on this genome
 * next - the next point on this genome
 * parent - the Link object containing this Point
 */
typedef struct Point
{
    unsigned int pos;
    struct Point * prev;
    struct Point * next;
    struct Link * parent;
} Point;

/**
 * A link between two matching positions on two different genomes
 *
 * Fields:
 * p - array of 2 pointers to Point structures on genome A and genome B
 * score - a measure of the certainty that this link is correct
 */
typedef struct Link
{
    struct Point ** p;
    float score; 
} Link;

/**
 * Initialize a Point structure
 *
 * Allocate memory and initialize prev and next to NULL
 */
Point * init_point(unsigned int pos);

/**
 * Initialize a Link
 *
 * Allocate memory and initialize both p to NULL
 */
Link * init_link(float score);

/**
 * Read data from a file
 *
 * The file must be a space delimited file with the following columns:
 * 1. (int) Position on genome A
 * 2. (int) Position on genome B
 * 3. (float) Link score
 *
 * This method orders links on both sides of the genome by setting prev and
 * next in p Point structures.
 *
 */
Link * load(char * filename);

/**
 * Free memory in a Point and remove self from the linked list
 */
void delete_point(Point * point);

/**
 * Free memory for a Link and call free_point on points 
 */
void delete_link(Link * link);

/**
 * Print one Link structure
 *
 * The output is the same format as the input data file
 */
void print_link(Link * link);

#endif
