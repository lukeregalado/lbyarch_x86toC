#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void imgCvtGrayDoubleToInt(int total_size, float* image, int* int_image);

// generates random float values (depending on total_size)
void generate_random_image(float* image, int total_size) {
     int i;
     for (int i = 0; i < total_size; i++) {
         image[i] = (float)rand() / RAND_MAX; // Random float between 0 and 1
     }
}

// function that validates the correctes of output
int validate_output(float* image, int* int_image, int total_size) {
    int i;
    for (i = 0; i < total_size; i++) {
        int expected = (int)(image[i] * 255.0 + 0.5); // expected rounded int value
        
        if (int_image[i] != expected) {
            printf("Mismatch! at index %d: expected %d, got %d\n", i, expected, int_image[i]);
            return 0;
        }
    }
    return 1;
}

void test_mode() {
    int sizes[] = {10, 100, 1000}; // test case dimensions
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    int iterations = 30;          // specs: "run at least 30 times to get ave. exec. time"
    srand(time(NULL));            // seed for num. gen.
    
    int s, i, iter;

    for (s = 0; s < num_sizes; s++) {
        int width = sizes[s];
        int height = sizes[s];
        int total_size = width * height;

        for (i = 0; i < 63; i++) {
             if (i == 0) {          // top left
                printf("%c", 218);   
                
             }  else if (i == 62) { // top right
                printf("%c\n", 191);
                
             } else {               // horizontal line
                printf("%c", 196);
             }
         }
         
        char sprint_image_size[100];
        sprintf(sprint_image_size, "Testing for image size: %dx%d", width, height);
        printf("%c %-59s %c\n", 179, sprint_image_size, 179);

        // initialize image arrays
        float* image = (float*)malloc(total_size * sizeof(float));
        int* int_image = (int*)malloc(total_size * sizeof(int));
        
        if (image == NULL || int_image == NULL) {
            printf("Memory allocation failed for size %dx%d\n", width, height);
            return;
        }

        // for total time elapsed (all 30 iterations)
        double total_time = 0.0;
        int runs = 0;

        for (iter = 0; iter < iterations; iter++) {
            generate_random_image(image, total_size); 

            // timer
            clock_t start = clock();
            imgCvtGrayDoubleToInt(total_size, image, int_image);
            clock_t end = clock();

            // get sum of all iterations
            total_time += (double)(end - start) / CLOCKS_PER_SEC;
            runs++;

            // validate output
            if (!validate_output(image, int_image, total_size)) {
                printf("Validation failed for size %dx%d on iteration %d\n", width, height, iter + 1);
                free(image);
                free(int_image);
                return;
            } 
        }
        
         for (i = 0; i < 63; i++) {
             if (i == 0) {          // top left
                printf("%c", 195);   
                
             }  else if (i == 62) { // top right
                printf("%c\n", 180);
                
             } else {               // horizontal line
                printf("%c", 196);
             }
         }
        
        char runs_string[100];
        sprintf(runs_string, "Ran %d times.", runs);
        printf("%c %-59s %c\n", 179, runs_string, 179);
        
        // if it gets out of the for loop, it means no data mismatch in the validation occurred
        printf("%c %-59s %c\n", 179, "Validation succeeded! All values accounted for.", 179);

        // display ave. exec. time
        char message[100];
        sprintf(message, "Average execution time for size %dx%d: %.6f seconds", width, height, total_time / iterations);
        printf("%c %-59s %c\n", 179, message, 179);

       for (i = 0; i < 63; i++) {
         if (i == 0) {          // bot left
            printf("%c", 192);   
            
         }  else if (i == 62) { // bot right
            printf("%c\n", 217);
            
         } else {               // horizontal line
            printf("%c", 196);
         }
       }

        free(image);
        free(int_image);
    }
}

void manual_mode() {
    int rows, cols;
    int i, j;

    // user prompt: no. of rows, no. of columns
    printf("Enter the height and width (e.g., 3 4):\n");
    scanf("%d %d", &rows, &cols);

    // calculate total size
    int total_size = rows * cols;

    // initialize image arrays
    float* image = (float*)malloc(total_size * sizeof(float));
    int* int_image = (int*)malloc(total_size * sizeof(int));
    
    if (image == NULL || int_image == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    // user prompt: values for each pixel (row by col)
    printf("\nEnter the pixel values (row by row):\n");
    for (i = 0; i < total_size; i++) {
        scanf("%f", &image[i]);
    }

    // call asm func
    imgCvtGrayDoubleToInt(total_size, image, int_image);

    // display converted values
    printf("\nConverted image (integer values):\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d ", int_image[i * cols + j]);
        }
        printf("\n");
    }

    free(image);
    free(int_image);
}

void display_menu() {
     int i;
     for (i = 0; i < 52; i++) {
         if (i == 0) {          // top left
            printf("%c", 218);   
            
         }  else if (i == 51) { // top right
            printf("%c\n", 191);
            
         } else {               // horizontal line
            printf("%c", 196);
         }
     }
     
     printf("%c%31s%19s%c\n", 179, "Choose Mode", "", 179);
     
     for (i = 0; i < 52; i++) {
         if (i == 0) {          // leftmost
            printf("%c", 195);   
         }  else if (i == 51) { // rightmost
            printf("%c\n", 180);
         } else if (i == 4) {   // intersection
            printf("%c", 194);
         } else {               // horizontal line
            printf("%c", 196);
         }
     }
     printf("%c 1 %c Test mode (random input, timing, validation) %c\n", 179, 179, 179);
     
     for (i = 0; i < 52; i++) {
         if (i == 0) {          // leftmost
            printf("%c", 195);   
            
         }  else if (i == 51) { // rightmost
            printf("%c\n", 180);
            
         } else if (i == 4) {   // intersection
            printf("%c", 197);
            
         } else {               // horizontal line
            printf("%c", 196);
         }
     }
     printf("%c 2 %c Manual input mode (user inputs pixel values) %c\n", 179, 179, 179);
     
     for (i = 0; i < 52; i++) {
         if (i == 0) {          // bot left
            printf("%c", 192);   
            
         }  else if (i == 51) { // bot right
            printf("%c\n", 217);
            
         } else if (i == 4) {   // intersection
            printf("%c", 193);
            
         } else {               // horizontal line
            printf("%c", 196);
         }
     }
}

int main() {
    int choice;

    display_menu();
    
    printf("Select: ");
    scanf("%d", &choice);

    if (choice == 1) {
        test_mode();
    } else if (choice == 2) {
        manual_mode();
    } else {
        printf("Invalid choice. Exiting.\n");
    }

    return 0;
}
