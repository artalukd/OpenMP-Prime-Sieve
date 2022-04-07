#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#define min(X, Y)  ((X) < (Y) ? (X) : (Y))

void lowerBase(char* numLine, int limit){
    int i = 3;
    while ((i*i) <= limit)
    {   
        if (numLine[i] == 0)
        {
            for(int j=3; i*j<limit; j+=2)
            {
                    numLine[i*j]=1;
            }
        }
        i++;
    }
}



int main(int argc, char * argv[]) {
    long long N = atoi(argv[1]);
    long number_of_threads = atoi(argv[2]);
    char * primes;
    int count = 1;
    char * fileName = (char*) malloc(13 * sizeof(char));
    sprintf(fileName, "%lld.txt", N);
    FILE * fp = fopen(fileName,"w");

    double tstart = 0.0, ttaken;
    tstart = omp_get_wtime();
    primes =  (char*)calloc(N+1, sizeof(char));

    long x = (int)floor(sqrt(N+1));

    lowerBase(primes, x);


    // for(long long i =2; i <=min(N,3); i++){
    //     printf("%d, %lld \n",count++, i);
    // }
    // for(long long i = 5; i < x; i++){
    // if (primes[i] == 0 && i%2 != 0 )   
    //     printf("%d, %lld \n",count++, i);
    // }
    
    long long lower = x;
    long long upper = N;

    long long block_size = (int)ceil((upper - lower*1.0)/number_of_threads);
    // printf("block size %lld %lld %lld\n", block_size,lower, upper);
    #pragma omp parallel for num_threads(number_of_threads)
    for(long long int i = lower; i < upper; i+=block_size){

        // printf("%lld %lld \n", i, block_size + i);
        for(long long int k = 3; k <= lower; k+=2){
            if(primes[k] != 0)  
                continue;
            long long start = i +(k-i%k);
            if(start%2 == 0)
                start+=k;

            // printf("%lld %lld \n", k, start);
            for(long long int j = start; j <= i+block_size; j+=k*2 ){
                primes[j] = 1;
            }
        }
        
    }

    ttaken = omp_get_wtime() - tstart;
    printf("Time take for the main part: %f\n", ttaken);
    // printf("completed loop 1\n");
    count = 1;
    for(long long int i =2; i <=min(N,3); i++){
        fprintf(fp, "%d, %lld \n",count++, i);
    }
    // printf("completed loop 2\n");
    for (long long int i = 4; i < N - 1; i++) {
    if (primes[i] == 0){
        if(i%2 == 0 || i%3 == 0)
            continue;
        fprintf(fp, "%d, %lld \n",count++, i);
        }
    }
    // printf("completed loop\n");
    fclose(fp);
    return 0;
}
