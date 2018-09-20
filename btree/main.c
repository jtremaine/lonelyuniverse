#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "btree.h"

#define _BOOT_TEST 1

/* 
 * Quick boot test
 */
int boot_test(void)
{
  struct btree *bt;
  int error = 0;
  bool bt_open;

  printf("Boot Test: Start\n");

  /* BVT: create, insert, lookup */
  bt_open = false;
  error = btree_create(&bt);
  if (error != 0) {
    bt_open = true;
    goto out;
  }

  error = btree_insert(bt);
  if (error != 0)
    goto out;

  error = btree_lookup(bt);
  if (error != 0)
    goto out;

  printf("Boot Test: Success\n");

 out:
  if (bt_open)
    btree_close(bt);

  if (error != 0)
    printf("Boot Test: Fail with error: %s\n", strerror(error));
  return error;
}

int main(void)
{
  int error = 0;

  printf("Main Start\n");

#ifdef _BOOT_TEST
  boot_test();
#endif

  printf("Main End\n");

  return error;
}
