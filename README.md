# STM32 UART Driver

This repository contains a custom UART driver implementation for the STM32F401RE microcontroller. The driver is designed to initialize and use UART communication for transmitting and receiving data, leveraging the STM32 HAL registers for efficient and low-level hardware control.

---

## Features

- **UART Initialization**: Configures UART peripheral settings such as baud rate, data bits, stop bits, and enabling transmission and reception.
- **GPIO Configuration**: Sets the GPIO pins for UART TX and RX functionality.
- **Data Transmission**: Sends single characters or strings via UART.
- **Data Reception**: Reads incoming UART data with handling for overrun errors (ORE).

---

## Requirements

- **Hardware**: STM32F401RE Nucleo Board
- **Software**: STM32CubeIDE (or equivalent development environment)
- **Toolchain**: ARM GCC Compiler

---

## Code Breakdown

### **Driver Functions**

1. **GPIO Initialization**:
    - `init_gpio_TX()`: Configures GPIOA pin 9 as TX (Alternate Function 7).
    - `init_gpio_RX()`: Configures GPIOA pin 10 as RX (Alternate Function 7).

2. **UART Initialization**:
    - `init_uart()`: Configures UART settings like enabling the clock, setting the baud rate, enabling transmitter and receiver, and programming the M-bit.

3. **Data Transmission**:
    - `sendChar(char c)`: Sends a single character over UART.
    - `UART_write(const char *str)`: Sends a string over UART.

4. **Data Reception**:
    - `UART_read()`: Waits for a character to be received and handles overrun errors.

5. **Combined Initialization**:
    - `init_UART()`: Combines UART and GPIO initialization for ease of use.

---

## Example Usage

Below is a simple example of how to use this UART driver:

```c
#include "uart.h"

int main() {
    // Initialize UART and GPIO
    init_UART();

    // Send a welcome message
    UART_write("UART Initialized!\n");

    while (1) {
        // Read a character from UART
        uint16_t received_char = UART_read();

        // Echo the received character back
        sendChar(received_char);
    }

    return 0;
}
```

---

## Register Details

### **GPIO Configuration**
- **PA9 (TX)**:
  - Clock enabled through `RCC_AHB1ENR_GPIOAEN`
  - Alternate Function mode (`GPIO_MODER_MODE9 = 0x2`)
  - Alternate Function 7 (`GPIO_AFRH_AFSEL9 = 7`)

- **PA10 (RX)**:
  - Clock enabled through `RCC_AHB1ENR_GPIOAEN`
  - Alternate Function mode (`GPIO_MODER_MODE10 = 0x2`)
  - Alternate Function 7 (`GPIO_AFRH_AFSEL10 = 7`)

### **UART Configuration**
- **Baud Rate**: 115200 (programmed using `USART_BRR_DIV_Mantissa` and `USART_BRR_DIV_Fraction`)
- **Data Bits**: 8-bit (`USART_CR1_M = 0`)
- **Stop Bits**: 1 stop bit (`USART_CR2_STOP = 0`)
- **Transmitter Enable**: `USART_CR1_TE = 1`
- **Receiver Enable**: `USART_CR1_RE = 1`

---

## Error Handling

- **Overrun Error (ORE)**: Handled in the `UART_read()` function. The ORE flag is cleared if set, ensuring smooth operation without data corruption.

---

## Contribution

Feel free to open issues or submit pull requests if you have improvements or suggestions for the driver.


## Author

Developed by sudoXpg(https://github.com/sudoXpg).

