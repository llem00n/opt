// *************************************************************************
// filestream.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 11/30/23
// *************************************************************************

#ifndef OPT_UTILS_STREAM_FILESTREAM_H
#define OPT_UTILS_STREAM_FILESTREAM_H

#include <stdio.h>
#include <opt/utils/stream/stream.h>

/**
 * @brief Defines file stream
 */
typedef struct filestream {
  stream_t base;
  FILE *file;
  char mode[3];
} filestream_t;

/**
 * @brief Initializes file stream
 * @param filestream File stream
 * @param filename File name
 * @param mode File mode
 * @return ERROR_BAD_PARAMETER if filestream is NULL,
 *         ERROR_FILESTREAM_CANNOT_OPEN_FILE if file cannot be opened,
 *         ERROR_OK if success
 */
error_t filestream_init(filestream_t *filestream, const char *filename, const char *mode);

/**
 * @brief Reads from file stream
 * @param filestream File stream
 * @param buffer Buffer
 * @param buffer_size Buffer size
 * @param read_bytes Read bytes
 * @return ERROR_BAD_PARAMETER if filestream or buffer,
 *         ERROR_STREAM_CANNOT_READ if cannot read from stream,
 *         ERROR_STREAM_INVALID if stream is invalid,
 *         ERROR_OK if success
 */
error_t filestream_read(const filestream_t *filestream, char *buffer, size_t buffer_size, size_t *read_bytes);

/**
 * @brief Writes to file stream
 * @param filestream File stream
 * @param buffer Buffer
 * @param buffer_size Buffer size
 * @param written_bytes Written bytes
 * @return ERROR_BAD_PARAMETER if filestream or buffer is NULL,
 *         ERROR_STREAM_CANNOT_WRITE if cannot write to stream,
 *         ERROR_STREAM_INVALID if stream is invalid,
 *         ERROR_OK if success
 */
error_t filestream_write(const filestream_t *filestream, const char *buffer, size_t buffer_size, size_t *written_bytes);

/**
 * @brief Closes file stream
 * @param filestream File stream
 */
void filestream_close(filestream_t *filestream);

#endif //OPT_UTILS_STREAM_FILESTREAM_H
