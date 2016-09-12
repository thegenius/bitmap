#include <stdio.h>
#include "bitmap.h"

int verify_bitmap_create() {
	bitmap_t *bitmap;
	bitmap_create(&bitmap, 31);	
	printf("bitmap size: %d\n", bitmap->size);
	printf("bitmap data: %d\n", bitmap->data[0]);
}
int verify_bitmap_set_get() {
	bitmap_t *bitmap;
	bitmap_create(&bitmap, 31);	
	bitmap_set(bitmap, 12);
	printf("bitmap[12] data: %d\n", bitmap_get(bitmap, 12));
	printf("bitmap->data: %d\n", bitmap->data[0]);

	bitmap_unset(bitmap, 12);
	printf("bitmap[12] data: %d\n", bitmap_get(bitmap, 12));
	printf("bitmap->data: %d\n", bitmap->data[0]);
}
int verify_bitmap_pop() {
	bitmap_t *bitmap;
	bitmap_create(&bitmap, 31);	
	bitmap_set_all(bitmap);
	for (size_t i=0; i<32; ++i) {
		printf("bitmap_pop: %u\n", bitmap_pop(bitmap));	
		printf("bitmap->data[%d] : %u\n", 0, bitmap->data[0]);
	}
	return 1;
}
int main(int argc, char* argv[]) {
	int success;
	success = verify_bitmap_create();
	success = verify_bitmap_set_get();
	success = verify_bitmap_pop();
	return 0;
}
