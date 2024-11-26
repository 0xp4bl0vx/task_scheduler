/*
 * Program developed by Pablo Moya, Samuel Tarancón & Ignacio Pérez (Group 9)
 */

#include <stdio.h>
#include <stdbool.h>

// Custom data type for tasks
typedef struct {
    int id;
    int duration;
    int priority;
    int dependencies[499];
    bool completed;
} Task;

// Functions

/*
 * The first argument is a pointer to an array of Task datatype
 * create_tasks and executes tasks return values by reference
 */

void create_tasks(Task *tasks, int *tasks_size);
void execute_tasks(Task *tasks, int tasks_size, int *execution_time);
void status(Task *tasks, int tasks_size);
void report(Task *tasks, int tasks_size, int execution_time);

int main() {
    // Variables
    int tasks_size = 0, execution_time = 0;

    // Array of structs for storing the tasks
    Task tasks[500];

    /*
    * If you need to test functions remember to clear the main before doing the commit
    * or test the function in another file
    */

    //Menu goes here

    return 0;
}
