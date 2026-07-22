/* SPDX-License-Identifier: MIT */
/* Project: MUSL */

#include <stdlib.h>

void *bsearch(const void *key, const void *base, size_t nel, size_t width, int (*cmp)(const void *, const void *))
{
	void *try;
	int sign;
	while (nel > 0) {
		try = (char *)base + width*(nel>>1);
		sign = cmp(key, try);
		if (sign == 0) {
			return try;
		}

                if (sign > 0) {
			base = try + width;
			nel--;
		}
		nel >>= 1;
	}
	return NULL;
}
