#include "map.h"

/**
 * Return the Link with the lowest position
 *
 * Parameters
 * 1. link - current link to print
 * 2. order_by - 0 or 1, specifying which genome we are ordering by
 */
Link * get_minimum(Link * link, size_t order_by);

/**
 * Print Link structures in specified order
 *
 * Parameters:
 * 1. link - current link to print
 * 2. order_by - 0 or 1, specifying which genome we are ordering by
 */
void recursive_print(Link * link, size_t order_by);

/**
 * Remove all entries in the list with scores below a given threshold
 *
 * Parameters
 * 1. link - current link to print
 * 2. threshold - minimum score required to retain a link
 */
Link * winnow(Link * link, float threshold);
