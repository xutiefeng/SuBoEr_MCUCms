/* u8g2_d_memory.c */
/* generated code, codebuild, u8g2 project */

#include "u8g2.h"

#define U8G2_SIZE_MAX 128

uint8_t *u8g2_m_16_8_f(uint8_t *page_cnt)
{
  #ifdef U8G2_USE_DYNAMIC_ALLOC
  *page_cnt = 8;
  return 0;
  #else
  static uint8_t buf[U8G2_SIZE_MAX];
  *page_cnt = 8;
  return buf;
  #endif
}
