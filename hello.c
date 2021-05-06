#include <omp.h>

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <inttypes.h>
#include <unistd.h>
#include <math.h>

#define nthreads 1

void getEnergy(){

    uint64_t  msr_value;
    double energy_units = pow (0.5, 14);

    //Open File in Read-Only mode
    int fd = open("/dev/cpu/0/msr", O_RDONLY);
    if (fd < 0){
        printf("Errore nell'apertura del file\n");
		exit(1);
    }

    //Reading Address into file
    if (pread(fd, &msr_value, 8, 0x611) < 0) {
        perror("rdmsr:pread");
		exit(1);
    }

    double energy = msr_value*energy_units;
    printf("%f\n", energy);
}

int main(int argc, char **argv){

#pragma omp parallel num_threads(nthreads)
getEnergy();

printf("\n");
return 0;

}

