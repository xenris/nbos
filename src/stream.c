#include "stream.h"

static uint8_t streamNextIndex(Stream* stream, uint8_t i);

bool streamPush(Stream* stream, uint8_t in) {
    const uint8_t nextHead = streamNextIndex(stream, stream->head);

    if(nextHead == stream->tail) {
        stream->overflowed = true;
        return false;
    }

    stream->data[stream->head] = in;
    stream->head = nextHead;

    return true;
}

bool streamPop(Stream* stream, uint8_t* out) {
    if(stream->tail == stream->head) {
        return false;
    }

    const uint8_t nextTail = streamNextIndex(stream, stream->tail);

    *out = stream->data[stream->tail];
    stream->tail = nextTail;

    return true;
}

bool streamPeek(Stream* stream, uint8_t* out) {
    if(stream->tail == stream->head) {
        return false;
    }

    *out = stream->data[stream->tail];

    return true;
}

int16_t streamAvailable(Stream* stream) {
    const uint8_t head = stream->head;
    const uint8_t tail = stream->tail;
    const uint8_t size = stream->size;

    if(head >= tail) {
        return head - tail;
    } else {
        return (size - tail) + head;
    }
}

int16_t streamFree(Stream* stream) {
    int16_t diff = stream->tail - stream->head;

    if(diff < 0) {
        diff += stream->size;
    }

    return diff;

    const uint8_t head = stream->head;
    const uint8_t tail = stream->tail;
    const uint8_t size = stream->size;

    if(head >= tail) {
        return (size - head) + tail;
    } else {
        return tail - head;
    }
}

static uint8_t streamNextIndex(Stream* stream, uint8_t i) {
    return (i + 1) % stream->size;
}