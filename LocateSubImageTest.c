#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "image8bit.h" // Assuming this is the file where ImageLocateSubImage is defined
#include "instrumentation.h"

int randomInRange(int min, int max) {
    return min + rand() % (max - min + 1);
}

int main() {
    // List of images to test
    const char* largeImages[] = {"pgm/large/airfield-05_1600x1200.pgm", "pgm/large/einstein_940x940.pgm", "pgm/large/ireland-06-1200x1600.pgm"};
    const char* mediumImages[] = {"pgm/medium/mandrill_512x512.pgm", "pgm/medium/airfield-05_640x480.pgm"};
    const char* smallImages[] = {"pgm/small/art3_222x217.pgm", "pgm/small/art4_300x300.pgm", "pgm/small/bird_256x256.pgm"};

    double start_time;
    double finish_time;
    double exec_time1;
    double exec_time2;
    double exec_time3;
    int foundLargeMedium;
    int foundLargeSmall;
    int foundMediumSmall;
    int x1, y1;
    int x2, y2;
    int x3, y3;
    int comp1;
    int comp2;
    int comp3;
    int pasteX;
    int pasteY;

    
    for (int i = 0; i < sizeof(largeImages) / sizeof(largeImages[0]); i++) {
        for (int j = 0; j < sizeof(mediumImages) / sizeof(mediumImages[0]); j++) {
            for (int k = 0; k < sizeof(smallImages) / sizeof(smallImages[0]); k++) {
                // Load the images
                Image largeImage1 = ImageLoad(largeImages[i]);
                Image largeImage2 = ImageLoad(largeImages[i]);
                Image mediumImage = ImageLoad(mediumImages[j]);
                Image smallImage = ImageLoad(smallImages[k]);

                if (largeImage1 == NULL || largeImage2 == NULL || mediumImage == NULL || smallImage == NULL) {
                    printf("Failed to load images.\n");
                    continue;
                }

                pasteX = randomInRange(0, ImageWidth(largeImage1) - ImageWidth(mediumImage));
                pasteY = randomInRange(0, ImageHeight(largeImage1) - ImageHeight(mediumImage));

                ImagePaste(largeImage1, pasteX, pasteY, mediumImage);


                COMP = 0;

                // Measure the time it takes to locate the subImages
                start_time = cpu_time();
                foundLargeMedium = ImageLocateSubImage(largeImage1, &x1, &y1, mediumImage);
                finish_time = cpu_time();
                exec_time1 = finish_time - start_time;

                comp1 = COMP;        

                pasteX = randomInRange(0, ImageWidth(largeImage2) - ImageWidth(smallImage));
                pasteY = randomInRange(0, ImageHeight(largeImage2) - ImageHeight(smallImage));        

                ImagePaste(largeImage2, pasteX, pasteY, smallImage);

                start_time = cpu_time();
                foundLargeSmall = ImageLocateSubImage(largeImage2, &x2, &y2, smallImage);
                finish_time = cpu_time();
                exec_time2 = finish_time - start_time;

                comp2 = COMP;    

                pasteX = randomInRange(0, ImageWidth(mediumImage) - ImageWidth(smallImage));
                pasteY = randomInRange(0, ImageHeight(mediumImage) - ImageHeight(smallImage));

                ImagePaste(mediumImage, pasteX, pasteY, smallImage);

                start_time = cpu_time();
                foundMediumSmall = ImageLocateSubImage(mediumImage, &x3, &y3, smallImage);
                finish_time = cpu_time();
                exec_time3 = finish_time - start_time;

                comp3 = COMP;    

                // Print the results
                printf("Large-Medium Image: %s\n", foundLargeMedium ? "Found" : "Not Found");
                if (foundLargeMedium) {
                    printf("Position: (%d, %d)\n", x1, y1);
                }
                printf("Execution Time: %f seconds\n", exec_time1);
                printf("Image1 Size: %d x %d\n", ImageWidth(largeImage1), ImageHeight(largeImage1));
                printf("Image2 Size: %d x %d\n", ImageWidth(mediumImage), ImageHeight(mediumImage));
                printf("Comparisons: %d\n", comp1);
                printf("\n");

                printf("Large-Small Image: %s\n", foundLargeSmall ? "Found" : "Not Found");
                if (foundLargeSmall) {
                    printf("Position: (%d, %d)\n", x2, y2);
                }
                printf("Execution Time: %f seconds\n", exec_time2);
                printf("Image1 Size: %d x %d\n", ImageWidth(largeImage2), ImageHeight(largeImage2));
                printf("Image2 Size: %d x %d\n", ImageWidth(smallImage), ImageHeight(smallImage));
                printf("Comparisons: %d\n", comp2);
                printf("\n");

                printf("Medium-Small Image: %s\n", foundMediumSmall ? "Found" : "Not Found");
                if (foundMediumSmall) {
                    printf("Position: (%d, %d)\n", x3, y3);
                }
                printf("Execution Time: %f seconds\n", exec_time3);
                printf("Image1 Size: %d x %d\n", ImageWidth(mediumImage), ImageHeight(mediumImage));
                printf("Image2 Size: %d x %d\n", ImageWidth(smallImage), ImageHeight(smallImage));
                printf("Comparisons: %d\n", comp3);

                // Free the images
                ImageDestroy(&largeImage1);
                ImageDestroy(&largeImage2);
                ImageDestroy(&mediumImage);
                ImageDestroy(&smallImage);

            }
        }
    }

    return 0;
}
