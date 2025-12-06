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
 * @file      driver_bmm150_interrupt.h
 * @brief     driver bmm150 interrupt header file
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

#ifndef DRIVER_BMM150_INTERRUPT_H
#define DRIVER_BMM150_INTERRUPT_H

#include "driver_bmm150_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @addtogroup bmm150_example_driver
 * @{
 */

/**
 * @brief bmm150 interrupt example default definition
 */
#define BMM150_INTERRUPT_DEFAULT_INTERRUPT_DATA_OVERRUN            BMM150_BOOL_FALSE                         /**< disable data overrun */
#define BMM150_INTERRUPT_DEFAULT_INTERRUPT_OVERFLOW                BMM150_BOOL_FALSE                         /**< disable overflow */
#define BMM150_INTERRUPT_DEFAULT_INTERRUPT_HIGH_THRESHOLD_Z        BMM150_BOOL_TRUE                          /**< enable high threshold z */
#define BMM150_INTERRUPT_DEFAULT_INTERRUPT_HIGH_THRESHOLD_Y        BMM150_BOOL_TRUE                          /**< enable high threshold y */
#define BMM150_INTERRUPT_DEFAULT_INTERRUPT_HIGH_THRESHOLD_X        BMM150_BOOL_TRUE                          /**< enable high threshold x */
#define BMM150_INTERRUPT_DEFAULT_INTERRUPT_LOW_THRESHOLD_Z         BMM150_BOOL_TRUE                          /**< enable low threshold z */
#define BMM150_INTERRUPT_DEFAULT_INTERRUPT_LOW_THRESHOLD_Y         BMM150_BOOL_TRUE                          /**< enable low threshold y */
#define BMM150_INTERRUPT_DEFAULT_INTERRUPT_LOW_THRESHOLD_X         BMM150_BOOL_TRUE                          /**< enable low threshold x */
#define BMM150_INTERRUPT_DEFAULT_DATA_READY_PIN                    BMM150_BOOL_TRUE                          /**< enable data ready pin */
#define BMM150_INTERRUPT_DEFAULT_INTERRUPT_PIN                     BMM150_BOOL_TRUE                          /**< enable interrupt pin */
#define BMM150_INTERRUPT_DEFAULT_DATA_READY_PIN_POLARITY           BMM150_DATA_READY_PIN_POLARITY_LOW        /**< polarity low */
#define BMM150_INTERRUPT_DEFAULT_INTERRUPT_LATCH                   BMM150_BOOL_TRUE                          /**< enable latch */
#define BMM150_INTERRUPT_DEFAULT_INTERRUPT_PIN_POLARITY            BMM150_INTERRUPT_PIN_POLARITY_LOW         /**< polarity low */
#define BMM150_INTERRUPT_DEFAULT_REPXY                             47                                        /**< 47 */
#define BMM150_INTERRUPT_DEFAULT_REPZ                              83                                        /**< 83 */
#define BMM150_INTERRUPT_DEFAULT_DATA_RATE                         BMM150_DATA_RATE_2HZ                      /**< 2Hz */

/**
 * @brief  interrupt irq
 * @return status code
 *         - 0 success
 *         - 1 run failed
 * @note   none
 */
uint8_t bmm150_interrupt_irq_handler(void);

/**
 * @brief     interrupt example init
 * @param[in] interface chip interface
 * @param[in] addr_pin iic device address
 * @param[in] low_threshold_ut low threshold in ut
 * @param[in] high_threshold_ut high threshold in ut
 * @param[in] *callback pointer to an irq callback address
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t bmm150_interrupt_init(bmm150_interface_t interface, bmm150_address_t addr_pin,
                              float low_threshold_ut, float high_threshold_ut, void (*callback)(uint8_t type));

/**
 * @brief  interrupt example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t bmm150_interrupt_deinit(void);

/**
 * @brief      interrupt example read
 * @param[out] *ut pointer to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t bmm150_interrupt_read(float ut[3]);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
