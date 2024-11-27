/*
 * Program developed by Pablo Moya, Samuel Tarancón & Ignacio Pérez (Group 9)
 */

#include <stdio.h>
#include <stdbool.h>

const int MAX_TASKS = 500;

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
 * create_tasks and executes_tasks return values by reference
 * All the prints must be inside if statements that check the user_mode variable
 */

void create_tasks(Task *tasks, int *tasks_num);
void execute_tasks(Task *tasks, int tasks_num, int *execution_time);
void status(Task *tasks, int tasks_num);
void report(Task *tasks, int tasks_num, int execution_time);
// void c_printf(char *string[], int *args[], int args_num, bool user_mode);

int main() {
    // Variables
    int tasks_num = 0, execution_time = 0;
    bool user_mode = true;

    // Array of structs for storing the tasks
    Task tasks[MAX_TASKS];

    /*
    * If you need to test functions remember to clear the main before doing the commit
    * or test the function in another file
    */

    //Menu goes here

    return 0;
}