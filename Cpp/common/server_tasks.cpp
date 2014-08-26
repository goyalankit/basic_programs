/*
There are at most eight servers in a data center. Each server has got a capacity/memory limit. There can be at most 8 tasks that need to be scheduled on those servers. Each task requires certain capacity/memory to run, and each server can handle multiple tasks as long as the capacity limit is not hit. Write a program to see if all of the given tasks can be scheduled or not on the servers?

Ex:
Servers capacity limits: 8, 16, 8, 32
Tasks capacity needs: 18, 4, 8, 4, 6, 6, 8, 8
For this example, the program should say 'true'.

Ex2:
Server capacity limits: 1, 3
Task capacity needs: 4
For this example, program should return false.

Got some idea that this needs to be solved using dynamic programming concept, but could not figure out exact solution.
*/

#include <iostream>
#include <algorithm>
#include <vector>

#define NUM_SERVERS 4
#define NUM_TASKS 8

using namespace std;

int totalLimit(int limits[], int size) {
  int sum = 0;
  for (int i = 0; i < size; ++i) {
    sum += limits[i];
  }
  return sum;
}

bool canScheduleHelper(int serverLimits[], int tasks[], int task_low) {
  // all the tasks are scheduled.
  if (task_low >= NUM_TASKS) return true;

  for (int i=0; i < NUM_SERVERS; ++i) {
    if (tasks[task_low] <= serverLimits[i]) {
      serverLimits[i] -= tasks[task_low];

      if (canScheduleHelper(serverLimits, tasks, task_low+1))
        return true;

      serverLimits[i] += tasks[task_low];
    }
  }
  return false;
}

bool canSchedule(int serverLimits[], int tasks[]) {
  // Base Case
  // simply check that the total server limit is greater than the total task requirements.
  if (totalLimit(serverLimits, NUM_SERVERS) < totalLimit(tasks, NUM_TASKS)) return false;

  std::cout << "It might be possible to schedule the tasks..." << std::endl;

  return canScheduleHelper(serverLimits, tasks, 0);
}

void printArray(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    std::cout << arr[i] << " ";
  }
  std::cout << "" << std::endl;
}

bool sort_op(int &i, int &j) {
  return i > j;
}

int main(void) {
  int serverLimits[NUM_SERVERS] = {8, 16, 8, 32};
  int tasks[NUM_TASKS] = {4, 8, 4, 6, 6, 8, 8, 18};

  // sort both the arrays
  sort(serverLimits, serverLimits + NUM_SERVERS, sort_op);
  sort(tasks, tasks + NUM_TASKS, sort_op);

  // print both arrays
  printArray(serverLimits, NUM_SERVERS);
  printArray(tasks, NUM_TASKS);

  std::cout << boolalpha << canSchedule(serverLimits, tasks) << std::endl;

  return EXIT_SUCCESS;
}
