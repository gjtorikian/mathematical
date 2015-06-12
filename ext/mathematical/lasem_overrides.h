#include <glib.h>

/**
 * lsm_mtex_to_mathml:
 * @mtex: (allow-none): an mtex string
 * @size: mtex string length, -1 if NULL terminated
 *
 * Converts an mtex string to a Mathml representation.
 *
 * Return value: a newly allocated string, NULL on parse error. The returned data must be freed using @lsm_mtex_free_mathml_buffer.
 */

extern char * lsm_mtex_to_mathml (const char *mtex, gssize size, int global_start);

/**
 * lsm_mtex_free_mathml_buffer:
 * @mathml: (allow-none): a mathml buffer
 *
 * Free the buffer returned by @lsm_mtex_to_mathml.
 */

extern void lsm_mtex_free_mathml_buffer (char *mathml);
