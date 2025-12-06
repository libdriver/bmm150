/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_bmm150.h
 * @brief     driver bmm150 header file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2025-12-23
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2025/12/23  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_BMM150_H
#define DRIVER_BMM150_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup bmm150_driver bmm150 driver function
 * @brief    bmm150 driver modules
 * @{
 */

/**
 * @addtogroup bmm150_basic_driver
 * @{
 */

/**
 * @brief bmm150 interface enumeration definition
 */
typedef enum
{
    BMM150_INTERFACE_IIC = 0x00,        /**< iic interface function */
    BMM150_INTERFACE_SPI = 0x01,        /**< spi interface function */
} bmm150_interface_t;

/**
 * @brief bmm150 address enumeration definition
 */
typedef enum
{
    BMM150_ADDRESS_CSB_SDO_00 = (0x10 << 1),        /**< csb = gnd, sdo = gnd */
    BMM150_ADDRESS_CSB_SDO_01 = (0x11 << 1),        /**< csb = gnd, sdo = vcc */
    BMM150_ADDRESS_CSB_SDO_10 = (0x12 << 1),        /**< csb = vcc, sdo = gnd */
    BMM150_ADDRESS_CSB_SDO_11 = (0x13 << 1),        /**< csb = vcc, sdo = vcc */
} bmm150_address_t;

/**
 * @brief bmm150 bool enumeration definition
 */
typedef enum
{
    BMM150_BOOL_FALSE = 0x00,        /**< false */
    BMM150_BOOL_TRUE  = 0x01,        /**< true */
} bmm150_bool_t;

/**
 * @brief bmm150 interrupt status enumeration definition
 */
typedef enum
{
    BMM150_INTERRUPT_STATUS_DATA_OVERRUN     = 7,        /**< data overrun */
    BMM150_INTERRUPT_STATUS_OVERFLOW         = 6,        /**< overflow */
    BMM150_INTERRUPT_STATUS_HIGH_THRESHOLD_Z = 5,        /**< high threshold z */
    BMM150_INTERRUPT_STATUS_HIGH_THRESHOLD_Y = 4,        /**< high threshold y */
    BMM150_INTERRUPT_STATUS_HIGH_THRESHOLD_X = 3,        /**< high threshold x */
    BMM150_INTERRUPT_STATUS_LOW_THRESHOLD_Z  = 2,        /**< low threshold z */
    BMM150_INTERRUPT_STATUS_LOW_THRESHOLD_Y  = 1,        /**< low threshold y */
    BMM150_INTERRUPT_STATUS_LOW_THRESHOLD_X  = 0,        /**< low threshold x */
} bmm150_interrupt_status_t;

/**
 * @brief bmm150 spi wire enumeration definition
 */
typedef enum
{
    BMM150_SPI_WIRE_4 = 0x00,        /**< 4 wire */
    BMM150_SPI_WIRE_3 = 0x01,        /**< 3 wire */
} bmm150_spi_wire_t;

/**
 * @brief bmm150 advanced self test enumeration definition
 */
typedef enum
{
    BMM150_ADVANCED_SELF_TEST_NORMAL   = 0x00,        /**< normal mode */
    BMM150_ADVANCED_SELF_TEST_NEGATIVE = 0x02,        /**< negative mode */
    BMM150_ADVANCED_SELF_TEST_POSITIVE = 0x03,        /**< positive mode */
} bmm150_advanced_self_test_t;

/**
 * @brief bmm150 data rate enumeration definition
 */
typedef enum
{
    BMM150_DATA_RATE_10HZ = 0x00,        /**< 10hz */
    BMM150_DATA_RATE_2HZ  = 0x01,        /**< 2hz */
    BMM150_DATA_RATE_6HZ  = 0x02,        /**< 6hz */
    BMM150_DATA_RATE_8HZ  = 0x03,        /**< 8hz */
    BMM150_DATA_RATE_15HZ = 0x04,        /**< 15hz */
    BMM150_DATA_RATE_20HZ = 0x05,        /**< 20hz */
    BMM150_DATA_RATE_25HZ = 0x06,        /**< 25hz */
    BMM150_DATA_RATE_30HZ = 0x07,        /**< 30hz */
} bmm150_data_rate_t;

/**
 * @brief bmm150 mode enumeration definition
 */
typedef enum
{
    BMM150_MODE_NORMAL = 0x00,        /**< normal mode */
    BMM150_MODE_FORCED = 0x01,        /**< forced mode */
    BMM150_MODE_SLEEP  = 0x03,        /**< sleep mode */
} bmm150_mode_t;

/**
 * @brief bmm150 data ready pin polarity enumeration definition
 */
typedef enum
{
    BMM150_DATA_READY_PIN_POLARITY_LOW  = 0x00,        /**< active low */
    BMM150_DATA_READY_PIN_POLARITY_HIGH = 0x01,        /**< active high */
} bmm150_data_ready_pin_polarity_t;

/**
 * @brief bmm150 interrupt pin polarity enumeration definition
 */
typedef enum
{
    BMM150_INTERRUPT_PIN_POLARITY_LOW  = 0x00,        /**< active low */
    BMM150_INTERRUPT_PIN_POLARITY_HIGH = 0x01,        /**< active high */
} bmm150_interrupt_pin_polarity_t;

/**
 * @brief bmm150 handle structure definition
 */
typedef struct bmm150_handle_s
{
    uint8_t iic_addr;                                                                   /**< iic address */
    uint8_t (*iic_init)(void);                                                          /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                                        /**< point to an iic_deinit function address */
    uint8_t (*iic_read)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);         /**< point to an iic_read function address */
    uint8_t (*iic_write)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);        /**< point to an iic_write function address */
    uint8_t (*spi_init)(void);                                                          /**< point to a spi_init function address */
    uint8_t (*spi_deinit)(void);                                                        /**< point to a spi_deinit function address */
    uint8_t (*spi_read)(uint8_t reg, uint8_t *buf, uint16_t len);                       /**< point to a spi_read function address */
    uint8_t (*spi_write)(uint8_t reg, uint8_t *buf, uint16_t len);                      /**< point to a spi_write function address */
    void (*receive_callback)(uint8_t type);                                             /**< point to a receive_callback function address */
    void (*delay_ms)(uint32_t ms);                                                      /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                                    /**< point to a debug_print function address */
    uint8_t inited;                                                                     /**< inited flag */
    uint8_t iic_spi;                                                                    /**< iic spi interface type */
    int8_t dig_x1;                                                                      /**< trim x1 data */
    int8_t dig_y1;                                                                      /**< trim y1 data */
    int8_t dig_x2;                                                                      /**< trim x2 data */
    int8_t dig_y2;                                                                      /**< trim y2 data */
    uint16_t dig_z1;                                                                    /**< trim z1 data */
    int16_t dig_z2;                                                                     /**< trim z2 data */
    int16_t dig_z3;                                                                     /**< trim z3 data */
    int16_t dig_z4;                                                                     /**< trim z4 data */
    uint8_t dig_xy1;                                                                    /**< trim xy1 data */
    int8_t dig_xy2;                                                                     /**< trim xy2 data */
    uint16_t dig_xyz1;                                                                  /**< trim xyz1 data */
} bmm150_handle_t;

