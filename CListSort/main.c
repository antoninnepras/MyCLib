/**
 * @file main.c
 * @author Antonin Nepras
 * @brief CList sort example
 * @version 0.1
 * @date 2022-08-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "src/list_sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * @brief Sorted person structure
 * 
 */
typedef struct
{
  char name[16];
  double income;
  double heigth;
} Person;


/**
 * @brief New person structure
 * 
 * @param name    name of the person
 * @param income  income ot the person
 * @param heigth  heigth of the person
 * @return Person* 
 */
Person*
person_new(const char* name, double income, double heigth);


/**
 * @brief Get person income (metric)
 * 
 * @param person  person
 * @return double 
 */
double
person_get_income(Person* person);


/**
 * @brief Get person heigth (metric)
 * 
 * @param person  person
 * @return double 
 */
double
person_get_heigth(Person* person);


/**
 * @brief Get person name value (metric)
 * 
 * @param person  person
 * @return double 
 */
double
person_get_name_val(Person* person);


/**
 * @brief Print person info
 * 
 * @param person 
 */
void
person_print(Person* person);


int
main(const int argc, const char** argv)
{
  // Generated data size
  int size = 15;
  if (argc > 1) {
    size = atoi(argv[1]);
  }
  printf("Data size: %i\n", size);

  // Generate random data (Except name)
  srand(time(NULL));
  List* persons = list_new();
  for (int i = 0; i < size; ++i) {
    char name[16];
    sprintf(name, "A%i", i);
    double income = 10 + 40 * (double)rand() / RAND_MAX;
    double heigth = 160 + 80 * (double)rand() / RAND_MAX;
    Person* p = person_new(name, income, heigth);
    //person_print((Person*)p);
    list_append(persons, (void*)p);
  }

  // Prepare metric
  double (*metric)(void*) = (double (*)(void*))person_get_heigth;

  // Sort data
  list_sort(persons, metric);

  putchar('\n');

  // Free generated data
  while(persons->size > 0) {
    Person* p = list_pop_back(persons);
    //person_print((Person*)p);
    free(p);
  }

  list_del(persons);
  //free(persons);

  return 0;
}


Person*
person_new(const char* name, double income, double heigth)
{
  Person* p = malloc(sizeof(Person));
  memcpy(p->name, name, strlen(name) > 16 ? 16 : strlen(name));
  p->name[15] = '\0';
  p->income = income;
  p->heigth = heigth;
  return p;
}


double
person_get_income(Person* person)
{
  return person->income;
}


double
person_get_heigth(Person* person)
{
  return person->heigth;
}


double
person_get_name_val(Person* person)
{
  return string_get_alpha_value(person->name);
}


void
person_print(Person* person)
{
  printf("%16s - income: %lf, heigth:%lf\n",
         person->name,
         person->income,
         person->heigth);
}
