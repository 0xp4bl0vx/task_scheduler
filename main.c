/*
 * Program developed by Pablo Moya, Samuel Tarancón & Ignacio Pérez (Group 9)
 */

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

const int MAX_TASKS = 500;

// Custom data type for tasks
typedef struct {
    int id;
    int duration;
    int priority;
    int dependencies[499];
    bool completed;
    double weight;
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

void execute_tasks(Task *tasks, int tasks_num, int *execution_time) {
    /*
     * To order the task, the bubble algorithm is used. Bubble consist in
     * comparing each element of the array with the previous element. If
     * the element is smaller, the element position is changed with the
     * previous one. This process is repeated until the array is sorted
     * As this algorithm uses a list of arrays, each task hash a weight
     * based on priority, duration and id. If it is completed the
     * weight is 0.
     */

    // For each task the weight is calculated and the execution time is added to the total
    for (int i = 0; i < tasks_num; i++) {
        tasks[i].weight = (tasks[i].priority * pow(10, 7) + tasks[i].duration * pow(10, 3) + tasks[i].id) * !tasks[i].completed;
    }

    // To order the tasks taking into account the dependencies a new weight is calculated
    for (int i = 0; i < tasks_num; i++) {
        int j = 0;
        double new_weight = 0;
        // Check if task has dependencies
        while (tasks[i].dependencies[j] != -1) {
            // If the task has more priority than the dependencies a new weight is calculated
            // The new weight is the weight of the dependency and the task weight as the decimal part
            if (tasks[i].dependencies[j] <= tasks_num) {
                if (tasks[i].weight < tasks[tasks[i].dependencies[j]].weight && new_weight < tasks[tasks[i].dependencies[j]].weight) {
                    new_weight = tasks[tasks[i].dependencies[j]].weight + tasks[i].weight * pow(10, -9);
                }
            } else {
                new_weight = -1;
            }
            j++;
        }
        // Replace the original weight with the new weight
        tasks[i].weight = new_weight;
    }

    // Start the sorting of the array
    bool sorted = false;
    while (!sorted) {
        // If no changes are made in the array, sorted is true so the array ends
        sorted = true;
        for (int i = 1; i < tasks_num; i++) {
            // If the previous weight is bigger they change positions
            if (tasks[i - 1].weight > tasks[i].weight && tasks[i].weight > 0) {
                Task temp = tasks[i - 1];
                tasks[i - 1] = tasks[i];
                tasks[i] = temp;
                sorted = false;
            }
        }
    }

    for (int i = 0; i < tasks_num; i++) {
        if (!tasks[i].completed && tasks[i].weight > 0) {
            printf("Task %d started...\n", tasks[i].id);
            printf("Task %d completed in %d seconds.\n", tasks[i].id, tasks[i].duration);
            *execution_time += tasks[i].duration;
        }
        // Judge Output
    }
}