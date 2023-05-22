#ifndef HELPER_H
#define HELPER_H

#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>

#ifndef K_MAX_MSG
#define K_MAX_MSG 4096
#endif

void msg(const char *msg);

int32_t read_full(int fd, char *buf, size_t n);

int32_t write_all(int fd, const char *buf, size_t n);

void die(const char *msg);
#endif
