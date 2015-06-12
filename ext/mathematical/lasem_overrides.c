#include <lasem_overrides.h>
#include <string.h>
#include "mtex2mml.h"

char *
lsm_mtex_to_mathml (const char *mtex, gssize size, int global_start)
{
  gsize usize;
  char *mathml;
  int status = 0;

  if (mtex == NULL) {
    return NULL;
  }

  if (size < 0) {
    usize = strlen (mtex);
  } else {
    usize = size;
  }

  status = mtex2MML_text_filter(mtex, usize, 0);
  mathml = mtex2MML_output();

  if (status) {
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
