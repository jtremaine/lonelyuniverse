#include <stdio.h>
#include "solar.h"

#define _SOLAR_TEST_COUNT 1000000

static int
test_solar(void)
{
	struct solar solar = {};
	int error = 0;
	int i = 0;

	for (i = 0; i < _SOLAR_TEST_COUNT; i++) {
		error = create_solar(&solar);
		if (error != 0)
			goto out;

		error = dump_solar(&solar);
		if (error != 0)
			goto out;

	}

 out:
	return error;
}

int main(void)
{
	int error = 0;

	printf("Solar test driver\n");
	error = test_solar();
	if (error != 0)
		goto out;

 out:
	if (error != 0)
		printf("%d", error);
	return error;
}
