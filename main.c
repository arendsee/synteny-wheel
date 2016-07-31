#include "map.h"
#include "algorithms.h"


int main(){

    // In production code, of course, we won't hardcode this
    Link * link = load("data.txt");

    printf("Print as ordered by genome A\n");
    recursive_print(link, 0);

    printf("\nPrint as ordered by genome B\n");
    recursive_print(link, 1);

    printf("\nLowest position on genome A\n");
    print_link(get_minimum(link, 0));

    printf("\nLowest position on genome B\n");
    print_link(get_minimum(link, 1));

    printf("\nAll links with scores above 50\n");
    recursive_print(winnow(link, 50), 0);

    return EXIT_SUCCESS;
}
