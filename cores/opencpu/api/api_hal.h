/*
  BC66 - API
    Created on: 01.01.2019
    Author: Georgi Angelov

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA   
 */

#ifndef API_HAL_H_
#define API_HAL_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef enum
{
  UTC_E8 = 0x0,
  UTC_0 = 0x1,
  UTC_E1 = 0x2,
  UTC_E2 = 0x3,
  UTC_E3 = 0x4,
  UTC_E4 = 0x5,
  UTC_E5 = 0x6,
  UTC_E6 = 0x7,
  UTC_E7 = 0x8,
  UTC_E9 = 0x9,
  UTC_E10 = 0xA,
  UTC_E11 = 0xB,
  UTC_12 = 0xC,
  UTC_W11 = 0xD,
  UTC_W10 = 0xE,
  UTC_W9 = 0xF,
  UTC_W8 = 0x10,
  UTC_W7 = 0x11,
  UTC_W6 = 0x12,
  UTC_W5 = 0x13,
  UTC_W4 = 0x14,
  UTC_W3 = 0x15,
  UTC_W2 = 0x16,
  UTC_W1 = 0x17,
  UTC_MAX = 0x17,
} rtc_time_zone_t;

typedef struct
{
  uint8_t rtc_sec;
  uint8_t rtc_min;
  uint8_t rtc_hour;
  uint8_t rtc_day;
  uint8_t rtc_mon;
  uint8_t rtc_week;
  uint8_t rtc_year;
  uint16_t rtc_milli_sec;
} hal_rtc_time_t;

typedef enum
{
  HAL_RTC_STATUS_ERROR = 0xFE,
  HAL_RTC_STATUS_INVALID_PARAM = 0xFF,
  HAL_RTC_STATUS_OK = 0x0,
} hal_rtc_status_t;

typedef enum hal_gpt_status_t
{
  HAL_GPT_STATUS_ERROR_PORT_USED = 0xFC,
  HAL_GPT_STATUS_ERROR = 0xFD,
  HAL_GPT_STATUS_ERROR_PORT = 0xFE,
  HAL_GPT_STATUS_INVALID_PARAMETER = 0xFF,
  HAL_GPT_STATUS_OK = 0x0,
} hal_gpt_status_t;

typedef enum hal_wdt_status_t
{
  HAL_WDT_STATUS_INVALID_PARAMETER = 0xFE,
  HAL_WDT_STATUS_INVALID_MAGIC = 0xFF,
  HAL_WDT_STATUS_OK = 0x0,
} hal_wdt_status_t;

typedef enum hal_wdt_mode_t
{
  HAL_WDT_MODE_RESET = 0x0,
  HAL_WDT_MODE_INTERRUPT = 0x1,
} hal_wdt_mode_t;

typedef struct
{
  hal_wdt_mode_t mode;
  uint32_t seconds;
} hal_wdt_config_t;

typedef enum hal_uart_port_t
{
  HAL_UART_0 = 0x0,
  HAL_UART_1 = 0x1,
  HAL_UART_2 = 0x2,
  HAL_UART_3 = 0x3,
  HAL_UART_MAX = 0x4,
} hal_uart_port_t;

typedef enum hal_gpio_pin_t
{
  HAL_GPIO_0 = 0x0,
  HAL_GPIO_1 = 0x1,
  HAL_GPIO_2 = 0x2,
  HAL_GPIO_3 = 0x3,
  HAL_GPIO_4 = 0x4,
  HAL_GPIO_5 = 0x5,
  HAL_GPIO_6 = 0x6,
  HAL_GPIO_7 = 0x7,
  HAL_GPIO_8 = 0x8,
  HAL_GPIO_9 = 0x9,
  HAL_GPIO_10 = 0xA,
  HAL_GPIO_11 = 0xB,
  HAL_GPIO_12 = 0xC,
  HAL_GPIO_13 = 0xD,
  HAL_GPIO_14 = 0xE,
  HAL_GPIO_15 = 0xF,
  HAL_GPIO_16 = 0x10,
  HAL_GPIO_17 = 0x11,
  HAL_GPIO_18 = 0x12,
  HAL_GPIO_19 = 0x13,
  HAL_GPIO_20 = 0x14,
  HAL_GPIO_21 = 0x15,
  HAL_GPIO_22 = 0x16,
  HAL_GPIO_23 = 0x17,
  HAL_GPIO_24 = 0x18,
  HAL_GPIO_25 = 0x19,
  HAL_GPIO_26 = 0x1A,
  HAL_GPIO_27 = 0x1B,
  HAL_GPIO_28 = 0x1C,
  HAL_GPIO_29 = 0x1D,
  HAL_GPIO_30 = 0x1E,
  HAL_GPIO_31 = 0x1F,
  HAL_GPIO_32 = 0x20,
  HAL_GPIO_33 = 0x21,
  HAL_GPIO_34 = 0x22,
  HAL_GPIO_35 = 0x23,
  HAL_GPIO_36 = 0x24,
  HAL_GPIO_MAX = 0x25,
} hal_gpio_pin_t;

typedef enum
{
  HAL_ADC_CHANNEL_0 = 0x0,
  HAL_ADC_CHANNEL_1 = 0x1,
  HAL_ADC_CHANNEL_2 = 0x2,
  HAL_ADC_CHANNEL_3 = 0x3,
  HAL_ADC_CHANNEL_4 = 0x4,
  HAL_ADC_CHANNEL_5 = 0x5,
  HAL_ADC_CHANNEL_6 = 0x6,
  HAL_ADC_CHANNEL_MAX = 0x7,
} hal_adc_channel_t;

typedef enum hal_eint_number_t
{
  HAL_EINT_NUMBER_0 = 0x0,
  HAL_EINT_NUMBER_1 = 0x1,
  HAL_EINT_NUMBER_2 = 0x2,
  HAL_EINT_NUMBER_3 = 0x3,
  HAL_EINT_NUMBER_4 = 0x4,
  HAL_EINT_NUMBER_5 = 0x5,
  HAL_EINT_NUMBER_6 = 0x6,
  HAL_EINT_NUMBER_7 = 0x7,
  HAL_EINT_NUMBER_8 = 0x8,
  HAL_EINT_NUMBER_9 = 0x9,
  HAL_EINT_NUMBER_10 = 0xA,
  HAL_EINT_NUMBER_11 = 0xB,
  HAL_EINT_NUMBER_12 = 0xC,
  HAL_EINT_USB = 0xD,
  HAL_EINT_NUMBER_13 = 0xD,
  HAL_EINT_NUMBER_14 = 0xE,
  HAL_EINT_NUMBER_15 = 0xF,
  HAL_EINT_NUMBER_16 = 0x10,
  HAL_EINT_NUMBER_17 = 0x11,
  HAL_EINT_NUMBER_18 = 0x12,
  HAL_EINT_NUMBER_19 = 0x13,
  HAL_EINT_NUMBER_20 = 0x14,
  HAL_EINT_NUMBER_21 = 0x15,
  HAL_EINT_NUMBER_22 = 0x16,
  HAL_EINT_NUMBER_23 = 0x17,
  HAL_EINT_NUMBER_24 = 0x18,
  HAL_EINT_NUMBER_25 = 0x19,
  HAL_EINT_NUMBER_26 = 0x1A,
  HAL_EINT_NUMBER_27 = 0x1B,
  HAL_EINT_NUMBER_28 = 0x1C,
  HAL_EINT_NUMBER_29 = 0x1D,
  HAL_EINT_NUMBER_30 = 0x1E,
  HAL_EINT_NUMBER_31 = 0x1F,
  HAL_EINT_NUMBER_MAX = 0x20,
} hal_eint_number_t;

