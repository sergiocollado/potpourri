#include "ring.h"

static
volatile
char *ring_next_r(struct ring *ring) {
    return (ring->r + 1) < (ring->buf + ring->size)? (ring->r + 1) : ring->buf;
}

static
volatile
char *ring_next_w(struct ring *ring) {
    return (ring->w + 1) < (ring->buf + ring->size)? (ring->w + 1) : ring->buf;
}

int ring_is_empty(struct ring *ring) {
    return ring->r == ring->w;
}

int ring_is_full(struct ring *ring) {
    return ring_next_w(ring) == ring->r;
}

char ring_read(struct ring *ring) {
    char ret = *ring->r;
    ring->r = ring_next_r(ring);
    return ret;
}

void ring_write(struct ring *ring, char val) {
    *ring->w = val;
    ring->w = ring_next_w(ring);
}

void ring_clear(struct ring *ring) {
    ring->r = ring->w;
}
