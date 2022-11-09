/**
 * @file csv.c
 * @author Antonin Nepras
 * @brief csv operations implementation
 * @version 0.1
 * @date 2022-10-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "csv.h"

csv_value_t*
csv_value_new(char* value)
{
  csv_value_t* val = (csv_value_t*)malloc(sizeof(csv_value_t));
  if (val == NULL) {
    return NULL;
  }

  val->value = (char*)malloc(sizeof(char) * (strlen(value) + 1));
  if (val->value == NULL) {
    free(val);
    return NULL;
  }

  strcpy(val->value, value);

  return val;
}


void
csv_value_del(csv_value_t** val)
{
  if (val == NULL || *val == NULL) {
    return;
  }

  if ((*val)->value != NULL) {
    free((*val)->value);
  }

  free(*val);
  *val = NULL;
}


csv_value_t*
csv_value_fload(FILE* file, char separator)
{
  char* value = (char*)calloc(sizeof(char), 8);
  size_t value_size = 8;

  size_t len = 0;
  bool in_dq = false;
  while (1) {
    int cur = getc(file);
    int nxt = getc(file);
    fseek(file, -1, SEEK_CUR);

    // unexpected end of file
    if (nxt == EOF) {
      free(value);
      return NULL;
    }

    // check for double quotes placement
    if (cur == '"' && !in_dq) {
      if (len == 0) {
        in_dq = true;
      } else {
        // misplaced quotes
        free(value);
        return NULL;
      }
    }

    // add char to value
    ++len;
    if (value_size > len) {
      value[len - 1] = cur;
    } else {
      char* tmp = (char*)realloc(value, sizeof(char) * value_size * 2);
      if (tmp == NULL) {
        // alloc error
        free(value);
        return NULL;
      }
      value = tmp;
      value[len - 1] = cur;
    }

    // end of value
    if ((nxt == separator || nxt == '\n') && (!in_dq || cur == '"')) {
      break;
    }
  }

  value[len] = '\0';

  csv_value_t* val = (csv_value_t*)malloc(sizeof(csv_value_t));
  val->value = value;
  return val;
}


size_t
csv_value_fwrite(FILE* file, csv_value_t* value)
{
  if (file == NULL || value == NULL) {
    return 0;
  }

  size_t len = strlen(value->value);
  return fwrite(value->value, sizeof(char), len, file);
}


csv_table_t*
csv_table_new(size_t r, size_t c)
{
  csv_table_t* table = (csv_table_t*)malloc(sizeof(csv_table_t));
  if (table == NULL) {
    return NULL;
  }

  // allocate values
  table->table = (csv_value_t***)malloc(sizeof(csv_value_t**) * r);
  if (table->table == NULL) {
    free(table);
    return NULL;
  }
  for (int i = 0; i < r; ++i) {
    table->table[i] = (csv_value_t**)calloc(c, sizeof(csv_value_t*));
    if (table->table[i] == NULL) {
      for (int j = 0; j < i; ++j) {
        free(table->table[j]);
      }
      free(table->table);
      free(table);
      return NULL;
    }
  }

  table->r = r;
  table->c = c;

  return table;
}


void
csv_table_del(csv_table_t** table)
{
  if (table == NULL || *table == NULL) {
    return;
  }

  if ((*table)->table != NULL) {
    for (int i = 0; i < (*table)->r; ++i) {
      if ((*table)->table[i] != NULL) {
        for (int j = 0; j < (*table)->c; ++j) {
          csv_value_del(&(*table)->table[i][j]);
        }
        free((*table)->table[i]);
      }
    }
    free((*table)->table);
  }

  free((*table));
  *table = NULL;
}


int
csv_table_set_val(csv_table_t* table, csv_value_t* val, size_t r, size_t c)
{
  if (table == NULL || table->r < r || table->c < c) {
    return ERROR;
  }

  table->table[r][c] = val;
  return SUCCESS;
}


csv_value_t*
csv_table_get_val(csv_table_t* table, size_t r, size_t c)
{
  if (table == NULL || table->r < r || table->c < c) {
    return NULL;
  }

  return table->table[r][c];
}


int
csv_table_resize(csv_table_t* table, size_t r, size_t c)
{
  if (table == NULL) {
    return ERROR;
  }

  // rows
  if (r < table->r) {
    for (size_t i = r; i < table->r; ++i) {
      for (size_t j = 0; j < table->c; ++j) {
        csv_value_del(&table->table[i][j]);
      }
      free(table->table[i]);
    }

    csv_value_t*** tmp =
      (csv_value_t***)realloc(table->table, sizeof(csv_value_t**) * r);
    if (tmp == NULL) {
      return ERROR;
    }
    table->table = tmp;
  }
  if (r > table->r) {
    csv_value_t*** tmp =
      (csv_value_t***)realloc(table->table, sizeof(csv_value_t**) * r);
    if (tmp == NULL) {
      return ERROR;
    }
    table->table = tmp;

    for (size_t i = r; i < table->r; ++i) {
      table->table[i] = calloc(c, sizeof(csv_value_t*));
      free(table->table[i]);
    }
  }

  // columns
  if (c < table->c) {
    for (size_t i = 0; i < r && i < table->r; ++i) {
      for (size_t j = c; j < table->c; ++j) {
        csv_value_del(&table->table[i][j]);
      }

      csv_value_t** tmp =
        (csv_value_t**)realloc(table->table[i], sizeof(csv_value_t*) * c);
      if (tmp == NULL) {
        return ERROR;
      }
      table->table[i] = tmp;
    }
  } else {
    for (size_t i = 0; i < r && i < table->r; ++i) {
      csv_value_t** tmp =
        (csv_value_t**)realloc(table->table[i], sizeof(csv_value_t*) * c);
      if (tmp == NULL) {
        return ERROR;
      }
      table->table[i] = tmp;
    }
  }

  table->r = r;
  table->c = c;

  return SUCCESS;
}


csv_table_t*
csv_table_fload(FILE* file, char separator)
{
  size_t max_row = 0;
  size_t max_column = 0;
  size_t table_rows = 16;
  size_t table_columns = 8;
  size_t row = 0;
  size_t column = 0;

  csv_table_t* table = csv_table_new(table_rows, table_columns);

  // load rows
  while (1) {
    csv_value_t* tmp = csv_value_fload(file, separator);
    if (tmp != NULL) {
      if (column == table_columns) {
        table_columns *= 2;
        if (csv_table_resize(table, table_rows, table_columns) == ERROR) {
          csv_table_del(&table);
          return NULL;
        }
      }

      if (row == table_rows) {
        table_rows *= 2;
        if (csv_table_resize(table, table_rows, table_columns) == ERROR) {
          csv_table_del(&table);
          return NULL;
        }
      }

      csv_table_set_val(table, tmp, row, column);
    }

    // next needed to detect EOF
    int sep = getc(file);
    int nxt = getc(file);
    fseek(file, -1, SEEK_CUR);

    if (nxt == EOF) {
      break;
    } else if (sep == separator) {
      column += 1;
      if (max_column < column) {
        max_column = column;
      }
    } else if (sep == '\n') {
      row += 1;
      if (max_row < row) {
        max_row = row;
      }
      column = 0;
    }
  }

  csv_table_resize(table, max_row + 1, max_column + 1);

  return table;
}


void
csv_table_fwrite(FILE* file, csv_table_t* table, char separator)
{
  if (file == NULL || table == NULL) {
    return;
  }

  for (int i = 0; i < table->r; ++i) {
    for (int j = 0; j < table->c; ++j) {
      if (j != 0)
        putc(separator, file);
      csv_value_fwrite(file, table->table[i][j]);
    }

    putc('\n', file);
  }
}


void
csv_table_sort_rows(csv_table_t* table, double (*func)(csv_value_t**))
{
  sort(
    algr_quick_sort, (void**)table->table, table->r, (double (*)(void*))func);
}


size_t _row_eval_alpha_column = 0;
bool _row_eval_alpha_reverse = false;
double
_row_eval_alpha(csv_value_t** row)
{
  if (!_row_eval_alpha_reverse)
    return string_get_alpha_value(row[_row_eval_alpha_column]->value);
  else
    return 1.0 / string_get_alpha_value(row[_row_eval_alpha_column]->value);
}


size_t _row_eval_num_column = 0;
bool _row_eval_num_reverse = false;
double
_row_eval_num(csv_value_t** row)
{
  if (!_row_eval_num_reverse)
    return atof(row[_row_eval_num_column]->value);
  else
    return 1.0 / atof(row[_row_eval_num_column]->value);
}


void
csv_table_sort_by_column_alpha(csv_table_t* table, size_t c, bool reverse)
{
  _row_eval_alpha_column = c;
  _row_eval_alpha_reverse = reverse;
  csv_table_sort_rows(table, _row_eval_alpha);
}


void
csv_table_sort_by_column_num(csv_table_t* table, size_t c, bool reverse)
{
  _row_eval_num_column = c;
  _row_eval_num_reverse = reverse;
  csv_table_sort_rows(table, _row_eval_num);
}
