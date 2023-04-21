// Andrew Pipo (pipoat)
// pipoat@mail.uc.edu
// CS2011 Intro to Computer Systems
// Lab 04



#include "lab4.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h> 

// One main struct for the entire cache.
struct Cache{
    long valid;
    long tag;
    long lru;
};

// Tracking of the hits, misses and evictions. Initialized at 0 for all
int hit_count = 0;
int miss_count = 0;
int evict_count = 0;

/* 

Per lab document

-h: Optional help flag that prints usage info
• -v: Optional verbose flag that displays trace info
• -s <s>: Number of set index bits (S =2s is the number of sets)
• -E <E>: Associativity (number of lines per set)
• -b <b>: Number of block bits (B =2b is the block size)
• -t <tracefile>: Name of the valgrind trace to replay

*/


int s, b, E, v, size, B;

// Initialize the struct
struct Cache **cache = NULL;

// Set up the counter for lru and mask ;long for precision.
long mask = 0;
long lruCounter = 0;

void fileTrace(char *fileName);
void print(char* argv);
void initCache();
void cleanCache();
void useCache(unsigned long addr);


// A function used to run the trace of the valgrind file.
// @param fileName the variable used for the actual filename of the trace

void fileTrace(char *fileName)
{
    char buf[1024];

    // Open the file.
    FILE *fp = fopen(fileName, "r");

    // This will print error and return if file not found.
    if (fp == NULL)
    {
        printf("The file cannot be found.\n\n");
        return;
    }

    // File opened, read a line from the stream and store it in buf
    while (fgets(buf, 1024, fp))
    {
        unsigned long addr = 0;
        unsigned size = 0;

        // Checking for the chars, L, S, or M.
        //L is a data load.
        //S is a data store
        //M is data modify

        if (buf[1] == 'S' ||
            buf[1] == 'L' ||
            buf[1] == 'M'){

            
            sscanf(buf + 2, "%lx,%u", &addr, &size);

            //If the verbose flag is 1 then we print.
            if (v)
                printf("%c %lx,%u ", buf[1], addr, size);
            useCache(addr);

            //If it is M then we modify the data, simply by calling the useCache function.
            if (buf[1] == 'M')
            {
                useCache(addr);
            }

            if (v) putchar('\n');
        }
    }
    // Closing the file
    fclose(fp);
}


// Function to initiate the cache.
void initCache()
{
    // Allocate the memory for the cache.
    cache = malloc(size * sizeof(*cache));

    // Use calloc to our advantage and allocate memory for the cache while also initializing it to zero
    for (int i = 0; i < size; i++)
    {
        //Our E is number of lines per set.
        cache[i] = calloc(E, sizeof(*cache[i]));
    }

    mask = size - 1;
}

void useCache(unsigned long addr)
{
    
    // We right shift the addr by b and use the mask to get the set.
    long set = (addr >> b) &mask;

    // We right shift the addr again by b + s to get the tag.
    long tag = (addr >> (b+s));

    int x = 0;

    // Loop through the cache.
    while (x < E)
    {
        // Checking if both the tag and the valid bit are not 0.
        if (cache[set][x].tag == tag && cache[set][x].valid != 0)
        {
            // If true: hit, increase hit counter, print hit.
            hit_count++;
            if (v) printf("hit ");

            //We also update the lru.
            cache[set][x].lru = lruCounter++;
            return;
        }
        else{
            x++;
        }
    }

    // If not a hit, it is miss, thus everything else is a miss.
    miss_count++;

    // Initialize the variables; lrum to the lowest memory addr for comparisons.
    long lrum = 0xFFFFFFFF;
    int evictL = 0;

    if (v) printf("miss ");

    int i = 0;
    while (i < E)
    {
        //If lru min is greater than counter
        if (lrum > cache[set][i].lru)
        {
            evictL = i;
            lrum = cache[set][i].lru;
        }
        i++;
    }

    // Checking if valid bit == 1, if it is then increase the hit count, print eviction.
    if (cache[set][evictL].valid == 1)
    {
        evict_count++;
        if (v) printf("eviction ");
    }

    // Set the rest of the cache before exiting function
    cache[set][evictL].valid = 1;
    cache[set][evictL].tag = tag;
    cache[set][evictL].lru = lruCounter++;
}

void cleanCache() // cleans cache
{
    free(cache);
}

void print(char * argv)  // print function for summary
{
    printf("Usage: %s [-hv] -s <num> -E <num> -b <num> -t <file>\n", argv);
    printf("Options:\n");
    printf("  -h         Print this help message.\n");
    printf("  -v         Optional verbose flag.\n");
    printf("  -s <num>   Number of set index bits.\n");
    printf("  -E <num>   Number of lines per set.\n");
    printf("  -b <num>   Number of block offset bits.\n");
    printf("  -t <file>  Trace file.\n");
    exit(0);
}

int main (int argc, char * argv[])
{
    // Declare variables
    char opt = 0;
    char *file = NULL;

    
    while ((opt = getopt(argc, argv, "s:E:b:t:vh")) != -1)
    {
        switch (opt)
        {
            case 's':
                s = atoi(optarg); //optarg utilized for each case

                if (s == 0){
                    return 1;
                }
                break;
            case 'E':
                E = atoi(optarg);
                if (E == 0){
                    return 1;
                }
                break;
            case 'b':
                b = atoi(optarg);
                if (b == 0){
                    return 1;
                }
                break;
            case 't':
                file = optarg;
                if (file == 0){
                    return 1;
                }
                break;
            case 'v':
                v = 1;
                break;
            default:
                print(argv[0]);
                return 1;
        }
    }

    // Updating size
    size = 1 << s;
    B = 1 << b;

    // Calls main functions and prints the summary
    initCache();
    fileTrace(file);
    cleanCache();

    printSummary(hit_count, miss_count, evict_count);
    return 0;
}