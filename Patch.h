#ifndef PATCH_H
#define PATCH_H

#include <stdbool.h>
#include <stdio.h>

typedef unsigned char byte;
typedef unsigned int uint;

#define PATCH_BYTES(...) sizeof((const byte[]){__VA_ARGS__}), (const byte[]){__VA_ARGS__}

struct Patch {
	const uint pattern_size;
	const byte* const pattern;

	const uint patch_size;
	const byte* const patch;
};

const bool apply(const struct Patch* const this, byte** const start, const byte* const* const end, void* const out);

#endif
