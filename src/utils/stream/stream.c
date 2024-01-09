// *************************************************************************
// stream.c
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 11/30/23
// *************************************************************************

#include <opt/utils/stream/stream.h>
#include <opt/utils/stream/memstream.h>
#include <opt/utils/stream/filestream.h>
#include <opt/utils/win_and_lin.h>
#include <string.h>

error_t stream_init(stream_t *stream, const stream_type_t type) {
  if (stream == NULL) {
    return ERROR_BAD_PARAMETER;
  }

  if (type >= STREAM_TYPE_COUNT) {
    return ERROR_STREAM_BAD_TYPE;
  }

  stream->type = type;
  stream->open = 0;

  return ERROR_OK;
}

stream_type_t get_stream_type(const stream_t *stream) {
  if (stream == NULL) {
    return STREAM_TYPE_COUNT;
  }

  return stream->type;
}

error_t stream_read(stream_t *stream, char *buffer, const size_t buffer_size, size_t *read_bytes) {
  if (stream == NULL || buffer == NULL) {
    return ERROR_BAD_PARAMETER;
  }

  if (!stream->open) {
    return ERROR_STREAM_INVALID;
  }

  switch (stream->type) {
    case STREAM_TYPE_FILE:
      return filestream_read((filestream_t *) stream, buffer, buffer_size, read_bytes);
    case STREAM_TYPE_STRING:
      return memstream_read((memstream_t *) stream, buffer, buffer_size, read_bytes);
    default:
      return ERROR_STREAM_CANNOT_READ;
  }
}

error_t stream_write(stream_t *stream, const char *buffer, const size_t buffer_size, size_t *written_bytes) {
  if (stream == NULL || buffer == NULL) {
    return ERROR_BAD_PARAMETER;
  }

  if (!stream->open) {
    return ERROR_STREAM_INVALID;
  }

  switch (stream->type) {
    case STREAM_TYPE_FILE:
      return filestream_write((filestream_t *) stream, buffer, buffer_size, written_bytes);
    case STREAM_TYPE_STRING:
      return memstream_write((memstream_t *) stream, buffer, buffer_size, written_bytes);
    default:
      return ERROR_STREAM_CANNOT_WRITE;
  }
}

void stream_close(stream_t *stream) {
  if (stream == NULL) {
    return;
  }

  switch (stream->type) {
    case STREAM_TYPE_FILE:
      filestream_close((filestream_t *) stream);
      break;
    case STREAM_TYPE_STRING:
      memstream_close((memstream_t *) stream);
      break;
    default:
      break;
  }
  stream->open = 0;
}

error_t filestream_init(filestream_t *filestream, const char *filename, const char *mode) {
  if (!filestream) {
    return ERROR_BAD_PARAMETER;
  }

  stream_init(&filestream->base, STREAM_TYPE_FILE);
  filestream->file = fopen(filename, mode);
  if (!filestream->file) {
    return ERROR_FILESTREAM_CANNOT_OPEN_FILE;
  }
  filestream->base.open = 1;

  strncpy(filestream->mode, mode, 3);

  return ERROR_OK;
}

error_t filestream_read(const filestream_t *filestream, char *buffer, const size_t buffer_size, size_t *read_bytes) {
  if (!filestream || !buffer) {
    return ERROR_BAD_PARAMETER;
  }

  if (filestream->mode[0] != 'r' && filestream->mode[1] != '+') {
    return ERROR_STREAM_CANNOT_READ;
  }

  *read_bytes = fread(buffer, sizeof(char), buffer_size, filestream->file);

  return ERROR_OK;
}

error_t filestream_write(const filestream_t *filestream, const char *buffer, const size_t buffer_size, size_t *written_bytes) {
  if (!filestream || !buffer) {
    return ERROR_BAD_PARAMETER;
  }

  if (filestream->mode[0] != 'w' && filestream->mode[0] != 'a' && filestream->mode[1] != '+') {
    return ERROR_STREAM_CANNOT_WRITE;
  }

  *written_bytes = fwrite(buffer, sizeof(char), buffer_size, filestream->file);

  return ERROR_OK;
}

void filestream_close(filestream_t *filestream) {
  if (!filestream) {
    return;
  }

  fclose(filestream->file);
  filestream->file = NULL;
}

error_t memstream_init(memstream_t *memstream, char *buffer, const size_t buffer_size) {
  if (!memstream) {
    return ERROR_BAD_PARAMETER;
  }

  stream_init(&memstream->base, STREAM_TYPE_STRING);
  memstream->buffer = buffer;
  memstream->buffer_size = buffer_size;
  memstream->position = 0;
  memstream->base.open = 1;

  return ERROR_OK;
}

error_t memstream_read(memstream_t *memstream, char *buffer, const size_t buffer_size, size_t *read_bytes) {
  if (!memstream || !buffer) {
    return ERROR_BAD_PARAMETER;
  }

  if (memstream->position >= memstream->buffer_size) {
    return ERROR_STREAM_CANNOT_READ;
  }

  *read_bytes = memstream->buffer_size - memstream->position;
  if (*read_bytes > buffer_size) {
    *read_bytes = buffer_size;
  }

  memcpy(buffer, memstream->buffer + memstream->position, *read_bytes);
  memstream->position += *read_bytes;

  return ERROR_OK;
}

error_t memstream_write(memstream_t *memstream, const char *buffer, const size_t buffer_size, size_t *written_bytes) {
  error_t error = ERROR_OK;

  if (!memstream || !buffer) {
    return ERROR_BAD_PARAMETER;
  }

  if (memstream->position >= memstream->buffer_size) {
    return ERROR_STREAM_STREAM_FULL;
  }

  *written_bytes = memstream->buffer_size - memstream->position;
  if (*written_bytes > buffer_size) {
    error = ERROR_STREAM_STREAM_FULL;
    *written_bytes = buffer_size;
  }

  memcpy(memstream->buffer + memstream->position, buffer, *written_bytes);
  memstream->position += *written_bytes;

  return error;
}

void memstream_close(memstream_t *memstream) {
  if (!memstream) {
    return;
  }

  memstream->buffer = NULL;
  memstream->buffer_size = 0;
  memstream->position = 0;
}