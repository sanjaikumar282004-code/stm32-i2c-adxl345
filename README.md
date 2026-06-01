# STM32 I2C ADXL345

## Hardware

- STM32F401RE Nucleo Board
- ADXL345 Accelerometer Module

## Project Included

### I2C_ADXL345

Interface the ADXL345 accelerometer using I2C communication and read acceleration values from X, Y and Z axes.

The project also verifies communication by reading the ADXL345 Device ID register before configuring the sensor.

## Peripherals Used

- I2C1
- UART2
- GPIO
- ADXL345 Accelerometer

## Concepts Learned

- I2C Register-Level Programming
- Start and Repeated Start Conditions
- Slave Addressing
- ACK/NACK Handling
- Single Byte Read
- Burst Read
- Sensor Configuration
- Accelerometer Data Acquisition

## Flow Diagram

```text
System Start
      │
      ▼
Initialize UART2
      │
      ▼
Initialize I2C1
      │
      ▼
Read ADXL345 Device ID
      │
      ▼
Verify Device ID (0xE5)
      │
      ▼
Configure Data Format Register
      │
      ▼
Enable Measurement Mode
      │
      ▼
Main Loop
      │
      ▼
Read X, Y, Z Registers
      │
      ▼
Combine LSB and MSB
      │
      ▼
Calculate Axis Values
      │
      ▼
Transmit Data via UART
      │
      ▼
Repeat
```

## Output

Output screenshot is available in:

```text
I2C_ADXL345/Output.png
```

Example:

```text
DEVID = 0xE5

X = 59
Y = -44
Z = 101

DEVID = 0xE5

X = 57
Y = -52
Z = 101
```

This confirms successful I2C communication with the ADXL345 and continuous acquisition of acceleration data from all three axes.

## Register Configuration

### Device ID Register

```text
Address : 0x00
Expected Value : 0xE5
```

### Data Format Register

```text
Address : 0x31
Value   : 0x01
Range   : ±4g
```

### Power Control Register

```text
Address : 0x2D
Value   : 0x08
Mode    : Measurement Mode
```
