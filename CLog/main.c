/**
 * @file main.c
 * @author Antonin Nepras
 * @brief Logging test
 * @version 0.1
 * @date 2022-10-04
 *
 * @copyright Copyright (c) 2022
 *
 */


#include "src/log.h"

#define LOG_FILE "log.log"

int
main(int argc, const char** argv)
{
  log_start(LOG_FILE);
  log_add(LOG_FILE, "Float %4f\n", 2.3);
  log_add_err(LOG_FILE, "Error: Int %4i\n", 6);
}
