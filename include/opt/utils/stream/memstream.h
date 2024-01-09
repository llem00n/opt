// *************************************************************************
// memstream.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 11/30/23
// *************************************************************************

#ifndef OPT_UTILS_STREAM_MEMSTREAM_H
#define OPT_UTILS_STREAM_MEMSTREAM_H

#include <stddef.h>
#include <opt/utils/stream/stream.h>

/**
 * @brief Defines memory stream
 */
typedef struct memstream {
  stream_t base;
  char *buffer;
  size_t buffer_size;
  size_t position;
} memstream_t;

/**
 * @brief Initializes memory stream
 * @param memstream Memory stream
 * @param buffer Buffer
 * @param buffer_size Buffer size
 * @return ERROR_BAD_PARAMETER if memstream is NULL,
 *         ERROR_OK if success
 */
error_t memstream_init(memstream_t *memstream, char *buffer, size_t buffer_size);

/**
 * @brief Reads from memory stream
 * @param memstream Memory stream
 * @param buffer Buffer
 * @param buffer_size Buffer size
 * @param read_bytes Read bytes
 * @return ERROR_BAD_PARAMETER if memstream or buffer is NULL,
 *         ERROR_STREAM_CANNOT_READ if cannot read from stream,
 *         ERROR_OK if success
 */
error_t memstream_read(memstream_t *memstream, char *buffer, size_t buffer_size, size_t *read_bytes);

/**
 * @brief Writes to memory stream
 * @param memstream Memory stream
 * @param buffer Buffer
 * @param buffer_size Buffer size
 * @param written_bytes Written bytes
 * @return ERROR_BAD_PARAMETER if memstream or buffer is NULL,
 *         ERROR_STREAM_CANNOT_WRITE if cannot write to stream,
 *         ERROR_STREAM_FULL if stream is full,
 *         ERROR_OK if success
 */
error_t memstream_write(memstream_t *memstream, const char *buffer, size_t buffer_size, size_t *written_bytes);

/**
 * @brief Closes memory stream
 * @param memstream Memory stream
 */
void memstream_close(memstream_t *memstream);

#endif //OPT_UTILS_STREAM_MEMSTREAM_H
