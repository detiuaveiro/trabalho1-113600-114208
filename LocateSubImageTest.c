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
    const char* largeImages[] = {"pgm/large/airfield-05_1600x1200.pgm"};
    const char* mediumImages[] = {"pgm/medium/mandrill_512x512.pgm"};
    const char* smallImages[] = {"pgm/small/art3_222x217.pgm"};

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
    int count = 0;


    FILE *fp = fopen("testes.txt", "w");

    if (fp == NULL)
    {
        printf("Error opening the file testes.txt");
        return -1;
    }

    
    
    for (int i = 0; i < 1; i++) {
        Image largeImage1 = ImageLoad(largeImages[i]);
        Image largeImage2 = ImageLoad(largeImages[i]);
        for (int j = 0; j < 1; j++) {

            Image mediumImage = ImageLoad(mediumImages[j]);

            for (int k = 0; k < 1; k++) {

                for (int l = 0; l < 2; l++)
                {
                   
                    Image smallImage = ImageLoad(smallImages[k]);


                    printf("count: %d\n", count);


                    if (largeImage1 == NULL || largeImage2 == NULL || mediumImage == NULL || smallImage == NULL) {
                        printf("Failed to load images.\n");
                        continue;
                    }

                    
                    pasteX = 100;
                    pasteY = 100;

                    if (l>0){
                        ImagePaste(largeImage1, pasteX, pasteY, mediumImage);
                    }


                    COMP = 0;

                    // Measure the time it takes to locate the subImages
                    start_time = cpu_time();
                    foundLargeMedium = ImageLocateSubImage(largeImage1, &x1, &y1, mediumImage);
                    finish_time = cpu_time();
                    exec_time1 = finish_time - start_time;

                    comp1 = COMP;        

                    pasteX = 100;
                    pasteY = 100;     

                    if (l>0){
                        ImagePaste(largeImage2, pasteX, pasteY, smallImage);
                    }


                    COMP = 0;

                    start_time = cpu_time();
                    foundLargeSmall = ImageLocateSubImage(largeImage2, &x2, &y2, smallImage);
                    finish_time = cpu_time();
                    exec_time2 = finish_time - start_time;

                    comp2 = COMP;    

                    pasteX = 100;
                    pasteY = 100;

                    if (l>0){
                        ImagePaste(mediumImage, pasteX, pasteY, smallImage);
                    }


                    COMP = 0;

                    start_time = cpu_time();
                    foundMediumSmall = ImageLocateSubImage(mediumImage, &x3, &y3, smallImage);
                    finish_time = cpu_time();
                    exec_time3 = finish_time - start_time;

                    comp3 = COMP;    

                    // Print the results
                    if (foundLargeMedium) {
                        fprintf(fp,"LM Position: (%d, %d)\n", x1, y1);
                    }else{
                        fprintf(fp,"LM Position: Not Found\n");
                    }
                    fprintf(fp,"LM Execution Time: %lf\n", exec_time1);
                    fprintf(fp,"LM Image1 Size: %s (%d x %d)\n",largeImages[i], ImageWidth(largeImage1), ImageHeight(largeImage1));
                    fprintf(fp,"LM Image2 Size: %s (%d x %d)\n",mediumImages[j], ImageWidth(mediumImage), ImageHeight(mediumImage));
                    fprintf(fp,"LM Comparisons: %d\n", comp1);
                    fprintf(fp,"\n");

                    if (foundLargeSmall) {
                        fprintf(fp,"LS Position: (%d, %d)\n", x2, y2);
                    }else{
                        fprintf(fp,"LS Position: Not Found\n");
                    }

                    fprintf(fp,"LS Execution Time: %lf\n", exec_time2);
                    fprintf(fp,"LS Image1 Size: %s (%d x %d)\n",largeImages[i], ImageWidth(largeImage2), ImageHeight(largeImage2));
                    fprintf(fp,"LS Image2 Size: %s (%d x %d)\n",smallImages[k], ImageWidth(smallImage), ImageHeight(smallImage));
                    fprintf(fp,"LS Comparisons: %d\n", comp2);
                    fprintf(fp,"\n");

                    if (foundMediumSmall) {
                        fprintf(fp,"MS Position: (%d, %d)\n", x3, y3);
                    }else{
                        fprintf(fp,"MS Position: Not Found\n");
                    }

                    fprintf(fp,"MS Execution Time: %lf\n", exec_time3);
                    fprintf(fp,"MS Image1 Size: %s (%d x %d)\n",mediumImages[j], ImageWidth(mediumImage), ImageHeight(mediumImage));
                    fprintf(fp,"MS Image2 Size: %s (%d x %d)\n",smallImages[k], ImageWidth(smallImage), ImageHeight(smallImage));
                    fprintf(fp,"MS Comparisons: %d\n", comp3);

                    // Free the images


                    fprintf(fp,"*****************************************\n");

                    count++;


                    

                    ImageDestroy(&smallImage);
                }
                

            }

            ImageDestroy(&mediumImage);
        }

        
        ImageDestroy(&largeImage1);
        ImageDestroy(&largeImage2);
    }

    fclose(fp);

    return 0;
}