/**
 * @brief bmm150 information structure definition
 */
typedef struct bmm150_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} bmm150_info_t;

/**
 * @}
 */

/**
 * @defgroup bmm150_link_driver bmm150 link driver function
 * @brief    bmm150 link driver modules
 * @ingroup  bmm150_driver
 * @{
 */

/**
 * @brief     initialize bmm150_handle_t structure
 * @param[in] HANDLE pointer to a bmm150 handle structure
 * @param[in] STRUCTURE bmm150_handle_t
 * @note      none
 */
#define DRIVER_BMM150_LINK_INIT(HANDLE, STRUCTURE)         memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE pointer to a bmm150 handle structure
 * @param[in] FUC pointer to an iic_init function address
 * @note      none
 */
#define DRIVER_BMM150_LINK_IIC_INIT(HANDLE, FUC)          (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE pointer to a bmm150 handle structure
 * @param[in] FUC pointer to an iic_deinit function address
 * @note      none
 */
#define DRIVER_BMM150_LINK_IIC_DEINIT(HANDLE, FUC)        (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_read function
 * @param[in] HANDLE pointer to a bmm150 handle structure
 * @param[in] FUC pointer to an iic_read function address
 * @note      none
 */
#define DRIVER_BMM150_LINK_IIC_READ(HANDLE, FUC)          (HANDLE)->iic_read = FUC

