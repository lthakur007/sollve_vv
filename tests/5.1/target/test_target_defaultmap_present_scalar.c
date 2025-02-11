//===--- test_target_defaultmap_present_scalar.c ----------------------------===//
//
//  OpenMP API Version 5.1 Aug 2021
//
//  This test checks behavior of the defaultmap clause when the specified 
//  implicit-behavior is present. The variable-categories available for defaultmap
//  are scalar, aggregate, and pointer. If implicit-behavior is present, each 
//  variable referenced in the construct in the category specified by 
//  variable-category is treated as if it had been listed in a map clause wih the
//  map-type of alloc and map-type-modifier of present.
//
////===----------------------------------------------------------------------===//

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "ompvv.h"
#include <math.h>

#define N 1024

int errors, i;

int test_defaultmap_present_scalar() {

   int scalar_var; 
   float float_var;
   double double_var;
   errors = 0;
   scalar_var = 1;
   float_var = 10.7f;
   double_var = 12.22;

   #pragma omp target enter data map(to: scalar_var, float_var, double_var)
   #pragma omp target map(tofrom: errors) defaultmap(present: scalar)
   {
      if(scalar_var != 1){errors++;}
      if(float_var != 10.7f){errors++;}
      if(double_var != 12.22){errors++;}

      scalar_var = 7;
      float_var = 20.1f;
      double_var = 55.55;
   }

   OMPVV_TEST_AND_SET(errors, scalar_var == 7);
   OMPVV_TEST_AND_SET(errors, float_var == 20.1f);
   OMPVV_TEST_AND_SET(errors, double_var == 55.55);

   return errors;
}

int main() {
   errors = 0;
   OMPVV_TEST_OFFLOADING;
   OMPVV_TEST_AND_SET_VERBOSE(errors, test_defaultmap_present_scalar() != 0);
   OMPVV_REPORT_AND_RETURN(errors);
}
