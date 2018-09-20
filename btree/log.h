#ifndef __LOG_H
#define __LOG_H

/* Comment to disable logging */
#define __LOG_ON 1

#ifdef __LOG_ON
#define log printf
#else
#define log void
#endif

#endif