/**
 * @brief     link iic_write function
 * @param[in] HANDLE pointer to a bmm150 handle structure
 * @param[in] FUC pointer to an iic_write function address
 * @note      none
 */
#define DRIVER_BMM150_LINK_IIC_WRITE(HANDLE, FUC)         (HANDLE)->iic_write = FUC

/**
 * @brief     link spi_init function
 * @param[in] HANDLE pointer to a bmm150 handle structure
 * @param[in] FUC pointer to a spi_init function address
 * @note      none
 */
#define DRIVER_BMM150_LINK_SPI_INIT(HANDLE, FUC)          (HANDLE)->spi_init = FUC

/**
 * @brief     link spi_deinit function
 * @param[in] HANDLE pointer to a bmm150 handle structure
 * @param[in] FUC pointer to a spi_deinit function address
 * @note      none
 */
#define DRIVER_BMM150_LINK_SPI_DEINIT(HANDLE, FUC)        (HANDLE)->spi_deinit = FUC

/**
 * @brief     link spi_read function
 * @param[in] HANDLE pointer to a bmm150 handle structure
 * @param[in] FUC pointer to a spi_read function address
 * @note      none
 */
#define DRIVER_BMM150_LINK_SPI_READ(HANDLE, FUC)          (HANDLE)->spi_read = FUC

/**
 * @brief     link spi_write function
 * @param[in] HANDLE pointer to a bmm150 handle structure
 * @param[in] FUC pointer to a spi_write function address
 * @note      none
 */
#define DRIVER_BMM150_LINK_SPI_WRITE(HANDLE, FUC)         (HANDLE)->spi_write = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE pointer to a bmm150 handle structure
 * @param[in] FUC pointer to a delay_ms function address
 * @note      none
 */
#define DRIVER_BMM150_LINK_DELAY_MS(HANDLE, FUC)          (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE pointer to a bmm150 handle structure
 * @param[in] FUC pointer to a debug_print function address
 * @note      none
 */
#define DRIVER_BMM150_LINK_DEBUG_PRINT(HANDLE, FUC)       (HANDLE)->debug_print = FUC

/**
 * @brief     link receive_callback function
 * @param[in] HANDLE pointer to a bmm150 handle structure
 * @param[in] FUC pointer to a receive_callback function address
 * @note      none
 */
#define DRIVER_BMM150_LINK_RECEIVE_CALLBACK(HANDLE, FUC)  (HANDLE)->receive_callback = FUC

/**
 * @}
 */

