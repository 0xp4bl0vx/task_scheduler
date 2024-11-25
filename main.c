#include <stdio.h>
#include <stdbool.h>

// Custom data type for tasks
struct task {
    int id;
    int duration;
    int priority;
    int dependencies[500];
    bool completed;
};

// Functions
void create_tasks(struct task *tasks, int tasks_size);
void execute_tasks(struct task *tasks, int tasks_size, int *execution_time);
void status(struct task *tasks, int tasks_size);
void report(struct task *tasks, int tasks_size, int execution_time);
void menu(struct task *tasks, int tasks_size);

int main(void) {

    return 0;
}