typedef enum hal_pwm_channel_t
{
  HAL_PWM_0 = 0x0,
  HAL_PWM_1 = 0x1,
  HAL_PWM_2 = 0x2,
  HAL_PWM_3 = 0x3,
  HAL_PWM_MAX_CHANNEL = 0x4,
} hal_pwm_channel_t;

typedef enum hal_pwm_source_clock_t
{
  HAL_PWM_CLOCK_13MHZ = 0x0,
  HAL_PWM_CLOCK_32KHZ = 0x1,
} hal_pwm_source_clock_t;

typedef enum hal_pwm_status_t
{
  HAL_PWM_STATUS_ERROR = 0xFC,
  HAL_PWM_STATUS_ERROR_CHANNEL = 0xFD,
  HAL_PWM_STATUS_INVALID_PARAMETER = 0xFE,
  HAL_PWM_STATUS_INVALID_FREQUENCY = 0xFF,
  HAL_PWM_STATUS_OK = 0x0,
} hal_pwm_status_t;

typedef enum hal_pwm_advanced_config_t
{
  HAL_PWM_CLOCK_DIVISION_2 = 0x1,
  HAL_PWM_CLOCK_DIVISION_4 = 0x2,
  HAL_PWM_CLOCK_DIVISION_8 = 0x3,
} hal_pwm_advanced_config_t;

typedef enum hal_eint_status_t
{
  HAL_EINT_STATUS_ERROR_EINT_NUMBER = 0xFD,
  HAL_EINT_STATUS_INVALID_PARAMETER = 0xFE,
  HAL_EINT_STATUS_ERROR = 0xFF,
  HAL_EINT_STATUS_OK = 0x0,
} hal_eint_status_t;

typedef void (*hal_eint_callback_t)(void *);

typedef enum hal_gpio_direction_t
{
  HAL_GPIO_DIRECTION_INPUT = 0x0,
  HAL_GPIO_DIRECTION_OUTPUT = 0x1,
} hal_gpio_direction_t;

typedef enum hal_gpio_data_t
{
  HAL_GPIO_DATA_LOW = 0x0,
  HAL_GPIO_DATA_HIGH = 0x1,
} hal_gpio_data_t;

typedef enum hal_gpio_status_t
{
  HAL_GPIO_STATUS_ERROR = 0xFD,
  HAL_GPIO_STATUS_ERROR_PIN = 0xFE,
  HAL_GPIO_STATUS_INVALID_PARAMETER = 0xFF,
  HAL_GPIO_STATUS_OK = 0x0,
} hal_gpio_status_t;

typedef enum hal_pinmux_status_t
{
  HAL_PINMUX_STATUS_ERROR = 0xFD,
  HAL_PINMUX_STATUS_ERROR_PORT = 0xFE,
  HAL_PINMUX_STATUS_INVALID_FUNCTION = 0xFF,
  HAL_PINMUX_STATUS_OK = 0x0,
} hal_pinmux_status_t;

typedef enum hal_adc_status_t
{
  HAL_ADC_STATUS_INVALID_PARAMETER = 0xFC,
  HAL_ADC_STATUS_ERROR_BUSY = 0xFD,
  HAL_ADC_STATUS_ERROR_CHANNEL = 0xFE,
  HAL_ADC_STATUS_ERROR = 0xFF,
  HAL_ADC_STATUS_OK = 0x0,
} hal_adc_status_t;

typedef enum hal_uart_baudrate_t
{
  HAL_UART_BAUDRATE_110 = 0x0,
  HAL_UART_BAUDRATE_300 = 0x1,
  HAL_UART_BAUDRATE_1200 = 0x2,
  HAL_UART_BAUDRATE_2400 = 0x3,
  HAL_UART_BAUDRATE_4800 = 0x4,
  HAL_UART_BAUDRATE_9600 = 0x5,
  HAL_UART_BAUDRATE_19200 = 0x6,
  HAL_UART_BAUDRATE_38400 = 0x7,
  HAL_UART_BAUDRATE_57600 = 0x8,
  HAL_UART_BAUDRATE_115200 = 0x9,
  HAL_UART_BAUDRATE_230400 = 0xA,
  HAL_UART_BAUDRATE_460800 = 0xB,
  HAL_UART_BAUDRATE_921600 = 0xC,
  HAL_UART_BAUDRATE_3000000 = 0xD,
  HAL_UART_BAUDRATE_1500000 = 0xE,
  HAL_UART_BAUDRATE_MAX = 0xF,
} hal_uart_baudrate_t;

typedef enum hal_uart_word_length_t
{
  HAL_UART_WORD_LENGTH_5 = 0x0,
  HAL_UART_WORD_LENGTH_6 = 0x1,
  HAL_UART_WORD_LENGTH_7 = 0x2,
  HAL_UART_WORD_LENGTH_8 = 0x3,
} hal_uart_word_length_t;

typedef enum hal_uart_stop_bit_t
{
  HAL_UART_STOP_BIT_1 = 0x0,
  HAL_UART_STOP_BIT_2 = 0x1,
} hal_uart_stop_bit_t;

typedef enum hal_uart_parity_t
{
  HAL_UART_PARITY_NONE = 0x0,
  HAL_UART_PARITY_ODD = 0x1,
  HAL_UART_PARITY_EVEN = 0x2,
} hal_uart_parity_t;

typedef enum hal_uart_status_t
{
  HAL_UART_STATUS_ERROR_PARAMETER = 0xFC,
  HAL_UART_STATUS_ERROR_BUSY = 0xFD,
  HAL_UART_STATUS_ERROR_UNINITIALIZED = 0xFE,
  HAL_UART_STATUS_ERROR = 0xFF,
  HAL_UART_STATUS_OK = 0x0,
} hal_uart_status_t;

typedef enum hal_uart_callback_event_t
{
  HAL_UART_EVENT_TRANSACTION_ERROR = 0xFF,
  HAL_UART_EVENT_READY_TO_READ = 0x1,
  HAL_UART_EVENT_READY_TO_WRITE = 0x2,
  HAL_UART_EVENT_SAVE_AUTO_BAUD_RATE = 0x3,
} hal_uart_callback_event_t;

typedef struct
{
  hal_uart_baudrate_t baudrate;
  hal_uart_word_length_t word_length;
  hal_uart_stop_bit_t stop_bit;
  hal_uart_parity_t parity;
} hal_uart_config_t;

typedef struct
{
  uint8_t *send_vfifo_buffer;
  uint32_t send_vfifo_buffer_size;
  uint32_t send_vfifo_threshold_size;
  uint8_t *receive_vfifo_buffer;
  uint32_t receive_vfifo_buffer_size;
  uint32_t receive_vfifo_threshold_size;
  uint32_t receive_vfifo_alert_size;
} hal_uart_dma_config_t;

typedef void (*hal_uart_callback_t)(hal_uart_port_t, hal_uart_callback_event_t, void *);

typedef enum
{
  HAL_UART_EVENT_TRANSACTION_ERROR_0 = 0xFF,
  HAL_UART_EVENT_READY_TO_READ_0 = 0x1,
  HAL_UART_EVENT_READY_TO_WRITE_0 = 0x2,
  HAL_UART_EVENT_SAVE_AUTO_BAUD_RATE_0 = 0x3,
} hal_event_uart_e;

typedef enum hal_eint_trigger_mode_t
{
  HAL_EINT_LEVEL_LOW = 0x0,
  HAL_EINT_LEVEL_HIGH = 0x1,
  HAL_EINT_EDGE_FALLING = 0x2,
  HAL_EINT_EDGE_RISING = 0x3,
  HAL_EINT_EDGE_FALLING_AND_RISING = 0x4,
} hal_eint_trigger_mode_t;

typedef struct
{
  hal_eint_trigger_mode_t trigger_mode;
  uint32_t debounce_time;
  uint8_t firq_enable;
} hal_eint_config_t __attribute__((aligned(4)));