/**
 * @defgroup bmm150_basic_driver bmm150 basic driver function
 * @brief    bmm150 basic driver modules
 * @ingroup  bmm150_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info pointer to a bmm150 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t bmm150_info(bmm150_info_t *info);

/**
 * @brief     set the chip interface
 * @param[in] *handle pointer to a bmm150 handle structure
 * @param[in] interface chip interface
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t bmm150_set_interface(bmm150_handle_t *handle, bmm150_interface_t interface);

/**
 * @brief      get the chip interface
 * @param[in]  *handle pointer to a bmm150 handle structure
 * @param[out] *interface pointer to a chip interface buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t bmm150_get_interface(bmm150_handle_t *handle, bmm150_interface_t *interface);

/**
 * @brief     set the iic address pin
 * @param[in] *handle pointer to a bmm150 handle structure
 * @param[in] addr_pin address pin
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t bmm150_set_addr_pin(bmm150_handle_t *handle, bmm150_address_t addr_pin);

/**
 * @brief      get the iic address pin
 * @param[in]  *handle pointer to a bmm150 handle structure
 * @param[out] *addr_pin pointer to an address pin buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t bmm150_get_addr_pin(bmm150_handle_t *handle, bmm150_address_t *addr_pin);

/**
 * @brief     irq handler
 * @param[in] *handle pointer to a bmm150 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bmm150_irq_handler(bmm150_handle_t *handle);

/**
 * @brief     initialize the chip
 * @param[in] *handle pointer to a bmm150 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 spi or iic initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 *            - 4 soft reset failed
 *            - 5 power on failed
 *            - 6 id is invalid
 *            - 7 load trim failed
 * @note      none
 */
