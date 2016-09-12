all: bitmap_spec

bitmap_spec: bitmap.h bitmap_spec.c
	gcc -std=c11 bitmap_spec.c -o bitmap_spec
