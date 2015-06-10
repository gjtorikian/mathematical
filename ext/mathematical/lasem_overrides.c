#include <lasem_overrides.h>
#include <string.h>

char *
lsm_mtex_to_mathml (const char *mtex, gssize size, int global_start)
{
  gsize usize;
  char *mathml;

  if (mtex == NULL) {
    return NULL;
  }

  if (size < 0) {
    usize = strlen (mtex);
  } else {
    usize = size;
  }

  mathml = mtex2MML_global_parse (mtex, usize, global_start);
  if (mathml == NULL) {
    return NULL;
  }

  if (mathml[0] == '\0') {
    mtex2MML_free_string (mathml);
    return NULL;
  }

  return mathml;
}

void
lsm_mtex_free_mathml_buffer (char *mathml)
{
  if (mathml == NULL) {
    return;
  }

  mtex2MML_free_string (mathml);
}
