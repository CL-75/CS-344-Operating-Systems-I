/**********************
Name: Casey Levy
Info: CS 344 - Module 1 Assignment - Movies
Program Description: Reading CSV file content and creating a linked list of structs made
     from the file content

Some code inspired from Assignment 1 Canvas explorations pages
as well as from https://replit.com/@cs344/studentsc#main.c
***********************/

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*****

Movie struct
Code inspired from Module 1 Exploration: Arrays and Structures
and from https://replit.com/@cs344/studentsc#main.c

******/
struct movie {
    int movie_year;
    char* language;
    char* movie_title;
    double movie_rating;
    struct movie* next;
};


/*****

Function to allocate memory and make new entries for movies. 
Uses tokens to store data in movie struct.
Pointer usage with help from Module 1 Exploration: Pointers
as well as from https://replit.com/@cs344/studentsc#main.c

*****/
struct movie* make_movie(char* curr) {
    struct movie* current = malloc(sizeof(struct movie));   // Allocating memory
    double num;
    char* pointer;         // Creating variables needed for code below
    char* string;
    int copy;
    char* movie_token = strtok_r(curr, ",", &pointer);

    // Movie title
    current->movie_title = calloc(strlen(movie_token) + 1, sizeof(char));
    strcpy(current->movie_title, movie_token);

    // Movie year 
    movie_token = strtok_r(NULL, ",", &pointer);
    copy = atoi(movie_token);
    current->movie_year = copy;

    // Movie language
    movie_token = strtok_r(NULL, ",", &pointer);
    current->language = calloc(strlen(movie_token) + 1, sizeof(char));
    strcpy(current->language, movie_token);

    // Movie rating
    movie_token = strtok_r(NULL, ",", &pointer);
    num = strtod(movie_token, &string);
    current->movie_rating = num;
    

    current->next = NULL;    // Setting next node to NULL in newly created movie
    return current;
}


/*****

Function to read file, in this case, the given .csv file
Code ispired from https://replit.com/@cs344/studentsc#main.c

*****/

struct movie* readFile(char* movie_file, int* num) {
    FILE* file = fopen(movie_file, "r");    // Opening file for read only
    char* temp = NULL;
    char* tok;
    struct movie* head = NULL;    // Creating needed variables
    struct movie* tail = NULL;
    size_t len = 0;
    ssize_t read;

    while((read = getline(&temp, &len, file)) != -1) {     // Reading file line by line
        *num = *num+1;
        struct movie* new = make_movie(temp);

        if(head == NULL) {
            tail = new;
            head = new;
        }

        else {
            tail->next = new;
            tail = new;
        }
    }

    // Freeing memory and closing file
    free(temp);
    fclose(file);
    return head;
    
}



/*****

Function for user to choose movies based on their lanaguage choice

*****/
void user_movie_lang(struct movie* data) {
    bool end = false;
    char language_arr[20];
    printf("\nTo see movies in a specific language, please enter the language you prefer: ");
    scanf("%s", language_arr);

    while (data != NULL){
        if(strstr(data->language, language_arr)) {
            printf("%d %s\n", data->movie_year, data->movie_title);     // Gathering necessary movie data
            end = true;
        } 
        data = data -> next;
    }

    if (end == false) {
        printf("Error: There unfortunately are no movies in your preferred language. (HINT: Be sure to use proper capitalization in your entry)\n");
        
    }

}



/*****

Function for user to choose movies based on year input

*****/
void user_movie_year(struct movie* data) {
    bool end = false;
    int user_year = 0;
    printf("\nPlease enter a year to see all movies released then: ");
    scanf("%d", &user_year);

    while (data != NULL) {
        if(user_year == data -> movie_year) {
            printf("%s\n", data -> movie_title);
            end = true;
        }

        data = data -> next;
    }
    if(end == false) {
        printf("\nError: No movies released that year.\n");
    }
}


/*****

Function for user to choose movies based on input rating

*****/
void user_movie_rating(struct movie* data) {
    int x = 0;
    for (x = 1900; x <= 2021; x++) {
        struct movie* highest = NULL;
        struct movie* temp = NULL;
        struct movie* extra_data = data;
        while (extra_data != NULL) {
            if (extra_data->movie_year == x) {
                temp = extra_data;

                while (temp != NULL) {
                    if (temp->movie_year == extra_data->movie_year) {
                        if (temp->movie_rating >= extra_data->movie_rating)
                            highest = temp;


                        else if (temp->movie_rating < extra_data->movie_rating)
                            highest = extra_data;
                    }

                    temp = temp->next;

                }

                printf("%d %.1f %s\n", highest->movie_year, highest->movie_rating, highest->movie_title);
                break;
            }

            else
                extra_data = extra_data->next;
        }
    }
}


/*****

Function for user menu to use program.

*****/
void user_menu(struct movie* movie_info) {
    bool end = false;
    int user_input = 0;
    do {
        printf("\n------------ Movie Program ------------\n");
        printf("\nPlease select an option from the list below by entering the corresponding number and pressing 'ENTER': \n");
        printf("\n1. Display movies based on entered language. \n");
        printf("\n2. Display all movies released in the entered year. \n");
        printf("\n3. Display the highest rated movie from each year. \n");
        printf("\n4. Exit \n");

        int validate = scanf("%d", &user_input);

        if (user_input == 1) {
            user_movie_lang(movie_info);
            end = true;
        }

        else if (user_input == 2) {
            user_movie_year(movie_info);
            end = true;
        }

        else if (user_input == 3) {
            user_movie_rating(movie_info);
            end = true;
        }

        else if (user_input == 4) {
            printf("\nExiting...\n");
            end = true;
        }

        else if(validate != 1) {
            printf("\nERROR: Invalid entry. Please enter only a number from the given options (1-4).\n");
            break;
        }

        else {
            printf("\nERROR: Invalid entry. Please enter only a number from the given options (1-4).\n");
            break;
        }

    } while (end == false);
}
