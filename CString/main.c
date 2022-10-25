#include "src/string.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef SUCCESS
#define SUCCESS 0
#endif
#ifndef ERROR
#define ERROR 1
#endif

#define COLOR "\033[01;31m\033K"
#define DECOLOR "\033[m\033K"


//------------------------------------------------------------------------------

int
main(int argc, const char** argv)
{
  String* readme = string_load_file("README.md");
  string_fprint(stdout, readme);
  string_del(readme);

  if (argc < 2) {
    return ERROR;
  }

  FILE* file = stdin;
  bool use_color = false;

  bool pattern_loaded = false;
  const char* pattern_str;
  bool file_loaded = false;
  const char* filename;

  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] == '-') {
      if (!cstrcmp(argv[i], "--color=always")) {
        use_color = true;
      } else {
        return ERROR;
      }
    } else if (!pattern_loaded) {
      pattern_loaded = true;
      pattern_str = argv[i];
    } else if (!file_loaded) {
      file_loaded = true;
      filename = argv[i];
    }
  }

  if (file_loaded) {
    file = fopen(filename, "r");
    if (file == NULL) {
      return ERROR;
    }
  }

  String* color = string_new(COLOR);
  String* decolor = string_new(DECOLOR);

  String* pattern = string_new(pattern_str);


  int occurences = 0;
  while (true) {
    String* str = string_load_line(file);
    if (str == NULL) {
      break;
    }

    if (string_in_string(str, pattern)) {
      if (use_color) {
        String* colored = string_color_pattern(str, pattern, color, decolor);
        string_fprint(stdout, colored);
        string_del(colored);
      } else {
        string_fprint(stdout, str);
      }
      ++occurences;
    }
    string_del(str);
  }


  string_del(color);
  string_del(decolor);
  string_del(pattern);

  if (file_loaded) {
    fclose(file);
  }

  return occurences > 0;
}


//------------------------------------------------------------------------------
