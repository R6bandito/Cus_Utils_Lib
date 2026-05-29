#ifndef __CUS_SPI_H__
#define __CUS_SPI_H__

#include <stdint.h>
#include <stdbool.h>

/* ***************** Enum ***************** */
typedef enum
{
  CUS_SPI_MODE_0 = 0,
  CUS_SPI_MODE_1,
  CUS_SPI_MODE_2,
  CUS_SPI_MODE_3

} spiMode_t;
/* ***************** Enum ***************** */

typedef struct spiBus_t spiBus_t;   // 前置声明

/* ***************** Dev_Node ***************** */
typedef struct 
{
  deviceNode_t *next;
  deviceNode_t *prev;
  spiMode_t devMode;          // 该设备进行通信的SPI模式.
  spiBus_t *spiBus;           // 所属总线.

} deviceNode_t;
/* ***************** Dev_Node ***************** */


/* ***************** SPI_SENTINEL ***************** */
typedef struct 
{
  deviceNode_t *next;
  deviceNode_t *prev;

} spiSentinel_t;
/* ***************** SPI_SENTINEL ***************** */


/* ***************** SPI_BUS ***************** */
/* SPI 总线结构定义 */
typedef struct 
{
  uint16_t devCount;                                      // 当前SPI总线挂载设备数.
  bool isBusValid;                                        // SPI总线保护锁. (当前SPI总线是否可用).

  void (*select)( uint8_t devId, uint8_t pin_level );     // 片选控制回调.
  spiSentinel_t borderNode;                               // 哨兵节点.
} spiBus_t;
/* ***************** SPI_BUS ***************** */




#endif /* __CUS_SPI_H__ */
