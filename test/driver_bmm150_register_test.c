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
 * @file      driver_bmm150_register_test.c
 * @brief     driver bmm150 register test source file
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

#include "driver_bmm150_register_test.h"
#include <stdlib.h>

static bmm150_handle_t gs_handle;        /**< bmm150 handle */

/**
 * @brief     register test
 * @param[in] interface chip interface
 * @param[in] addr_pin iic device address
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t bmm150_register_test(bmm150_interface_t interface, bmm150_address_t addr_pin)
{
    uint8_t res;
    uint8_t reg;
    uint8_t reg_check;
    int8_t reg2;
    int8_t reg2_check;
    float ut;
    float ut_check;
    bmm150_interface_t interface_test;
    bmm150_address_t addr_check;
    bmm150_info_t info;
    bmm150_bool_t enable;
    bmm150_spi_wire_t wire;
    bmm150_advanced_self_test_t test;
    bmm150_data_rate_t rate;
    bmm150_mode_t mode;
    bmm150_data_ready_pin_polarity_t ready_pin_polarity;
    bmm150_interrupt_pin_polarity_t interrupt_pin_polarity;
    
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
    
    /* start register test */
    bmm150_interface_debug_print("bmm150: start register test.\n");
    
    /* bmm150_set_interface/bmm150_get_interface test */
    bmm150_interface_debug_print("bmm150: bmm150_set_interface/bmm150_get_interface test.\n");
    
    /* set IIC interface */
    res = bmm150_set_interface(&gs_handle, BMM150_INTERFACE_IIC);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interface failed.\n");
       
        return 1;
    }
    bmm150_interface_debug_print("bmm150: set interface iic.\n");
    res = bmm150_get_interface(&gs_handle, &interface_test);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get interface failed.\n");
       
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check interface %s.\n", (interface_test == BMM150_INTERFACE_IIC) ? "ok" : "error");
    
    /* set SPI interface */
    res = bmm150_set_interface(&gs_handle, BMM150_INTERFACE_SPI);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interface failed.\n");
       
        return 1;
    }
    bmm150_interface_debug_print("bmm150: set interface spi.\n");
    res = bmm150_get_interface(&gs_handle, &interface_test);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get interface failed.\n");
       
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check interface %s.\n", (interface_test == BMM150_INTERFACE_SPI) ? "ok" : "error");
    
    /* bmm150_set_addr_pin/bmm150_get_addr_pin test */
    bmm150_interface_debug_print("bmm150: bmm150_set_addr_pin/bmm150_get_addr_pin test.\n");
    
    /* set addr csb sdo 00 */
    res = bmm150_set_addr_pin(&gs_handle, BMM150_ADDRESS_CSB_SDO_00);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set addr pin failed.\n");
       
        return 1;
    }
    bmm150_interface_debug_print("bmm150: set addr csb sdo 00.\n");
    res = bmm150_get_addr_pin(&gs_handle, &addr_check);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get addr pin failed.\n");
       
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check addr pin %s.\n", (addr_check == BMM150_ADDRESS_CSB_SDO_00) ? "ok" : "error");
    
    /* set addr csb sdo 01 */
    res = bmm150_set_addr_pin(&gs_handle, BMM150_ADDRESS_CSB_SDO_01);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set addr pin failed.\n");
       
        return 1;
    }
    bmm150_interface_debug_print("bmm150: set addr csb sdo 01.\n");
    res = bmm150_get_addr_pin(&gs_handle, &addr_check);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get addr pin failed.\n");
       
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check addr pin %s.\n", (addr_check == BMM150_ADDRESS_CSB_SDO_01) ? "ok" : "error");
    
    /* set addr csb sdo 10 */
    res = bmm150_set_addr_pin(&gs_handle, BMM150_ADDRESS_CSB_SDO_10);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set addr pin failed.\n");
       
        return 1;
    }
    bmm150_interface_debug_print("bmm150: set addr csb sdo 10.\n");
    res = bmm150_get_addr_pin(&gs_handle, &addr_check);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get addr pin failed.\n");
       
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check addr pin %s.\n", (addr_check == BMM150_ADDRESS_CSB_SDO_10) ? "ok" : "error");
    
    /* set addr csb sdo 11 */
    res = bmm150_set_addr_pin(&gs_handle, BMM150_ADDRESS_CSB_SDO_11);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set addr pin failed.\n");
       
        return 1;
    }
    bmm150_interface_debug_print("bmm150: set addr csb sdo 11.\n");
    res = bmm150_get_addr_pin(&gs_handle, &addr_check);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get addr pin failed.\n");
       
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check addr pin %s.\n", (addr_check == BMM150_ADDRESS_CSB_SDO_11) ? "ok" : "error");
    
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
    
    /* init the bmm150 */
    res = bmm150_init(&gs_handle);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: init failed.\n");
       
        return 1;
    }
    
    /* bmm150_set_power_on/bmm150_get_power_on test */
    bmm150_interface_debug_print("bmm150: bmm150_set_power_on/bmm150_get_power_on test.\n");
    
    /* disable power on */
    res = bmm150_set_power_on(&gs_handle, BMM150_BOOL_FALSE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set power on failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: disable power on .\n");
    res = bmm150_get_power_on(&gs_handle, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get power on failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check power on %s.\n", (enable == BMM150_BOOL_FALSE) ? "ok" : "error");
    
    /* enable power on */
    res = bmm150_set_power_on(&gs_handle, BMM150_BOOL_TRUE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set power on failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: enable power on .\n");
    res = bmm150_get_power_on(&gs_handle, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get power on failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check power on %s.\n", (enable == BMM150_BOOL_TRUE) ? "ok" : "error");
    
    if (interface == BMM150_INTERFACE_IIC)
    {
        /* bmm150_set_spi_wire/bmm150_get_spi_wire test */
        bmm150_interface_debug_print("bmm150: bmm150_set_spi_wire/bmm150_get_spi_wire test.\n");
        
        /* set spi wire4 */
        res = bmm150_set_spi_wire(&gs_handle, BMM150_SPI_WIRE_4);
        if (res != 0)
        {
            bmm150_interface_debug_print("bmm150: set spi wire failed.\n");
            (void)bmm150_deinit(&gs_handle);
            
            return 1;
        }
        bmm150_interface_debug_print("bmm150: set spi wire4.\n");
        res = bmm150_get_spi_wire(&gs_handle, &wire);
        if (res != 0)
        {
            bmm150_interface_debug_print("bmm150: get spi wire failed.\n");
            (void)bmm150_deinit(&gs_handle);
            
            return 1;
        }
        bmm150_interface_debug_print("bmm150: check spi wire on %s.\n", (wire == BMM150_SPI_WIRE_4) ? "ok" : "error");
        
        /* set spi wire3 */
        res = bmm150_set_spi_wire(&gs_handle, BMM150_SPI_WIRE_3);
        if (res != 0)
        {
            bmm150_interface_debug_print("bmm150: set spi wire failed.\n");
            (void)bmm150_deinit(&gs_handle);
            
            return 1;
        }
        bmm150_interface_debug_print("bmm150: set spi wire3.\n");
        res = bmm150_get_spi_wire(&gs_handle, &wire);
        if (res != 0)
        {
            bmm150_interface_debug_print("bmm150: get spi wire failed.\n");
            (void)bmm150_deinit(&gs_handle);
            
            return 1;
        }
        bmm150_interface_debug_print("bmm150: check spi wire on %s.\n", (wire == BMM150_SPI_WIRE_3) ? "ok" : "error");
    }
    
    /* bmm150_set_advanced_self_test/bmm150_get_advanced_self_test test */
    bmm150_interface_debug_print("bmm150: bmm150_set_advanced_self_test/bmm150_get_advanced_self_test test.\n");
    
    /* set advanced self test positive mode */
    res = bmm150_set_advanced_self_test(&gs_handle, BMM150_ADVANCED_SELF_TEST_POSITIVE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set advanced self test failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: set advanced self test positive mode.\n");
    res = bmm150_get_advanced_self_test(&gs_handle, &test);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get advanced self test failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check advanced self test %s.\n", (test == BMM150_ADVANCED_SELF_TEST_POSITIVE) ? "ok" : "error");
    
    /* set advanced self test negative mode */
    res = bmm150_set_advanced_self_test(&gs_handle, BMM150_ADVANCED_SELF_TEST_NEGATIVE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set advanced self test failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: set advanced self test negative mode.\n");
    res = bmm150_get_advanced_self_test(&gs_handle, &test);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get advanced self test failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check advanced self test %s.\n", (test == BMM150_ADVANCED_SELF_TEST_NEGATIVE) ? "ok" : "error");
    
    /* set advanced self test normal mode */
    res = bmm150_set_advanced_self_test(&gs_handle, BMM150_ADVANCED_SELF_TEST_NORMAL);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set advanced self test failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: set advanced self test normal mode.\n");
    res = bmm150_get_advanced_self_test(&gs_handle, &test);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get advanced self test failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check advanced self test %s.\n", (test == BMM150_ADVANCED_SELF_TEST_NORMAL) ? "ok" : "error");
    
    /* bmm150_set_data_rate/bmm150_get_data_rate test */
    bmm150_interface_debug_print("bmm150: bmm150_set_data_rate/bmm150_get_data_rate test.\n");
    
    /* set data rate 10hz */
    res = bmm150_set_data_rate(&gs_handle, BMM150_DATA_RATE_10HZ);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set data rate failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: set data rate 10hz.\n");
    res = bmm150_get_data_rate(&gs_handle, &rate);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get data rate failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check data rate %s.\n", (rate == BMM150_DATA_RATE_10HZ) ? "ok" : "error");
    
    /* set data rate 2hz */
    res = bmm150_set_data_rate(&gs_handle, BMM150_DATA_RATE_2HZ);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set data rate failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: set data rate 2hz.\n");
    res = bmm150_get_data_rate(&gs_handle, &rate);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get data rate failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check data rate %s.\n", (rate == BMM150_DATA_RATE_2HZ) ? "ok" : "error");
    
    /* set data rate 6hz */
    res = bmm150_set_data_rate(&gs_handle, BMM150_DATA_RATE_6HZ);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set data rate failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: set data rate 6hz.\n");
    res = bmm150_get_data_rate(&gs_handle, &rate);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get data rate failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check data rate %s.\n", (rate == BMM150_DATA_RATE_6HZ) ? "ok" : "error");
    
    /* set data rate 8hz */
    res = bmm150_set_data_rate(&gs_handle, BMM150_DATA_RATE_8HZ);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set data rate failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: set data rate 8hz.\n");
    res = bmm150_get_data_rate(&gs_handle, &rate);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get data rate failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check data rate %s.\n", (rate == BMM150_DATA_RATE_8HZ) ? "ok" : "error");
    
    /* set data rate 15hz */
    res = bmm150_set_data_rate(&gs_handle, BMM150_DATA_RATE_15HZ);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set data rate failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: set data rate 15hz.\n");
    res = bmm150_get_data_rate(&gs_handle, &rate);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get data rate failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check data rate %s.\n", (rate == BMM150_DATA_RATE_15HZ) ? "ok" : "error");
    
    /* set data rate 20hz */
    res = bmm150_set_data_rate(&gs_handle, BMM150_DATA_RATE_20HZ);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set data rate failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: set data rate 20hz.\n");
    res = bmm150_get_data_rate(&gs_handle, &rate);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get data rate failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check data rate %s.\n", (rate == BMM150_DATA_RATE_20HZ) ? "ok" : "error");
    
    /* set data rate 25hz */
    res = bmm150_set_data_rate(&gs_handle, BMM150_DATA_RATE_25HZ);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set data rate failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: set data rate 25hz.\n");
    res = bmm150_get_data_rate(&gs_handle, &rate);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get data rate failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check data rate %s.\n", (rate == BMM150_DATA_RATE_25HZ) ? "ok" : "error");
    
    /* set data rate 30hz */
    res = bmm150_set_data_rate(&gs_handle, BMM150_DATA_RATE_30HZ);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set data rate failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: set data rate 30hz.\n");
    res = bmm150_get_data_rate(&gs_handle, &rate);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get data rate failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check data rate %s.\n", (rate == BMM150_DATA_RATE_30HZ) ? "ok" : "error");
    
    /* bmm150_set_mode/bmm150_get_mode test */
    bmm150_interface_debug_print("bmm150: bmm150_set_mode/bmm150_get_mode test.\n");
    
    /* set normal mode */
    res = bmm150_set_mode(&gs_handle, BMM150_MODE_NORMAL);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set mode failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: set normal mode.\n");
    res = bmm150_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get mode failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check mode %s.\n", (mode == BMM150_MODE_NORMAL) ? "ok" : "error");
    
    /* set forced mode */
    res = bmm150_set_mode(&gs_handle, BMM150_MODE_FORCED);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set mode failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: set forced mode.\n");
    res = bmm150_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get mode failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check mode %s.\n", (res == 0) ? "ok" : "error");
    
    /* set sleep mode */
    res = bmm150_set_mode(&gs_handle, BMM150_MODE_SLEEP);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set mode failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: set sleep mode.\n");
    res = bmm150_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get mode failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check mode %s.\n", (mode == BMM150_MODE_SLEEP) ? "ok" : "error");
    
    /* bmm150_set_self_test/bmm150_get_self_test test */
    bmm150_interface_debug_print("bmm150: bmm150_set_self_test/bmm150_get_self_test test.\n");
    
    /* enable self test */
    res = bmm150_set_self_test(&gs_handle, BMM150_BOOL_TRUE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set self test failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: enable self test.\n");
    res = bmm150_get_self_test(&gs_handle, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get self test failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check self test %s.\n", (res == 0) ? "ok" : "error");
    
    /* disable self test */
    res = bmm150_set_self_test(&gs_handle, BMM150_BOOL_FALSE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set self test failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: disable self test.\n");
    res = bmm150_get_self_test(&gs_handle, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get self test failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check self test %s.\n", (enable == BMM150_BOOL_FALSE) ? "ok" : "error");
    
    /* bmm150_set_interrupt/bmm150_get_interrupt test */
    bmm150_interface_debug_print("bmm150: bmm150_set_interrupt/bmm150_get_interrupt test.\n");
    
    /* enable data overrun */
    res = bmm150_set_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_DATA_OVERRUN, BMM150_BOOL_TRUE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: enable data overrun.\n");
    res = bmm150_get_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_DATA_OVERRUN, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check interrupt %s.\n", (enable == BMM150_BOOL_TRUE) ? "ok" : "error");
    
    /* disable data overrun */
    res = bmm150_set_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_DATA_OVERRUN, BMM150_BOOL_FALSE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: disable data overrun.\n");
    res = bmm150_get_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_DATA_OVERRUN, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check interrupt %s.\n", (enable == BMM150_BOOL_FALSE) ? "ok" : "error");
    
    /* enable overflow */
    res = bmm150_set_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_OVERFLOW, BMM150_BOOL_TRUE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: enable overflow.\n");
    res = bmm150_get_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_OVERFLOW, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check interrupt %s.\n", (enable == BMM150_BOOL_TRUE) ? "ok" : "error");
    
    /* disable overflow */
    res = bmm150_set_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_OVERFLOW, BMM150_BOOL_FALSE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: disable overflow.\n");
    res = bmm150_get_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_OVERFLOW, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check interrupt %s.\n", (enable == BMM150_BOOL_FALSE) ? "ok" : "error");
    
    /* enable high threshold z */
    res = bmm150_set_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_HIGH_THRESHOLD_Z, BMM150_BOOL_TRUE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: enable high threshold z.\n");
    res = bmm150_get_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_HIGH_THRESHOLD_Z, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check interrupt %s.\n", (enable == BMM150_BOOL_TRUE) ? "ok" : "error");
    
    /* disable high threshold z */
    res = bmm150_set_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_HIGH_THRESHOLD_Z, BMM150_BOOL_FALSE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: disable high threshold z.\n");
    res = bmm150_get_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_HIGH_THRESHOLD_Z, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check interrupt %s.\n", (enable == BMM150_BOOL_FALSE) ? "ok" : "error");
    
    /* enable high threshold y */
    res = bmm150_set_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_HIGH_THRESHOLD_Y, BMM150_BOOL_TRUE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: enable high threshold y.\n");
    res = bmm150_get_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_HIGH_THRESHOLD_Y, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check interrupt %s.\n", (enable == BMM150_BOOL_TRUE) ? "ok" : "error");
    
    /* disable high threshold y */
    res = bmm150_set_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_HIGH_THRESHOLD_Y, BMM150_BOOL_FALSE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: disable high threshold y.\n");
    res = bmm150_get_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_HIGH_THRESHOLD_Y, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check interrupt %s.\n", (enable == BMM150_BOOL_FALSE) ? "ok" : "error");
    
    /* enable high threshold x */
    res = bmm150_set_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_HIGH_THRESHOLD_X, BMM150_BOOL_TRUE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: enable high threshold x.\n");
    res = bmm150_get_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_HIGH_THRESHOLD_X, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check interrupt %s.\n", (enable == BMM150_BOOL_TRUE) ? "ok" : "error");
    
    /* disable high threshold x */
    res = bmm150_set_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_HIGH_THRESHOLD_X, BMM150_BOOL_FALSE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: disable high threshold x.\n");
    res = bmm150_get_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_HIGH_THRESHOLD_X, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check interrupt %s.\n", (enable == BMM150_BOOL_FALSE) ? "ok" : "error");
    
    /* enable low threshold z */
    res = bmm150_set_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_LOW_THRESHOLD_Z, BMM150_BOOL_TRUE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: enable low threshold z.\n");
    res = bmm150_get_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_LOW_THRESHOLD_Z, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check interrupt %s.\n", (enable == BMM150_BOOL_TRUE) ? "ok" : "error");
    
    /* disable low threshold z */
    res = bmm150_set_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_LOW_THRESHOLD_Z, BMM150_BOOL_FALSE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: disable low threshold z.\n");
    res = bmm150_get_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_LOW_THRESHOLD_Z, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check interrupt %s.\n", (enable == BMM150_BOOL_FALSE) ? "ok" : "error");
    
    /* enable low threshold y */
    res = bmm150_set_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_LOW_THRESHOLD_Y, BMM150_BOOL_TRUE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: enable low threshold y.\n");
    res = bmm150_get_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_LOW_THRESHOLD_Y, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check interrupt %s.\n", (enable == BMM150_BOOL_TRUE) ? "ok" : "error");
    
    /* disable low threshold y */
    res = bmm150_set_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_LOW_THRESHOLD_Y, BMM150_BOOL_FALSE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: disable low threshold y.\n");
    res = bmm150_get_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_LOW_THRESHOLD_Y, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check interrupt %s.\n", (enable == BMM150_BOOL_FALSE) ? "ok" : "error");
    
    /* enable low threshold x */
    res = bmm150_set_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_LOW_THRESHOLD_X, BMM150_BOOL_TRUE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: enable low threshold x.\n");
    res = bmm150_get_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_LOW_THRESHOLD_X, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check interrupt %s.\n", (enable == BMM150_BOOL_TRUE) ? "ok" : "error");
    
    /* disable low threshold x */
    res = bmm150_set_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_LOW_THRESHOLD_X, BMM150_BOOL_FALSE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: disable low threshold x.\n");
    res = bmm150_get_interrupt(&gs_handle, BMM150_INTERRUPT_STATUS_LOW_THRESHOLD_X, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get interrupt failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check interrupt %s.\n", (enable == BMM150_BOOL_FALSE) ? "ok" : "error");
    
    /* bmm150_set_data_ready_pin/bmm150_get_data_ready_pin test */
    bmm150_interface_debug_print("bmm150: bmm150_set_data_ready_pin/bmm150_get_data_ready_pin test.\n");
    
    /* enable data ready pin */
    res = bmm150_set_data_ready_pin(&gs_handle, BMM150_BOOL_TRUE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set data ready pin failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: enable data ready pin.\n");
    res = bmm150_get_data_ready_pin(&gs_handle, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get data ready pin failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check data ready pin %s.\n", (enable == BMM150_BOOL_TRUE) ? "ok" : "error");
    
    /* disable data ready pin */
    res = bmm150_set_data_ready_pin(&gs_handle, BMM150_BOOL_FALSE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set data ready pin failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: disable data ready pin.\n");
    res = bmm150_get_data_ready_pin(&gs_handle, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get data ready pin failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check data ready pin %s.\n", (enable == BMM150_BOOL_FALSE) ? "ok" : "error");
    
    /* bmm150_set_interrupt_pin/bmm150_get_interrupt_pin test */
    bmm150_interface_debug_print("bmm150: bmm150_set_interrupt_pin/bmm150_get_interrupt_pin test.\n");
    
    /* enable interrupt pin */
    res = bmm150_set_interrupt_pin(&gs_handle, BMM150_BOOL_TRUE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt pin failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: enable interrupt pin.\n");
    res = bmm150_get_interrupt_pin(&gs_handle, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get interrupt pin failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check interrupt pin %s.\n", (enable == BMM150_BOOL_TRUE) ? "ok" : "error");
    
    /* disable interrupt pin */
    res = bmm150_set_interrupt_pin(&gs_handle, BMM150_BOOL_FALSE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt pin failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: disable interrupt pin.\n");
    res = bmm150_get_interrupt_pin(&gs_handle, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get interrupt pin failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check interrupt pin %s.\n", (enable == BMM150_BOOL_FALSE) ? "ok" : "error");
    
    /* bmm150_set_channel_z/bmm150_get_channel_z test */
    bmm150_interface_debug_print("bmm150: bmm150_set_channel_z/bmm150_get_channel_z test.\n");
    
    /* enable channel z */
    res = bmm150_set_channel_z(&gs_handle, BMM150_BOOL_TRUE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set channel z failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: enable channel z.\n");
    res = bmm150_get_channel_z(&gs_handle, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get channel z failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check channel z %s.\n", (enable == BMM150_BOOL_TRUE) ? "ok" : "error");
    
    /* disable channel z */
    res = bmm150_set_channel_z(&gs_handle, BMM150_BOOL_FALSE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set channel z failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: disable channel z.\n");
    res = bmm150_get_channel_z(&gs_handle, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get channel z failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check channel z %s.\n", (enable == BMM150_BOOL_FALSE) ? "ok" : "error");
    
    /* enable channel y */
    res = bmm150_set_channel_y(&gs_handle, BMM150_BOOL_TRUE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set channel y failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: enable channel y.\n");
    res = bmm150_get_channel_y(&gs_handle, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get channel y failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check channel y %s.\n", (enable == BMM150_BOOL_TRUE) ? "ok" : "error");
    
    /* disable channel y */
    res = bmm150_set_channel_y(&gs_handle, BMM150_BOOL_FALSE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set channel y failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: disable channel y.\n");
    res = bmm150_get_channel_y(&gs_handle, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get channel y failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check channel y %s.\n", (enable == BMM150_BOOL_FALSE) ? "ok" : "error");
    
    /* enable channel x */
    res = bmm150_set_channel_x(&gs_handle, BMM150_BOOL_TRUE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set channel x failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: enable channel x.\n");
    res = bmm150_get_channel_x(&gs_handle, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get channel x failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check channel x %s.\n", (enable == BMM150_BOOL_TRUE) ? "ok" : "error");
    
    /* disable channel x */
    res = bmm150_set_channel_x(&gs_handle, BMM150_BOOL_FALSE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set channel x failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: disable channel x.\n");
    res = bmm150_get_channel_x(&gs_handle, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get channel x failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check channel x %s.\n", (enable == BMM150_BOOL_FALSE) ? "ok" : "error");
    
    /* bmm150_set_data_ready_pin_polarity/bmm150_get_data_ready_pin_polarity test */
    bmm150_interface_debug_print("bmm150: bmm150_set_data_ready_pin_polarity/bmm150_get_data_ready_pin_polarity test.\n");
    
    /* set data ready pin polarity low */
    res = bmm150_set_data_ready_pin_polarity(&gs_handle, BMM150_DATA_READY_PIN_POLARITY_LOW);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set data ready pin polarity failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: set data ready pin polarity low.\n");
    res = bmm150_get_data_ready_pin_polarity(&gs_handle, &ready_pin_polarity);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get data ready pin polarity failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check data ready pin polarity x %s.\n", (ready_pin_polarity == BMM150_DATA_READY_PIN_POLARITY_LOW) ? "ok" : "error");
    
    /* set data ready pin polarity high */
    res = bmm150_set_data_ready_pin_polarity(&gs_handle, BMM150_DATA_READY_PIN_POLARITY_HIGH);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set data ready pin polarity failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: set data ready pin polarity high.\n");
    res = bmm150_get_data_ready_pin_polarity(&gs_handle, &ready_pin_polarity);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get data ready pin polarity failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check data ready pin polarity x %s.\n", (ready_pin_polarity == BMM150_DATA_READY_PIN_POLARITY_HIGH) ? "ok" : "error");
    
    /* bmm150_set_interrupt_latch/bmm150_get_interrupt_latch test */
    bmm150_interface_debug_print("bmm150: bmm150_set_interrupt_latch/bmm150_get_interrupt_latch test.\n");
    
    /* enable interrupt latch */
    res = bmm150_set_interrupt_latch(&gs_handle, BMM150_BOOL_TRUE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt latch failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: enable interrupt latch.\n");
    res = bmm150_get_interrupt_latch(&gs_handle, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get interrupt latch failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check interrupt latch %s.\n", (enable == BMM150_BOOL_TRUE) ? "ok" : "error");
    
    /* disable interrupt latch */
    res = bmm150_set_interrupt_latch(&gs_handle, BMM150_BOOL_FALSE);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt latch failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: disable interrupt latch.\n");
    res = bmm150_get_interrupt_latch(&gs_handle, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get interrupt latch failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check interrupt latch %s.\n", (enable == BMM150_BOOL_FALSE) ? "ok" : "error");
    
    /* bmm150_set_interrupt_pin_polarity/bmm150_get_interrupt_pin_polarity test */
    bmm150_interface_debug_print("bmm150: bmm150_set_interrupt_pin_polarity/bmm150_get_interrupt_pin_polarity test.\n");
    
    /* set interrupt pin polarity low */
    res = bmm150_set_interrupt_pin_polarity(&gs_handle, BMM150_INTERRUPT_PIN_POLARITY_LOW);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt pin polarity failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: set interrupt pin polarity low.\n");
    res = bmm150_get_interrupt_pin_polarity(&gs_handle, &interrupt_pin_polarity);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get interrupt pin polarity failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check interrupt pin polarity %s.\n", (interrupt_pin_polarity == BMM150_INTERRUPT_PIN_POLARITY_LOW) ? "ok" : "error");
    
    /* set interrupt pin polarity high */
    res = bmm150_set_interrupt_pin_polarity(&gs_handle, BMM150_INTERRUPT_PIN_POLARITY_HIGH);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set interrupt pin polarity failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: set interrupt pin polarity high.\n");
    res = bmm150_get_interrupt_pin_polarity(&gs_handle, &interrupt_pin_polarity);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get interrupt pin polarity failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check interrupt pin polarity %s.\n", (interrupt_pin_polarity == BMM150_INTERRUPT_PIN_POLARITY_HIGH) ? "ok" : "error");
    
    /* bmm150_set_low_threshold/bmm150_get_low_threshold test */
    bmm150_interface_debug_print("bmm150: bmm150_set_low_threshold/bmm150_get_low_threshold test.\n");
    
    reg2 = rand() % 100;
    res = bmm150_set_low_threshold(&gs_handle, reg2);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set low threshold failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: set low threshold %d.\n", reg2);
    res = bmm150_get_low_threshold(&gs_handle, &reg2_check);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get low threshold failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check low threshold %s.\n", (reg2 == reg2_check) ? "ok" : "error");
    
    /* bmm150_set_high_threshold/bmm150_get_high_threshold test */
    bmm150_interface_debug_print("bmm150: bmm150_set_high_threshold/bmm150_get_high_threshold test.\n");
    
    reg2 = -(rand() % 100);
    res = bmm150_set_high_threshold(&gs_handle, reg2);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set high threshold failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: set high threshold %d.\n", reg2);
    res = bmm150_get_high_threshold(&gs_handle, &reg2_check);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get high threshold failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check high threshold %s.\n", (reg2 == reg2_check) ? "ok" : "error");
    
    /* bmm150_set_repxy_number/bmm150_get_repxy_number test */
    bmm150_interface_debug_print("bmm150: bmm150_set_repxy_number/bmm150_get_repxy_number test.\n");
    
    reg = rand() % 0xFFU;
    res = bmm150_set_repxy_number(&gs_handle, reg);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set repxy number failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: set repxy number %d.\n", reg);
    res = bmm150_get_repxy_number(&gs_handle, &reg_check);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get repxy number failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check repxy number %s.\n", (reg == reg_check) ? "ok" : "error");
    
    /* bmm150_set_repz_number/bmm150_get_repz_number test */
    bmm150_interface_debug_print("bmm150: bmm150_set_repz_number/bmm150_get_repz_number test.\n");
    
    reg = rand() % 0xFFU;
    res = bmm150_set_repz_number(&gs_handle, reg);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: set repz number failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: set repz number %d.\n", reg);
    res = bmm150_get_repz_number(&gs_handle, &reg_check);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get repz number failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check repz number %s.\n", (reg == reg_check) ? "ok" : "error");
    
    /* bmm150_interrupt_threshold_convert_to_register/bmm150_interrupt_threshold_convert_to_data test */
    bmm150_interface_debug_print("bmm150: bmm150_interrupt_threshold_convert_to_register/bmm150_interrupt_threshold_convert_to_data test.\n");
    
    ut = (float)(rand() % 1000) / 10.0f;
    res = bmm150_interrupt_threshold_convert_to_register(&gs_handle, ut, &reg2);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: interrupt threshold convert to register failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: set interrupt threshold %0.2fuT.\n", ut);
    res = bmm150_interrupt_threshold_convert_to_data(&gs_handle, reg2, &ut_check);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: interrupt threshold convert to data failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check interrupt threshold %0.2fuT.\n", ut_check);
    
    /* bmm150_get_self_test_x test */
    bmm150_interface_debug_print("bmm150: bmm150_get_self_test_x test.\n");
    
    /* get self test x */
    res = bmm150_get_self_test_x(&gs_handle, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get self test x failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check self test x %s.\n", (enable == BMM150_BOOL_TRUE) ? "true" : "false");
    
    /* bmm150_get_self_test_y test */
    bmm150_interface_debug_print("bmm150: bmm150_get_self_test_y test.\n");
    
    /* get self test y */
    res = bmm150_get_self_test_y(&gs_handle, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get self test y failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check self test y %s.\n", (enable == BMM150_BOOL_TRUE) ? "true" : "false");
    
    /* bmm150_get_self_test_z test */
    bmm150_interface_debug_print("bmm150: bmm150_get_self_test_z test.\n");
    
    /* get self test z */
    res = bmm150_get_self_test_z(&gs_handle, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get self test z failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check self test z %s.\n", (enable == BMM150_BOOL_TRUE) ? "true" : "false");
    
    /* bmm150_get_data_ready_status test */
    bmm150_interface_debug_print("bmm150: bmm150_get_data_ready_status test.\n");
    
    /* get data ready status */
    res = bmm150_get_data_ready_status(&gs_handle, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get data ready status failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check data ready status %s.\n", (enable == BMM150_BOOL_TRUE) ? "true" : "false");
    
    /* bmm150_get_interrupt_status test */
    bmm150_interface_debug_print("bmm150: bmm150_get_interrupt_status test.\n");
    
    /* data overrun */
    res = bmm150_get_interrupt_status(&gs_handle, BMM150_INTERRUPT_STATUS_DATA_OVERRUN, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get interrupt status failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check data overrun interrupt status %s.\n", (enable == BMM150_BOOL_TRUE) ? "true" : "false");
    
    /* overflow */
    res = bmm150_get_interrupt_status(&gs_handle, BMM150_INTERRUPT_STATUS_OVERFLOW, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get interrupt status failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check overflow interrupt status %s.\n", (enable == BMM150_BOOL_TRUE) ? "true" : "false");
    
    /* high threshold z */
    res = bmm150_get_interrupt_status(&gs_handle, BMM150_INTERRUPT_STATUS_HIGH_THRESHOLD_Z, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get interrupt status failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check high threshold z interrupt status %s.\n", (enable == BMM150_BOOL_TRUE) ? "true" : "false");
    
    /* high threshold y */
    res = bmm150_get_interrupt_status(&gs_handle, BMM150_INTERRUPT_STATUS_HIGH_THRESHOLD_Y, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get interrupt status failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check high threshold y interrupt status %s.\n", (enable == BMM150_BOOL_TRUE) ? "true" : "false");
    
    /* high threshold x */
    res = bmm150_get_interrupt_status(&gs_handle, BMM150_INTERRUPT_STATUS_HIGH_THRESHOLD_X, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get interrupt status failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check high threshold x interrupt status %s.\n", (enable == BMM150_BOOL_TRUE) ? "true" : "false");
    
    /* low threshold z */
    res = bmm150_get_interrupt_status(&gs_handle, BMM150_INTERRUPT_STATUS_LOW_THRESHOLD_Z, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get interrupt status failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check low threshold z interrupt status %s.\n", (enable == BMM150_BOOL_TRUE) ? "true" : "false");
    
    /* low threshold y */
    res = bmm150_get_interrupt_status(&gs_handle, BMM150_INTERRUPT_STATUS_LOW_THRESHOLD_Y, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get interrupt status failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check low threshold y interrupt status %s.\n", (enable == BMM150_BOOL_TRUE) ? "true" : "false");
    
    /* low threshold x */
    res = bmm150_get_interrupt_status(&gs_handle, BMM150_INTERRUPT_STATUS_LOW_THRESHOLD_X, &enable);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: get interrupt status failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check low threshold x interrupt status %s.\n", (enable == BMM150_BOOL_TRUE) ? "true" : "false");
    
    /* bmm150_soft_reset test */
    bmm150_interface_debug_print("bmm150: bmm150_soft_reset test.\n");
    
    /* soft reset */
    res = bmm150_soft_reset(&gs_handle);
    if (res != 0)
    {
        bmm150_interface_debug_print("bmm150: soft reset failed.\n");
        (void)bmm150_deinit(&gs_handle);
        
        return 1;
    }
    bmm150_interface_debug_print("bmm150: check soft reset %s.\n", (res == 0) ? "ok" : "error");
    
    /* finish register test */
    bmm150_interface_debug_print("bmm150: finish register test.\n");
    (void)bmm150_deinit(&gs_handle);
    
    return 0;
}