typedef void (*eint_hisr_fun)(void *);

typedef enum hal_gpt_port_t
{
  HAL_GPT_0 = 0x0,
  HAL_GPT_1 = 0x1,
  HAL_GPT_2 = 0x2,
  HAL_GPT_3 = 0x3,
  HAL_GPT_4 = 0x4,
  HAL_GPT_5 = 0x5,
  HAL_GPT_MAX_PORT = 0x6,
  HAL_GPT_MAX = 0x6,
} hal_gpt_port_t;

typedef void (*hal_gpt_callback_t)(void *);

typedef enum
{
  HAL_GPT_TIMER_TYPE_ONE_SHOT = 0x0,
  HAL_GPT_TIMER_TYPE_REPEAT = 0x1,
} hal_gpt_timer_type_t;

typedef enum
{
  HAL_GPT_STOPPED = 0x0,
  HAL_GPT_RUNNING = 0x1,
} hal_gpt_running_status_t;

typedef enum
{
  HAL_I2C_MASTER_0 = 0x0,
  HAL_I2C_MASTER_1 = 0x1,
  HAL_I2C_MASTER_2 = 0x2,
  HAL_I2C_MASTER_MAX = 0x3,
} hal_i2c_port_t;

typedef enum
{
  HAL_SPI_MASTER_0 = 0x0,
  HAL_SPI_MASTER_1 = 0x1,
  HAL_SPI_MASTER_MAX = 0x2,
} hal_spi_master_port_t;

typedef enum
{
  HAL_SPI_MASTER_SLAVE_0 = 0x0,
  HAL_SPI_MASTER_SLAVE_MAX = 0x1,
} hal_spi_master_slave_port_t;

typedef enum
{
  HAL_SPI_MASTER_LSB_FIRST = 0x0,
  HAL_SPI_MASTER_MSB_FIRST = 0x1,
} hal_spi_master_bit_order_t;

typedef enum
{
  HAL_SPI_MASTER_CLOCK_POLARITY0 = 0x0,
  HAL_SPI_MASTER_CLOCK_POLARITY1 = 0x1,
} hal_spi_master_clock_polarity_t;

typedef enum
{
  HAL_SPI_MASTER_CLOCK_PHASE0 = 0x0,
  HAL_SPI_MASTER_CLOCK_PHASE1 = 0x1,
} hal_spi_master_clock_phase_t;

typedef enum
{
  HAL_I2C_EVENT_ACK_ERROR = 0xFD,
  HAL_I2C_EVENT_NACK_ERROR = 0xFE,
  HAL_I2C_EVENT_TIMEOUT_ERROR = 0xFF,
  HAL_I2C_EVENT_SUCCESS = 0x0,
} hal_i2c_callback_event_t;

typedef enum
{
  HAL_I2C_STATUS_ERROR = 0xFC,
  HAL_I2C_STATUS_ERROR_BUSY = 0xFD,
  HAL_I2C_STATUS_INVALID_PORT_NUMBER = 0xFE,
  HAL_I2C_STATUS_INVALID_PARAMETER = 0xFF,
  HAL_I2C_STATUS_OK = 0x0,
} hal_i2c_status_t;

typedef enum
{
  HAL_I2C_FREQUENCY_50K = 0x0,
  HAL_I2C_FREQUENCY_100K = 0x1,
  HAL_I2C_FREQUENCY_200K = 0x2,
  HAL_I2C_FREQUENCY_300K = 0x3,
  HAL_I2C_FREQUENCY_400K = 0x4,
  HAL_I2C_FREQUENCY_1M = 0x5,
  HAL_I2C_FREQUENCY_MAX = 0x6,
} hal_i2c_frequency_e;

typedef struct
{
  hal_i2c_frequency_e frequency;
} hal_i2c_config_t;

typedef struct
{
  uint8_t slave_address;
  const uint8_t *send_data;
  uint32_t send_length;
  uint8_t *receive_buffer;
  uint32_t receive_length;
} hal_i2c_send_to_receive_config_t;

typedef void (*hal_i2c_callback_t)(uint8_t, hal_i2c_callback_event_t, void *);

typedef enum
{
  HAL_SPI_MASTER_EVENT_SEND_FINISHED = 0x0,
  HAL_SPI_MASTER_EVENT_RECEIVE_FINISHED = 0x1,
} hal_spi_master_callback_event_t;

typedef enum
{
  HAL_SPI_MASTER_STATUS_ERROR = 0xFC,
  HAL_SPI_MASTER_STATUS_ERROR_BUSY = 0xFD,
  HAL_SPI_MASTER_STATUS_ERROR_PORT = 0xFE,
  HAL_SPI_MASTER_STATUS_INVALID_PARAMETER = 0xFF,
  HAL_SPI_MASTER_STATUS_OK = 0x0,
} hal_spi_master_status_t;

typedef struct
{
  uint32_t clock_frequency;
  hal_spi_master_slave_port_t slave_port;
  hal_spi_master_bit_order_t bit_order;
  hal_spi_master_clock_polarity_t polarity;
  hal_spi_master_clock_phase_t phase;
} hal_spi_master_config_t;

typedef struct
{
  uint8_t *send_data;
  uint32_t send_length;
  uint8_t *receive_buffer;
  uint32_t receive_length;
} hal_spi_master_send_and_receive_config_t;

typedef void (*hal_spi_master_callback_t)(hal_spi_master_callback_event_t, void *);

typedef enum
{
  HAL_SLEEP_LOCK_ALL = 0x0,
  HAL_SLEEP_LOCK_DEEP = 0x1,
  HAL_SLEEP_LOCK_NUMBER = 0x2,
} hal_sleep_lock_t;

typedef enum
{
  HAL_SLEEP_MANAGER_ERROR = 0xFF,
  HAL_SLEEP_MANAGER_OK = 0x0,
} hal_sleep_manager_status_t;

typedef void (*hal_rtc_eint_callback_t)(void *);

typedef enum
{
  HAL_SLEEP_MODE_NONE = 0x0,
  HAL_SLEEP_MODE_IDLE = 0x1,
  HAL_SLEEP_MODE_LIGHT_SLEEP = 0x2,
  HAL_SLEEP_MODE_DEEP_SLEEP = 0x4,
  HAL_SLEEP_MODE_DEEPER_SLEEP = 0x8,
  HAL_SLEEP_MODE_NUMBER = 0x10,
} hal_sleep_mode_t;

typedef enum
{
  HAL_GPT_CLOCK_SOURCE_32K = 0x0,
  HAL_GPT_CLOCK_SOURCE_1M = 0x1,
} hal_gpt_clock_source_t;

typedef enum
{
  HAL_NVIC_STATUS_ERROR_NO_ISR = 0xFC,
  HAL_NVIC_STATUS_ERROR_IRQ_NUMBER = 0xFD,
  HAL_NVIC_STATUS_INVALID_PARAMETER = 0xFE,
  HAL_NVIC_STATUS_ERROR = 0xFF,
  HAL_NVIC_STATUS_OK = 0x0,
} hal_nvic_status_t;

typedef enum
{
  HAL_UART_FLOWCONTROL_NONE = 0x0,
  HAL_UART_FLOWCONTROL_SOFTWARE = 0x1,
  HAL_UART_FLOWCONTROL_HARDWARE = 0x2,
} hal_uart_flowcontrol_t;

typedef struct
{
  uint8_t xon;
  uint8_t xoff;
  uint8_t escape_character;
} hal_uart_sw_flowcontrol_config_t;

