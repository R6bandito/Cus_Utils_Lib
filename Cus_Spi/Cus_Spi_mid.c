#include "Cus_Spi_mid.h"


/* ****************************************** */
void Cus_SPI_Mid_ResetIdle( uint8_t mode );
void Cus_SPI_Mid_SendByte_MSB( uint8_t tx, uint8_t mode );
void Cus_SPI_Mid_SendByte_LSB( uint8_t tx, uint8_t mode );
uint8_t Cus_SPI_Mid_RecvByte_MSB( uint8_t mode ); 
uint8_t Cus_SPI_Mid_RecvByte_LSB( uint8_t mode );
/* ****************************************** */


/* ************* Defines ************* */
#define CUS_SPI_MID_BIT_SEND_MODE0(data)  do                                \
                                          {                                 \
                                            Cus_SPI_MOSI_Write(data);       \
                                            Cus_SPI_Delay_us(SPI_DELAY_US); \
                                            Cus_SPI_CLK_Write(1);           \
                                            Cus_SPI_Delay_us(SPI_DELAY_US); \
                                            Cus_SPI_CLK_Write(0);           \
                                          } while(0)

#define CUS_SPI_MID_BIT_SEND_MODE1(data)  do                                \
                                          {                                 \
                                            Cus_SPI_MOSI_Write(data);       \
                                            Cus_SPI_Delay_us(SPI_DELAY_US); \
                                            Cus_SPI_CLK_Write(1);           \
                                            Cus_SPI_Delay_us(SPI_DELAY_US); \
                                            Cus_SPI_CLK_Write(0);           \
                                            Cus_SPI_Delay_us(SPI_DELAY_US); \
                                          } while(0)                                          

#define CUS_SPI_MID_BIT_SEND_MODE2(data)  do                                \
                                          {                                 \
                                            Cus_SPI_CLK_Write(0);           \
                                            Cus_SPI_Delay_us(SPI_DELAY_US); \
                                            Cus_SPI_MOSI_Write(data);       \
                                            Cus_SPI_CLK_Write(1);           \
                                            Cus_SPI_Delay_us(SPI_DELAY_US); \
                                          } while(0)                                  
                                          
#define CUS_SPI_MID_BIT_SEND_MODE3(data)  do                                \
                                          {                                 \
                                            Cus_SPI_MOSI_Write(data);       \
                                            Cus_SPI_CLK_Write(0);           \
                                            Cus_SPI_Delay_us(SPI_DELAY_US); \
                                            Cus_SPI_CLK_Write(1);           \
                                            Cus_SPI_Delay_us(SPI_DELAY_US); \
                                          } while(0)  
                                          
#define CUS_SPI_MID_BIT_RECV_MODE0()                                        \
                                          ({                                \
                                            Cus_SPI_MOSI_Write(1);          \
                                            uint8_t bit;                    \
                                            Cus_SPI_CLK_Write(1);           \
                                            Cus_SPI_Delay_us(SPI_DELAY_US); \
                                            bit = Cus_SPI_MISO_Read();      \
                                            Cus_SPI_CLK_Write(0);           \
                                            Cus_SPI_Delay_us(SPI_DELAY_US); \
                                            bit;                            \
                                          }) 

#define CUS_SPI_MID_BIT_RECV_MODE1()                                        \
                                          ({                                \
                                            Cus_SPI_MOSI_Write(1);          \
                                            uint8_t bit;                    \
                                            Cus_SPI_CLK_Write(1);           \
                                            Cus_SPI_Delay_us(SPI_DELAY_US); \
                                            Cus_SPI_CLK_Write(0);           \
                                            bit = Cus_SPI_MISO_Read();      \
                                            Cus_SPI_Delay_us(SPI_DELAY_US); \
                                            bit;                            \
                                          }) 

#define CUS_SPI_MID_BIT_RECV_MODE2()                                        \
                                          ({                                \
                                            Cus_SPI_MOSI_Write(1);          \
                                            uint8_t bit;                    \
                                            Cus_SPI_CLK_Write(0);           \
                                            bit = Cus_SPI_MISO_Read();      \
                                            Cus_SPI_Delay_us(SPI_DELAY_US); \
                                            Cus_SPI_CLK_Write(1);           \
                                            Cus_SPI_Delay_us(SPI_DELAY_US); \
                                            bit;                            \
                                          }) 

#define CUS_SPI_MID_BIT_RECV_MODE3()                                        \
                                          ({                                \
                                            Cus_SPI_MOSI_Write(1);          \
                                            uint8_t bit;                    \
                                            Cus_SPI_CLK_Write(0);           \
                                            Cus_SPI_Delay_us(SPI_DELAY_US); \
                                            Cus_SPI_CLK_Write(1);           \
                                            bit = Cus_SPI_MISO_Read();      \                                     
                                            Cus_SPI_Delay_us(SPI_DELAY_US); \
                                            bit;                            \
                                          }) 
