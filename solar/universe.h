#ifndef __UNIVERSE_H__
#define __UNIVERSE_H__

#include <stdint.h>

struct universe {
  uint64_t system_count;
  uint64_t size;

  void *system_cache;
};

int create_universe(struct universe *un);

#endif
