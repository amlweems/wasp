/*
 * wasp - an ASP.NET Random() brute force device
 *  Functions derived from .NET source code
 */

#include <sys/time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#include "asp.h"

static long long counter = 0;
double st;

/*
 * --- EDIT THIS FUNCTION ---
 * This function should return true if the Random() object
 * has been successfully seeded (an example is shown).
 */
static inline bool
Success()
{
    return ((Next(0, 26) == 16) &&
            (Next(0, 26) == 14) &&
            (Next(0, 10) ==  6) &&
            (Next(0,  3) ==  1) &&
            (Next(0, 26) ==  9) &&
            (Next(0, 26) == 11) &&
            (Next(0, 10) ==  0) &&
            (Next(0,  3) ==  1));
}

void
summary(int unused)
{
    struct timeval tv;
    double secs;
    char buf[100];

    gettimeofday(&tv, (struct timezone *)NULL);
    secs = tv.tv_sec + tv.tv_usec * 1e-6 - st;
    if (secs < 1e-6)
        secs = 1e-6;
    snprintf(buf, sizeof(buf),
        "%qu seeds tested %.6f secs (%.0f seeds/sec)\n",
        counter, secs, counter / secs);
    write(2, buf, strlen(buf));
}

int
main(int argc, char **argv) {
    struct timeval tv;
    gettimeofday(&tv, (struct timezone *)NULL);
    st = tv.tv_sec + tv.tv_usec * 1e-6;

    signal(SIGINFO, summary);

    int seed = 0;
    if (argc > 1) {
        seed = atoi(argv[1]);
    }
    int start = seed;

    setbuf(stdout, NULL);
    printf("[+] Starting brute force.\n");
    do {
        Random(seed);
        if (Success()) {
            printf("[+] Found seed: %d\n", seed);
            summary(0);
            return 0;
        }
        seed++;
        counter++;
    } while (seed != start);
    printf("[-] Seed not found. :(\n");
    summary(0);
    return 1;
}
