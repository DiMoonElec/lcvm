#ifndef __LCVM_CORE_MEMORY_ACCESS_H__
#define __LCVM_CORE_MEMORY_ACCESS_H__

#if defined(LCVM_ALLOW_UNALIGNED_ACCESS)

#define READ_U32_FROM_ARRAY_4(dst, src, index) dst = *(uint32_t *)&src[index]

#define WRITE_U32_TO_ARRAY_4(dst, index, src) *(uint32_t *)&dst[index] = src

#elif defined(LCVM_USE_MEMCPY)

#define READ_U32_FROM_ARRAY_4(dst, src, index) memcpy(&dst, &src[index], 4)

#define WRITE_U32_TO_ARRAY_4(dst, index, src) memcpy(&dst, &src[index], 4)

#else

/*
  Макросы чтения значения в переменную UINT32
  из массива побайтно
*/

#define READ_U32_FROM_ARRAY_4(dst, src, index) \
  dst = (uint32_t)src[index] |               \
        ((uint32_t)src[index + 1] << 8) |    \
        ((uint32_t)src[index + 2] << 16) |   \
        ((uint32_t)src[index + 3] << 24)

/*
  Макросы записи значения из переменной UINT32
  в массив побайтно.
*/

#define WRITE_U32_TO_ARRAY_1(dst, index, src) \
  dst[index] = (uint8_t)(src);

#define WRITE_U32_TO_ARRAY_2(dst, index, src) \
  {                                         \
    uint32_t value = src;                   \
    dst[index] = (uint8_t)(value);          \
    dst[index + 1] = (uint8_t)(value >> 8); \
  }

#define WRITE_U32_TO_ARRAY_4(dst, index, src)  \
  {                                          \
    uint32_t value = src;                    \
    dst[index] = (uint8_t)(value);           \
    dst[index + 1] = (uint8_t)(value >> 8);  \
    dst[index + 2] = (uint8_t)(value >> 16); \
    dst[index + 3] = (uint8_t)(value >> 24); \
  }

#endif

#endif