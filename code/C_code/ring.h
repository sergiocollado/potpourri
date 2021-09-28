#ifndef RING_H
#define RING_H

/*
 * Ring buffer structure.  Holds the base address, the read pointer, the write
 * pointer, and the allocated size.
 */
struct ring {
    unsigned int size;
    char *buf;
    volatile char *r, *w;  // read and write pointers
};

/*
 * A macro to create a statically-allocated ring at compile time, to avoid the
 * use of malloc().
 */
#define STATIC_RING(NAME, SIZE)     \
                                    \
    char __ring_buf_##NAME[SIZE];   \
                                    \
    struct ring NAME = {            \
        .size = SIZE,               \
        .buf = __ring_buf_##NAME,   \
        .r   = __ring_buf_##NAME,   \
        .w   = __ring_buf_##NAME    \
    }

int ring_is_empty(struct ring *ring);
int ring_is_full(struct ring *ring);
char ring_read(struct ring *ring);
void ring_write(struct ring *ring, char val);
void ring_clear(struct ring *ring);

#endif
