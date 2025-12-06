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
 * @file      driver_bmm150_shot.c
 * @brief     driver bmm150 shot source file
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

#include "driver_bmm150_shot.h"

static bmm150_handle_t gs_handle;        /**< bmm150 handle */

/**
 * @brief     shot example init
 * @param[in] interface chip interface
 * @param[in] addr_pin iic device address
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t bmm150_shot_init(bmm150_interface_t interface, bmm150_address_t addr_pin)
{
    uint8_t res;
    
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
    DRIVER_BMM150_LINK_RECEIVE_CALLBACK(&gs_handle, bmm150_interface_receive_callback);
    
    /* set the interface */
    res = bmm150_set_interface(&gs_handle, interface);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interface failed.\n");
       
        return 1;
    }
    
    /* set addr pin */
    res = bmm150_set_addr_pin(&gs_handle, addr_pin);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set addr pin failed.\n");
       
        return 1;
    }
    /* set the interface */
    res = bmm150_set_interface(&gs_handle, interface);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interface failed.\n");
       
        return 1;
    }
    
    /* set addr pin */
    res = bmm150_set_addr_pin(&gs_handle, addr_pin);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set addr pin failed.\n");
       
        return 1;
    }
    
    /* bmm150 initialization */
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
    
    /* disable high threshold z */
    res = bmm150_set_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_HIGH_THRESHOLD_Z, BMM150_BOOL_FALSE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable high threshold y */
    res = bmm150_set_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_HIGH_THRESHOLD_Y, BMM150_BOOL_FALSE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable high threshold x */
    res = bmm150_set_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_HIGH_THRESHOLD_X, BMM150_BOOL_FALSE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable low threshold z */
    res = bmm150_set_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_LOW_THRESHOLD_Z, BMM150_BOOL_FALSE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable low threshold y */
    res = bmm150_set_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_LOW_THRESHOLD_Y, BMM150_BOOL_FALSE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable low threshold x */
    res = bmm150_set_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_LOW_THRESHOLD_X, BMM150_BOOL_FALSE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable data ready pin */
    res = bmm150_set_data_ready_pin(&gs_handle, BMM150_BOOL_FALSE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set data ready pin failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable interrupt pin */
    res = bmm150_set_interrupt_pin(&gs_handle, BMM150_BOOL_FALSE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt pin failed.\n");
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
    
    /* set default repxy number */
    res = bmm150_set_repxy_number(&gs_handle, BMM150_SHOT_DEFAULT_REPXY);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set repxy number failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default repz number */
    res = bmm150_set_repz_number(&gs_handle, BMM150_SHOT_DEFAULT_REPZ);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set repz number failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default data rate */
    res = bmm150_set_data_rate(&gs_handle, BMM150_SHOT_DEFAULT_DATA_RATE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set data rate failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set sleep mode */
    res = bmm150_set_mode(&gs_handle, BMM150_MODE_SLEEP);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set mode failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief      shot example read
 * @param[out] *ut pointer to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t bmm150_shot_read(float ut[3])
{
    int16_t raw[3];
    
    /* read data */
    if (bmm150_read(&gs_handle, raw, ut) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  shot example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t bmm150_shot_deinit(void)
{
    /* deinit */
    if (bmm150_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}