typedef enum
{
  HAL_SLEEP_MODE_NONE_0 = 0x0,
  HAL_SLEEP_MODE_IDLE_0 = 0x1,
  HAL_SLEEP_MODE_LIGHT_SLEEP_0 = 0x2,
  HAL_SLEEP_MODE_DEEP_SLEEP_0 = 0x4,
  HAL_SLEEP_MODE_DEEPER_SLEEP_0 = 0x8,
  HAL_SLEEP_MODE_NUMBER_0 = 0x10,
} hal_seep_mode_e;

typedef enum
{
  HAL_CLOCK_CG_DMA = 0x0,
  HAL_CLOCK_CG_I2S1 = 0x1,
  HAL_CLOCK_CG_SPISLV = 0x2,
  HAL_CLOCK_CG_SDIOMST0 = 0x3,
  HAL_CLOCK_CG_SDIOMST1 = 0x4,
  HAL_CLOCK_CG_I2S0 = 0x5,
  HAL_CLOCK_CG_SPIMST0 = 0x6,
  HAL_CLOCK_CG_SPIMST1 = 0x7,
  HAL_CLOCK_CG_UART1 = 0x8,
  HAL_CLOCK_CG_UART2 = 0x9,
  HAL_CLOCK_CG_USIM_26M = 0xA,
  HAL_CLOCK_CG_UART3 = 0xB,
  HAL_CLOCK_CG_PWMSG_BUS = 0xC,
  HAL_CLOCK_CG_PWMSG = 0xD,
  HAL_CLOCK_CG_PWMSG1 = 0xE,
  HAL_CLOCK_CG_PWMSG2 = 0xF,
  HAL_CLOCK_CG_CM_SYSROM = 0x10,
  HAL_CLOCK_CG_SFC = 0x11,
  HAL_CLOCK_CG_TRNG = 0x12,
  HAL_CLOCK_CG_AESOTF = 0x13,
  HAL_CLOCK_CG_UART0 = 0x14,
  HAL_CLOCK_CG_CRYPTO = 0x15,
  HAL_CLOCK_CG_SDIOSLV = 0x16,
  HAL_CLOCK_CG_GPTIMER = 0x17,
  HAL_CLOCK_CG_OSTIMER = 0x18,
  HAL_CLOCK_CG_USB48M = 0x19,
  HAL_CLOCK_CG_USB_BUS = 0x1A,
  HAL_CLOCK_CG_CIPHER = 0x1B,
  HAL_CLOCK_CG_SDIOMST0_BUS = 0x1C,
  HAL_CLOCK_CG_SDIOMST1_BUS = 0x1D,
  HAL_CLOCK_CG_48M = 0x20,
  HAL_CLOCK_CG_SENSOR_DMA = 0x21,
  HAL_CLOCK_CG_PWM0 = 0x24,
  HAL_CLOCK_CG_PWM1 = 0x25,
  HAL_CLOCK_CG_PWM2 = 0x26,
  HAL_CLOCK_CG_PWM3 = 0x27,
  HAL_CLOCK_CG_SENSOR_CTRL_TOP_AO = 0x28,
  HAL_CLOCK_CG_USIM_BCLK = 0x29,
  HAL_CLOCK_CG_I2C0 = 0x2A,
  HAL_CLOCK_CG_I2C1 = 0x2B,
  HAL_CLOCK_CG_I2C2 = 0x2C,
  HAL_CLOCK_CG_SENSOR_uP = 0x2D,
  HAL_CLOCK_CG_SPM = 0x30,
  HAL_CLOCK_CG_EFUSE = 0x32,
  HAL_CLOCK_CG_SEJ = 0x33,
  HAL_CLOCK_CG_AUXADC = 0x35,
  HAL_CLOCK_CG_MD_XO = 0x36,
  HAL_CLOCK_CG_END = 0x37,
} hal_clock_cg_id;

typedef enum
{
  HAL_CLOCK_STATUS_UNINITIALIZED = 0xFD,
  HAL_CLOCK_STATUS_INVALID_PARAMETER = 0xFE,
  HAL_CLOCK_STATUS_ERROR = 0xFF,
  HAL_CLOCK_STATUS_OK = 0x0,
} hal_clock_status_t;

typedef enum
{
  HAL_FLASH_STATUS_ERROR_ERASE_FAIL = 0xF9,
  HAL_FLASH_STATUS_ERROR_PROG_FAIL = 0xFA,
  HAL_FLASH_STATUS_ERROR_NO_INIT = 0xFB,
  HAL_FLASH_STATUS_ERROR_NO_SPACE = 0xFC,
  HAL_FLASH_STATUS_ERROR_WRONG_ADDRESS = 0xFD,
  HAL_FLASH_STATUS_ERROR_LOCKED = 0xFE,
  HAL_FLASH_STATUS_ERROR = 0xFF,
  HAL_FLASH_STATUS_OK = 0x0,
} hal_flash_status_t;

typedef enum
{
  HAL_FLASH_BLOCK_4K = 0x0,
  HAL_FLASH_BLOCK_32K = 0x1,
  HAL_FLASH_BLOCK_64K = 0x2,
} hal_flash_block_t;

typedef enum
{
  HAL_I2C_STATUS_IDLE = 0x0,
  HAL_I2C_STATUS_BUS_BUSY = 0x1,
} hal_i2c_running_type_t;

typedef struct
{
  hal_i2c_running_type_t running_status;
} hal_i2c_running_status_t;

typedef struct
{
  uint8_t slave_address;
  const uint8_t *send_data;
  uint32_t send_packet_length;
  uint32_t send_bytes_in_one_packet;
} hal_i2c_send_config_t;

typedef struct
{
  uint8_t slave_address;
  uint8_t *receive_buffer;
  uint32_t receive_packet_length;
  uint32_t receive_bytes_in_one_packet;
} hal_i2c_receive_config_t;

typedef struct
{
  uint8_t slave_address;
  const uint8_t *send_data;
  uint8_t *receive_buffer;
  uint32_t send_packet_length;
  uint32_t send_bytes_in_one_packet;
  uint32_t receive_packet_length;
  uint32_t receive_bytes_in_one_packet;
} hal_i2c_send_to_receive_config_ex_t;

typedef enum
{
  HAL_I2C_MASTER_0_0 = 0x0,
  HAL_I2C_MASTER_1_0 = 0x1,
  HAL_I2C_MASTER_2_0 = 0x2,
  HAL_I2C_MASTER_MAX_0 = 0x3,
} hal_i2c_e;

typedef enum
{
  HAL_I2C_FREQUENCY_50K_0 = 0x0,
  HAL_I2C_FREQUENCY_100K_0 = 0x1,
  HAL_I2C_FREQUENCY_200K_0 = 0x2,
  HAL_I2C_FREQUENCY_300K_0 = 0x3,
  HAL_I2C_FREQUENCY_400K_0 = 0x4,
  HAL_I2C_FREQUENCY_1M_0 = 0x5,
  HAL_I2C_FREQUENCY_MAX_0 = 0x6,
} hal_i2c_freq;

typedef struct
{
  uint8_t is_sw_control;
  uint8_t is_sw_output_high;
  uint8_t is_eint_output_high;
  uint8_t is_alarm_output_high;
  uint8_t is_tick_output_high;
  uint8_t is_clear_output;
} hal_rtc_gpio_control_t;

typedef struct
{
  uint8_t is_enable_rtc_eint;
  uint8_t is_falling_edge_active;
  uint8_t is_enable_debounce;
} hal_rtc_eint_config_t;

typedef enum
{
  HAL_RTC_SRAM_NORMAL_MODE = 0x0,
  HAL_RTC_SRAM_SLEEP_MODE = 0x1,
  HAL_RTC_SRAM_PD_MODE = 0x2,
} hal_rtc_sram_mode_t;

