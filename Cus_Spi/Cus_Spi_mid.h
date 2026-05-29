#ifndef __CUS_SPI_MID_H__
#define __CUS_SPI_MID_H__


#include "Cus_Spi_port.h"


/* ******** Defines ******** */
  #define SPI_DELAY_US      (5)
/* ******** Defines ******** */


/* ************************************ */ 
void Cus_SPI_Mid_ResetIdle( uint8_t mode );                       // 总线电平复位.
void Cus_SPI_Mid_SendByte_MSB( uint8_t tx, uint8_t mode );      // 半双工发送一个字节.(MSB字序)
void Cus_SPI_Mid_SendByte_LSB( uint8_t tx, uint8_t mode );      // 半双工发送一个字节.(LSB字序)
uint8_t Cus_SPI_Mid_RecvByte_MSB( uint8_t mode );               // 半双工接收一个字节.(MSB字序)
uint8_t Cus_SPI_Mid_RecvByte_LSB( uint8_t mode );               // 半双工接收一个字节.(LSB字序)
/* ************************************ */

#endif /* __CUS_SPI_MID_H__ */ 
