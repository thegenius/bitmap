#ifndef __POPCNT_H__
#define __POPCNT_H__
#include <stdint.h>

#ifdef __MSC_VER
#include <intrin.h>
extern inline size_t assembly_popcnt_u64(uint64_t val) {
	return _mm_popcnt_u64(val);
}
extern inline size_t assembly_popcnt_u32(uint32_t val) {
	return _mm_popcnt_u32(val);
}
extern inline size_t assembly_popcnt_u16(uint16_t val) {
	return _mm_popcnt_u32((uint32_t)val);
}
extern inline size_t assembly_popcnt_u8(uint8_t val) {
	return _mm_popcnt_u32((uint32_t)val);
}
#define __ASSEMBLY_POPCNT__
#endif

#ifdef __GNUC__
extern inline size_t assembly_popcnt_u64(uint64_t val) {
	return __builtin_popcountll(val);
}
extern inline size_t assembly_popcnt_u32(uint32_t val) {
	return __builtin_popcount(val);
}
extern inline size_t assembly_popcnt_u16(uint16_t val) {
	return __builtin_popcount((uint32_t)val);
}
extern inline size_t assembly_popcnt_u8(uint8_t val) {
	return __builtin_popcount((uint32_t)val);
}
#define __ASSEMBLY_POPCNT__
#endif

extern inline size_t nifty_popcnt_u8(uint8_t v) {
	v = (v & (uint8_t)(0x55)) + ( (v >> 1) & (uint8_t)(0x55));
	v = (v & (uint8_t)(0x33)) + ( (v >> 2) & (uint8_t)(0x33));
	v = (v & (uint8_t)(0x0f)) + ( (v >> 4) & (uint8_t)(0x0f));
	return (size_t)v;
}
extern inline size_t nifty_popcnt_u16(uint16_t v) {
	v = (v & (uint16_t)(0x5555)) + ( (v >> 1) & (uint16_t)(0x5555));
	v = (v & (uint16_t)(0x3333)) + ( (v >> 2) & (uint16_t)(0x3333));
	v = (v & (uint16_t)(0x0f0f)) + ( (v >> 4) & (uint16_t)(0x0f0f));
	v = (v & (uint16_t)(0x00ff)) + ( (v >> 8) & (uint16_t)(0x00ff));
	return (size_t)v;
}
extern inline size_t nifty_popcnt_u32(uint32_t v) {
	v = (v & (uint32_t)(0x55555555)) + ( (v >> 1) & (uint32_t)(0x55555555));
	v = (v & (uint32_t)(0x33333333)) + ( (v >> 2) & (uint32_t)(0x33333333));
	v = (v & (uint32_t)(0x0f0f0f0f)) + ( (v >> 4) & (uint32_t)(0x0f0f0f0f));
	v = (v & (uint32_t)(0x00ff00ff)) + ( (v >> 8) & (uint32_t)(0x00ff00ff));
	v = (v & (uint32_t)(0x0000ffff)) + ( (v >>16) & (uint32_t)(0x0000ffff));
	return (size_t)v;
}
extern inline size_t popcnt_u64(uint64_t v) {
	v = (v & (uint64_t)(0x5555555555555555)) + ( (v >> 1) & (uint64_t)(0x5555555555555555));
	v = (v & (uint64_t)(0x3333333333333333)) + ( (v >> 2) & (uint64_t)(0x3333333333333333));
	v = (v & (uint64_t)(0x0f0f0f0f0f0f0f0f)) + ( (v >> 4) & (uint64_t)(0x0f0f0f0f0f0f0f0f));
	v = (v & (uint64_t)(0x00ff00ff00ff00ff)) + ( (v >> 8) & (uint64_t)(0x00ff00ff00ff00ff));
	v = (v & (uint64_t)(0x0000ffff0000ffff)) + ( (v >>16) & (uint64_t)(0x0000ffff0000ffff));
	v = (v & (uint64_t)(0x00000000ffffffff)) + ( (v >>32) & (uint64_t)(0x00000000ffffffff));
	return (size_t)v;
}

#ifdef __ASSEMBLY_POPCNT__
#define popcnt_u64(v) assembly_popcnt_u64(v)
#define popcnt_u32(v) assembly_popcnt_u32(v)
#define popcnt_u16(v) assembly_popcnt_u16(v)
#define popcnt_u8(v) assembly_popcnt_u8(v)
#else
#define popcnt_u64(v) nifty_popcnt_u64(v)
#define popcnt_u32(v) nifty_popcnt_u32(v)
#define popcnt_u16(v) nifty_popcnt_u16(v)
#define popcnt_u8(v) nifty_popcnt_u8(v)
#endif

#endif
