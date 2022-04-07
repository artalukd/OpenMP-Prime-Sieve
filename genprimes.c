#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#define min(X, Y)  ((X) < (Y) ? (X) : (Y))

void calculate (char *, long long, int base);

int main(int argc, char * argv[]) {
    long long N = atoi(argv[1]);
    long number_of_threads = atoi(argv[2]);
    char * primes;
    double tstart = 0.0, ttaken;
    char * fileName = (char*) malloc(13 * sizeof(char));
    sprintf(fileName, "%lld.txt", N);
    FILE * fp = fopen(fileName,"w");
    tstart = omp_get_wtime(); 
    primes =  (char*)calloc(N+1, sizeof(char));
    
    int count = 1;

    long x = (int)(N+1)/2;
    for(int i =2; i <=min(N,3); i++){
        fprintf(fp, "%d %d \n",count++, i);
    }

    #pragma omp parallel for num_threads(number_of_threads) schedule(monotonic:dynamic)
    for(int i = 5; i <= x; i++){
        if(primes[i] == 0 && (i%2 != 0 && i%3 != 0))
        calculate(primes,N,i);
    }
    
    for (long long i = 4; i < N - 1; i++) {
    if (primes[i] == 0){
        if(i%2 == 0 || i%3 == 0)
            continue;
        fprintf(fp, "%d %lld \n",count++, i);
        }
    }
    ttaken = omp_get_wtime() - tstart;
    printf("Time take for the main part: %f\n", ttaken); 
    fclose(fp);
    free(fileName);
    free(primes);
    return 0;
}

void calculate(char * primes, long long N, int base) {
    long long ptr = 5 * base;
    while (ptr <= N) {
        if(!(ptr%2 == 0 || ptr%3 == 0))
            primes[ptr] = 1;
        ptr += base;
    }
}