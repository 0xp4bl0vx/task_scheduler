# Task Scheduler
C-based simulation that manages the scheduling of a set of tasks based on their duration, priority,
and dependencies. Each task has a unique identifier, a duration in seconds, and a priority. Additionally,
some tasks depend on others; that is, certain tasks cannot begin until the tasks they depend on are completed.

## Operating Modes:
- 0 judge mode:
  - Without menu and info messages
  - Only raw output
- 1 user mode:
  - Menu and info messages 
  - Formatted output 

## Task struct:
- task_id (max 500) (int)
- duration (max 1000 seconds) (int)
- priority (1-25, 1 higher) (int)
- dependencies (task_id's, -1 for no dependencies) (int array)
- completed (bool)
- weight (used for sorting tasks)

## Functions:
- create_tasks() -> Create tasks and store them in an array, max 500 tasks
- execute_tasks() -> Execute tasks by priority, shortest execution time and smallest id, taking into account dependencies
- status() -> Show if tasks are completed
- report() -> Show report of the execution
  - total execution time
  - list of completed tasks
  - list of uncompleted tasks due to unmet dependencies 

## Example output:
### User mode:
```
1
Menu:
1. Enter tasks
2. Execute task scheduling
3. Show the status of all tasks
4. View results report
5. Exit
Choose an option: 1
Enter the total number of tasks: 3
For task with ID #0:
Enter task duration (in seconds, must be positive): 5
Enter task priority (lower values indicate higher priority): 2
For task with ID #1:
Enter task duration (in seconds, must be positive): 3
Enter task priority (lower values indicate higher priority): 1
For task with ID #2:
Enter task duration (in seconds, must be positive): 4
Enter task priority (lower values indicate higher priority): 3
Enter dependencies for task 0 (end with -1): -1
Enter dependencies for task 1 (end with -1): -1
Enter dependencies for task 2 (end with -1): 1
-1
Menu:
1. Enter tasks
2. Execute task scheduling
3. Show the status of all tasks
4. View results report
5. Exit
Choose an option: 3
Status of all tasks:
Task #0 - Duration: 5 sec, Priority: 2, Status: pending, Dependencies: none
Task #1 - Duration: 3 sec, Priority: 1, Status: pending, Dependencies: none
Task #2 - Duration: 4 sec, Priority: 3, Status: pending, Dependencies: 1
Menu:
1. Enter tasks
2. Execute task scheduling
3. Show the status of all tasks
4. View results report
5. Exit
Choose an option: 2
Task 1 started...
Task 1 completed in 3 seconds.
Task 0 started...
Task 0 completed in 8 seconds.
Task 2 started...
Task 2 completed in 12 seconds.
Task scheduling completed.
Menu:
1. Enter tasks
2. Execute task scheduling
3. Show the status of all tasks
4. View results report
5. Exit
Choose an option: 4
Total time: 12 seconds.
Completed tasks: 1 0 2
Menu:
1. Enter tasks
2. Execute task scheduling
3. Show the status of all tasks
4. View results report
5. Exit
Choose an option: 5
Thank you for using the task scheduling simulator...
```

### Judge mode:
```
0  // Judge mode
1  // Option to enter tasks
3  // Total number of tasks
   // Task introduction
   // Task 0
5  // Task 0 duration in seconds
2  // Task 0 priority

   // Task 1
3  // Task 1 duration in seconds
1  // Task 1 priority

   // Task 2
4  // Task 2 duration in seconds
3  // Task 2 priority

   // Dependency introduction
-1 // End of dependencies for task 0
-1 // End of dependencies for task 1
1  // Task 2 depends on task 1
-1 // End of dependencies for task 2
3  // Option to display task status
2  // Option to execute task scheduling
4  // Option to view results report
5  // Exit program

12 // Execution time
1 0 2 // Ordered list of executed task
      // List of unexecuted tasks
```