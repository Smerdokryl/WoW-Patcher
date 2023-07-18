#include "Patch.h"

#include <string.h>

const bool apply(const struct Patch* const this,
	byte** const start, const byte* const* const end,
	void* const out
) {
	const byte* const offs = *start;

	while (*start <= *end) {
		if (memcmp(*start, this->pattern, this->pattern_size))
			(*start)++;
		else {
			fwrite(offs, *start-offs, 1, out); // Unchanged bytes
			fwrite(this->patch, this->patch_size, 1, out);
			(*start) += this->patch_size;
			return true;
		}
	}

	return false;
};
