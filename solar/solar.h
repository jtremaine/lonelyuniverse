#ifndef __SOLAR_H__
#define __SOLAR_H__

#include <stdint.h>

/*
 * These two parameters are interrelated.
 * LAND = GRID * GRID
 */
#define _PLANET_LAND 16
#define _PLANET_GRID 4

enum land_type {
	LAND_OCEAN,
	LAND_DESERT,
	LAND_MOUNTAIN,
	LAND_PLAIN,
	LAND_MAX = LAND_PLAIN
};

struct land {
	enum land_type type;
};

struct planet {
	struct land land[_PLANET_LAND];
};

enum sun_type {
	SUN_HABITABLE,
	SUN_UNINHABITABLE,
	SUN_MAX = SUN_UNINHABITABLE
};

struct sun {
	unsigned int creation;
	unsigned int age;
	enum sun_type type;
};

/* One habitable planet and one sun for now */
struct solar {
	struct sun sun;
	struct planet planet;
};

int create_solar(struct solar *solar);
int write_solar(struct solar *solar);
int read_solar(struct solar *solar);
int dump_solar(struct solar *solar);

#endif
