/**
 * @file ringbuff.c
 * @author CuteMan0
 * @date 2024/4/25
 */

#include "RingBuff_sl.h"

void RingBuff_Init(RB_t *l_rb)
{
    l_rb->Lenght = l_rb->Capicity = l_rb->Head = l_rb->Tail = 0;
    l_rb->Array                                             = NULL;
}

RB_Status Write_RingBuff(RB_t *l_rb, RBDat_t data)
{
    // 缓冲区满
    if (l_rb->Lenght >= l_rb->Capicity) {
        uint32_t newcap = l_rb->Capicity == 0 ? RINGBUFF_LEN : l_rb->Capicity * 2;
        RBDat_t *temp   = (RBDat_t *)realloc(l_rb->Array, newcap * sizeof(RBDat_t));
        if (temp == NULL) {
            // 分配内存失败
            return FLASE;
        }
        l_rb->Array    = temp;
        l_rb->Capicity = newcap;
    }
    l_rb->Array[l_rb->Tail] = data;
    // 缓冲区临满
    if ((l_rb->Tail + 1) % l_rb->Capicity == l_rb->Head) {
        l_rb->Tail++;
    } else {
        l_rb->Tail = (l_rb->Tail + 1) % l_rb->Capicity;
    }
    l_rb->Lenght++;
    return TRUE;
}

RB_Status Read_RingBuff(RB_t *l_rb, RBDat_t *rdata)
{
    // 缓冲区空
    if (l_rb->Lenght == 0) {
        if (l_rb->Head == 0) {
            l_rb->Tail = l_rb->Head;
        }
        return FLASE;
    }
    *rdata     = l_rb->Array[l_rb->Head];
    l_rb->Head = (l_rb->Head + 1) % l_rb->Capicity;
    l_rb->Lenght--;
    return TRUE;
}