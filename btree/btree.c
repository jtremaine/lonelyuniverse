#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "btree.h"

/***
 *** Struct btree
 ***/
static int
btree_im_init(struct btree** bt)
{
  struct btree* bt_tmp;
  int error = 0;

  printf("Btree IM init\n");

  /* Allocate */
  *bt = NULL;
  bt_tmp = malloc(sizeof(struct btree));
  if (bt_tmp == NULL)
    return errno;
  
  /* Initialize */
  bt_tmp->root = NULL;
  bt_tmp->dirty = false;

  /* Hand off pointer */
  *bt = bt_tmp;

 out:
  return error;
}

static int
btree_im_free(struct btree* bt)
{
  int error = 0;

  printf("Btree IM free\n");

  free(bt);

  return error;
}

/***
 *** Btree On Disk encode/decode
 ***/
static int btree_od_header_write(void)
{
  int error = 0;

  return error;
}

static int btree_od_header_read(void)
{
  int error = 0;
  return error;
}

/***
 *** Btree IO
 ***/

/* Backing store. Static for now. */
#define __B_IO_FILE "/home/jtremaine/btree/bt.dat";

struct btree_io {
  int fd;
}

static int
btree_io_start(struct btree *bt, struct btree_io *bio)
{
  int error = 0;

  /* Open the backing store */
  bio->fd = open(__B_IO_FILE, O_RDWR | O_CREAT);
  if (bio->fd == -1) {
    error = errno;
    goto out;
  }

  return error;
}

static int
btree_io_end(struct btree_io* bio)
{
  int error = 0;

  close(bio->fd);

  return error;
}

/*
 * Writes a block to disk
 */
static int
btree_io_put(struct btree_io *bio, offset_t off, size_t size, void* buf)
{
  int error = 0;

  /* XXXJAT */
  error = ENOTSUP;

  return error;
}

/*
 * Reads a block from disk
 */
static int
btree_io_get(struct btree_io* bio, offset_t off, size_t size, void* buf)
{
  int error = 0;

  /* XXXJAT */
  error = ENOTSUP;
  return error;
}

/*
 * Transactional write
 */
static int 
btree_io_write_bt(struct btree *bt)
{
  struct btree_io bio;
  int error = 0;
  bool bt_open = false;

  /* No data to write */
  if (!bt->dirty) {
    printf("Btree IO write nodirty\n");
    goto out;
  }

  printf("Btree IO write\n");

  error = btree_io_start(bt, &bio);
  if (error != 0)
    goto out;
  bt_open = true;

  /* Write header */
  error = btree_od_header_write();
  if (error != 0)
    goto out;

  /* TODO: Write other things */

  /* Successful write. Mark not dirty */
  bt->dirty = false;

 out:
  if (bt_open)
    /* XXXJAT This covers previous errors */
    error = btree_io_end(&bio);
  return error;
}

/*** 
 *** Btree API
 ***/
int 
btree_create(struct btree** bt)
{
  int error = 0;

  printf("Btree create\n");

  error = btree_im_init(bt);
  if (error != 0)
    goto out;

  error = ENOTSUP;

 out:
  return error;
}

int 
btree_insert(struct btree *bt)
{
  int error = 0;

  printf("Btree insert\n");

  error = ENOTSUP;

  return error;
}

int 
btree_lookup(struct btree *bt)
{
  int error = 0;

  printf("Btree lookup");

  error = ENOTSUP;

  return error;
}

int 
btree_close(struct btree *bt)
{
  int error = 0;

  printf("Btree close\n");

  /* Flush changes to disk */
  error = btree_io_write_bt(bt);
  if (error != 0)
    goto out;

  error = btree_im_free(bt);
  if (error != 0)
    goto out;
  
 out:
  return error;
}
