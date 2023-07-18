#include "Patcher.h"

#include <stdlib.h>

static inline const unsigned long filesize(FILE* file) {
	fseek(file, 0, SEEK_END);
	const unsigned long size = ftell(file);
	rewind(file);
	return size;
}

int main(int argc, char* argv[])  {
	if (argc < 2) {
		LOG("Usage: %s [INPUT WoW.exe PATH] ([OUTPUT WoW.exe PATH])\n", argv[0]);
		return 1;
	}

	LOG("Reading %s\n", argv[1]);
	byte* exe_start; const byte* exe_end;
	{
		FILE* const from = fopen(argv[1], "rb");
		const unsigned long size = filesize(from);

		exe_start = malloc(size + 1);
		exe_end = exe_start + size;
		fread(exe_start, size, 1, from);

		fclose(from);
		LOG("Read %lu bytes\n", size);
	}

	FILE* out;
	if (argc > 2) {
		LOG("Writing to %s\n", argv[2]);
		out = fopen(argv[2], "wb");
	} else {
		LOG("Writing to stdout\n");
		out = fdopen(fileno(stdout), "wb");
	}

	byte* const offs = exe_start;
	for (uint i = 0; i < n_patches; i++) {
	 	if (apply(&patches[i], &exe_start, &exe_end, out))
	 		LOG("\tPatched %d @ %lX\n", i, (unsigned long)exe_start);
	}

	fwrite(exe_start, exe_end-exe_start, 1, out);
	fclose(out);
	free(offs);

	LOG("Done\n");
	return 0;
}
