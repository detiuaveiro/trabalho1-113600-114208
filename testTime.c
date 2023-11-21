#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "instrumentation.h"
#include "image8bit.h"

int main(void)
{   
    Image img = ImageLoad("pgm/small/art3_222x217.pgm");

    double start_time = cpu_time();

    ImageBlur(img, 3, 3);

    double finish_time = cpu_time();

    double exec_time = finish_time - start_time;

    printf("Exec time: %f\n", exec_time);

    return 0;
}
