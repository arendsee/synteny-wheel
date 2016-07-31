#include "algorithms.h"

// ============================================================================
// Recursive functions
// ----
// Since the genomes are circular, it is necessary to store the initial input
// (except with get_minimum_r). If these algorithms are mis-implemented, they
// can easily result in infinite loops.
// ============================================================================

Link * get_minimum_r(Link * link, size_t order_by, Link * current_min){

    // TODO: Fill in the code

    return link;
}

void recursive_print_r(Link * link, size_t order_by, Link * stop_link){

    // TODO: Fill in the code

}

Link * winnow_r(Link * link, float threshold, Link * stop_link){

    // TODO: Fill in the code

    return link;
}


// ============================================================================
// These functions are wrappers for the real recursive functions.
// ============================================================================
Link * get_minimum(Link * link, size_t order_by){
    return get_minimum_r(link, order_by, link->p[order_by]->next->parent);
}

void recursive_print(Link * link, size_t order_by){
    recursive_print_r(link, order_by, link->p[order_by]->prev->parent);
}

Link * winnow(Link * link, float threshold){
    return winnow_r(link, threshold, link->p[0]->prev->parent);
}
