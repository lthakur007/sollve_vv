//===---------------- test_teams_default_firstprivate.c ----------------------===//
//
// OpenMP API Version 5.1 Nov 2020
//
// This test uses the default(firstprivate) clause on a teams directive. The test
// validates that when the default(firstprivate) clause is present that all
// variables without explicit sharing rules is not avaialble outside the region
// and is encapsulated between each thread. Starting with the initial value from
// outside the region. This is checked by by establishing a not_shared value. Since
// all changes should not persist after the construct region, it should have 
// not changed. Additionally if there is a race condition, we know the variable 
// is not defaulting to firstprivate either.
//
////===----------------------------------------------------------------------===//

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "ompvv.h"

#define N 1024

int main() {
	int errors = 0;
	int not_shared = 5;
	int num_teams = 0;

	#pragma omp teams default(firstprivate) shared(num_teams) num_teams(OMPVV_NUM_TEAMS_DEVICE)
	{
		num_teams = omp_get_num_teams();
		for (int i = 0; i < omp_get_num_teams(); i++) {
			not_shared += 5;
		}
	}

	OMPVV_WARNING_IF(num_teams != 8, "The number of teams was unexpected, the test results are likely inconcuslive")
	OMPVV_TEST_AND_SET(errors, (not_shared != 5));

	OMPVV_REPORT_AND_RETURN(errors);
}