typedef enum
{
  HAL_RTC_TIME_NOTIFICATION_NONE = 0x0,
  HAL_RTC_TIME_NOTIFICATION_EVERY_SECOND = 0x1,
  HAL_RTC_TIME_NOTIFICATION_EVERY_MINUTE = 0x2,
  HAL_RTC_TIME_NOTIFICATION_EVERY_HOUR = 0x3,
  HAL_RTC_TIME_NOTIFICATION_EVERY_DAY = 0x4,
  HAL_RTC_TIME_NOTIFICATION_EVERY_MONTH = 0x5,
  HAL_RTC_TIME_NOTIFICATION_EVERY_YEAR = 0x6,
  HAL_RTC_TIME_NOTIFICATION_EVERY_SECOND_1_2 = 0x7,
  HAL_RTC_TIME_NOTIFICATION_EVERY_SECOND_1_4 = 0x8,
  HAL_RTC_TIME_NOTIFICATION_EVERY_SECOND_1_8 = 0x9,
  HAL_RTC_TIME_NOTIFICATION_EVERY_SECOND_1_16 = 0xA,
} hal_rtc_time_notification_period_t;

typedef enum
{
  HAL_RTC_GPIO_0 = 0x0,
  HAL_RTC_GPIO_1 = 0x1,
} hal_rtc_gpio_t;

typedef void (*hal_rtc_time_callback_t)(void *);

typedef void (*hal_rtc_alarm_callback_t)(void *);

typedef enum
{
  HAL_WDT_TIMEOUT_RESET = 0x0,
  HAL_WDT_SOFTWARE_RESET = 0x1,
  HAL_WDT_NONE_RESET = 0x2,
} hal_wdt_reset_status_t;

typedef void (*hal_wdt_callback_t)(hal_wdt_reset_status_t);

typedef enum
{
  HAL_WDT_TIMEOUT_RESET_0 = 0x0,
  HAL_WDT_SOFTWARE_RESET_0 = 0x1,
  HAL_WDT_NONE_RESET_0 = 0x2,
} hal_wdt_e;

typedef enum
{
  HAL_WDT_MODE_RESET_0 = 0x0,
  HAL_WDT_MODE_INTERRUPT_0 = 0x1,
} hal_wdt_mode_e;

typedef enum
{
  HAL_PWM_IDLE = 0x0,
  HAL_PWM_BUSY = 0x1,
} hal_pwm_running_status_t;

typedef enum
{
  HAL_TRNG_STATUS_ERROR = 0xFE,
  HAL_TRNG_STATUS_INVALID_PARAMETER = 0xFF,
  HAL_TRNG_STATUS_OK = 0x0,
} hal_trng_status_t;

typedef enum
{
  HAL_SD_PORT_0 = 0x0,
  HAL_SD_PORT_1 = 0x1,
} hal_sd_port_t;

typedef enum
{
  HAL_GPIO_DRIVING_CURRENT_4MA = 0x0,
  HAL_GPIO_DRIVING_CURRENT_8MA = 0x1,
  HAL_GPIO_DRIVING_CURRENT_12MA = 0x2,
  HAL_GPIO_DRIVING_CURRENT_16MA = 0x3,
} hal_gpio_driving_current_t;

typedef enum
{
  HAL_SD_STATUS_BUSY = 0xFE,
  HAL_SD_STATUS_ERROR = 0xFF,
  HAL_SD_STATUS_OK = 0x0,
} hal_sd_status_t;

typedef enum
{
  HAL_SD_EVENT_CARD_INSERTED = 0x0,
  HAL_SD_EVENT_CARD_REMOVED = 0x1,
} hal_sd_card_event_t;

typedef enum
{
  HAL_SD_EVENT_SUCCESS = 0x0,
  HAL_SD_EVENT_TRANSFER_ERROR = 0xFF,
  HAL_SD_EVENT_CRC_ERROR = 0xFE,
  HAL_SD_EVENT_DATA_TIMEOUT = 0xFD,
} hal_sd_callback_event_t;

typedef enum
{
  HAL_SD_BUS_WIDTH_1 = 0x1,
  HAL_SD_BUS_WIDTH_4 = 0x2,
} hal_sd_bus_width_t;

typedef enum
{
  HAL_SD_TYPE_SD_CARD = 0x0,
  HAL_SD_TYPE_MMC_CARD = 0x1,
  HAL_SD_TYPE_SD20_LCS_CARD = 0x2,
  HAL_SD_TYPE_SD20_HCS_CARD = 0x3,
  HAL_SD_TYPE_MMC42_CARD = 0x4,
  HAL_SD_TYPE_CARD_TYPE_MAX = 0x5,
  HAL_SD_TYPE_UNKNOWN_CARD = 0xFF,
} hal_sd_card_type_t;

typedef struct
{
  hal_sd_bus_width_t bus_width;
  uint32_t clock;
} hal_sd_config_t;

typedef void (*hal_sd_card_detect_callback_t)(hal_sd_card_event_t, void *);

typedef void (*hal_sd_callback_t)(hal_sd_callback_event_t, void *);

typedef enum
{
  HAL_GPIO_CLOCK_0 = 0x0,
  HAL_GPIO_CLOCK_1 = 0x1,
  HAL_GPIO_CLOCK_2 = 0x2,
  HAL_GPIO_CLOCK_3 = 0x3,
  HAL_GPIO_CLOCK_4 = 0x4,
  HAL_GPIO_CLOCK_5 = 0x5,
  HAL_GPIO_CLOCK_MAX = 0x6,
} hal_gpio_clock_t;

typedef enum
{
  HAL_GPIO_CLOCK_MODE_32K = 0x0,
  HAL_GPIO_CLOCK_MODE_24M = 0x2,
  HAL_GPIO_CLOCK_MODE_48M = 0x3,
  HAL_GPIO_CLOCK_MODE_40K = 0x5,
  HAL_GPIO_CLOCK_MODE_MAX = 0x6,
} hal_gpio_clock_mode_t;

typedef enum
{
  HAL_AES_STATUS_ERROR = 0xFF,
  HAL_AES_STATUS_OK = 0x0,
} hal_aes_status_t;

typedef enum
{
  HAL_AES_EFUSE_KEY1 = 0x0,
  HAL_AES_EFUSE_KEY2 = 0x1,
} hal_aes_efuse_key_t;

typedef struct
{
  uint8_t *buffer;
  uint32_t length;
} hal_aes_buffer_t;

typedef enum
{
  HAL_SHA_STATUS_ERROR = 0xFF,
  HAL_SHA_STATUS_OK = 0x0,
} hal_sha_status_t;

typedef struct
{
  uint32_t hash_value[16];
  uint32_t message_length;
  uint8_t buffer[128];
  uint8_t *block;
  uint32_t block_length;
  uint8_t LoadInitIV;
} hal_sha_context_t __attribute__((aligned(4)));

typedef enum
{
  HAL_SHA_INTERNAL_SHA1 = 0x0,
  HAL_SHA_INTERNAL_SHA224 = 0x1,
  HAL_SHA_INTERNAL_SHA256 = 0x2,
  HAL_SHA_INTERNAL_SHA384 = 0x3,
  HAL_SHA_INTERNAL_SHA512 = 0x4,
} hal_sha_internal_type_t;

typedef enum
{
  HAL_SPI_MASTER_SINGLE_MODE = 0x0,
  HAL_SPI_MASTER_DUAL_MODE = 0x1,
  HAL_SPI_MASTER_QUAD_MODE = 0x2,
} hal_spi_master_mode_t;

typedef enum
{
  HAL_SPI_MASTER_LITTLE_ENDIAN = 0x0,
  HAL_SPI_MASTER_BIG_ENDIAN = 0x1,
} hal_spi_master_byte_order_t;

typedef enum
{
  HAL_SPI_MASTER_CHIP_SELECT_LOW = 0x0,
  HAL_SPI_MASTER_CHIP_SELECT_HIGH = 0x1,
} hal_spi_master_chip_select_polarity_t;

