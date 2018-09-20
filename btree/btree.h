#ifndef __BTREE_H__
#define __BTREE_H__

#include <stdbool.h>

/*
 * In memory btree
 */
struct btree {
  /* Does btree need a write?  */
  bool dirty;
  void * root;
};

int btree_create(struct btree **bt);
int btree_insert(struct btree *bt);
int btree_lookup(struct btree *bt);

#endif
