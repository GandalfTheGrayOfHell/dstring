#include "dstring.h"

dstring ds_new(char str[]) {
	uint64_t len = strlen(str);
	// TODO: handle error here
	dstring d = malloc(sizeof(dstring));

	uint64_t alloc = DS_MAX_PREALLOC;
	while (alloc < len + 1) alloc += DS_MAX_PREALLOC;

	d->len = len;
	d->free = alloc - len;
	// TODO: handle error here
	d->buf = malloc(alloc);

	strcpy(d->buf, str);

	return d;
}

dstring ds_new_f(char str[]) {
	uint64_t len = strlen(str);
	// TODO: handle error here
	dstring d = malloc(sizeof(dstring));

	d->len = len;
	d->free = 0;
	// TODO: handle error here
	d->buf = malloc(len);

	strcpy(d->buf, str);

	return d;
} 

dstring ds_empty() {
	// TODO: handle error here
	dstring d = malloc(sizeof(dstring));
	d->len = 0;
	d->free = DS_MAX_PREALLOC;
	// TODO: handle error here
	d->buf = malloc(d->free);

	return d;
}

dstring ds_empty_f() {
	// TODO: handle error here
	dstring d = malloc(sizeof(dstring));
	d->len = 0;
	d->free = 0;

	return d;
}

dstring ds_cpy(dstring src) {
	// TODO: handle error here
	dstring d = malloc(sizeof(dstring));
	d->len = src->len;
	d->free = src->free;
	// TODO: handle error here
	d->buf = malloc(sizeof(d->len + d->free));
	d->buf = src->buf;

	return d;
}

dstring ds_range(dstring d, uint64_t a, uint64_t b) {
	if (a > d->len || b > d->len || a > b) return d;

	// TODO: handle error here
	dstring r = malloc(sizeof(dstring));
	r->len = b - a;

	uint64_t alloc = DS_MAX_PREALLOC;
	while (alloc < r->len + 1) alloc += DS_MAX_PREALLOC;

	r->free = alloc - r->len;
	r->buf = malloc(alloc);

	memcpy(r->buf, d->buf + a, r->len);

	return r;
}

int ds_append(dstring d, char str[]) {
	const uint64_t len_src = strlen(str);

	if (len_src > d->free) {
		while (d->free < len_src + 1) d->free += DS_MAX_PREALLOC; // 1 added for \0 in the end
		// TODO: handle realloc error
		d->buf = realloc(d->buf, d->free);
	}

	memcpy(d->buf + ds_len(d), str, len_src + 1);

	d->len += len_src;
	d->free -= len_src;

	return 1;
}

int ds_concat(dstring dest, dstring src) {
	const uint64_t len_src = ds_len(src);

	if (len_src > dest->free) {
		while (dest->free < len_src + 1) dest->free += DS_MAX_PREALLOC; // 1 added for \0 in the end
		// TODO: handle realloc error
		dest->buf = realloc(dest->buf, dest->free);
	}

	memcpy(dest->buf + ds_len(dest), src->buf, ds_len(src) + 1);

	dest->len += len_src;
	dest->free -= len_src;

	return 1;
}

int ds_concat_f(dstring dest, dstring src) {
	ds_concat(dest, src);
	ds_free(src);

	return 1;
}

void ds_replace(dstring d, char src[], char repl[]) {
	uint64_t len_src = strlen(src);
	uint64_t len_repl = strlen(repl);

	if (len_src > d->len) return;

	char * location = strstr(d->buf, src);
	if (location == NULL) return;

	if (len_src == len_repl) {
		memcpy(location, repl, len_repl);
	} else {
		uint64_t diff = (len_repl - len_src) > 0 ? len_repl - len_repl : len_src - len_repl;

		if  (d->free < diff) {
			while (d->free < diff + 1) d->free += DS_MAX_PREALLOC; // 1 added for \0 in the end
			// TODO: handle realloc error
			d->buf = realloc(d->buf, d->free);
		}

		size_t loc = location - d->buf;
		memmove(location + len_repl, location + len_src, d->len - loc - len_src + 1);
		memcpy(location, repl, len_repl);

		d->len -= diff;
		d->free += diff;
	}
}

void ds_ltrim(dstring d, int code) {
	uint64_t count = 0;
	
	while (d->buf[count] == code) count++;

	memmove(d->buf, d->buf + count, d->len);

	d->len -= count;
	d->free += count;
}

void ds_rtrim(dstring d, int code) {
	uint64_t count = d->len - 1;

	while (d->buf[count] == code) count--;

	d->buf[count + 1] = '\0';

	uint64_t diff = d->len - count - 1;
	d->len -= diff;
	d->free += diff;
}


void ds_trim(dstring d, int code) {
	ds_ltrim(d, code);
	ds_rtrim(d, code);	
}

void ds_ltrim_w(dstring d) {
	ds_ltrim(d, 32);
}

void ds_rtrim_w(dstring d) {
	ds_rtrim(d, 32);
}


void ds_trim_w(dstring d) {
	ds_ltrim_w(d);
	ds_rtrim_w(d);	
}


void ds_lower(dstring d) {
	int i;
	for (i = 0; i < d->len; ++i) {
		if (d->buf[i] >= 65 && d->buf[i] <= 90) {
			d->buf[i] = d->buf[i] + 32;
		}
	}
}

void ds_upper(dstring d) {
	int i;
	for (i = 0; i < d->len; ++i) {
		if (d->buf[i] >= 97 && d->buf[i] <= 122) {
			d->buf[i] = d->buf[i] - 32;
		}
	}
}

void ds_rmfree(dstring d) {
	if (d->free == 0) return;

	// TODO: handle error here
	d->buf = realloc(d->buf, d->len);
	d->free = 0;
}

void ds_free(dstring str) {
	free(str->buf);
	free(str);
}