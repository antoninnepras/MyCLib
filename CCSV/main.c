#include "src/csv.h"


double
sort_by_first_column(csv_value_t** row)
{
  return string_get_alpha_value(row[0]->value);
}


double
sort_by_second_column_num(csv_value_t** row)
{
  return atof(row[1]->value);
}


int
main(int argc, const char** argv)
{
  FILE* file_in = fopen("in.csv", "r");
  if (file_in == NULL) {
    fprintf(stderr, "Error in file not opened\n");
    return ERROR;
  }

  csv_table_t* table = csv_table_fload(file_in, ',');
  fclose(file_in);

  csv_table_sort_by_column_alpha(table, 0, true);

  FILE* file_out = fopen("out.csv", "w");
  if (file_out == NULL) {
    fprintf(stderr, "Error out file not opened\n");
    return ERROR;
  }
  csv_table_fwrite(file_out, table, ';');
  fclose(file_out);

  csv_table_sort_by_column_alpha(table, 0, false);

  FILE* file_out1 = fopen("out1.csv", "w");
  if (file_out == NULL) {
    fprintf(stderr, "Error out file not opened\n");
    return ERROR;
  }
  csv_table_fwrite(file_out1, table, ';');
  fclose(file_out1);

  csv_table_del(&table);

  return SUCCESS;
}
