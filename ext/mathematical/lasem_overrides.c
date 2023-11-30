#include "lasem_overrides.h"
#include <mtex2MML.h>

void
itex2MML_free_string (char * str)
{
  return mtex2MML_free_string(str);
}

void
lsm_itex_free_mathml_buffer	(char *mathml)
{
  if (mathml == NULL)
    return;

  mtex2MML_free_string (mathml);
}

char *
lsm_itex_to_mathml (const char *itex, gssize size) { return NULL; }


char *
lsm_mtex_to_mathml (const char *mtex, gssize size, int delimiter, int render_type)
{
  gsize usize;
  char *mathml;
  int status = 0;

  if (!mtex) {
    return NULL;
  }

  if (size < 0) {
    usize = strlen (mtex);
  } else {
    usize = size;
  }

  // reset parse pointer to clear out previous potential errors
  mtex2MML_reset_parsing_environment();

  switch (render_type) {
  case PARSE:
    mathml = mtex2MML_global_parse(mtex, usize, delimiter, 1);
    if (mathml == NULL) {
      status = 1;
    }
    break;
  case FILTER:
    status = mtex2MML_filter(mtex, usize, delimiter);
    mathml = mtex2MML_output();
    break;
  case TEXT_FILTER:
    status = mtex2MML_text_filter(mtex, usize, delimiter);
    mathml = mtex2MML_output();
    break;
  case STRICT_FILTER:
    status = mtex2MML_strict_filter(mtex, usize, delimiter);
    mathml = mtex2MML_output();
    break;
  default:
    mathml = mtex2MML_global_parse(mtex, usize, delimiter, 1);
    if (mathml == NULL) {
      status = 1;
    }
    break;
  }

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
  mtex2MML_free_string (mathml);
}
