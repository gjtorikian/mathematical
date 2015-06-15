#include "ruby.h"

#include <lasem_overrides.h>
#include <string.h>
#include "mtex2MML.h"

char *
lsm_mtex_to_mathml (const char *mtex, gssize size, int delimiter, int render_type)
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

  switch (render_type) {
  case PARSE:
    mathml = mtex2MML_parse(mtex, usize, delimiter);
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
    /* should be impossible, Ruby code prevents this */
    print_and_raise(rb_eTypeError, "not valid render format");
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
  if (mathml == NULL) {
    return;
  }

  mtex2MML_free_string (mathml);
}
