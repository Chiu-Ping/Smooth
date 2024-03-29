/*
 * spi.c
 *
 *  Created on: 19/feb/2015
 *      Author: Luca
 */

#include "spi.hpp"

// extern int handle;

static uint32_t addrs[MAX_SUPPORTED_PAGE_SIZE];
static SPI_API errors[MAX_SUPPORTED_PAGE_SIZE];
static uint32_t datas[MAX_SUPPORTED_PAGE_SIZE];

SPI_API spi_select(int handle) {

  CAENComm_ErrorCode ret;

  ret = CAENComm_Write32(handle, SPI_SELECT_REG_ADDR, 0x2);

  return ret;
}

SPI_API spi_unselect(int handle) {
  CAENComm_ErrorCode ret;
  ret = CAENComm_Write32(handle, SPI_SELECT_REG_ADDR, 0x3);
  return ret;
}

SPI_API spi_read(int handle, uint8_t *data) {

  uint32_t reg;
  CAENComm_ErrorCode ret;

  ret = CAENComm_Read32(handle, SPI_DATA_REG_ADDR, &reg);

  *data = (reg & 0xFF);
  return ret;
}

SPI_API spi_write(int handle, uint8_t data) {

  uint32_t reg;
  CAENComm_ErrorCode ret;

  reg = data & 0xFF;
  ret = CAENComm_Write32(handle, SPI_DATA_REG_ADDR, reg);

  return ret;
}

SPI_API spi_write_block(int handle, uint8_t *buf, uint32_t len) {

  int i;
  CAENComm_ErrorCode ret;

  for (i = 0; i < len; ++i) {
    addrs[i] = SPI_DATA_REG_ADDR;
    datas[i] = (uint32_t)buf[i];
  }

#ifdef __MULTIWRITE_SUPPORT__
  ret = CAENComm_MultiWrite32(handle, addrs, len, datas, errors);
#else
  for (i = 0; i < len; i++)
    ret = spi_write(buf[i]);
#endif

  return ret;
}

SPI_API spi_read_block(int handle, uint8_t *buf, uint32_t len) {

  SPI_API ret;
  int i;

  for (i = 0; i < len; ++i) {
    addrs[i] = SPI_DATA_REG_ADDR;
  }

#ifdef __MULTIREAD_SUPPORT__
  ret = CAENComm_MultiRead32(handle, addrs, len, datas, errors);
  for (i = 0; i < len; ++i) {
    buf[i] = (uint8_t)datas[i];
  }
#else
  for (i = 0; i < len; i++)
    ret = spi_read(&buf[i]);
#endif

  return ret;
}
