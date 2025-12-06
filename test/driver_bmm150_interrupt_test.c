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
 * @file      driver_bmm150_interrupt_test.c
 * @brief     driver bmm150 interrupt test source file
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

#include "driver_bmm150_interrupt_test.h"

static bmm150_handle_t gs_handle;        /**< bmm150 handle */
static volatile uint8_t gs_flag;         /**< interrupt flag */

/**
 * @brief     interface receive callback
 * @param[in] type irq type
 * @note      none
 */
static void a_receive_callback(uint8_t type)
{
    switch (type)
    {
        case BMM150_INTERRUPT_STATUS_DATA_OVERRUN :
        {
            break;
        }
        case BMM150_INTERRUPT_STATUS_OVERFLOW :
        {
            break;
        }
        case BMM150_INTERRUPT_STATUS_HIGH_THRESHOLD_Z :
        {
            bmm150_interface_debug_print("bmm150: irq high threshold z.\n");
            gs_flag = 1;
            
            break;
        }
        case BMM150_INTERRUPT_STATUS_HIGH_THRESHOLD_Y :
        {
            bmm150_interface_debug_print("bmm150: irq high threshold y.\n");
            gs_flag = 1;
            
            break;
        }
        case BMM150_INTERRUPT_STATUS_HIGH_THRESHOLD_X :
        {
            bmm150_interface_debug_print("bmm150: irq high threshold x.\n");
            gs_flag = 1;
            
            break;
        }
        case BMM150_INTERRUPT_STATUS_LOW_THRESHOLD_Z :
        {
            bmm150_interface_debug_print("bmm150: irq low threshold z.\n");
            gs_flag = 1;
            
            break;
        }
        case BMM150_INTERRUPT_STATUS_LOW_THRESHOLD_Y :
        {
            bmm150_interface_debug_print("bmm150: irq low threshold y.\n");
            gs_flag = 1;
            
            break;
        }
        case BMM150_INTERRUPT_STATUS_LOW_THRESHOLD_X :
        {
            bmm150_interface_debug_print("bmm150: irq low threshold x.\n");
            gs_flag = 1;
            
            break;
        }
        default :
        {
            bmm150_interface_debug_print("bmm150: unknown code.\n");
            
            break;
        }
    }
}

/**
 * @brief  interrupt test irq
 * @return status code
 *         - 0 success
 *         - 1 run failed
 * @note   none
 */
