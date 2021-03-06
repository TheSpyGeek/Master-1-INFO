#include "mem.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define NB_TESTS 10

static void *alloc_max(size_t estimate) {
	void *result;
	static size_t last = 0;

	while ((result = mem_alloc(estimate)) == NULL) {
		estimate--;
	}
	debug("Alloced %zu bytes at %p\n", estimate, result);
	if (last) {
		// Idempotence test
		assert(estimate == last);
	} else
		last = estimate;
	return result;
}

int main(int argc, char *argv[]) {

	void *adr;

	mem_init(get_memory_adr(), get_memory_size());
	adr = alloc_max(get_memory_size());

	mem_free(adr);
	

	return 0;
}