uint8_t bmm150_init(bmm150_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle pointer to a bmm150 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bmm150_deinit(bmm150_handle_t *handle);

/**
 * @brief      read data
 * @param[in]  *handle pointer to a bmm150 handle structure
 * @param[out] *raw pointer to a raw data buffer
 * @param[out] *ut pointer to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 read timeout
 * @note      none
 */
uint8_t bmm150_read(bmm150_handle_t *handle, int16_t raw[3], float ut[3]);

/**
 * @brief      get self test x result
 * @param[in]  *handle pointer to a bmm150 handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get self test x failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bmm150_get_self_test_x(bmm150_handle_t *handle, bmm150_bool_t *enable);

/**
 * @brief      get self test y result
 * @param[in]  *handle pointer to a bmm150 handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get self test y failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bmm150_get_self_test_y(bmm150_handle_t *handle, bmm150_bool_t *enable);

/**
 * @brief      get self test z result
 * @param[in]  *handle pointer to a bmm150 handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get self test z failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bmm150_get_self_test_z(bmm150_handle_t *handle, bmm150_bool_t *enable);

/**
 * @brief      get data ready status
 * @param[in]  *handle pointer to a bmm150 handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get data ready status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bmm150_get_data_ready_status(bmm150_handle_t *handle, bmm150_bool_t *enable);

/**
 * @brief      get interrupt status
 * @param[in]  *handle pointer to a bmm150 handle structure
 * @param[in]  status interrupt status
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get interrupt status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bmm150_get_interrupt_status(bmm150_handle_t *handle, bmm150_interrupt_status_t status, bmm150_bool_t *enable);

/**
 * @brief     soft reset
 * @param[in] *handle pointer to a bmm150 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 soft reset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bmm150_soft_reset(bmm150_handle_t *handle);

/**
 * @brief     set power on
 * @param[in] *handle pointer to a bmm150 handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set power on failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bmm150_set_power_on(bmm150_handle_t *handle, bmm150_bool_t enable);

/**
 * @brief      get power on
 * @param[in]  *handle pointer to a bmm150 handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get power on failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bmm150_get_power_on(bmm150_handle_t *handle, bmm150_bool_t *enable);

/**
 * @brief     set spi wire
 * @param[in] *handle pointer to a bmm150 handle structure
 * @param[in] wire spi wire
 * @return    status code
 *            - 0 success
 *            - 1 set spi wire failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bmm150_set_spi_wire(bmm150_handle_t *handle, bmm150_spi_wire_t wire);

/**
 * @brief      get spi wire
 * @param[in]  *handle pointer to a bmm150 handle structure
 * @param[out] *wire pointer to a spi wire buffer
 * @return     status code
 *             - 0 success
 *             - 1 get spi wire failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bmm150_get_spi_wire(bmm150_handle_t *handle, bmm150_spi_wire_t *wire);

/**
 * @brief     set advanced self test
 * @param[in] *handle pointer to a bmm150 handle structure
 * @param[in] test advanced self test mode
 * @return    status code
 *            - 0 success
 *            - 1 set advanced self test failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bmm150_set_advanced_self_test(bmm150_handle_t *handle, bmm150_advanced_self_test_t test);

/**
 * @brief      get advanced self test
 * @param[in]  *handle pointer to a bmm150 handle structure
 * @param[out] *test pointer to an advanced self test mode buffer
 * @return     status code
 *             - 0 success
 *             - 1 get advanced self test failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bmm150_get_advanced_self_test(bmm150_handle_t *handle, bmm150_advanced_self_test_t *test);

/**
 * @brief     set data rate
 * @param[in] *handle pointer to a bmm150 handle structure
 * @param[in] rate data rate
 * @return    status code
 *            - 0 success
 *            - 1 set data rate failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bmm150_set_data_rate(bmm150_handle_t *handle, bmm150_data_rate_t rate);

/**
 * @brief      get data rate
 * @param[in]  *handle pointer to a bmm150 handle structure
 * @param[out] *rate pointer to a data rate buffer
 * @return     status code
 *             - 0 success
 *             - 1 get data rate failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bmm150_get_data_rate(bmm150_handle_t *handle, bmm150_data_rate_t *rate);

/**
 * @brief     set mode
 * @param[in] *handle pointer to a bmm150 handle structure
 * @param[in] mode chip mode
 * @return    status code
 *            - 0 success
 *            - 1 set mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bmm150_set_mode(bmm150_handle_t *handle, bmm150_mode_t mode);

/**
 * @brief      get mode
 * @param[in]  *handle pointer to a bmm150 handle structure
 * @param[out] *mode pointer to a chip mode buffer
 * @return     status code
 *             - 0 success
 *             - 1 get mode failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bmm150_get_mode(bmm150_handle_t *handle, bmm150_mode_t *mode);

/**
 * @brief     enable or disable self test
 * @param[in] *handle pointer to a bmm150 handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set self test failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bmm150_set_self_test(bmm150_handle_t *handle, bmm150_bool_t enable);

/**
 * @brief      get self test status
 * @param[in]  *handle pointer to a bmm150 handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get self test failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bmm150_get_self_test(bmm150_handle_t *handle, bmm150_bool_t *enable);

/**
 * @brief     enable or disable interrupt
 * @param[in] *handle pointer to a bmm150 handle structure
 * @param[in] status interrupt index
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set interrupt failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bmm150_set_interrupt(bmm150_handle_t *handle, bmm150_interrupt_status_t status, bmm150_bool_t enable);

/**
 * @brief      get interrupt status
 * @param[in]  *handle pointer to a bmm150 handle structure
 * @param[in]  status interrupt index
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get interrupt failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bmm150_get_interrupt(bmm150_handle_t *handle, bmm150_interrupt_status_t status, bmm150_bool_t *enable);

/**
 * @brief     enable or disable data ready pin
 * @param[in] *handle pointer to a bmm150 handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set data ready pin failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bmm150_set_data_ready_pin(bmm150_handle_t *handle, bmm150_bool_t enable);

/**
 * @brief      get data ready pin status
 * @param[in]  *handle pointer to a bmm150 handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get data ready pin failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bmm150_get_data_ready_pin(bmm150_handle_t *handle, bmm150_bool_t *enable);

/**
 * @brief     enable or disable interrupt pin
 * @param[in] *handle pointer to a bmm150 handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set interrupt pin failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bmm150_set_interrupt_pin(bmm150_handle_t *handle, bmm150_bool_t enable);

/**
 * @brief      get interrupt pin status
 * @param[in]  *handle pointer to a bmm150 handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get interrupt pin failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bmm150_get_interrupt_pin(bmm150_handle_t *handle, bmm150_bool_t *enable);

/**
 * @brief     enable or disable channel z
 * @param[in] *handle pointer to a bmm150 handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set channel z failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bmm150_set_channel_z(bmm150_handle_t *handle, bmm150_bool_t enable);

/**
 * @brief      get channel z status
 * @param[in]  *handle pointer to a bmm150 handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get channel z failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bmm150_get_channel_z(bmm150_handle_t *handle, bmm150_bool_t *enable);

/**
 * @brief     enable or disable channel y
 * @param[in] *handle pointer to a bmm150 handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set channel y failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bmm150_set_channel_y(bmm150_handle_t *handle, bmm150_bool_t enable);

/**
 * @brief      get channel y status
 * @param[in]  *handle pointer to a bmm150 handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get channel y failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bmm150_get_channel_y(bmm150_handle_t *handle, bmm150_bool_t *enable);

/**
 * @brief     enable or disable channel x
 * @param[in] *handle pointer to a bmm150 handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set channel x failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bmm150_set_channel_x(bmm150_handle_t *handle, bmm150_bool_t enable);

/**
 * @brief      get channel x status
 * @param[in]  *handle pointer to a bmm150 handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get channel x failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bmm150_get_channel_x(bmm150_handle_t *handle, bmm150_bool_t *enable);

/**
 * @brief     set data ready pin polarity
 * @param[in] *handle pointer to a bmm150 handle structure
 * @param[in] polarity data ready pin polarity
 * @return    status code
 *            - 0 success
 *            - 1 set data ready pin polarity failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bmm150_set_data_ready_pin_polarity(bmm150_handle_t *handle, bmm150_data_ready_pin_polarity_t polarity);

/**
 * @brief      get data ready pin polarity
 * @param[in]  *handle pointer to a bmm150 handle structure
 * @param[out] *polarity pointer to a data ready pin polarity buffer
 * @return     status code
 *             - 0 success
 *             - 1 get data ready pin polarity failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bmm150_get_data_ready_pin_polarity(bmm150_handle_t *handle, bmm150_data_ready_pin_polarity_t *polarity);

/**
 * @brief     enable or disable interrupt latch
 * @param[in] *handle pointer to a bmm150 handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set interrupt latch failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bmm150_set_interrupt_latch(bmm150_handle_t *handle, bmm150_bool_t enable);

/**
 * @brief      get interrupt latch status
 * @param[in]  *handle pointer to a bmm150 handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get interrupt latch failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bmm150_get_interrupt_latch(bmm150_handle_t *handle, bmm150_bool_t *enable);

/**
 * @brief     set interrupt pin polarity
 * @param[in] *handle pointer to a bmm150 handle structure
 * @param[in] polarity interrupt pin polarity
 * @return    status code
 *            - 0 success
 *            - 1 set interrupt pin polarity failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bmm150_set_interrupt_pin_polarity(bmm150_handle_t *handle, bmm150_interrupt_pin_polarity_t polarity);

/**
 * @brief      get interrupt pin polarity
 * @param[in]  *handle pointer to a bmm150 handle structure
 * @param[out] *polarity pointer to an interrupt pin polarity buffer
 * @return     status code
 *             - 0 success
 *             - 1 get interrupt pin polarity failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bmm150_get_interrupt_pin_polarity(bmm150_handle_t *handle, bmm150_interrupt_pin_polarity_t *polarity);

/**
 * @brief     set low threshold
 * @param[in] *handle pointer to a bmm150 handle structure
 * @param[in] threshold low threshold
 * @return    status code
 *            - 0 success
 *            - 1 set low threshold failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bmm150_set_low_threshold(bmm150_handle_t *handle, int8_t threshold);

/**
 * @brief      get low threshold
 * @param[in]  *handle pointer to a bmm150 handle structure
 * @param[out] *threshold pointer to a low threshold buffer
 * @return     status code
 *             - 0 success
 *             - 1 get low threshold failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bmm150_get_low_threshold(bmm150_handle_t *handle, int8_t *threshold);

/**
 * @brief     set high threshold
 * @param[in] *handle pointer to a bmm150 handle structure
 * @param[in] threshold high threshold
 * @return    status code
 *            - 0 success
 *            - 1 set high threshold failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bmm150_set_high_threshold(bmm150_handle_t *handle, int8_t threshold);

/**
 * @brief      get high threshold
 * @param[in]  *handle pointer to a bmm150 handle structure
 * @param[out] *threshold pointer to a high threshold buffer
 * @return     status code
 *             - 0 success
 *             - 1 get high threshold failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bmm150_get_high_threshold(bmm150_handle_t *handle, int8_t *threshold);

/**
 * @brief     set repxy number
 * @param[in] *handle pointer to a bmm150 handle structure
 * @param[in] number repxy number
 * @return    status code
 *            - 0 success
 *            - 1 set repxy number failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      preset                     repxy    repz    odr(hz)
 *            low power preset           3        3       10
 *            regular preset             9        15      10
 *            enhanced regular preset    15       27      10
 *            high accuracy preset       47       83      10
 */
uint8_t bmm150_set_repxy_number(bmm150_handle_t *handle, uint8_t number);

/**
 * @brief      get repxy number
 * @param[in]  *handle pointer to a bmm150 handle structure
 * @param[out] *number pointer to a repxy number buffer
 * @return     status code
 *             - 0 success
 *             - 1 get repxy number failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note      none
 */
uint8_t bmm150_get_repxy_number(bmm150_handle_t *handle, uint8_t *number);

/**
 * @brief     set repz number
 * @param[in] *handle pointer to a bmm150 handle structure
 * @param[in] number repz number
 * @return    status code
 *            - 0 success
 *            - 1 set repz number failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      preset                     repxy    repz    odr(hz)
 *            low power preset           3        3       10
 *            regular preset             9        15      10
 *            enhanced regular preset    15       27      10
 *            high accuracy preset       47       83      10
 */
uint8_t bmm150_set_repz_number(bmm150_handle_t *handle, uint8_t number);

/**
 * @brief      get repz number
 * @param[in]  *handle pointer to a bmm150 handle structure
 * @param[out] *number pointer to a repz number buffer
 * @return     status code
 *             - 0 success
 *             - 1 get repz number failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note      none
 */
uint8_t bmm150_get_repz_number(bmm150_handle_t *handle, uint8_t *number);

/**
 * @brief      convert the interrupt threshold to the register raw data
 * @param[in]  *handle pointer to a bmm150 handle structure
 * @param[in]  ut interrupt threshold in ut
 * @param[out] *reg pointer to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bmm150_interrupt_threshold_convert_to_register(bmm150_handle_t *handle, float ut, int8_t *reg);

/**
 * @brief      convert the register raw data to the interrupt threshold
 * @param[in]  *handle pointer to a bmm150 handle structure
 * @param[in]  reg register raw data
 * @param[out] *ut pointer to an interrupt threshold buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bmm150_interrupt_threshold_convert_to_data(bmm150_handle_t *handle, int8_t reg, float *ut);

/**
 * @}
 */

/**
 * @defgroup bmm150_extern_driver bmm150 extern driver function
 * @brief    bmm150 extern driver modules
 * @ingroup  bmm150_driver
 * @{
 */

/**
 * @brief     set the chip register
 * @param[in] *handle pointer to a bmm150 handle structure
 * @param[in] reg register address
 * @param[in] *buf pointer to a data buffer
 * @param[in] len length of data buffer
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bmm150_set_reg(bmm150_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len);

/**
 * @brief      get the chip register
 * @param[in]  *handle pointer to a bmm150 handle structure
 * @param[in]  reg register address
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len length of data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bmm150_get_reg(bmm150_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
