#include "task1.h"

static void setup(void);
static void loop(void);

Task task1 = {
    .setup = setup,
    .loop = loop,
};

static uint32_t mDelay;
static uint16_t count;

static Stream _task1Stream = streamInit(5);
Stream* task1Stream = &_task1Stream;

static void setup(void) {
    mDelay = 0;
    count = 0;
    streamClear(task1Stream);
}

static void loop(void) {
    uint32_t ticks = getTicks();

    if(ticks >= mDelay) {
        printstr(stdout, "Task1 running (");
        printi16(stdout, count, PrintUDec);
        printstr(stdout, ")\n");
        mDelay = ticks + MS_TO_TICKS(1000);
        count++;
    }

    uint8_t b;

    if(streamPop(task1Stream, &b)) {
        printstr(stdout, "Task1 received byte 0x");
        printi16(stdout, b, PrintUHex);
        printchar(stdout, '\n');
    }
}
