/*
 * i2c.h
 *
 *  Created on: May 30, 2026
 *      Author: sanja
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>

void i2c_config(void);
void i2c_byteread(char saddr, char maddr, char *data);
void i2c_burstread(char saddr, char maddr, int n, char *data);
void i2c_burstwrite(char saddr, char maddr, int n, char *data);






#endif /* I2C_H_ */
