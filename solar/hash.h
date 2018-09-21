#ifndef __HASH_H__
#define __HASH_H__

/* XXXJAT: This doesn't need to be a global */
#define _HASH_BUCKETS 19999

struct entry {
  struct entry *chain;
  void *key;
  void *payload;
};

struct chain {
  struct entry *entry;
};

struct hash {
  struct chain *chains;
  unsigned int buckets;

  /* Function virtuals */
  uint64_t (*h)(void *key);
  int (*match)(void *key1, void *key2);
  void (*destroy)(void *key, void *payload);
};

int hash_create(struct hash *hash, unsigned int buckets,
		uint64_t (*h)(void *key),
		int (*match)(void *key1, void*key2),
		void (*destroy)(void *key, void *payload));
int hash_lookup(struct hash *hash, void *key);
int hash_insert(struct hash *hash, void *element);
int hash_destroy(struct hash *hash);

#endif
