// *************************************************************************
// stream.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 11/30/23
// *************************************************************************

#ifndef OPT_UTILS_STREAM_STREAM_H
#define OPT_UTILS_STREAM_STREAM_H

#include <opt/err.h>
#include <stddef.h>
#include <stdint.h>

/**
 * @brief Defines stream type
 */
typedef enum stream_type {
  STREAM_TYPE_FILE,
  STREAM_TYPE_STRING,
  STREAM_TYPE_COUNT,
} stream_type_t;

/**
 * @brief Defines stream base
 */
typedef struct stream {
  stream_type_t type: 2;
  int8_t open : 1;
} stream_t;

/**
 * @brief Initializes stream base
 * @param stream Stream
 * @param type Stream type
 * @returns ERROR_BAD_PARAMETER if stream is NULL,
 *          ERROR_STREAM_BAD_TYPE if stream type is invalid,
 *          ERROR_OK if success
 */
error_t stream_init(stream_t *stream, stream_type_t type);

/**
 * @brief Get stream type
 * @param stream Stream
 * @returns Stream type
 */
stream_type_t get_stream_type(const stream_t *stream);

/**
 * @brief Reads from stream
 * @param stream Stream
 * @param buffer Buffer
 * @param buffer_size Buffer size
 * @param read_bytes Read bytes
 * @return ERROR_BAD_PARAMETER if stream or buffer is NULL,
 *         ERROR_STREAM_CANNOT_READ if cannot read from stream,
 *         ERROR_OK if success
 */
error_t stream_read(stream_t *stream, char *buffer, size_t buffer_size, size_t *read_bytes);

/**
 * @brief Writes to stream
 * @param stream Stream
 * @param buffer Buffer
 * @param buffer_size Buffer size
 * @param written_bytes Written bytes
 * @return ERROR_BAD_PARAMETER if stream or buffer is NULL,
 *         ERROR_STREAM_CANNOT_WRITE if cannot write to stream,
 *         ERROR_OK if success
 */
error_t stream_write(stream_t *stream, const char *buffer, size_t buffer_size, size_t *written_bytes);

/**
 * @brief Closes stream
 * @param stream Stream
 */
void stream_close(stream_t *stream);

#endif //OPT_UTILS_STREAM_STREAM_H
