/*
 * uart.h
 *
 *  Created on: May 9, 2026
 *      Author: sanja
 */

#ifndef UART_H_
#define UART_H_

void uart_init();
void uart_write(int ch);
int __io_putchar(int ch);
int uart_read();
void led_blink();

#endif /* UART_H_ */
