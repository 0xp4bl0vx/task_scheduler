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
    bool can_be_executed;
    double weight;
} Task;

// Enum for the different modes, makes the code easier to read
enum mode {judge = 0, user};

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
    int option = 0;

    // Array of structs for storing the tasks
    Task tasks[MAX_TASKS];

    scanf("%d", &mode);

    while (option != 5) {
        if (mode == user) {
            printf("Menu:\n");
            printf("1. Enter tasks\n");
            printf("2. Execute task scheduling\n");
            printf("3. Show the status of all tasks\n");
            printf("4. View results report\n");
            printf("5. Exit\n");
            printf("Choose an option: ");
        }
        scanf(" %d", &option);
        switch (option) {
            case 1:
                create_tasks(tasks, &tasks_num, mode);
                break;
            case 2:
                execute_tasks(tasks, tasks_num, &execution_time, mode);
                break;
            case 3:
                status(tasks, tasks_num, mode);
                break;
            case 4:
                report(tasks, tasks_num, execution_time, mode);
                break;
        }
    }

    if (mode == user) {
        printf("Thank you for using the task scheduling simulator...");
    }
}

void execute_tasks(Task *tasks, int tasks_num, int *execution_time, int mode) {
    /*
     * To order the task, each element of the array is compared with the
     * previous element. If the element is smaller, the element position
     * is changed with the previous one. This process is repeated until
     * the array is sorted. Each task has a weight based on priority,
     * duration and id. If it is impossible to execute the task the weight
     * is a big number calculated with the id, for the array to order correctly.
     */

    // For each task the weight is calculated and the execution time is added to the total
    for (int i = 0; i < tasks_num; i++) {
        tasks[i].weight = (tasks[i].priority * pow(10, 7) + tasks[i].duration * pow(10, 3) + tasks[i].id) * !tasks[i].completed;
    }

    // To order the tasks taking into account the dependencies a new weight is calculated
    for (int i = 0; i < tasks_num; i++) {
        int j = 0;
        // Check if task has dependencies
        while (tasks[i].dependencies[j] != -1) {

            // Detects is the task is dependency of his dependency, if it is a special weight is assigned.
            int k = 0;
            while (tasks[tasks[i].dependencies[j]].dependencies[k] != -1) {
                if (tasks[tasks[i].dependencies[j]].dependencies[k] == i || !tasks[tasks[i].dependencies[j]].can_be_executed) {
                    tasks[i].weight = tasks[i].id * pow(10, 8);
                    tasks[i].can_be_executed = false;
                }
                k++;
            }

            // If the task cant be executed, stop ordering by dependencies
            if (!tasks[i].can_be_executed) {break;}

            // If the task has more priority than the dependencies a new weight is calculated
            // The new weight is the weight of the dependency and the task weight as the decimal part
            if (tasks[i].weight < tasks[tasks[i].dependencies[j]].weight && !tasks[tasks[i].dependencies[j]].completed
                && tasks[i].dependencies[j] != tasks[i].id) {

                // Replace the original weight with the new weight
                tasks[i].weight = tasks[tasks[i].dependencies[j]].weight + tasks[i].weight * pow(10, -9);
            }
            j++;

        }
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
        if (!tasks[i].completed && tasks[i].weight < pow(10, 8)) {
            tasks[i].completed = true;
            *execution_time += tasks[i].duration;
            if (mode == user) {
                printf("Task %d started...\n", tasks[i].id);
                printf("Task %d completed in %d seconds.\n", tasks[i].id, *execution_time);
            }
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
    } while (*tasks_num > MAX_TASKS);

    // Then, it assigns an ID to each task and prompts the user
    // to enter their corresponding duration and priority

    for (int i = 0; i< *tasks_num; i++) {
        tasks[i].id = i;
        tasks[i].completed = false;
        tasks[i].can_be_executed = true;

        if (user == mode) {
            printf("For task with ID #%d\n", tasks[i].id);
        }

        //Duration assignment
        do{
            if (mode == user) {
                printf("\tEnter task duration (in seconds, must be positive): ");
            }
            scanf("%d", &tasks[i].duration);
            if (tasks[i].duration >= 1000 || tasks[i].duration < 0 && mode == user) {
                printf("\tThe maximum duration for a task is 1000 seconds. Also, it must be positive. Try again.\n");
            }
        } while (tasks[i].duration >= 1000 || tasks[i].duration < 0 );


        //Priority assignment
        do{
            if (mode == user) {
                printf("\tEnter task priority (lower values indicate higher priority): ");
            }

            scanf("%d", &tasks[i].priority);
            if (tasks[i].priority > 25 || tasks[i].priority < 1 && mode == user) {
                printf("That priority level is not valid. Try again.\n");
            }
        } while (tasks[i].priority > 25 || tasks[i].priority < 1);
    }

    /*
     * Now, the functions requests a dependency list
     * for each task, that will be stored in an array
     * independent for every task
     */

    for (int i = 0; i < *tasks_num; i++) {
        int k = 0;
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

void status(Task *tasks, int tasks_num, int mode) {
    //This function shows the status of each task
    if (mode == user) {
        for(int i = 0; i< tasks_num; i++) {

            printf("\tTask #%d - ", tasks[i].id);
            printf("Priority: %d, ", tasks[i].priority);
            printf("Status: %s, ", tasks[i].completed ? "completed" : "pending");
            printf("Dependencies: ");
            int j = 0;
            //if the dependency in the slot 0 is -1 it shows that it doesn't have dependencies
            if (tasks[i].dependencies[j] == -1) {
                printf("none\n ");
            }
            //if it has them, each dependency is printed until -1 is detected
            else {
                while (tasks[i].dependencies[j] != -1) {
                    printf("%d ", tasks[i].dependencies[j]);
                    j++;
                }
                printf("\n");
            }
        }
    }
}

void report(Task *tasks, int tasks_num, int execution_time, int mode) {
    if (mode == user) {
        printf("Total time: %d seconds.\n", execution_time);
        printf("Completed tasks: ");
    } else {
        printf("%d\n", execution_time);
    }
    for (int i = 0; i < tasks_num; i++) {
        if (tasks[i].completed == true) {
            printf("%d ", tasks[i].id);
        }
    }
    printf("\n");
    if (mode == user) {
        printf("Uncompleted tasks: ");
    }
    for (int i = 0; i < tasks_num; i++) {
        if (tasks[i].completed == false) {
            printf("%d ", tasks[i].id);
        }
    }
    printf("\n");
}