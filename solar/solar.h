#ifndef __SOLAR_H__
#define __SOLAR_H__

/***
 * Solar.h presents the structures and API representing a solar system.
 * Each solar system contains
 * 1) A sun
 * 2) A planet
 * If the sun is uninhabitable for any reason, the planet is all desert (=)
 ***/

#include <stdint.h>
#include <stdbool.h>

/*
 * These two parameters are interrelated.
 * LAND = GRID * GRID
 */
#define _PLANET_LAND 16
#define _PLANET_GRID 4

/* XXXJAT: This should ultimately be a part of the universe definition */
#define _UNIVERSE_MAX 1024

/***
 *** SOlar system Structures
 ***/
enum land_type {
	LAND_OCEAN,
	LAND_DESERT,
	LAND_MOUNTAIN,
	LAND_PLAIN,
	LAND_NATURAL_MAX = LAND_PLAIN,
	LAND_CITY,
	LAND_MAX = LAND_CITY
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

struct position {
	uint64_t x;
	uint64_t y;
};

/* One habitable planet and one sun for now */
struct solar {
	struct position position;
	struct sun sun;
	struct planet planet;
};

/***
 *** Basic Solar operations
 ***/
int create_solar(struct solar *solar);
int write_solar(struct solar *solar);
int read_solar(struct solar *solar);
int dump_solar(struct solar *solar);

/***
 *** People related operations
 ***/
int add_people(struct solar *solar);
bool has_people(struct solar *solar);
bool is_habitable(struct solar *solar);
int remove_people(struct solar *solar);

#endif
