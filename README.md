##A small fast bitmap library for C11

##Header only  
    You only need put the bitmap.h and popcnt.h into your project

##API:  
    bitmap_t *bitmap;  
    bitmap_create(&bitmap, 32);  
    bitmap_set(bitmap, 10);  
    bitmap_unset(bitmap, 10);  
    bitmap_set_all(bitmap);  
    bitmap_unset_all(bitmap);
    int pos = bitmap_pop(bitmap);
