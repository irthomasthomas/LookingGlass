/**
 * Looking Glass
 * Copyright (C) 2017-2021 The Looking Glass Authors
 * https://looking-glass.io
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc., 59
 * Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "common/ringbuffer.h"

#include <stdlib.h>
#include <string.h>

struct RingBuffer
{
  int     length;
  size_t  valueSize;
  int     start, pos, count;
  char    values[0];
};

RingBuffer ringbuffer_new(int length, size_t valueSize)
{
  struct RingBuffer * rb = calloc(1, sizeof(*rb) + valueSize * length);
  rb->length    = length;
  rb->valueSize = valueSize;
  return rb;
}

void ringbuffer_free(RingBuffer * rb)
{
  if (!*rb)
    return;

  free(*rb);
  *rb = NULL;
}

void ringbuffer_push(RingBuffer rb, const void * value)
{
  if (rb->count < rb->length)
    ++rb->count;
  else
    if (++rb->start == rb->length)
      rb->start = 0;

  memcpy(rb->values + rb->pos * rb->valueSize, value, rb->valueSize);

  if (++rb->pos == rb->length)
    rb->pos = 0;
}

void ringbuffer_reset(RingBuffer rb)
{
  rb->start = 0;
  rb->pos   = 0;
  rb->count = 0;
}

int ringbuffer_getStart(const RingBuffer rb)
{
  return rb->start;
}

int ringbuffer_getCount(const RingBuffer rb)
{
  return rb->count;
}

void * ringbuffer_getValues(const RingBuffer rb)
{
  return rb->values;
}