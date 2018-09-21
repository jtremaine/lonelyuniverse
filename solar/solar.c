#include <stdio.h>
#include <stdlib.h>
#include "solar.h"

/*
 * Determines if a piece of land is habitable or not.
 * This will be a fun paramater to play with
 * Maybe LAND_OCEAN should be habitable? E.g waterworld
 */
static bool
land_is_habitable(struct land *land)
{
	bool habitable = false;

	switch (land->type) {
	case LAND_MOUNTAIN:
	case LAND_PLAIN:
		habitable = true;
	}

	return habitable;
}

int
create_solar(struct solar *solar)
{
	long int rval = 0;
	int land, sun;
	int error = 0;

	/* Get a position */
	/* XXXJAT: Maybe this belongs in the universe code? */
	solar->position.x = random() % _UNIVERSE_MAX;
	solar->position.y = random() % _UNIVERSE_MAX;

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
			/* If we have a habitable sun add a natural land type */
			rval = random();
			land = rval % (LAND_NATURAL_MAX + 1);
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

/* Serialize to disk */
int
write_solar(struct solar *solar)
{
}

/* Deserialize from disk */
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
#define CITY_SYMBOL "$"

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
	case LAND_CITY:
		printf(CITY_SYMBOL);
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

	/* Print position */
	printf("\n(%lu, %lu)\n", solar->position.x, solar->position.y);

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

/*
 * Replaces all habitable land with LAND_CITY
 */
int
add_people(struct solar *solar)
{
	int error = 0;
	int i = 0;

	if (solar->sun.type == SUN_UNINHABITABLE)
		goto out;

	for (i= 0; i < _PLANET_LAND; i++) {
		if (land_is_habitable(&solar->planet.land[i]))
		    solar->planet.land[i].type = LAND_CITY;
	}

 out:
	return error;
}

/* Anywhere there were people is turned to desert */
int
remove_people(struct solar *solar)
{
	int error = 0;
	int i = 0;

	for (i = 0; i < _PLANET_LAND; i++) {
		if (solar->planet.land[i].type == LAND_CITY)
			solar->planet.land[i].type = LAND_DESERT;
	}

	return error;
}

/* Are there people on this planet? */
bool
has_people(struct solar *solar)
{
	int i = 0;
	bool has_people = false;

	for (i = 0; i < _PLANET_LAND; i++) {
		if (solar->planet.land[i].type == LAND_CITY)
			has_people = true;
	}

	return has_people;
}

/* Is there anywhere people can live in this solar system? */
bool
is_habitable(struct solar *solar)
{
	int i = 0;
	bool habitable = false;

	if (solar->sun.type == SUN_UNINHABITABLE)
		goto out;

	for (i= 0; i < _PLANET_LAND; i++) {
		if (land_is_habitable(&solar->planet.land[i]))
			habitable = true;
	}

 out:
	return habitable;
}
