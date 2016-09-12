#ifndef __BITMAP_H__
#define __BITMAP_H__
#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <stdint.h>
#include <stdbool.h>
#include <uchar.h>
#include <math.h>
#include "popcnt.h"

extern inline uint32_t next_pow_u32(uint32_t value) {
	size_t n = value - 1;
	n = n | (n>>1);
	n = n | (n>>2);
	n = n | (n>>4);
	n = n | (n>>8);
	n = n | (n>>16);
	return n + 1;
}
extern inline uint64_t next_pow_u64(uint64_t value) {
	size_t n = value - 1;
	n = n | (n>>1);
	n = n | (n>>2);
	n = n | (n>>4);
	n = n | (n>>8);
	n = n | (n>>16);
	n = n | (n>>32);
	return n + 1;
}

extern size_t get_first_one_pos_u32(uint32_t container) {
	if (container == 0) {
		return -1;
	} else {
		return popcnt_u32(container ^ (container - 1)) - 1;
	}
}

extern size_t get_first_zero_pos_u32(uint32_t container) {
	return get_first_one_pos_u32(~container);
}

typedef struct bitmap_t {
	size_t size;
	uint32_t data[0];
} bitmap_t;

int bitmap_create(bitmap_t **bitmap, size_t size) {
	if (size <= 32) {
		size = 32;
	}
	size_t map_size = next_pow_u32(size);
	(*bitmap) = (bitmap_t*)calloc(1, sizeof(bitmap_t) + (map_size>>3));
	(*bitmap)->size = map_size;
	return 0;
}

extern inline bool bitmap_set(bitmap_t *bitmap, size_t pos) {
	uint32_t val = bitmap->data[pos>>5] & (1<<pos);
	bitmap->data[pos>>5] |= (1<<pos);
	return !val;
}

extern inline bool bitmap_unset(bitmap_t *bitmap, size_t pos) {
	uint32_t val = bitmap->data[pos>>5] & (1<<pos);
	bitmap->data[pos>>5] &= ~(1<<pos);
	return val;
}

extern inline void bitmap_set_all(bitmap_t *bitmap) {
	size_t csize = bitmap->size >> 5;
	for (size_t i=0; i<csize; ++i) {
		bitmap->data[i] = 0xffffffff;
	}
}

extern inline void bitmap_unset_all(bitmap_t *bitmap) {
	size_t csize = bitmap->size >> 5;
	for (size_t i=0; i<csize; ++i) {
		bitmap->data[i] = 0;
	}
}

extern inline bool bitmap_get(bitmap_t *bitmap, size_t pos) {
	return bitmap->data[pos>>5] & (1<<pos);
}

int bitmap_pop(bitmap_t *bitmap) {
	for (size_t i=0; i<bitmap->size; ++i) {
		size_t pos = get_first_one_pos_u32(bitmap->data[i]);
		if (pos != -1) {
			bitmap_unset(bitmap, pos);
			return pos;
		}
	}
	return -1;
}
#endif
