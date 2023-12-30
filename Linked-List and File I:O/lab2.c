/*
Author: Ibrahim Mohamed
Date Created: 3/29/23
Lab 2
Purpose: Implement a linked list to store data read from a file
stream
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
char name [50] ; 
double grade ; 
struct node* next ; 
};

// function prototypes
struct node* create_node (char *name , double grade) ;
struct node* push_data (char *name , double grade , struct node*
list) ;

void print_list (struct node *list) ;
void delete_list (struct node *list) ;
void print_file (char *filename) ;

// bonus functions
double max_grade (struct node *list) ;
double min_grade (struct node *list) ;
struct node *file_to_list (char *filename) ;

int main ( ) {
// test linked  actual function definitions of the required
functions
*/

// create_node function
struct node *create_node(char *name, double grade) {
   struct node *new_node = (struct node*)malloc(sizeof(struct
node));
   if (new_node == NULL) {
       printf("memory allocation failed\n");
       abort();
   }
   strcpy(new_node->name, name);
   new_node->grade = grade;
   new_node->next = NULL;
   // Free any allocated memory in case of failure
   if (new_node->name == NULL) {
       free(new_node);
       return NULL;
   }
   return new_node;
}

// push_data function
struct node* push_data(char* name, double grade, struct node*
list) {
   struct node* new_node = create_node(name, grade);
   new_node->next = list;
   return new_node;
}

// print_list function
void print_list(struct node* list) {
   if (list == NULL) {
       printf("empty list\n");
return; }
   struct node* current_node = list;
   while (current_node != NULL) {
       printf("(%s, %.1f)->", current_node->name, current_node-
>grade);
       current_node = current_node->next;
   }
   printf("NULL\n");
}

// delete_list function
void delete_list(struct node* list) {
   struct node* curr = list;
   while (curr != NULL) {
       struct node* temp = curr;
       curr = curr->next;
       free(temp);
}

}
// bonus functions max_grade and min_grade
double max_grade(struct node* list) {
   double max = list->grade;
   struct node* current = list->next;
   while (current != NULL) {
       if (current->grade > max) {
           max = current->grade;
       }
       current = current->next;
   }
return max; }
double min_grade(struct node* list) {
   double min = list->grade;
   struct node* current = list->next;
   while (current != NULL) {
       if (current->grade < min) {
           min = current->grade;
       }
       current = current->next;
   }
return min; }

// print_file function
void print_file(char* filename) {
   FILE* fp = fopen(filename, "r");
   if (fp == NULL) {
       printf("Error: Could not open file '%s'\n", filename);
abort(); }
   char name[50];
   double grade;
   while (fscanf(fp, "%s %lf", name, &grade) == 2) {
       printf("(%s, %.1lf)\n", name, grade);
   }
   fclose(fp);
}

// file_to_list function
struct node* file_to_list(char* filename) {
   FILE* fp = fopen(filename, "r");

if (fp == NULL) {
       printf("Error: Could not open file '%s'\n", filename);
abort(); }
   struct node* front = NULL;
   char name[50];
   double grade;
   while (fscanf(fp, "%s %lf", name, &grade) == 2) {
       struct node* new_node = create_node(name, grade);
       if (new_node == NULL) {
           printf("Error creating new node\n");
           delete_list(front);
           fclose(fp);
           return NULL;
}
       front = push_data(new_node->name, new_node->grade, front);
   }

fclose(fp);
   return front;
}