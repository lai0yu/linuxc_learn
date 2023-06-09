#ifndef __DRV_DMA_H__
#define __DRV_DMA_H__

#include "stm32f10x.h"

extern void dma_config(uint32_t *src, uint32_t *dst, uint32_t size);
extern int is_dma_finish(uint32_t *src, uint32_t *dst, uint32_t size);
#endif
