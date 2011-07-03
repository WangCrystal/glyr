#include <stdlib.h>
#include <stdio.h>

#include <pthread.h>
#include "../lib/glyr.h"

/*
 * Example program showing how to use libglyr with multiple threads.
 * Compile: gcc threads.c -o threads -pthread -L../bin -lglyr -Wall -Wextra
 * libglyr is fully thread-compatible as long every thread uses it's own query struct.
 * (Honestly: Something else won't make much sense....)
*/

static void * call_get(void * p)
{
    GlyMemCache * r = Gly_get(p,NULL,NULL);
    puts("Thread finished");
    return r;
}

static void configure(GlyQuery * s, enum GLYR_GET_TYPE type)
{
    Gly_init_query(s);
    GlyOpt_artist(s,"Die Apokalyptischen Reiter");
    GlyOpt_album (s,"Moral & Wahnsinn");
    GlyOpt_title (s,"Die Boten");
    GlyOpt_verbosity(s,1);
    GlyOpt_type  (s,type);
    GlyOpt_from(s,"fast");
}

static void printme(GlyMemCache * start)
{
    GlyMemCache * i = start;
    while(i != NULL)
    {
        Gly_write(i,"stdout");
        i = i->next;
    }

    Gly_free_list(start);
}

int main(void)
{
    /* Init */
    Gly_init();
    atexit(Gly_cleanup);

    pthread_t agent_long,agent_longer;
    GlyQuery query_long, query_longer;

    /* Fill some silly values */
    configure(&query_long,GET_SIMILIAR_ARTISTS);
    configure(&query_longer,GET_LYRICS);

    GlyMemCache * a, * b;

    /* Create two threads */
    pthread_create(&agent_long,  NULL,call_get,&query_long  );
    pthread_create(&agent_longer,NULL,call_get,&query_longer);

    puts("Running!");

    /* Wait for threads to join, get results */
    pthread_join(agent_long,  (void**)&a);
    pthread_join(agent_longer,(void**)&b);

    puts("Joined!\n---> Data: ");

    if(a && b)
    {
        printme(a);
        puts("-------------");
        printme(b);
    }

    Gly_destroy_query(&query_long);
    Gly_destroy_query(&query_longer);
    return EXIT_SUCCESS;
}