typedef enum
{
  HAL_SPI_MASTER_NO_GET_TICK_MODE = 0x0,
  HAL_SPI_MASTER_GET_TICK_DELAY1 = 0x1,
  HAL_SPI_MASTER_GET_TICK_DELAY2 = 0x2,
  HAL_SPI_MASTER_GET_TICK_DELAY3 = 0x3,
  HAL_SPI_MASTER_GET_TICK_DELAY4 = 0x4,
  HAL_SPI_MASTER_GET_TICK_DELAY5 = 0x5,
  HAL_SPI_MASTER_GET_TICK_DELAY6 = 0x6,
  HAL_SPI_MASTER_GET_TICK_DELAY7 = 0x7,
} hal_spi_master_get_tick_mode_t;

typedef enum
{
  HAL_SPI_MASTER_SAMPLE_POSITIVE = 0x0,
  HAL_SPI_MASTER_SAMPLE_NEGATIVE = 0x1,
} hal_spi_master_sample_select_t;

typedef enum
{
  HAL_SPI_MASTER_DEASSERT_DISABLE = 0x0,
  HAL_SPI_MASTER_DEASSERT_ENABLE = 0x1,
} hal_spi_master_deassert_t;

typedef enum
{
  HAL_SPI_MASTER_BUSY = 0x0,
  HAL_SPI_MASTER_IDLE = 0x1,
} hal_spi_master_running_status_t;

typedef struct
{
  hal_spi_master_byte_order_t byte_order;
  hal_spi_master_chip_select_polarity_t chip_polarity;
  hal_spi_master_get_tick_mode_t get_tick;
  hal_spi_master_sample_select_t sample_select;
} hal_spi_master_advanced_config_t;

typedef struct
{
  uint32_t chip_select_setup_count;
  uint32_t chip_select_hold_count;
  uint32_t chip_select_idle_count;
} hal_spi_master_chip_select_timing_t;

typedef enum
{
  HAL_SLEEP_MANAGER_WAKEUP_SOURCE_GPT = 0x0,
  HAL_SLEEP_MANAGER_WAKEUP_SOURCE_EINT = 0x1,
  HAL_SLEEP_MANAGER_WAKEUP_SOURCE_SDIO_SLV = 0x2,
  HAL_SLEEP_MANAGER_WAKEUP_SOURCE_SPI_SLAVE_A = 0x3,
  HAL_SLEEP_MANAGER_WAKEUP_SOURCE_WDT = 0x4,
  HAL_SLEEP_MANAGER_WAKEUP_SOURCE_KP = 0x5,
  HAL_SLEEP_MANAGER_WAKEUP_SOURCE_MD = 0x6,
  HAL_SLEEP_MANAGER_WAKEUP_SOURCE_OST = 0x7,
  HAL_SLEEP_MANAGER_WAKEUP_SOURCE_MD_DEBUGSYS = 0x8,
  HAL_SLEEP_MANAGER_WAKEUP_SOURCE_DEBUGSYS = 0x9,
  HAL_SLEEP_MANAGER_WAKEUP_SOURCE_SENSOR_CTRLER = 0xA,
  HAL_SLEEP_MANAGER_WAKEUP_SOURCE_ALL = 0xB,
} hal_sleep_manager_wakeup_source_t;

typedef void (*hal_sleep_manager_callback_t)(void *, uint32_t);

typedef enum
{
  HAL_SLEEP_MANAGER_WAKEUP_SOURCE_GPT_0 = 0x0,
  HAL_SLEEP_MANAGER_WAKEUP_SOURCE_EINT_0 = 0x1,
  HAL_SLEEP_MANAGER_WAKEUP_SOURCE_SDIO_SLV_0 = 0x2,
  HAL_SLEEP_MANAGER_WAKEUP_SOURCE_SPI_SLAVE_A_0 = 0x3,
  HAL_SLEEP_MANAGER_WAKEUP_SOURCE_WDT_0 = 0x4,
  HAL_SLEEP_MANAGER_WAKEUP_SOURCE_KP_0 = 0x5,
  HAL_SLEEP_MANAGER_WAKEUP_SOURCE_MD_0 = 0x6,
  HAL_SLEEP_MANAGER_WAKEUP_SOURCE_OST_0 = 0x7,
  HAL_SLEEP_MANAGER_WAKEUP_SOURCE_MD_DEBUGSYS_0 = 0x8,
  HAL_SLEEP_MANAGER_WAKEUP_SOURCE_DEBUGSYS_0 = 0x9,
  HAL_SLEEP_MANAGER_WAKEUP_SOURCE_SENSOR_CTRLER_0 = 0xA,
  HAL_SLEEP_MANAGER_WAKEUP_SOURCE_ALL_0 = 0xB,
} hal_sleep_manager_e;

/************************************************************************************************/

