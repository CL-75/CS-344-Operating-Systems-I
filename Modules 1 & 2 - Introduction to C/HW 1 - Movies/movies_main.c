/**********************
Name: Casey Levy
Info: CS 344 - Module 1 Assignment - Movies
Program Description: Reading CSV file content and creating a linked list of structs made
     from the file content
***********************/

#include "movies_data.c"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    int num = 0;
    if (argc < 2) {
        printf("\nFile and filename must be provided: \n");
        exit(1);
    }

    struct movie* movies = readFile(argv[1], &num);
    num = num - 1;
    printf("\nProcessed file '%s' and parsed data for %i movies.\n", argv[1], num);
    user_menu(movies);
    free(movies);

    return 0;
}