#include "drv_dma.h"

void dma_config(uint32_t *src, uint32_t *dst, uint32_t size) {
    DMA_InitTypeDef dma_init_struct;

    // 使能DMA1时钟
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    // 配置DMA1 Channel2
    dma_init_struct.DMA_PeripheralBaseAddr = (uint32_t)src;               // 源地址
    dma_init_struct.DMA_MemoryBaseAddr = (uint32_t)dst;                   // 目标地址
    dma_init_struct.DMA_DIR = DMA_DIR_PeripheralSRC;                      // 数据传输方向，从外设到存储器
    dma_init_struct.DMA_BufferSize = size;                                // 数据传输长度
    dma_init_struct.DMA_PeripheralInc = DMA_PeripheralInc_Enable;         // 外设地址自增
    dma_init_struct.DMA_MemoryInc = DMA_MemoryInc_Enable;                 // 存储器地址自增
    dma_init_struct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word; // 外设数据宽度为32位
    dma_init_struct.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;         // 存储器数据宽度为32位
    dma_init_struct.DMA_Mode = DMA_Mode_Normal;                           // DMA模式为Normal
    dma_init_struct.DMA_Priority = DMA_Priority_Medium;                   // DMA传输优先级为中
    dma_init_struct.DMA_M2M = DMA_M2M_Enable;                             // 存储器到存储器模式使能
    DMA_Init(DMA1_Channel2, &dma_init_struct);

    // 使能DMA1 Channel2
    DMA_Cmd(DMA1_Channel2, ENABLE);
}

int is_dma_finish(uint32_t *src, uint32_t *dst, uint32_t size) {
    int i;
    for (i = 0; i < size; i++) {
        if (src[i] != dst[i]) {
            return 0;
        }
    }
    return 1;
}