hal_gpt_status_t hal_gpt_get_free_run_count(hal_gpt_clock_source_t clock_source, uint32_t *count);
hal_gpt_status_t hal_gpt_get_duration_count(uint32_t start_count, uint32_t end_count, uint32_t *duration_count);
hal_gpt_status_t hal_gpt_delay_ms(uint32_t ms);
hal_gpt_status_t hal_gpt_delay_us(uint32_t us);
hal_eint_status_t eint_mask_wakeup_source(hal_eint_number_t eint_number);
hal_eint_status_t eint_unmask_wakeup_source(hal_eint_number_t eint_number);
hal_eint_status_t hal_eint_mask(hal_eint_number_t eint_number);
hal_eint_status_t hal_eint_unmask(hal_eint_number_t eint_number);
hal_clock_status_t hal_clock_enable(hal_clock_cg_id clock_id);
hal_clock_status_t hal_clock_disable(hal_clock_cg_id clock_id);
uint8_t hal_clock_is_enabled(hal_clock_cg_id clock_id);
uint32_t hal_clock_get_freq_meter(uint8_t tcksel, uint8_t fcksel);
uint32_t hal_clock_get_freq_meter_cycle(uint8_t tcksel, uint8_t fcksel, uint16_t winset);
uint8_t hal_time_check_disable_irq_end(uint32_t limter_us);
void adc_data_calibrate(hal_adc_channel_t channel, uint32_t input_data, uint32_t *output_data);
hal_adc_status_t hal_adc_get_data_polling(hal_adc_channel_t channel, uint32_t *data);
hal_flash_status_t get_rawdisk_error_code(int32_t ori_err_code);
hal_flash_status_t hal_flash_erase(uint32_t start_address, hal_flash_block_t block);
hal_flash_status_t hal_flash_read(uint32_t start_address, uint8_t *buffer, uint32_t length);
hal_flash_status_t hal_flash_write(uint32_t address, const uint8_t *data, uint32_t length);
hal_flash_status_t hal_flash_otp_read(uint32_t start_address, uint8_t *buffer, uint32_t length);
hal_flash_status_t hal_flash_otp_write(uint32_t start_address, uint8_t *buffer, uint32_t length);
hal_flash_status_t hal_flash_get_otp_length(uint32_t *length);
uint8_t hal_gpt_is_port_valid(hal_gpt_port_t gpt_port);
hal_gpt_status_t hal_gpt_init(hal_gpt_port_t gpt_port);
hal_gpt_status_t hal_gpt_get_running_status(hal_gpt_port_t gpt_port, hal_gpt_running_status_t *running_status);
hal_gpt_status_t hal_gpt_register_callback(hal_gpt_port_t gpt_port, hal_gpt_callback_t callback, void *user_data);
hal_gpt_status_t hal_gpt_start_timer_ms(hal_gpt_port_t gpt_port, uint32_t timeout_time_ms, hal_gpt_timer_type_t timer_type);
hal_gpt_status_t hal_gpt_stop_timer(hal_gpt_port_t gpt_port);
hal_gpt_status_t hal_gpt_sw_get_timer(uint32_t *handle);
hal_gpt_status_t hal_gpt_sw_free_timer(uint32_t handle);
hal_gpt_status_t hal_gpt_sw_start_timer_ms(uint32_t handle, uint32_t timeout_time_ms, hal_gpt_callback_t callback, void *user_data);
hal_gpt_status_t hal_gpt_sw_stop_timer_ms(uint32_t handle);
hal_uart_status_t hal_uart_init(hal_uart_port_t uart_port, hal_uart_config_t *uart_config);
hal_uart_status_t hal_uart_deinit(hal_uart_port_t uart_port);
void hal_uart_put_char(hal_uart_port_t uart_port, unsigned char byte);
uint32_t hal_uart_send_polling(hal_uart_port_t uart_port, const uint8_t *data, uint32_t size);
uint32_t hal_uart_receive_dma(hal_uart_port_t uart_port, uint8_t *buffer, uint32_t size);
hal_uart_status_t hal_uart_register_callback(hal_uart_port_t uart_port, hal_uart_callback_t user_callback, void *user_data);
uint32_t hal_uart_get_available_send_space(hal_uart_port_t uart_port);
uint32_t hal_uart_get_available_receive_bytes(hal_uart_port_t uart_port);
hal_uart_status_t hal_uart_set_hardware_flowcontrol(hal_uart_port_t uart_port);
hal_uart_status_t hal_uart_set_software_flowcontrol(hal_uart_port_t uart_port, uint8_t xon, uint8_t xoff, uint8_t escape_character);
hal_uart_status_t hal_uart_disable_flowcontrol(hal_uart_port_t uart_port);
hal_uart_status_t hal_uart_set_dma(hal_uart_port_t uart_port, const hal_uart_dma_config_t *dma_config);
hal_uart_status_t hal_uart_set_auto_baudrate(hal_uart_port_t uart_port, uint8_t is_enable);
uint32_t hal_uart_get_auto_baudrate_result(hal_uart_port_t uart_port);
uint32_t hal_uart_send_dma(hal_uart_port_t uart_port, const uint8_t *data, uint32_t size);
hal_uart_status_t hal_uart_set_auto_baudrate_recover(hal_uart_port_t uart_port, uint8_t is_enable);
hal_i2c_status_t hal_i2c_master_init(hal_i2c_port_t i2c_port, hal_i2c_config_t *i2c_config);
hal_i2c_status_t hal_i2c_master_deinit(hal_i2c_port_t i2c_port);
hal_i2c_status_t hal_i2c_master_register_callback(hal_i2c_port_t i2c_port, hal_i2c_callback_t i2c_callback, void *user_data);
hal_i2c_status_t hal_i2c_master_send_dma(hal_i2c_port_t i2c_port, uint8_t slave_address, const uint8_t *data, uint32_t size);
hal_i2c_status_t hal_i2c_master_receive_dma(hal_i2c_port_t i2c_port, uint8_t slave_address, uint8_t *buffer, uint32_t size);
hal_i2c_status_t hal_i2c_master_send_to_receive_dma(hal_i2c_port_t i2c_port, hal_i2c_send_to_receive_config_t *i2c_send_to_receive_config);
void hal_i2c_isr_handler(hal_i2c_port_t i2c_port, hal_i2c_callback_t user_callback, void *user_data);
void hal_i2c_backup_all_register(void *data, uint32_t mode);
void hal_i2c_restore_all_register(void *data, uint32_t mode);
hal_eint_status_t hal_eint_register_callback(hal_eint_number_t eint_number, hal_eint_callback_t eint_callback, void *user_data);
hal_eint_status_t hal_eint_set_trigger_mode(hal_eint_number_t eint_number, hal_eint_trigger_mode_t trigger_mode);
hal_eint_status_t hal_eint_set_debounce_time(hal_eint_number_t eint_number, uint32_t time_ms);
hal_eint_status_t hal_eint_init(hal_eint_number_t eint_number, const hal_eint_config_t *eint_config);
hal_eint_status_t hal_eint_deinit(hal_eint_number_t eint_number);
uint32_t eint_caculate_debounce_time(uint32_t ms);
hal_clock_status_t hal_clock_set_mpll_hopping(int start, int range);
hal_rtc_status_t hal_rtc_get_time(hal_rtc_time_t *time);
hal_rtc_status_t hal_rtc_set_alarm(const hal_rtc_time_t *time);
hal_rtc_status_t hal_rtc_get_alarm(hal_rtc_time_t *time);
hal_rtc_status_t hal_rtc_set_alarm_callback(const hal_rtc_alarm_callback_t callback_function, void *user_data);
hal_rtc_status_t hal_rtc_set_eint_callback(const hal_rtc_eint_callback_t callback_function, void *user_data);
hal_rtc_status_t hal_rtc_get_f32k_frequency(uint32_t *frequency);
hal_rtc_status_t rtc_set_data(uint16_t offset, const unsigned char *buf, uint16_t len, uint8_t access_hw);
hal_rtc_status_t hal_rtc_set_data(uint16_t offset, const unsigned char *buf, uint16_t len);
hal_rtc_status_t rtc_set_time_zone(rtc_time_zone_t time_zone);
hal_rtc_status_t rtc_get_data(uint16_t offset, unsigned char *buf, uint16_t len, uint8_t access_hw);
hal_rtc_status_t hal_rtc_get_data(uint16_t offset, unsigned char *buf, uint16_t len);
hal_rtc_status_t rtc_get_time_zone(rtc_time_zone_t *pTime_zone);
hal_rtc_status_t hal_rtc_retention_sram_config(uint32_t mask, hal_rtc_sram_mode_t mode);
hal_rtc_status_t hal_rtc_configure_gpio(hal_rtc_gpio_t pin, hal_rtc_gpio_control_t *gpio_control);
hal_rtc_status_t hal_rtc_eint_init(hal_rtc_eint_config_t *eint_config);
uint32_t rtc_get_second_diff_from_two_time(hal_rtc_time_t *start_point, hal_rtc_time_t *end_point);
uint32_t rtc_tick_calculation(hal_rtc_time_t *start_point, hal_rtc_time_t *end_point, uint32_t cali_value);
hal_rtc_status_t hal_rtc_get_elapsed_tick(uint8_t is_after_sleep, uint32_t *elapsed_tick);
hal_rtc_status_t rtc_get_elapsed_tick_sram(uint8_t is_after_sleep, uint64_t *elapsed_tick);
void rtc_sw_timer_forward_time(hal_rtc_time_t *time, uint32_t forward_time_ms);
void rtc_eint_callback(void *user_data);
hal_rtc_status_t hal_rtc_set_time(const hal_rtc_time_t *time);
hal_wdt_status_t hal_wdt_init(hal_wdt_config_t *wdt_config);
hal_wdt_callback_t hal_wdt_register_callback(hal_wdt_callback_t wdt_callback);
hal_wdt_status_t hal_wdt_feed(uint32_t magic);
hal_wdt_status_t hal_wdt_enable(uint32_t magic);
hal_wdt_status_t hal_wdt_disable(uint32_t magic);
hal_pwm_status_t hal_pwm_init(hal_pwm_channel_t pwm_channel, hal_pwm_source_clock_t source_clock);
hal_pwm_status_t hal_pwm_deinit(hal_pwm_channel_t pwm_channel);
hal_pwm_status_t hal_pwm_set_frequency(hal_pwm_channel_t pwm_channel, uint32_t frequency, uint32_t *total_count);
hal_pwm_status_t hal_pwm_set_duty_cycle(hal_pwm_channel_t pwm_channel, uint32_t duty_cycle);
hal_pwm_status_t hal_pwm_start(hal_pwm_channel_t pwm_channel);
hal_pwm_status_t hal_pwm_stop(hal_pwm_channel_t pwm_channel);
hal_pwm_status_t hal_pwm_get_frequency(hal_pwm_channel_t pwm_channel, uint32_t *frequency);
hal_pwm_status_t hal_pwm_set_advanced_config(hal_pwm_channel_t pwm_channel, hal_pwm_advanced_config_t advanced_config);
hal_trng_status_t hal_trng_get_generated_random_number(uint32_t *random_number);
hal_sd_status_t hal_sd_set_bus_width(hal_sd_port_t sd_port, hal_sd_bus_width_t bus_width);
hal_sd_status_t hal_sd_init(hal_sd_port_t sd_port, hal_sd_config_t *sd_config);
hal_sd_status_t hal_sd_deinit(hal_sd_port_t sd_port);
hal_sd_status_t hal_sd_read_blocks(hal_sd_port_t sd_port, uint32_t *read_buffer, uint32_t read_address, uint32_t block_number);
hal_sd_status_t hal_sd_write_blocks(hal_sd_port_t sd_port, const uint32_t *write_buffer, uint32_t write_address, uint32_t block_number);
hal_sd_status_t hal_sd_read_blocks_dma_blocking(hal_sd_port_t sd_port, uint32_t *read_buffer, uint32_t read_address, uint32_t block_number);
hal_sd_status_t hal_sd_write_blocks_dma_blocking(hal_sd_port_t sd_port, const uint32_t *write_buffer, uint32_t write_address, uint32_t block_number);
hal_sd_status_t hal_sd_set_clock(hal_sd_port_t sd_port, uint32_t clock);
hal_sd_status_t hal_sd_get_clock(hal_sd_port_t sd_port, uint32_t *clock);
hal_gpio_status_t hal_gpio_init(hal_gpio_pin_t gpio_pin);
hal_gpio_status_t hal_gpio_deinit(hal_gpio_pin_t gpio_pin);
hal_gpio_status_t hal_gpio_set_direction(hal_gpio_pin_t gpio_pin, hal_gpio_direction_t gpio_direction);
hal_gpio_status_t hal_gpio_get_direction(hal_gpio_pin_t gpio_pin, hal_gpio_direction_t *gpio_direction);
hal_pinmux_status_t hal_pinmux_set_function(hal_gpio_pin_t gpio_pin, uint8_t function_index);
hal_gpio_status_t hal_gpio_get_input(hal_gpio_pin_t gpio_pin, hal_gpio_data_t *gpio_data);
hal_gpio_status_t hal_gpio_set_output(hal_gpio_pin_t gpio_pin, hal_gpio_data_t gpio_data);
hal_gpio_status_t hal_gpio_get_output(hal_gpio_pin_t gpio_pin, hal_gpio_data_t *gpio_data);
hal_gpio_status_t hal_gpio_set_pupd_register(hal_gpio_pin_t gpio_pin, uint8_t gpio_pupd, uint8_t gpio_r0, uint8_t gpio_r1);
hal_gpio_status_t hal_gpio_pull_up(hal_gpio_pin_t gpio_pin);
hal_gpio_status_t hal_gpio_pull_down(hal_gpio_pin_t gpio_pin);
hal_gpio_status_t hal_gpio_disable_pull(hal_gpio_pin_t gpio_pin);
hal_gpio_status_t hal_gpio_set_driving_current(hal_gpio_pin_t gpio_pin, hal_gpio_driving_current_t driving);
hal_gpio_status_t hal_gpio_get_driving_current(hal_gpio_pin_t gpio_pin, hal_gpio_driving_current_t *driving);
hal_aes_status_t do_aes_encrypt(uint8_t *encrypt_buffer, uint32_t encrypt_buffer_length, uint8_t *plain_buffer, uint32_t plain_buffer_length, uint8_t *init_vector);
hal_aes_status_t hal_aes_encrypt_with_padding(hal_aes_buffer_t *encrypted_text, hal_aes_buffer_t *plain_text, hal_aes_buffer_t *key, uint8_t *init_vector, uint8_t mode, uint8_t key_source, uint8_t key_slot);
hal_aes_status_t hal_aes_decrypt(hal_aes_buffer_t *plain_text, hal_aes_buffer_t *encrypted_text, hal_aes_buffer_t *key, uint8_t *init_vector, uint8_t mode, uint8_t key_source, uint8_t key_slot);
hal_aes_status_t hal_aes_cbc_encrypt(hal_aes_buffer_t *encrypted_text, hal_aes_buffer_t *plain_text, hal_aes_buffer_t *key, uint8_t *init_vector);
hal_aes_status_t hal_aes_cbc_decrypt(hal_aes_buffer_t *plain_text, hal_aes_buffer_t *encrypted_text, hal_aes_buffer_t *key, uint8_t *init_vector);
hal_aes_status_t hal_aes_ecb_encrypt(hal_aes_buffer_t *encrypted_text, hal_aes_buffer_t *plain_text, hal_aes_buffer_t *key);
hal_aes_status_t hal_aes_ecb_decrypt(hal_aes_buffer_t *plain_text, hal_aes_buffer_t *encrypted_text, hal_aes_buffer_t *key);
hal_sha_status_t hal_sha256_init(hal_sha_context_t *context);
hal_sha_status_t hal_sha256_append(hal_sha_context_t *context, uint8_t *message, uint32_t length);
hal_sha_status_t hal_sha256_end(hal_sha_context_t *context, uint8_t *digest_message);
hal_spi_master_status_t hal_spi_master_init(hal_spi_master_port_t master_port, hal_spi_master_config_t *spi_config);
hal_spi_master_status_t hal_spi_master_deinit(hal_spi_master_port_t master_port);
hal_spi_master_status_t hal_spi_master_register_callback(hal_spi_master_port_t master_port, hal_spi_master_callback_t callback, void *user_data);
hal_spi_master_status_t hal_spi_master_send_dma(hal_spi_master_port_t master_port, uint8_t *data, uint32_t size);
hal_spi_master_status_t hal_spi_master_send_and_receive_dma(hal_spi_master_port_t master_port, hal_spi_master_send_and_receive_config_t *spi_send_and_receive_config);
uint8_t hal_sleep_manager_set_sleep_handle(const unsigned char *handle_name);
hal_sleep_manager_status_t hal_sleep_manager_acquire_sleeplock(uint8_t handle_index, hal_sleep_lock_t level);
hal_sleep_manager_status_t hal_sleep_manager_release_sleeplock(uint8_t handle_index, hal_sleep_lock_t level);
hal_sleep_manager_status_t hal_sleep_manager_release_sleep_handle(uint8_t handle_index);
uint8_t hal_sleep_manager_get_sleep_lock_status(hal_sleep_lock_t level, uint32_t *info_high, uint32_t *info_low);
uint8_t hal_sleep_manager_is_sleep_lock_locked(hal_sleep_lock_t level);
uint8_t hal_sleep_manager_is_sleep_handle_alive(uint8_t handle_index);
hal_sleep_manager_status_t hal_sleep_manager_set_sleep_time(uint32_t sleep_time_ms);
void hal_sleep_manager_enter_sleep_mode(hal_sleep_mode_t mode);
void hal_sleep_manager_register_suspend_callback(hal_sleep_manager_callback_t callback, void *data, uint32_t mode);
bool hal_efuse_read_uid(uint8_t *uid, uint32_t len);
bool hal_efuse_is_uid_matched(uint8_t *uid, uint32_t len);
bool hal_efuse_is_pubkey_hash_matched(uint8_t *pubkey_hash, uint32_t len);

void hal_rtc_enter_forced_shut_down_mode(int, int);

#endif /* API_HAL_H_ */
