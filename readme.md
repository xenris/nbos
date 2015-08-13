# nbavr

Non-blocking AVR.

Created by Henry Shepperd (hshepperd@gmail.com)

## Aim
A set of libraries for AVR microprocessors which are assured to never block.

Plus a simple and reliable real time OS which provides the ability to run tasks (fake threads) atomically (in terms of both time and memory), and has the ability to reset tasks if they happen to crash/halt.

## TaskManager (real time os)
* The task manager is nonpreemptive, which means all tasks share the same stack and each task step has to return before the next task can start. This has the advantage that less RAM is required, and that every task is atomic relative to each other.
* The task manager also monitors each task step and will reset a task if it is taking too long, allowing all the other tasks to continue running, while giving the crashed task the chance to recover.

```c
// Create a new task manager with a maximum number of tasks.
TaskManager* taskManagerInit(uint8_t maxTasks);
```
```c
// Add a new task to a task manager.
// TaskFunctions take a void pointer and a uint32_t, and return a bool.
// dataSize is how much memory this task needs (in bytes).
// id is a string to identify this task.
// The priority can be one of PRIORITY_HIGH, PRIORITY_MEDIUM, or PRIORITY_LOW.
//  There is also PRIORITY_DRIVER, but this should only be used for things like
//  TWI and serial which require a higher priority than normal.
bool taskManagerAddTask(TaskManager* taskManager, TaskFunction taskFunction, uint16_t dataSize, const char* id, TaskPriority priority);
```
```c
// Start the task manager.
// This function never returns.
// Tasks can still be added to the task manager after it has been started
void taskManagerRun(TaskManager* taskManager);
```

## Tasks (fake threads)
* If a task takes too long to return it will be reset by the task manager. (This really just means its memory will be cleared before it is polled again.)
* data is the memory provided to the task. The task manager manages this memory.
* As of yet the task manager can't manage memory allocated with m/calloc, so if a task calls calloc and then crashes or doesn't call free before exiting then there will be a memory leak. Allocating memory at any time other than at startup on a microprocessor is not recomended anyway, so full memory management probably won't be implemented any time soon.
* millis is the number of milliseconds passed since the task manager was started.
* The return value indicates if this task should finish or not. Return true to keep running, or false for the task to be stopped and its memory to be freed.

```c
// The task function.
typedef bool (*TaskFunction)(void* data, uint32_t millis);
```

## Recommended tools
* git
* avr-gcc
* avr-binutils
* avr-libc
* avrdude
* tup
* bash
* a terminal
* picocom

## Building
Running build.sh will compile the library and all the examples.

## Running the examples

### Method 1
1. Clone nbavr.
2. Check that Tuprules.tup and build.sh are correct for your setup.
3. Run "build.sh -u hellotask" to compile and upload hellotask to a device.

### Method 2
1. Copy one of the examples to somewhere convenient.
2. Clone nbavr into lib/nbavr/.
3. Check that Tuprules.tup and build.sh are correct for your setup.
4. Run build.sh -u to compile and upload to a device.

## Interrupts and hardware used
The task manager uses the 16bit timer/counter1 to run .

## Devices tested
* atmega328p

## Contributors
(If you add or fix or improve something in this library feel free to put your name here.)
* Henry Shepperd

## Warranty
No.

## License
Feel free to use any of this code however you like, except for evil.
