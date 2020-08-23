#include <stdio.h>
#include <string.h>
#include <sys/queue.h>


int main() {
    // The TAILQ_ENTRY macro is used to establish the pointers used to insert items into the list.
    // You place it into your structure that you want to list up.
    struct foo {
        TAILQ_ENTRY(foo) tailq;
        int datum;
        /* ... */
    };

    //The TAILQ_HEAD is used to define a structure 
    // that will act as the container for your link list elements. 
    // You provide it with a structure name, 
    // and the name of the type that it will contain.

    TAILQ_HEAD(fooq, foo);

    //Use TAILQ_INIT to initialize an instance of your list container.

    struct fooq q;
    TAILQ_INIT(&q);

    //Use the TAILQ_INSERT_* macros to add elements.

    struct foo data[3] = { foo(3), foo(7), foo(1) };
    TAILQ_INSERT_HEAD(&q, &data[0], tailq);
    TAILQ_INSERT_AFTER(&q, &data[0], &data[1], tailq);
    TAILQ_INSERT_TAIL(&q, &data[2], tailq);

    //You can use TAILQ_FOREACH and TAILQ_FOREACH_REVERSE to traverse the list.

    struct foo *p;
    TAILQ_FOREACH(p, &q, tailq) {
        printf(" %d", p->datum);
    }
    puts("");

    //If you want to iterate over the list while removing all its elements, 
    // it is probably easier to use a while loop 
    // and use the TAILQ_EMPTY and TAILQ_FIRST macros.

    while (!TAILQ_EMPTY(&q)) {
        p = TAILQ_FIRST(&q);
        TAILQ_REMOVE(&q, p, tailq);
        /* ... */
    }
}
