#include "algorithms.h"

// ============================================================================
// Recursive functions
// ----
// Since the genomes are circular, it is necessary to store the initial input
// (except with get_minimum_r). If these algorithms are mis-implemented, they
// can easily result in infinite loops.
// ============================================================================

Point * get_minimum_r(Point * pnt){
    if(pnt == NULL){
        pnt = (Point *)NULL;
    }
    else if(pnt->pos <= pnt->next->pos && pnt != pnt->next){
        pnt = get_minimum_r(pnt->prev);
    } else {
        pnt = pnt->next;
    }
    return pnt;
}

void recursive_print_r(Point * pnt){
    if(pnt != NULL){
        print_link(pnt->parent);
        if(pnt->pos <= pnt->next->pos && pnt != pnt->next){
            recursive_print_r(pnt->next);
        }
    }
}

Point * winnow_r(Point * pnt, float threshold, Point * stop_point){

    bool last = pnt == stop_point; // this is the last entry
    bool only = pnt == pnt->prev;  // this is the only node

    if(pnt->parent->score < threshold){
        Point * tmp = pnt->prev; 
        delete_link(pnt->parent);
        // We just deleted the only node
        if(only)
            return (Point *)NULL;
        pnt = tmp;
    }

    if(last){
        return pnt;
    } else {
        return winnow_r(pnt->next, threshold, stop_point);
    }
}


// ============================================================================
// These functions are wrappers for the real recursive functions.
// ============================================================================
Link * get_minimum(Link * link, size_t order_by){
    return get_minimum_r(link->p[order_by])->parent;
}

void recursive_print(Link * link, size_t order_by){
    recursive_print_r(get_minimum(link, order_by)->p[order_by]);
}

Link * winnow(Link * link, float threshold){
    return winnow_r(link->p[0], threshold, link->p[0]->prev)->parent;
}
