/*
 * Program developed by Pablo Moya, Samuel Tarancón & Ignacio Pérez (Group 9)
 */

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define MAX_TASKS 500

// Custom data type for tasks
typedef struct {
    int id;
    int duration;
    int priority;
    int dependencies[MAX_TASKS];
    bool completed;
    double weight;
} Task;

// Enum for the different modes, makes the code easier to read
enum mode {user = 0, judge};

// Functions

/*
 * The first argument is a pointer to an array of Task datatype
 * create_tasks and executes_tasks return values by reference
 * All the prints must be inside if statements that check the user_mode variable
 */

void create_tasks(Task *tasks, int *tasks_num, int mode);
void execute_tasks(Task *tasks, int tasks_num, int *execution_time, int mode);
void status(Task *tasks, int tasks_num, int mode);
void report(Task *tasks, int tasks_num, int execution_time, int mode);

int main() {
    // Variables
    int tasks_num = 0, execution_time = 0;
    int mode = user;

    // Array of structs for storing the tasks
    Task tasks[MAX_TASKS];

    /*
    * If you need to test functions remember to clear the main before doing the commit
    * or test the function in another file
    */
    return 0;
}

void execute_tasks(Task *tasks, int tasks_num, int *execution_time, int mode) {
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
                if (tasks[i].weight < tasks[tasks[i].dependencies[j]].weight && new_weight < tasks[tasks[i].dependencies[j]].weight
                    && !tasks[tasks[i].dependencies[j]].completed && tasks[i].dependencies[j] != tasks[i].id) {

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
            if (mode == user) {
                printf("Task %d started...\n", tasks[i].id);
                printf("Task %d completed in %d seconds.\n", tasks[i].id, tasks[i].duration);
            }
            tasks[i].completed = true;
            *execution_time += tasks[i].duration;
        }
    }
}

void create_tasks(Task *tasks, int *tasks_num, int mode) {
    // First, the function asks the user for the number of tasks

    do{
        if (mode == user) {
            printf("Enter the total number of tasks: ");
        }
        scanf("%d", tasks_num);
        if (*tasks_num > MAX_TASKS && mode == user) {
            printf("The maximum number of tasks is 500. Try again.\n");
        }
    }while(*tasks_num > MAX_TASKS);

    // Then, it assigns an ID to each task and prompts the user
    // to enter their corresponding duration and priority

    //  ID assignment
    for (int i = 0; i < *tasks_num; i++) {
        tasks[i].id = i;
    }

    for (int i=0; i< *tasks_num; i++) {
        if (user == mode) {
            printf("For task with ID #%d\n", tasks[i].id);
        }

    //Duration assignment
    do{
        if (mode == user) {
            printf("\tEnter task duration (in seconds, must be positive): ");
        }
        scanf("%d", &tasks[i].duration);
        if ((tasks[i].duration >= 1000 && mode == user) || (tasks[i].duration < 0 && mode == user) ) {
            printf("\tThe maximum duration for a task is 1000 seconds. Also, it must be positive. Try again.\n");
        }
    }while( (tasks[i].duration >= 1000 )  ||  (tasks[i].duration < 0) );


    //Priority assignment
    do{
        if (mode == user) {
            printf("\tEnter task priority (lower values indicate higher priority): ");
        }

        scanf("%d", &tasks[i].priority);
        if (tasks[i].priority > 25 || tasks[i].priority < 1 && mode == user) {
            printf("That priority level is not valid. Try again.\n");
        }
    }while(tasks[i].priority > 25 || tasks[i].priority < 1);
    }

    /*
     * Now, the functions requests a dependency list
     * for each task, that will be stored in an array
     * independent for every task
     */

    for (int i = 0; i < *tasks_num; i++) {
        int k=0;
        if (mode == user) {
            printf("Enter dependencies for task %d (end with -1): ", tasks[i].id);
        }

        while (k < MAX_TASKS) {
            int dependency_id;
            scanf("%d", &dependency_id);

            if (dependency_id == -1) {
                tasks[i].dependencies[k] = -1; // Marking the end of the dependencies
                break;
            }

            // Checking if the dependency ID is valid
            int valid = 0;
            for (int j = 0; j < *tasks_num; j++) {
                if (tasks[j].id == dependency_id) {
                    valid = 1;
                    break;
                }
            }

            // If it's not valid, the program goes to the next iteration of the while statement,
            // skipping the assigning part
            if (!valid) {
                if (mode == user){
                printf("Invalid dependency. Task ID %d does not exist. Please try again.\n", dependency_id);
                }
                continue;
            }

            // Assigning a valid dependency
            tasks[i].dependencies[k] = dependency_id;
            k++;
        }
    }
}