uint8_t bmm150_interrupt_test_irq_handler(void)
{
    if (bmm150_irq_handler(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     interrupt test
 * @param[in] interface chip interface
 * @param[in] addr_pin iic device address
 * @param[in] low_threshold_ut low threshold in ut
 * @param[in] high_threshold_ut high threshold in ut
 * @param[in] times test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t bmm150_interrupt_test(bmm150_interface_t interface, bmm150_address_t addr_pin,
                              float low_threshold_ut, float high_threshold_ut, uint32_t times)
{
    uint8_t res;
    int8_t reg;
    uint32_t i;
    bmm150_bool_t enable;
    bmm150_info_t info;
    
    /* link interface function */
    DRIVER_BMM150_LINK_INIT(&gs_handle, bmm150_handle_t);
    DRIVER_BMM150_LINK_IIC_INIT(&gs_handle, bmm150_interface_iic_init);
    DRIVER_BMM150_LINK_IIC_DEINIT(&gs_handle, bmm150_interface_iic_deinit);
    DRIVER_BMM150_LINK_IIC_READ(&gs_handle, bmm150_interface_iic_read);
    DRIVER_BMM150_LINK_IIC_WRITE(&gs_handle, bmm150_interface_iic_write);
    DRIVER_BMM150_LINK_SPI_INIT(&gs_handle, bmm150_interface_spi_init);
    DRIVER_BMM150_LINK_SPI_DEINIT(&gs_handle, bmm150_interface_spi_deinit);
    DRIVER_BMM150_LINK_SPI_READ(&gs_handle, bmm150_interface_spi_read);
    DRIVER_BMM150_LINK_SPI_WRITE(&gs_handle, bmm150_interface_spi_write);
    DRIVER_BMM150_LINK_DELAY_MS(&gs_handle, bmm150_interface_delay_ms);
    DRIVER_BMM150_LINK_DEBUG_PRINT(&gs_handle, bmm150_interface_debug_print);
    DRIVER_BMM150_LINK_RECEIVE_CALLBACK(&gs_handle, a_receive_callback);
    
    /* get information */
    res = bmm150_info(&info);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip info */
        bmm150_interface_debug_print("bmm150: chip is %s.\n", info.chip_name);
        bmm150_interface_debug_print("bmm150: manufacturer is %s.\n", info.manufacturer_name);
        bmm150_interface_debug_print("bmm150: interface is %s.\n", info.interface);
        bmm150_interface_debug_print("bmm150: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        bmm150_interface_debug_print("bmm150: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        bmm150_interface_debug_print("bmm150: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        bmm150_interface_debug_print("bmm150: max current is %0.2fmA.\n", info.max_current_ma);
        bmm150_interface_debug_print("bmm150: max temperature is %0.1fC.\n", info.temperature_max);
        bmm150_interface_debug_print("bmm150: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start interrupt test */
    bmm150_interface_debug_print("bmm150: start interrupt test.\n");
    
    /* set the interface */
    res = bmm150_set_interface(&gs_handle, interface);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interface failed.\n");
       
        return 1;
    }
    
    /* set the address pin */
    res = bmm150_set_addr_pin(&gs_handle, addr_pin);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set addr pin failed.\n");
       
        return 1;
    }
    
    /* init bmm150 */
    res = bmm150_init(&gs_handle);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: init failed.\n");
       
        return 1;
    }
    
    /* power on */
    res = bmm150_set_power_on(&gs_handle, BMM150_BOOL_TRUE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set power on failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set advanced self test normal mode */
    res = bmm150_set_advanced_self_test(&gs_handle, BMM150_ADVANCED_SELF_TEST_NORMAL);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set advanced self test failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable self test */
    res = bmm150_set_self_test(&gs_handle, BMM150_BOOL_FALSE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set self test failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable data overrun */
    res = bmm150_set_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_DATA_OVERRUN, BMM150_BOOL_FALSE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable overflow */
    res = bmm150_set_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_OVERFLOW, BMM150_BOOL_FALSE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable high threshold z */
    res = bmm150_set_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_HIGH_THRESHOLD_Z, BMM150_BOOL_TRUE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable high threshold y */
    res = bmm150_set_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_HIGH_THRESHOLD_Y, BMM150_BOOL_TRUE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable high threshold x */
    res = bmm150_set_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_HIGH_THRESHOLD_X, BMM150_BOOL_TRUE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable low threshold z */
    res = bmm150_set_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_LOW_THRESHOLD_Z, BMM150_BOOL_TRUE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable low threshold y */
    res = bmm150_set_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_LOW_THRESHOLD_Y, BMM150_BOOL_TRUE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable low threshold x */
    res = bmm150_set_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_LOW_THRESHOLD_X, BMM150_BOOL_TRUE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable data ready pin */
    res = bmm150_set_data_ready_pin(&gs_handle, BMM150_BOOL_TRUE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set data ready pin failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable interrupt pin */
    res = bmm150_set_interrupt_pin(&gs_handle, BMM150_BOOL_TRUE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt pin failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set data ready pin polarity low */
    res = bmm150_set_data_ready_pin_polarity(&gs_handle, BMM150_DATA_READY_PIN_POLARITY_LOW);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set data ready pin polarity failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable interrupt latch */
    res = bmm150_set_interrupt_latch(&gs_handle, BMM150_BOOL_TRUE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt latch failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set interrupt pin polarity low */
    res = bmm150_set_interrupt_pin_polarity(&gs_handle, BMM150_INTERRUPT_PIN_POLARITY_LOW);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt pin polarity failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    /* convert low threshold */
    res = bmm150_interrupt_threshold_convert_to_register(&gs_handle, low_threshold_ut, &reg);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: interrupt threshold convert to register failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set low threshold */
    res = bmm150_set_low_threshold(&gs_handle, reg);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set low threshold failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    /* convert high threshold */
    res = bmm150_interrupt_threshold_convert_to_register(&gs_handle, high_threshold_ut, &reg);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: interrupt threshold convert to register failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set high threshold */
    res = bmm150_set_high_threshold(&gs_handle, reg);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set high threshold failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable channel z */
    res = bmm150_set_channel_z(&gs_handle, BMM150_BOOL_TRUE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set channel z failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable channel y */
    res = bmm150_set_channel_y(&gs_handle, BMM150_BOOL_TRUE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set channel y failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable channel x */
    res = bmm150_set_channel_x(&gs_handle, BMM150_BOOL_TRUE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set channel x failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set repxy number */
    res = bmm150_set_repxy_number(&gs_handle, 9);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set repxy number failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set repz number */
    res = bmm150_set_repz_number(&gs_handle, 15);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set repz number failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set data rate 2hz */
    res = bmm150_set_data_rate(&gs_handle, BMM150_DATA_RATE_2HZ);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set data rate failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set normal mode */
    res = bmm150_set_mode(&gs_handle, BMM150_MODE_NORMAL);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set mode failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    /* clear interrupt status */
    res = bmm150_get_interrupt_status(&gs_handle, BMM150_INTERRUPT_STATUS_DATA_OVERRUN, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get interrupt status failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    gs_flag = 0;
    for (i = 0; i < times; i++)
    {
        int16_t raw[3];
        float ut[3];
        
        /* delay 1000ms */
        bmm150_interface_delay_ms(1000);
        
        if (gs_flag != 0)
        {
            bmm150_interface_debug_print("bmm150: find interrupt.\n");
            
            gs_flag = 0;
        }
        
        /* read data */
        res = bmm150_read(&gs_handle, raw, ut);
        if (res != 0)
        {
            bmm150_interface_debug_print("bmm150: read failed.\n");
            (void)bmm150_deinit(&gs_handle);
            
            return 1;
        }
        
        /* output */
        bmm150_interface_debug_print("bmm150: x is %0.2fuT.\n", ut[0]);
        bmm150_interface_debug_print("bmm150: y is %0.2fuT.\n", ut[1]);
        bmm150_interface_debug_print("bmm150: z is %0.2fuT.\n", ut[2]);
    }
    
    /* finish interrupt test */
    bmm150_interface_debug_print("bmm150: finish interrupt test.\n");
    (void)bmm150_deinit(&gs_handle);
    
    return 0;
}
