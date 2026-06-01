/*
 * adxl.h
 *
 *  Created on: May 28, 2026
 *      Author: sanja
 */
#include "stm32f4xx.h"
#include <stdint.h>

#ifndef ADXL_H_
#define ADXL_H_

void adxl_read_address(uint8_t reg);
void adxl_write(uint8_t reg, char value);
void adxl_read(uint8_t reg);
void adxl_init();

#endif /* ADXL_H_ */
