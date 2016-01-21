#include "taskmanager.h"

static void taskManagerProcessTask(Task* task);
static Task* getNextTask(Task** tasks, uint8_t taskCount);
inline TaskFunction processState(Task* task);

static bool mTaskIsActive;
static jmp_buf mHaltJmp;

void taskManagerRun(Task** tasks, uint8_t taskCount) {
    resetClearStatus();

    watchdog(WATCHDOG_16MS, WATCHDOG_INTERRUPT_RESET);

    while(true) {
        watchdogReset();
        watchdogInterruptEnable(true);
        sei();

        Task* task = getNextTask(tasks, taskCount);

        taskManagerProcessTask(task);
    }
}

static void taskManagerProcessTask(Task* task) {
    // Save state in case the task halts.
    uint8_t jmp = setjmp(mHaltJmp);

    if(jmp == 0) {
        mTaskIsActive = true;

        TaskFunction f = processState(task);

        if(f != NULL) {
            f(task);
        }

        mTaskIsActive = false;
    } else if(jmp == 1) { // Task halted.
        task->state = STATE_CRASH;
    } else { // Watchdog interrupt, but no task running.
        // Do nothing.
    }
}

static uint8_t mNextTaskIndex = -1;

static Task* getNextTask(Task** tasks, uint8_t taskCount) {
    Task* task;

    while(true) {
        mNextTaskIndex = (mNextTaskIndex + 1) % taskCount;

        task = tasks[mNextTaskIndex];

        if(task->priority == 0) {
            task->priority = PRIORITY_MEDIUM;
        }

        if(task->tokens >= task->priority) {
            task->tokens -= task->priority;
            break;
        }

        task->tokens++;
    }

    return task;
}

inline TaskFunction processState(Task* task) {
    if(task->state == STATE_LOOP) {
        return task->loop;
    } else if(task->state == STATE_CRASH) {
        task->state = STATE_SETUP;
        return task->crash;
    } else { // STATE_SETUP or any other value.
        if(task->data != NULL) {
            memset(task->data, 0, task->dataSize);
        }
        task->state = STATE_LOOP;
        return task->setup;
    }
}

ISR(WDT_vect) {
    longjmp(mHaltJmp, mTaskIsActive ? 1 : 2);
}