/* ************* Defines ************* */



void Cus_SPI_Mid_ResetIdle( uint8_t mode )
{
  switch (mode)
  {
    case 0:
    case 1: Cus_SPI_CLK_Write(0);   break;    // 模式 0/1. 空闲总线电平拉低.

    case 2:
    case 3: Cus_SPI_CLK_Write(1);     break;    // 模式 2/3. 空闲总线电平拉高.

    default:  break;
  }

  /* 延时一段时间. 确保总线电平稳定. */
  Cus_SPI_Delay_us(SPI_DELAY_US);
}


void Cus_SPI_Mid_SendByte_MSB( uint8_t tx, uint8_t mode )
{
  /* SPI 时序不允许被打断. */
  Cus_SPI_ENTER_CRITICAL();

  /* 总线状态复原. 准备发起一次通讯 */
  Cus_SPI_Mid_ResetIdle(mode);

  for( int8_t i = 7; i >= 0; i-- )
  {
    uint8_t send_bit = (tx >> i) & 0x01;
    switch (mode)
    {
      case 0:   CUS_SPI_MID_BIT_SEND_MODE0(send_bit);  break;
      case 1:   CUS_SPI_MID_BIT_SEND_MODE1(send_bit);  break;
      case 2:   CUS_SPI_MID_BIT_SEND_MODE2(send_bit);  break;
      case 3:   CUS_SPI_MID_BIT_SEND_MODE3(send_bit);  break;

      default:  break;
    }
  }

  Cus_SPI_EXIT_CRITICAL();
}


void Cus_SPI_Mid_SendByte_LSB( uint8_t tx, uint8_t mode )
{
  /* 进入临界段. */
  Cus_SPI_ENTER_CRITICAL();

  /* 复原总线状态. 准备开始通讯. */
  Cus_SPI_Mid_ResetIdle(mode);

  for( uint8_t i = 0; i < 8; i++ )
  {
    uint8_t send_bit = (tx >> i) & 0x01;

    switch (mode)
    {
      case 0:   CUS_SPI_MID_BIT_SEND_MODE0(send_bit);  break;
      case 1:   CUS_SPI_MID_BIT_SEND_MODE1(send_bit);  break;
      case 2:   CUS_SPI_MID_BIT_SEND_MODE2(send_bit);  break;
      case 3:   CUS_SPI_MID_BIT_SEND_MODE3(send_bit);  break;
      
      default:
        break;
    }
  }

  Cus_SPI_EXIT_CRITICAL();
}


uint8_t Cus_SPI_Mid_RecvByte_MSB( uint8_t mode )
{
  /* 进入临界段. 时序不允许被打断. */
  Cus_SPI_ENTER_CRITICAL();

  /* 复原总线状态. 准备开始一次接收通讯. */
  Cus_SPI_Mid_ResetIdle(mode);

  uint8_t recv_byte = 0;

  for( uint8_t i = 0; i < 8; i++ )
  {
    uint8_t bit = 0;
    switch (mode)
    {
      case 0:  bit = CUS_SPI_MID_BIT_RECV_MODE0();  break;
      case 1:  bit = CUS_SPI_MID_BIT_RECV_MODE1();  break;
      case 2:  bit = CUS_SPI_MID_BIT_RECV_MODE2();  break;
      case 3:  bit = CUS_SPI_MID_BIT_RECV_MODE3();  break;
      
      default:  break;
    }

    recv_byte |= (bit << (7 - i));
  }

  Cus_SPI_EXIT_CRITICAL();

  return recv_byte;
}


uint8_t Cus_SPI_Mid_RecvByte_LSB( uint8_t mode )
{
  /* 进入临界段. 时序不允许被打断. */
  Cus_SPI_ENTER_CRITICAL();

  /* 复原总线状态. 准备开始一次接收通讯. */
  Cus_SPI_Mid_ResetIdle(mode);

  uint8_t recv_byte = 0;

  for( uint8_t i = 0; i < 8; i++ )
  {
    uint8_t bit = 0;
    switch (mode)
    {
      case 0:  bit = CUS_SPI_MID_BIT_RECV_MODE0(); break;
      case 1:  bit = CUS_SPI_MID_BIT_RECV_MODE1(); break;
      case 2:  bit = CUS_SPI_MID_BIT_RECV_MODE2(); break;
      case 3:  bit = CUS_SPI_MID_BIT_RECV_MODE3(); break;
      
      default:  break;
    }

    recv_byte |= (bit << i);
  }

  Cus_SPI_EXIT_CRITICAL();

  return recv_byte;
}



