#include <stdio.h>
#include <stdlib.h>
#include "solar.h"

int
create_solar(struct solar *solar)
{
	long int rval = 0;
	int land, sun;
	int error = 0;

	/* Inititlize sun */
	solar->sun.creation = 0;
	solar->sun.age = 0;

	rval = random();
	sun = rval % (SUN_MAX + 1);
	solar->sun.type = sun;

	/* Initialize planet with random land types */
	int i;
	for (i = 0; i < _PLANET_LAND; i++) {

		switch (solar->sun.type) {
		case SUN_HABITABLE:
			rval = random();
			land = rval % (LAND_MAX + 1);
			solar->planet.land[i].type = land;
			break;
		case SUN_UNINHABITABLE:
			/* If the sun is uninhabitable we only get desert */
			solar->planet.land[i].type = LAND_DESERT;
			break;
			
		}
	}

	return error;
}

int
write_solar(struct solar *solar)
{
}

int
read_solar(struct solar *solar)
{
}

static int
dump_sun(struct sun *sun)
{
	switch (sun->type) {
	case SUN_HABITABLE:
		break;
	case SUN_UNINHABITABLE:
		break;
	}

	return 0;
}

#define OCEAN_SYMBOL "~"
#define DESERT_SYMBOL "="
#define MOUNTAIN_SYMBOL "^"
#define PLAIN_SYMBOL "#"

static int
dump_land(const struct land *land)
{
	int error = 0;

	switch (land->type) {
	case LAND_OCEAN:
		printf(OCEAN_SYMBOL);
		break;
	case LAND_DESERT:
		printf(DESERT_SYMBOL);
		break;
	case LAND_MOUNTAIN:
		printf(MOUNTAIN_SYMBOL);
		break;
	case LAND_PLAIN:
		printf(PLAIN_SYMBOL);
		break;
	}

	return error;
}

static int
dump_planet(const struct planet *planet)
{
	int error = 0;

	printf("\n");

	int i;
	for (i = 0; i < _PLANET_LAND; i++) {

		error = dump_land(&planet->land[i]);
		if (error != 0)
			goto out;
		if ((i + 1) % _PLANET_GRID == 0)
			printf("\n");
	}

	printf("\n");

 out:
	return error;
}

int
dump_solar(struct solar *solar)
{
	int error = 0;

	/* Print sun */
	error = dump_sun(&solar->sun);
	if (error != 0)
		goto out;

	/* Print planet */
	error = dump_planet(&solar->planet);
	if (error != 0)
		goto out;

 out:
	return error;
}
