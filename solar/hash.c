#include <stdint.h>
#include "hash.h"

int hash_create(struct hash *hash, unsigned int buckets,
                uint64_t (*h)(void *key),
		int (*match)(void *key1, void*key2),
                void (*destroy)(void *key, void *payload))
{
  int error = 0;
  int i = 0;

  hash->buckets = buckets;

  hash->chains = malloc(buckets * sizeof(struct chain*));
  if (hash->chains == NULL) {
    error = errno;
    goto out;
  }

  for (i = 0; i < buckets; i++)
    hash->chains = NULL;

  hash->h = h;
  hash->match = match;
  hash->destroy = destroy;

 out:
  return error;
}

int hash_lookup(struct hash *hash, void *key)
{
  int error = 0;

  return error;
}

int hash_insert(struct hash *hash, void *element)
{
  int error = 0;

  return error;
}

int
chain_destroy_tail(struct chain *chain)
{
  struct chain *iter_tail;
  struct chain *iter_prev;
  int error = 0;

  /* No tail entry */
  if (chain->entry == NULL)
    goto out;

  iter_tail = chain->entry;
  if (iter_tail->next == NULL) {
    /* There is only one entry, destroy it */
    /* TODO */
  }

  while (iter_tail

 out:
  return error;
}

int
chain_destroy(struct chain *chain)
{
  while (chain->entry != NULL)
    chain_destroy_tail(chain);

  free(chain);
  
}


int 
hash_destroy(struct hash *hash)
{
  int error = 0;
  int i = 0;

  for (i = 0; i < buckets; i++) {
    if (hash->chains[i] != NULL) {
      chain_destroy(hash->chains[i])
    }
  }

  free(hash->chains);

  return error;
}
