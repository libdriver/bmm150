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
 * @file      driver_bmm150.c
 * @brief     driver bmm150 source file
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

#include "driver_bmm150.h"

/**
 * @brief chip register definition
 */
#define CHIP_NAME                 "Bosch BMM150"        /**< chip name */
#define MANUFACTURER_NAME         "Bosch"               /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        1.62f                 /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        3.6f                  /**< chip max supply voltage */
#define MAX_CURRENT               20.0f                 /**< chip max current */
#define TEMPERATURE_MIN           -40.0f                /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f                 /**< chip max operating temperature */
#define DRIVER_VERSION            1000                  /**< driver version */

/**
 * @brief chip register definition
 */
#define BMM150_REG_CHIP_ID                 0x40        /**< chip id register */
#define BMM150_REG_DATA_X_LSB              0x42        /**< data x lsb register */
#define BMM150_REG_DATA_X_MSB              0x43        /**< data x msb register */
#define BMM150_REG_DATA_Y_LSB              0x44        /**< data y lsb register */
#define BMM150_REG_DATA_Y_MSB              0x45        /**< data y msb register */
#define BMM150_REG_DATA_Z_LSB              0x46        /**< data z lsb register */
#define BMM150_REG_DATA_Z_MSB              0x47        /**< data z msb register */
#define BMM150_REG_RHALL_LSB               0x48        /**< rhall lsb register */
#define BMM150_REG_RHALL_MSB               0x49        /**< rhall msb register */
#define BMM150_REG_INTERRUPT_STATUS        0x4A        /**< interrupt status register */
#define BMM150_REG_CONFIG_0                0x4B        /**< config0 register */
#define BMM150_REG_CONFIG_1                0x4C        /**< config1 register */
#define BMM150_REG_CONFIG_2                0x4D        /**< config2 register */
#define BMM150_REG_CONFIG_3                0x4E        /**< config3 register */
#define BMM150_REG_LOW_THRESHOLD           0x4F        /**< low threshold register */
#define BMM150_REG_HIGH_THRESHOLD          0x50        /**< high threshold register */
#define BMM150_REG_REPXY                   0x51        /**< repxy register */
#define BMM150_REG_REPZ                    0x52        /**< repz register */

/**
 * @brief chip trim extended register definition
 */
#define BMM150_REG_DIG_X1                  0x5D        /**< dig x1 register */
#define BMM150_REG_DIG_Y1                  0x5E        /**< dig y1 register */
#define BMM150_REG_DIG_Z4_LSB              0x62        /**< dig z4 lsb register */
#define BMM150_REG_DIG_Z4_MSB              0x63        /**< dig z4 msb register */
#define BMM150_REG_DIG_X2                  0x64        /**< dig x2 register */
#define BMM150_REG_DIG_Y2                  0x65        /**< dig y2 register */
#define BMM150_REG_DIG_Z2_LSB              0x68        /**< dig z2 lsb register */
#define BMM150_REG_DIG_Z2_MSB              0x69        /**< dig z2 msb register */
#define BMM150_REG_DIG_Z1_LSB              0x6A        /**< dig z1 lsb register */
#define BMM150_REG_DIG_Z1_MSB              0x6B        /**< dig z1 msb register */
#define BMM150_REG_DIG_XYZ1_LSB            0x6C        /**< dig xyz1 lsb register */
#define BMM150_REG_DIG_XYZ1_MSB            0x6D        /**< dig xyz1 msb register */
#define BMM150_REG_DIG_Z3_LSB              0x6E        /**< dig z3 lsb register */
#define BMM150_REG_DIG_Z3_MSB              0x6F        /**< dig z3 msb register */
#define BMM150_REG_DIG_XY2                 0x70        /**< dig xy2 register */
#define BMM150_REG_DIG_XY1                 0x71        /**< dig xy1 register */

/**
 * @brief      iic or spi interface read bytes
 * @param[in]  *handle pointer to a bmm150 handle structure
 * @param[in]  reg iic register address
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len length of data
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_bmm150_iic_spi_read(bmm150_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (handle->iic_spi == (uint8_t)BMM150_INTERFACE_IIC)                /* iic interface */
    {
        if (handle->iic_read(handle->iic_addr, reg, buf, len) != 0)      /* read data */
        {
            return 1;                                                    /* return error */
        }
        
        return 0;                                                        /* success return 0 */
    }
    else                                                                 /* spi interface */
    {
        reg |= 1 << 7;                                                   /* flag read */
        if (handle->spi_read(reg, buf, len) != 0)                        /* read data */
        {
            return 1;                                                    /* return error */
        }
        
        return 0;                                                        /* success return 0 */
    }
}

/**
 * @brief     iic or spi interface write bytes
 * @param[in] *handle pointer to a bmm150 handle structure
 * @param[in] reg iic register address
 * @param[in] *buf pointer to a data buffer
 * @param[in] len length of data
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_bmm150_iic_spi_write(bmm150_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (handle->iic_spi == (uint8_t)BMM150_INTERFACE_IIC)                 /* iic interface */
    {
        if (handle->iic_write(handle->iic_addr, reg, buf, len) != 0)      /* write data */
        {
            return 1;                                                     /* return error */
        }
        
        return 0;                                                         /* success return 0 */
    }
    else                                                                  /* spi interface */
    {
        reg &= ~(1 << 7);                                                 /* flag write */
        if (handle->spi_write(reg, buf, len) != 0)                        /* write data */
        {
            return 1;                                                     /* return error */
        }
        
        return 0;                                                         /* success return 0 */
    }
}

/**
 * @brief     load trim
 * @param[in] *handle pointer to a bmm150 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 load trim failed
 * @note      none
 */
static uint8_t a_bmm150_load_trim(bmm150_handle_t *handle)
{
    uint8_t res;
    uint8_t trim_x1y1[2];
    uint8_t trim_xyz_data[4];
    uint8_t trim_xy1xy2[10];
    uint16_t temp_msb = 0;

    res = a_bmm150_iic_spi_read(handle, BMM150_REG_DIG_X1, trim_x1y1, 2);                /* read part 0 */
    if (res != 0)                                                                        /* check the result */
    {
        handle->debug_print("bmm150: read dig x1 failed.\n");                            /* read dig x1 failed */
       
        return 1;                                                                        /* return error */
    }
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_DIG_Z4_LSB, trim_xyz_data, 4);        /* read part 1 */
    if (res != 0)                                                                        /* check the result */
    {
        handle->debug_print("bmm150: read dig z4 failed.\n");                            /* read dig z4 failed */
       
        return 1;                                                                        /* return error */
    }
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_DIG_Z2_LSB, trim_xy1xy2, 10);         /* read part 2 */
    if (res != 0)                                                                        /* check the result */
    {
        handle->debug_print("bmm150: read dig z2 failed.\n");                            /* read dig z2 failed */
       
        return 1;                                                                        /* return error */
    }
    handle->dig_x1 = (int8_t)trim_x1y1[0];                                               /* set x1 */
    handle->dig_y1 = (int8_t)trim_x1y1[1];                                               /* set y1 */
    handle->dig_x2 = (int8_t)trim_xyz_data[2];                                           /* set x2 */
    handle->dig_y2 = (int8_t)trim_xyz_data[3];                                           /* set y2 */
    temp_msb = ((uint16_t)trim_xy1xy2[3]) << 8;                                          /* set msb */
    handle->dig_z1 = (uint16_t)(temp_msb | trim_xy1xy2[2]);                              /* set z1 */
    temp_msb = ((uint16_t)trim_xy1xy2[1]) << 8;                                          /* set msb */
    handle->dig_z2 = (int16_t)(temp_msb | trim_xy1xy2[0]);                               /* set z2 */
    temp_msb = ((uint16_t)trim_xy1xy2[7]) << 8;                                          /* set msb */
    handle->dig_z3 = (int16_t)(temp_msb | trim_xy1xy2[6]);                               /* set z3 */
    temp_msb = ((uint16_t)trim_xyz_data[1]) << 8;                                        /* set msb */
    handle->dig_z4 = (int16_t)(temp_msb | trim_xyz_data[0]);                             /* set z4 */
    handle->dig_xy1 = trim_xy1xy2[9];                                                    /* set xy1 */
    handle->dig_xy2 = (int8_t)trim_xy1xy2[8];                                            /* set xy2 */
    temp_msb = ((uint16_t)(trim_xy1xy2[5] & 0x7F)) << 8;                                 /* set msb */
    handle->dig_xyz1 = (uint16_t)(temp_msb | trim_xy1xy2[4]);                            /* set xyz1 */
    
    return 0;                                                                            /* success return 0 */
}

/**
 * @brief     compensate x
 * @param[in] *handle pointer to a bmm150 handle structure
 * @param[in] mag_data_x mag data x
 * @param[in] data_rhall data rhall
 * @return    calculated result
 * @note      none
 */
static float a_bmm150_compensate_x(bmm150_handle_t *handle, int16_t mag_data_x, uint16_t data_rhall)
{
    float retval;
    float process_comp_x0;
    float process_comp_x1;
    float process_comp_x2;
    float process_comp_x3;
    float process_comp_x4;
    
    process_comp_x0 = (((float)handle->dig_xyz1) * 16384.0f / (float)data_rhall);                /* calculate process comp x0 */
    retval = (process_comp_x0 - 16384.0f);                                                       /* calculate retval */
    process_comp_x1 = ((float)handle->dig_xy2) * (retval * retval / 268435456.0f);               /* calculate process comp x1 */
    process_comp_x2 = process_comp_x1 + retval * ((float)handle->dig_xy1) / 16384.0f;            /* calculate process comp x2 */
    process_comp_x3 = ((float)handle->dig_x2) + 160.0f;                                          /* calculate process comp x3 */
    process_comp_x4 = (float)mag_data_x * ((process_comp_x2 + 256.0f) * process_comp_x3);        /* calculate process comp x4 */
    retval = ((process_comp_x4 / 8192.0f) + (((float)handle->dig_x1) * 8.0f)) / 16.0f;           /* calculate the final result */
    
    return retval;                                                                               /* return the final result */
}

/**
 * @brief     compensate y
 * @param[in] *handle pointer to a bmm150 handle structure
 * @param[in] mag_data_y mag data y
 * @param[in] data_rhall data rhall
 * @return    calculated result
 * @note      none
 */
static float a_bmm150_compensate_y(bmm150_handle_t *handle, int16_t mag_data_y, uint16_t data_rhall)
{
    float retval;
    float process_comp_y0;
    float process_comp_y1;
    float process_comp_y2;
    float process_comp_y3;
    float process_comp_y4;
    
    process_comp_y0 = ((float)handle->dig_xyz1) * 16384.0f / (float)data_rhall;                    /* calculate process comp y0 */
    retval = process_comp_y0 - 16384.0f;                                                           /* calculate retval */
    process_comp_y1 = ((float)handle->dig_xy2) * (retval * retval / 268435456.0f);                 /* calculate process comp y1 */
    process_comp_y2 = process_comp_y1 + retval * ((float)handle->dig_xy1) / 16384.0f;              /* calculate process comp y2 */
    process_comp_y3 = ((float)handle->dig_y2) + 160.0f;                                            /* calculate process comp y3 */
    process_comp_y4 = (float)mag_data_y * (((process_comp_y2) + 256.0f) * process_comp_y3);        /* calculate process comp y4 */
    retval = ((process_comp_y4 / 8192.0f) + (((float)handle->dig_y1) * 8.0f)) / 16.0f;             /* calculate the final result */
    
    return retval;                                                                                 /* return the final result */
}

/**
 * @brief     compensate z
 * @param[in] *handle pointer to a bmm150 handle structure
 * @param[in] mag_data_z mag data z
 * @param[in] data_rhall data rhall
 * @return    calculated result
 * @note      none
 */
static float a_bmm150_compensate_z(bmm150_handle_t *handle, int16_t mag_data_z, uint16_t data_rhall)
{
    float retval;
    float process_comp_z0;
    float process_comp_z1;
    float process_comp_z2;
    float process_comp_z3;
    float process_comp_z4;
    float process_comp_z5;
    
    process_comp_z0 = ((float)mag_data_z) - ((float)handle->dig_z4);                   /* calculate process comp z0 */
    process_comp_z1 = ((float)data_rhall) - ((float)handle->dig_xyz1);                 /* calculate process comp z1 */
    process_comp_z2 = (((float)handle->dig_z3) * process_comp_z1);                     /* calculate process comp z2 */
    process_comp_z3 = ((float)handle->dig_z1) * ((float)data_rhall) / 32768.0f;        /* calculate process comp z3 */
    process_comp_z4 = ((float)handle->dig_z2) + process_comp_z3;                       /* calculate process comp z4 */
    process_comp_z5 = (process_comp_z0 * 131072.0f) - process_comp_z2;                 /* calculate process comp z5 */
    retval = (process_comp_z5 / ((process_comp_z4) * 4.0f)) / 16.0f;                   /* calculate the final result */
    
    return retval;                                                                     /* return the final result */
}

/**
 * @brief     close the chip
 * @param[in] *handle pointer to a bmm150 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 close failed
 * @note      none
 */
static uint8_t a_bmm150_close(bmm150_handle_t *handle)
{
    uint8_t prev;
    
    if (a_bmm150_iic_spi_read(handle, BMM150_REG_CONFIG_0, &prev, 1) != 0)         /* read config */
    {
        handle->debug_print("bmm150: read config 0 failed.\n");                    /* read config 0 failed */
       
        return 1;                                                                  /* return error */
    }
    prev &= ~(1 << 0);                                                             /* clear settings */
    if (a_bmm150_iic_spi_write(handle, BMM150_REG_CONFIG_0, &prev, 1) != 0)        /* write config */
    {
        handle->debug_print("bmm150: write config 0 failed.\n");                   /* write config 0 failed */
       
        return 1;                                                                  /* return error */
    }
    
    if (handle->iic_spi == BMM150_INTERFACE_IIC)                                   /* iic interface */
    {
        if (handle->iic_deinit() != 0)                                             /* iic deinit */
        {
            handle->debug_print("bmm150: iic deinit failed.\n");                   /* iic deinit failed */
       
            return 1;                                                              /* return error */
        }
        
        return 0;                                                                  /* success return 0 */
    }
    else                                                                           /* spi interface */
    {
        if (handle->spi_deinit() != 0)                                             /* spi deinit */
        {
            handle->debug_print("bmm150: spi deinit failed.\n");                   /* spi deinit failed */
       
            return 1;                                                              /* return error */
        }
        
        return 0;                                                                  /* success return 0 */
    }
}

/**
 * @brief     set the chip interface
 * @param[in] *handle pointer to a bmm150 handle structure
 * @param[in] interface chip interface
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t bmm150_set_interface(bmm150_handle_t *handle, bmm150_interface_t interface)
{
    if (handle == NULL)                          /* check handle */
    {
        return 2;                                /* return error */
    }
    
    handle->iic_spi = (uint8_t)interface;        /* set interface */
    
    return 0;                                    /* success return 0 */
}

/**
 * @brief      get the chip interface
 * @param[in]  *handle pointer to a bmm150 handle structure
 * @param[out] *interface pointer to a chip interface buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t bmm150_get_interface(bmm150_handle_t *handle, bmm150_interface_t *interface)
{
    if (handle == NULL)                                        /* check handle */
    {
        return 2;                                              /* return error */
    }
    
    *interface = (bmm150_interface_t)(handle->iic_spi);        /* get interface */
    
    return 0;                                                  /* success return 0 */
}

/**
 * @brief     set the iic address pin
 * @param[in] *handle pointer to a bmm150 handle structure
 * @param[in] addr_pin address pin
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t bmm150_set_addr_pin(bmm150_handle_t *handle, bmm150_address_t addr_pin)
{
    if (handle == NULL)                        /* check handle */
    {
        return 2;                              /* return error */
    }
    
    handle->iic_addr = (uint8_t)addr_pin;      /* set pin */
    
    return 0;                                  /* success return 0 */
}

/**
 * @brief      get the iic address pin
 * @param[in]  *handle pointer to a bmm150 handle structure
 * @param[out] *addr_pin pointer to an address pin buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t bmm150_get_addr_pin(bmm150_handle_t *handle, bmm150_address_t *addr_pin)
{
    if (handle == NULL)                                      /* check handle */
    {
        return 2;                                            /* return error */
    }
    
    *addr_pin = (bmm150_address_t)(handle->iic_addr);        /* get pin */
    
    return 0;                                                /* success return 0 */
}

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
uint8_t bmm150_get_self_test_x(bmm150_handle_t *handle, bmm150_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_DATA_X_LSB, &prev, 1);        /* read config */
    if (res != 0)                                                                /* check the result */
    {
        handle->debug_print("bmm150: read data x failed.\n");                    /* read data x failed */
       
        return 1;                                                                /* return error */
    }
    *enable = (bmm150_bool_t)((prev >> 0) & 0x01);                               /* set bool */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t bmm150_get_self_test_y(bmm150_handle_t *handle, bmm150_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_DATA_Y_LSB, &prev, 1);        /* read config */
    if (res != 0)                                                                /* check the result */
    {
        handle->debug_print("bmm150: read data y failed.\n");                    /* read data y failed */
       
        return 1;                                                                /* return error */
    }
    *enable = (bmm150_bool_t)((prev >> 0) & 0x01);                               /* set bool */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t bmm150_get_self_test_z(bmm150_handle_t *handle, bmm150_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_DATA_Z_LSB, &prev, 1);        /* read config */
    if (res != 0)                                                                /* check the result */
    {
        handle->debug_print("bmm150: read data z failed.\n");                    /* read data z failed */
       
        return 1;                                                                /* return error */
    }
    *enable = (bmm150_bool_t)((prev >> 0) & 0x01);                               /* set bool */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t bmm150_get_data_ready_status(bmm150_handle_t *handle, bmm150_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_RHALL_LSB, &prev, 1);        /* read config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: read rhall failed.\n");                    /* read rhall failed */
       
        return 1;                                                               /* return error */
    }
    *enable = (bmm150_bool_t)((prev >> 0) & 0x01);                              /* set bool */
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t bmm150_get_interrupt_status(bmm150_handle_t *handle, bmm150_interrupt_status_t status, bmm150_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                /* check handle */
    {
        return 2;                                                                      /* return error */
    }
    if (handle->inited != 1)                                                           /* check handle initialization */
    {
        return 3;                                                                      /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_INTERRUPT_STATUS, &prev, 1);        /* read config */
    if (res != 0)                                                                      /* check the result */
    {
        handle->debug_print("bmm150: read interrupt status failed.\n");                /* read interrupt status failed */
       
        return 1;                                                                      /* return error */
    }
    *enable = (bmm150_bool_t)((prev >> (uint8_t)status) & 0x01);                       /* set bool */
    
    return 0;                                                                          /* success return 0 */
}

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
uint8_t bmm150_soft_reset(bmm150_handle_t *handle)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_CONFIG_0, &prev, 1);         /* read config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: read config 0 failed.\n");                 /* read config 0 failed */
       
        return 1;                                                               /* return error */
    }
    prev &= ~(1 << 1);                                                          /* clear settings */
    prev |= 1 << 1;                                                             /* set bool */
    prev &= ~(1 << 7);                                                          /* clear settings */
    prev |= 1 << 7;                                                             /* set bool */
    res = a_bmm150_iic_spi_write(handle, BMM150_REG_CONFIG_0, &prev, 1);        /* write config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: write config 0 failed.\n");                /* write config 0 failed */
       
        return 1;                                                               /* return error */
    }
    handle->delay_ms(5);                                                        /* delay 5ms */
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t bmm150_set_power_on(bmm150_handle_t *handle, bmm150_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_CONFIG_0, &prev, 1);         /* read config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: read config 0 failed.\n");                 /* read config 0 failed */
       
        return 1;                                                               /* return error */
    }
    prev &= ~(1 << 0);                                                          /* clear settings */
    prev |= enable << 0;                                                        /* set bool */
    res = a_bmm150_iic_spi_write(handle, BMM150_REG_CONFIG_0, &prev, 1);        /* write config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: write config 0 failed.\n");                /* write config 0 failed */
       
        return 1;                                                               /* return error */
    }
    handle->delay_ms(5);                                                        /* delay 5ms */
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t bmm150_get_power_on(bmm150_handle_t *handle, bmm150_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_CONFIG_0, &prev, 1);         /* read config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: read config 0 failed.\n");                 /* read config 0 failed */
       
        return 1;                                                               /* return error */
    }
    *enable = (bmm150_bool_t)((prev >> 0) & 0x01);                              /* set bool */
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t bmm150_set_spi_wire(bmm150_handle_t *handle, bmm150_spi_wire_t wire)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_CONFIG_0, &prev, 1);         /* read config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: read config 0 failed.\n");                 /* read config 0 failed */
       
        return 1;                                                               /* return error */
    }
    prev &= ~(1 << 2);                                                          /* clear settings */
    prev |= wire << 2;                                                          /* set wire */
    res = a_bmm150_iic_spi_write(handle, BMM150_REG_CONFIG_0, &prev, 1);        /* write config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: write config 0 failed.\n");                /* write config 0 failed */
       
        return 1;                                                               /* return error */
    }
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t bmm150_get_spi_wire(bmm150_handle_t *handle, bmm150_spi_wire_t *wire)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_CONFIG_0, &prev, 1);         /* read config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: read config 0 failed.\n");                 /* read config 0 failed */
       
        return 1;                                                               /* return error */
    }
    *wire = (bmm150_spi_wire_t)((prev >> 2) & 0x01);                            /* set wire */
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t bmm150_set_advanced_self_test(bmm150_handle_t *handle, bmm150_advanced_self_test_t test)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_CONFIG_1, &prev, 1);         /* read config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: read config 1 failed.\n");                 /* read config 1 failed */
       
        return 1;                                                               /* return error */
    }
    prev &= ~(3 << 6);                                                          /* clear settings */
    prev |= test << 6;                                                          /* set test */
    res = a_bmm150_iic_spi_write(handle, BMM150_REG_CONFIG_1, &prev, 1);        /* write config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: write config 1 failed.\n");                /* write config 1 failed */
       
        return 1;                                                               /* return error */
    }
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t bmm150_get_advanced_self_test(bmm150_handle_t *handle, bmm150_advanced_self_test_t *test)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_CONFIG_1, &prev, 1);         /* read config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: read config 1 failed.\n");                 /* read config 1 failed */
       
        return 1;                                                               /* return error */
    }
    *test = (bmm150_advanced_self_test_t)((prev >> 6) & 0x03);                  /* set test */
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t bmm150_set_data_rate(bmm150_handle_t *handle, bmm150_data_rate_t rate)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_CONFIG_1, &prev, 1);         /* read config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: read config 1 failed.\n");                 /* read config 1 failed */
       
        return 1;                                                               /* return error */
    }
    prev &= ~(7 << 3);                                                          /* clear settings */
    prev |= rate << 3;                                                          /* set rate */
    res = a_bmm150_iic_spi_write(handle, BMM150_REG_CONFIG_1, &prev, 1);        /* write config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: write config 1 failed.\n");                /* write config 1 failed */
       
        return 1;                                                               /* return error */
    }
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t bmm150_get_data_rate(bmm150_handle_t *handle, bmm150_data_rate_t *rate)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_CONFIG_1, &prev, 1);         /* read config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: read config 1 failed.\n");                 /* read config 1 failed */
       
        return 1;                                                               /* return error */
    }
    *rate = (bmm150_data_rate_t)((prev >> 3) & 0x07);                           /* set rate */
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t bmm150_set_mode(bmm150_handle_t *handle, bmm150_mode_t mode)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_CONFIG_1, &prev, 1);         /* read config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: read config 1 failed.\n");                 /* read config 1 failed */
       
        return 1;                                                               /* return error */
    }
    prev &= ~(3 << 1);                                                          /* clear settings */
    prev |= mode << 1;                                                          /* set mode */
    res = a_bmm150_iic_spi_write(handle, BMM150_REG_CONFIG_1, &prev, 1);        /* write config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: write config 1 failed.\n");                /* write config 1 failed */
       
        return 1;                                                               /* return error */
    }
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t bmm150_get_mode(bmm150_handle_t *handle, bmm150_mode_t *mode)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_CONFIG_1, &prev, 1);         /* read config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: read config 1 failed.\n");                 /* read config 1 failed */
       
        return 1;                                                               /* return error */
    }
    *mode = (bmm150_mode_t)((prev >> 1) & 0x03);                                /* set mode */
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t bmm150_set_self_test(bmm150_handle_t *handle, bmm150_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_CONFIG_1, &prev, 1);         /* read config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: read config 1 failed.\n");                 /* read config 1 failed */
       
        return 1;                                                               /* return error */
    }
    prev &= ~(1 << 0);                                                          /* clear settings */
    prev |= enable << 0;                                                        /* set bool */
    res = a_bmm150_iic_spi_write(handle, BMM150_REG_CONFIG_1, &prev, 1);        /* write config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: write config 1 failed.\n");                /* write config 1 failed */
       
        return 1;                                                               /* return error */
    }
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t bmm150_get_self_test(bmm150_handle_t *handle, bmm150_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_CONFIG_1, &prev, 1);         /* read config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: read config 1 failed.\n");                 /* read config 1 failed */
       
        return 1;                                                               /* return error */
    }
    *enable = (bmm150_bool_t)((prev >> 0) & 0x01);                              /* set bool */
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t bmm150_set_interrupt(bmm150_handle_t *handle, bmm150_interrupt_status_t status, bmm150_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_CONFIG_2, &prev, 1);         /* read config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: read config 2 failed.\n");                 /* read config 2 failed */
       
        return 1;                                                               /* return error */
    }
    prev &= ~(1 << (uint8_t)status);                                            /* clear settings */
    if (status >= (uint8_t)BMM150_INTERRUPT_STATUS_OVERFLOW)                    /* index >= 6 */
    {
        prev |= enable << (uint8_t)status;                                      /* set bool */
    }
    else                                                                        /* index < 6 */
    {
        prev |= (uint8_t)(!enable) << (uint8_t)status;                          /* set bool */
    }
    res = a_bmm150_iic_spi_write(handle, BMM150_REG_CONFIG_2, &prev, 1);        /* write config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: write config 2 failed.\n");                /* write config 2 failed */
       
        return 1;                                                               /* return error */
    }
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t bmm150_get_interrupt(bmm150_handle_t *handle, bmm150_interrupt_status_t status, bmm150_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_CONFIG_2, &prev, 1);         /* read config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: read config 2 failed.\n");                 /* read config 2 failed */
       
        return 1;                                                               /* return error */
    }
    if (status >= (uint8_t)BMM150_INTERRUPT_STATUS_OVERFLOW)                    /* index >= 6 */
    {
        *enable = (bmm150_bool_t)((prev >> (uint8_t)(status)) & 0x01);          /* set bool */
    }
    else                                                                        /* index < 6 */
    {
        *enable = (bmm150_bool_t)(!((prev >> (uint8_t)(status)) & 0x01));       /* set bool */
    }
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t bmm150_set_data_ready_pin(bmm150_handle_t *handle, bmm150_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_CONFIG_3, &prev, 1);         /* read config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: read config 3 failed.\n");                 /* read config 3 failed */
       
        return 1;                                                               /* return error */
    }
    prev &= ~(1 << 7);                                                          /* clear settings */
    prev |= enable << 7;                                                        /* set bool */
    res = a_bmm150_iic_spi_write(handle, BMM150_REG_CONFIG_3, &prev, 1);        /* write config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: write config 3 failed.\n");                /* write config 3 failed */
       
        return 1;                                                               /* return error */
    }
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t bmm150_get_data_ready_pin(bmm150_handle_t *handle, bmm150_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_CONFIG_3, &prev, 1);         /* read config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: read config 3 failed.\n");                 /* read config 3 failed */
       
        return 1;                                                               /* return error */
    }
    *enable = (bmm150_bool_t)((prev >> 7) & 0x01);                              /* set bool */
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t bmm150_set_interrupt_pin(bmm150_handle_t *handle, bmm150_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_CONFIG_3, &prev, 1);         /* read config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: read config 3 failed.\n");                 /* read config 3 failed */
       
        return 1;                                                               /* return error */
    }
    prev &= ~(1 << 6);                                                          /* clear settings */
    prev |= enable << 6;                                                        /* set bool */
    res = a_bmm150_iic_spi_write(handle, BMM150_REG_CONFIG_3, &prev, 1);        /* write config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: write config 3 failed.\n");                /* write config 3 failed */
       
        return 1;                                                               /* return error */
    }
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t bmm150_get_interrupt_pin(bmm150_handle_t *handle, bmm150_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_CONFIG_3, &prev, 1);         /* read config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: read config 3 failed.\n");                 /* read config 3 failed */
       
        return 1;                                                               /* return error */
    }
    *enable = (bmm150_bool_t)((prev >> 6) & 0x01);                              /* set bool */
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t bmm150_set_channel_z(bmm150_handle_t *handle, bmm150_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_CONFIG_3, &prev, 1);         /* read config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: read config 3 failed.\n");                 /* read config 3 failed */
       
        return 1;                                                               /* return error */
    }
    prev &= ~(1 << 5);                                                          /* clear settings */
    prev |= (uint8_t)(!enable) << 5;                                            /* set bool */
    res = a_bmm150_iic_spi_write(handle, BMM150_REG_CONFIG_3, &prev, 1);        /* write config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: write config 3 failed.\n");                /* write config 3 failed */
       
        return 1;                                                               /* return error */
    }
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t bmm150_get_channel_z(bmm150_handle_t *handle, bmm150_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_CONFIG_3, &prev, 1);         /* read config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: read config 3 failed.\n");                 /* read config 3 failed */
       
        return 1;                                                               /* return error */
    }
    *enable = (bmm150_bool_t)(!((prev >> 5) & 0x01));                           /* set bool */
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t bmm150_set_channel_y(bmm150_handle_t *handle, bmm150_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_CONFIG_3, &prev, 1);         /* read config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: read config 3 failed.\n");                 /* read config 3 failed */
       
        return 1;                                                               /* return error */
    }
    prev &= ~(1 << 4);                                                          /* clear settings */
    prev |= (uint8_t)(!enable) << 4;                                            /* set bool */
    res = a_bmm150_iic_spi_write(handle, BMM150_REG_CONFIG_3, &prev, 1);        /* write config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: write config 3 failed.\n");                /* write config 3 failed */
       
        return 1;                                                               /* return error */
    }
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t bmm150_get_channel_y(bmm150_handle_t *handle, bmm150_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_CONFIG_3, &prev, 1);         /* read config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: read config 3 failed.\n");                 /* read config 3 failed */
       
        return 1;                                                               /* return error */
    }
    *enable = (bmm150_bool_t)(!((prev >> 4) & 0x01));                           /* set bool */
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t bmm150_set_channel_x(bmm150_handle_t *handle, bmm150_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_CONFIG_3, &prev, 1);         /* read config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: read config 3 failed.\n");                 /* read config 3 failed */
       
        return 1;                                                               /* return error */
    }
    prev &= ~(1 << 3);                                                          /* clear settings */
    prev |= (uint8_t)(!enable) << 3;                                            /* set bool */
    res = a_bmm150_iic_spi_write(handle, BMM150_REG_CONFIG_3, &prev, 1);        /* write config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: write config 3 failed.\n");                /* write config 3 failed */
       
        return 1;                                                               /* return error */
    }
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t bmm150_get_channel_x(bmm150_handle_t *handle, bmm150_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_CONFIG_3, &prev, 1);         /* read config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: read config 3 failed.\n");                 /* read config 3 failed */
       
        return 1;                                                               /* return error */
    }
    *enable = (bmm150_bool_t)(!((prev >> 3) & 0x01));                           /* set bool */
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t bmm150_set_data_ready_pin_polarity(bmm150_handle_t *handle, bmm150_data_ready_pin_polarity_t polarity)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_CONFIG_3, &prev, 1);         /* read config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: read config 3 failed.\n");                 /* read config 3 failed */
       
        return 1;                                                               /* return error */
    }
    prev &= ~(1 << 2);                                                          /* clear settings */
    prev |= polarity << 2;                                                      /* set polarity */
    res = a_bmm150_iic_spi_write(handle, BMM150_REG_CONFIG_3, &prev, 1);        /* write config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: write config 3 failed.\n");                /* write config 3 failed */
       
        return 1;                                                               /* return error */
    }
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t bmm150_get_data_ready_pin_polarity(bmm150_handle_t *handle, bmm150_data_ready_pin_polarity_t *polarity)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_CONFIG_3, &prev, 1);         /* read config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: read config 3 failed.\n");                 /* read config 3 failed */
       
        return 1;                                                               /* return error */
    }
    *polarity = (bmm150_data_ready_pin_polarity_t)((prev >> 2) & 0x01);         /* set polarity */
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t bmm150_set_interrupt_latch(bmm150_handle_t *handle, bmm150_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_CONFIG_3, &prev, 1);         /* read config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: read config 3 failed.\n");                 /* read config 3 failed */
       
        return 1;                                                               /* return error */
    }
    prev &= ~(1 << 1);                                                          /* clear settings */
    prev |= enable << 1;                                                        /* set bool */
    res = a_bmm150_iic_spi_write(handle, BMM150_REG_CONFIG_3, &prev, 1);        /* write config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: write config 3 failed.\n");                /* write config 3 failed */
       
        return 1;                                                               /* return error */
    }
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t bmm150_get_interrupt_latch(bmm150_handle_t *handle, bmm150_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_CONFIG_3, &prev, 1);         /* read config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: read config 3 failed.\n");                 /* read config 3 failed */
       
        return 1;                                                               /* return error */
    }
    *enable = (bmm150_bool_t)((prev >> 1) & 0x01);                              /* set bool */
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t bmm150_set_interrupt_pin_polarity(bmm150_handle_t *handle, bmm150_interrupt_pin_polarity_t polarity)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_CONFIG_3, &prev, 1);         /* read config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: read config 3 failed.\n");                 /* read config 3 failed */
       
        return 1;                                                               /* return error */
    }
    prev &= ~(1 << 0);                                                          /* clear settings */
    prev |= polarity << 0;                                                      /* set polarity */
    res = a_bmm150_iic_spi_write(handle, BMM150_REG_CONFIG_3, &prev, 1);        /* write config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: write config 3 failed.\n");                /* write config 3 failed */
       
        return 1;                                                               /* return error */
    }
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t bmm150_get_interrupt_pin_polarity(bmm150_handle_t *handle, bmm150_interrupt_pin_polarity_t *polarity)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_CONFIG_3, &prev, 1);         /* read config */
    if (res != 0)                                                               /* check the result */
    {
        handle->debug_print("bmm150: read config 3 failed.\n");                 /* read config 3 failed */
       
        return 1;                                                               /* return error */
    }
    *polarity = (bmm150_interrupt_pin_polarity_t)((prev >> 0) & 0x01);          /* set polarity */
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t bmm150_set_low_threshold(bmm150_handle_t *handle, int8_t threshold)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                              /* check handle */
    {
        return 2;                                                                    /* return error */
    }
    if (handle->inited != 1)                                                         /* check handle initialization */
    {
        return 3;                                                                    /* return error */
    }
    
    prev = (uint8_t)threshold;                                                       /* set threshold */
    res = a_bmm150_iic_spi_write(handle, BMM150_REG_LOW_THRESHOLD, &prev, 1);        /* write config */
    if (res != 0)                                                                    /* check the result */
    {
        handle->debug_print("bmm150: write low threshold failed.\n");                /* write low threshold failed */
       
        return 1;                                                                    /* return error */
    }
    
    return 0;                                                                        /* success return 0 */
}

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
uint8_t bmm150_get_low_threshold(bmm150_handle_t *handle, int8_t *threshold)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                             /* check handle */
    {
        return 2;                                                                   /* return error */
    }
    if (handle->inited != 1)                                                        /* check handle initialization */
    {
        return 3;                                                                   /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_LOW_THRESHOLD, &prev, 1);        /* read config */
    if (res != 0)                                                                   /* check the result */
    {
        handle->debug_print("bmm150: read low threshold failed.\n");                /* read low threshold failed */
       
        return 1;                                                                   /* return error */
    }
    *threshold = (int8_t)(prev);                                                    /* set threshold */
    
    return 0;                                                                       /* success return 0 */
}

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
uint8_t bmm150_set_high_threshold(bmm150_handle_t *handle, int8_t threshold)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                              /* check handle */
    {
        return 2;                                                                    /* return error */
    }
    if (handle->inited != 1)                                                         /* check handle initialization */
    {
        return 3;                                                                    /* return error */
    }
    
    prev = (uint8_t)threshold;                                                       /* set threshold */
    res = a_bmm150_iic_spi_write(handle, BMM150_REG_HIGH_THRESHOLD, &prev, 1);       /* write config */
    if (res != 0)                                                                    /* check the result */
    {
        handle->debug_print("bmm150: write high threshold failed.\n");               /* write high threshold failed */
       
        return 1;                                                                    /* return error */
    }
    
    return 0;                                                                        /* success return 0 */
}

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
uint8_t bmm150_get_high_threshold(bmm150_handle_t *handle, int8_t *threshold)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                             /* check handle */
    {
        return 2;                                                                   /* return error */
    }
    if (handle->inited != 1)                                                        /* check handle initialization */
    {
        return 3;                                                                   /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_HIGH_THRESHOLD, &prev, 1);       /* read config */
    if (res != 0)                                                                   /* check the result */
    {
        handle->debug_print("bmm150: read high threshold failed.\n");               /* read high threshold failed */
       
        return 1;                                                                   /* return error */
    }
    *threshold = (int8_t)(prev);                                                    /* set threshold */
    
    return 0;                                                                       /* success return 0 */
}

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
uint8_t bmm150_set_repxy_number(bmm150_handle_t *handle, uint8_t number)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    prev = number;                                                           /* set number */
    res = a_bmm150_iic_spi_write(handle, BMM150_REG_REPXY, &prev, 1);        /* write config */
    if (res != 0)                                                            /* check the result */
    {
        handle->debug_print("bmm150: write repxy failed.\n");                /* write repxy failed */
       
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t bmm150_get_repxy_number(bmm150_handle_t *handle, uint8_t *number)
{
    uint8_t res;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_REPXY, number, 1);        /* read config */
    if (res != 0)                                                            /* check the result */
    {
        handle->debug_print("bmm150: read repxy failed.\n");                 /* read repxy failed */
       
        return 1;                                                            /* return error */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t bmm150_set_repz_number(bmm150_handle_t *handle, uint8_t number)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    prev = number;                                                          /* set number */
    res = a_bmm150_iic_spi_write(handle, BMM150_REG_REPZ, &prev, 1);        /* write config */
    if (res != 0)                                                           /* check the result */
    {
        handle->debug_print("bmm150: write repz failed.\n");                /* write repz failed */
       
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t bmm150_get_repz_number(bmm150_handle_t *handle, uint8_t *number)
{
    uint8_t res;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_REPZ, number, 1);        /* read config */
    if (res != 0)                                                           /* check the result */
    {
        handle->debug_print("bmm150: read repz failed.\n");                 /* read repz failed */
       
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t bmm150_read(bmm150_handle_t *handle, int16_t raw[3], float ut[3])
{
    uint8_t res;
    uint8_t prev;
    uint8_t mode;
    uint8_t buf[8];
    uint16_t temp;
    
    if (handle == NULL)                                                                     /* check handle */
    {
        return 2;                                                                           /* return error */
    }
    if (handle->inited != 1)                                                                /* check handle initialization */
    {
        return 3;                                                                           /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_CONFIG_1, &prev, 1);                     /* read config */
    if (res != 0)                                                                           /* check the result */
    {
        handle->debug_print("bmm150: read config 1 failed.\n");                             /* read config 1 failed */
       
        return 1;                                                                           /* return error */
    }
    mode = (prev >> 1) & 0x03;                                                              /* get mode config */
    if (mode == 0)                                                                          /* normal mode */
    {
        res = a_bmm150_iic_spi_read(handle, BMM150_REG_DATA_X_LSB, buf, 8);                 /* read data */
        if (res != 0)                                                                       /* check the result */
        {
            handle->debug_print("bmm150: read data failed.\n");                             /* read data failed */
           
            return 1;                                                                       /* return error */
        }
        if (((buf[1] >> 7) & 0x01) != 0)                                                    /* check signed bit */
        {
            temp = (int16_t)(((uint16_t)buf[1]) << 5 | (buf[0] >> 3) | (0x7 << 13));        /* set data */
            raw[0] = temp;                                                                  /* set x */
        }
        else
        {
            temp = (int16_t)(((uint16_t)buf[1]) << 5 | (buf[0] >> 3));                      /* make data */
            raw[0] = temp;                                                                  /* set x */
        }
        if (((buf[3] >> 7) & 0x01) != 0)                                                    /* check signed bit */
        {
            temp = (int16_t)(((uint16_t)buf[3]) << 5 | (buf[2] >> 3) | (0x7 << 13));        /* set data */
            raw[1] = temp;                                                                  /* set y */
        }
        else
        {
            temp = (int16_t)(((uint16_t)buf[3]) << 5 | (buf[2] >> 3));                      /* make data */
            raw[1] = temp;                                                                  /* set y */
        }
        if (((buf[5] >> 7) & 0x01) != 0)                                                    /* check signed bit */
        {
            temp = (int16_t)(((uint16_t)buf[5]) << 7 | (buf[4] >> 1) | (0x1 << 15));        /* set data */
            raw[2] = temp;                                                                  /* set z */
        }
        else
        {
            temp = (int16_t)(((uint16_t)buf[5]) << 7 | (buf[4] >> 1));                      /* make data */
            raw[2] = temp;                                                                  /* set z */
        }
        temp = (uint16_t)(((uint16_t)buf[7]) << 6 | (buf[6] >> 2));                         /* make data */
        ut[0] = a_bmm150_compensate_x(handle, raw[0], temp);                                /* compensate x */
        ut[1] = a_bmm150_compensate_y(handle, raw[1], temp);                                /* compensate y */
        ut[2] = a_bmm150_compensate_z(handle, raw[2], temp);                                /* compensate z */
        
        return 0;                                                                           /* success return 0 */
    }
    else                                                                                    /* forced mode */
    {
        uint16_t timeout;
        
        res = a_bmm150_iic_spi_read(handle, BMM150_REG_CONFIG_1, &prev, 1);                 /* read config */
        if (res != 0)                                                                       /* check the result */
        {
            handle->debug_print("bmm150: read config 1 failed.\n");                         /* read config 1 failed */
           
            return 1;                                                                       /* return error */
        }
        prev &= ~(3 << 1);                                                                  /* clear settings */
        prev |= 0x01 << 1;                                                                  /* set forced mode */
        res = a_bmm150_iic_spi_write(handle, BMM150_REG_CONFIG_1, &prev, 1);                /* write config */
        if (res != 0)                                                                       /* check the result */
        {
            handle->debug_print("bmm150: write config 1 failed.\n");                        /* write config 1 failed */
           
            return 1;                                                                       /* return error */
        }
        
        timeout = 1000;                                                                     /* timeout 1s */
        while (timeout != 0)                                                                /* check timeout */
        {
            res = a_bmm150_iic_spi_read(handle, BMM150_REG_RHALL_LSB, &prev, 1);            /* read rhall lsb */
            if (res != 0)                                                                   /* check the result */
            {
                handle->debug_print("bmm150: read rhall lsb failed.\n");                    /* read rhall lsb failed */
               
                return 1;                                                                   /* return error */
            }
            if ((prev & 0x01) != 0)                                                         /* check data ready bit */
            {
                break;                                                                      /* break */
            }
            timeout--;                                                                      /* timeout-- */
            handle->delay_ms(1);                                                            /* delay 1ms */
        }
        if (timeout == 0)                                                                   /* check timeout */
        {
            handle->debug_print("bmm150: read timeout.\n");                                 /* read timeout */
           
            return 4;                                                                       /* return error */
        }
        
        res = a_bmm150_iic_spi_read(handle, BMM150_REG_DATA_X_LSB, buf, 8);                 /* read data */
        if (res != 0)                                                                       /* check the result */
        {
            handle->debug_print("bmm150: read data failed.\n");                             /* read data failed */
           
            return 1;                                                                       /* return error */
        }
        if (((buf[1] >> 7) & 0x01) != 0)                                                    /* check signed bit */
        {
            temp = (int16_t)(((uint16_t)buf[1]) << 5 | (buf[0] >> 3) | (0x7 << 13));        /* set data */
            raw[0] = temp;                                                                  /* set x */
        }
        else
        {
            temp = (int16_t)(((uint16_t)buf[1]) << 5 | (buf[0] >> 3));                      /* make data */
            raw[0] = temp;                                                                  /* set x */
        }
        if (((buf[3] >> 7) & 0x01) != 0)                                                    /* check signed bit */
        {
            temp = (int16_t)(((uint16_t)buf[3]) << 5 | (buf[2] >> 3) | (0x7 << 13));        /* set data */
            raw[1] = temp;                                                                  /* set y */
        }
        else
        {
            temp = (int16_t)(((uint16_t)buf[3]) << 5 | (buf[2] >> 3));                      /* make data */
            raw[1] = temp;                                                                  /* set y */
        }
        if (((buf[5] >> 7) & 0x01) != 0)                                                    /* check signed bit */
        {
            temp = (int16_t)(((uint16_t)buf[5]) << 7 | (buf[4] >> 1) | (0x1 << 15));        /* set data */
            raw[2] = temp;                                                                  /* set z */
        }
        else
        {
            temp = (int16_t)(((uint16_t)buf[5]) << 7 | (buf[4] >> 1));                      /* make data */
            raw[2] = temp;                                                                  /* set z */
        }
        temp = (uint16_t)(((uint16_t)buf[7]) << 6 | (buf[6] >> 2));                         /* make data */
        ut[0] = a_bmm150_compensate_x(handle, raw[0], temp);                                /* compensate x */
        ut[1] = a_bmm150_compensate_y(handle, raw[1], temp);                                /* compensate y */
        ut[2] = a_bmm150_compensate_z(handle, raw[2], temp);                                /* compensate z */
        
        return 0;                                                                           /* success return 0 */
    }
}

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
uint8_t bmm150_irq_handler(bmm150_handle_t *handle)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                       /* check handle */
    {
        return 2;                                                                             /* return error */
    }
    if (handle->inited != 1)                                                                  /* check handle initialization */
    {
        return 3;                                                                             /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, BMM150_REG_INTERRUPT_STATUS, &prev, 1);               /* read config */
    if (res != 0)                                                                             /* check the result */
    {
        handle->debug_print("bmm150: read interrupt status failed.\n");                       /* read interrupt status failed */
       
        return 1;                                                                             /* return error */
    }
    
    if (prev != 0)                                                                            /* check valid bits */
    {
        if (((prev >> (uint8_t)BMM150_INTERRUPT_STATUS_DATA_OVERRUN) & 0x01) != 0)            /* check data overrun */
        {
            if (handle->receive_callback != NULL)                                             /* not null */
            {
                handle->receive_callback(BMM150_INTERRUPT_STATUS_DATA_OVERRUN);               /* run the callback */
            }
        }
        if (((prev >> (uint8_t)BMM150_INTERRUPT_STATUS_OVERFLOW) & 0x01) != 0)                /* check overflow */
        {
            if (handle->receive_callback != NULL)                                             /* not null */
            {
                handle->receive_callback(BMM150_INTERRUPT_STATUS_OVERFLOW);                   /* run the callback */
            }
        }
        if (((prev >> (uint8_t)BMM150_INTERRUPT_STATUS_HIGH_THRESHOLD_Z) & 0x01) != 0)        /* check high threshold z */
        {
            if (handle->receive_callback != NULL)                                             /* not null */
            {
                handle->receive_callback(BMM150_INTERRUPT_STATUS_HIGH_THRESHOLD_Z);           /* run the callback */
            }
        }
        if (((prev >> (uint8_t)BMM150_INTERRUPT_STATUS_HIGH_THRESHOLD_Y) & 0x01) != 0)        /* check high threshold y */
        {
            if (handle->receive_callback != NULL)                                             /* not null */
            {
                handle->receive_callback(BMM150_INTERRUPT_STATUS_HIGH_THRESHOLD_Y);           /* run the callback */
            }
        }
        if (((prev >> (uint8_t)BMM150_INTERRUPT_STATUS_HIGH_THRESHOLD_X) & 0x01) != 0)        /* check high threshold z */
        {
            if (handle->receive_callback != NULL)                                             /* not null */
            {
                handle->receive_callback(BMM150_INTERRUPT_STATUS_HIGH_THRESHOLD_X);           /* run the callback */
            }
        }
        if (((prev >> (uint8_t)BMM150_INTERRUPT_STATUS_LOW_THRESHOLD_Z) & 0x01) != 0)         /* check low threshold z */
        {
            if (handle->receive_callback != NULL)                                             /* not null */
            {
                handle->receive_callback(BMM150_INTERRUPT_STATUS_LOW_THRESHOLD_Z);            /* run the callback */
            }
        }
        if (((prev >> (uint8_t)BMM150_INTERRUPT_STATUS_LOW_THRESHOLD_Y) & 0x01) != 0)         /* check low threshold y */
        {
            if (handle->receive_callback != NULL)                                             /* not null */
            {
                handle->receive_callback(BMM150_INTERRUPT_STATUS_LOW_THRESHOLD_Y);            /* run the callback */
            }
        }
        if (((prev >> (uint8_t)BMM150_INTERRUPT_STATUS_LOW_THRESHOLD_X) & 0x01) != 0)         /* check low threshold x */
        {
            if (handle->receive_callback != NULL)                                             /* not null */
            {
                handle->receive_callback(BMM150_INTERRUPT_STATUS_LOW_THRESHOLD_X);            /* run the callback */
            }
        }
    }
    
    return 0;                                                                                 /* success return 0 */
}

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
uint8_t bmm150_interrupt_threshold_convert_to_register(bmm150_handle_t *handle, float ut, int8_t *reg)
{
    if (handle == NULL)                 /* check handle */
    {
        return 2;                       /* return error */
    }
    if (handle->inited != 1)            /* check handle initialization */
    {
        return 3;                       /* return error */
    }
    
    *reg = (int8_t)(ut / 6.0f);         /* convert real data to register data */
    
    return 0;                           /* success return 0 */
}

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
uint8_t bmm150_interrupt_threshold_convert_to_data(bmm150_handle_t *handle, int8_t reg, float *ut)
{
    if (handle == NULL)              /* check handle */
    {
        return 2;                    /* return error */
    }
    if (handle->inited != 1)         /* check handle initialization */
    {
        return 3;                    /* return error */
    }
    
    *ut = (float)(reg) * 6.0f;       /* convert raw data to real data */
    
    return 0;                        /* success return 0 */
}

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
uint8_t bmm150_init(bmm150_handle_t *handle)
{
    uint8_t id;
    uint8_t prev;
  
    if (handle == NULL)                                                                   /* check handle */
    {
        return 2;                                                                         /* return error */
    }
    if (handle->debug_print == NULL)                                                      /* check debug_print */
    {
        return 3;                                                                         /* return error */
    }
    if (handle->iic_init == NULL)                                                         /* check iic_init */
    {
        handle->debug_print("bmm150: iic_init is null.\n");                               /* iic_init is null */
       
        return 3;                                                                         /* return error */
    }
    if (handle->iic_deinit == NULL)                                                       /* check iic_deinit */
    {
        handle->debug_print("bmm150: iic_deinit is null.\n");                             /* iic_deinit is null */
       
        return 3;                                                                         /* return error */
    }
    if (handle->iic_read == NULL)                                                         /* check iic_read */
    {
        handle->debug_print("bmm150: iic_read is null.\n");                               /* iic_read is null */
       
        return 3;                                                                         /* return error */
    }
    if (handle->iic_write == NULL)                                                        /* check iic_write */
    {
        handle->debug_print("bmm150: iic_write is null.\n");                              /* iic_write is null */
       
        return 3;                                                                         /* return error */
    }
    if (handle->spi_init == NULL)                                                         /* check spi_init */
    {
        handle->debug_print("bmm150: spi_init is null.\n");                               /* spi_init is null */
       
        return 3;                                                                         /* return error */
    }
    if (handle->spi_deinit == NULL)                                                       /* check spi_deinit */
    {
        handle->debug_print("bmm150: spi_deinit is null.\n");                             /* spi_deinit is null */
       
        return 3;                                                                         /* return error */
    }
    if (handle->spi_read == NULL)                                                         /* check spi_read */
    {
        handle->debug_print("bmm150: spi_read is null.\n");                               /* spi_read is null */
       
        return 3;                                                                         /* return error */
    }
    if (handle->spi_write == NULL)                                                        /* check spi_write */
    {
        handle->debug_print("bmm150: spi_write is null.\n");                              /* spi_write is null */
       
        return 3;                                                                         /* return error */
    }
    if (handle->delay_ms == NULL)                                                         /* check delay_ms */
    {
        handle->debug_print("bmm150: delay_ms is null.\n");                               /* delay_ms is null */
       
        return 3;                                                                         /* return error */
    }
    if (handle->receive_callback == NULL)                                                 /* check receive_callback */
    {
        handle->debug_print("bmm150: receive_callback is null.\n");                       /* receive_callback is null */
       
        return 3;                                                                         /* return error */
    }
    
    if (handle->iic_spi == BMM150_INTERFACE_IIC)                                          /* iic interface */
    {
        if (handle->iic_init() != 0)                                                      /* initialize iic bus */
        {
            handle->debug_print("bmm150: iic init failed.\n");                            /* iic init failed */
            
            return 1;                                                                     /* return error */
        }
    }
    else                                                                                  /* spi interface */
    {
        if (handle->spi_init() != 0)                                                      /* initialize spi bus */
        {
            handle->debug_print("bmm150: spi init failed.\n");                            /* spi init failed */
           
            return 1;                                                                     /* return error */
        }
    }
    
    if (a_bmm150_iic_spi_read(handle, BMM150_REG_CONFIG_0, &prev, 1) != 0)                /* soft reset */
    {
        handle->debug_print("bmm150: read config 0 failed.\n");                           /* read config 0 failed */
        (void)a_bmm150_close(handle);                                                     /* close */
        
        return 4;                                                                         /* return error */
    }
    prev &= ~(1 << 1);                                                                    /* clear settings */
    prev |= 1 << 1;                                                                       /* set bool */
    if (a_bmm150_iic_spi_write(handle, BMM150_REG_CONFIG_0, &prev, 1) != 0)               /* soft reset */
    {
        handle->debug_print("bmm150: write config 0 failed.\n");                          /* write config 0 failed */
        (void)a_bmm150_close(handle);                                                     /* close */
        
        return 4;                                                                         /* return error */
    }
    handle->delay_ms(5);                                                                  /* delay 5ms */
    
    if (a_bmm150_iic_spi_read(handle, BMM150_REG_CONFIG_0, &prev, 1) != 0)                /* read config */
    {
        handle->debug_print("bmm150: read config 0 failed.\n");                           /* read config 0 failed */
       
        return 5;                                                                         /* return error */
    }
    prev &= ~(1 << 0);                                                                    /* clear settings */
    prev |= 1 << 0;                                                                       /* set bool */
    if (a_bmm150_iic_spi_write(handle, BMM150_REG_CONFIG_0, &prev, 1) != 0)               /* write config */
    {
        handle->debug_print("bmm150: write config 0 failed.\n");                          /* write config 0 failed */
       
        return 5;                                                                         /* return error */
    }
    handle->delay_ms(5);                                                                  /* delay 5ms */
    
    if (a_bmm150_iic_spi_read(handle, BMM150_REG_CHIP_ID, (uint8_t *)&id, 1) != 0)        /* read id */
    {
        handle->debug_print("bmm150: read failed.\n");                                    /* read failed */
        (void)a_bmm150_close(handle);                                                     /* close */
        
        return 6;                                                                         /* return error */
    }
    if (id != 0x32)                                                                       /* check id */
    {
        handle->debug_print("bmm150: id is invalid.\n");                                  /* id is invalid */
        (void)a_bmm150_close(handle);                                                     /* close */
       
        return 6;                                                                         /* return error */
    }
    if (a_bmm150_load_trim(handle) != 0)                                                  /* load trim */
    {
        handle->debug_print("bmm150: load trim failed.\n");                               /* load trim failed */
        (void)a_bmm150_close(handle);                                                     /* close */
       
        return 7;                                                                         /* return error */
    }
    handle->inited = 1;                                                                   /* flag finish initialization */
    
    return 0;                                                                             /* success return 0 */
}

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
uint8_t bmm150_deinit(bmm150_handle_t *handle)
{
    uint8_t res;
    
    if (handle == NULL)                  /* check handle */
    {
        return 2;                        /* return error */
    }
    if (handle->inited != 1)             /* check handle initialization */
    {
        return 3;                        /* return error */
    }
    
    res = a_bmm150_close(handle);        /* close */
    if (res != 0)                        /* check result */
    {
        return 1;                        /* return error */
    }
    else
    {
        handle->inited = 0;              /* flag close */
        
        return 0;                        /* success return 0 */
    }
}

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
uint8_t bmm150_set_reg(bmm150_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    uint8_t res;
    
    if (handle == NULL)                                         /* check handle */
    {
        return 2;                                               /* return error */
    }
    if (handle->inited != 1)                                    /* check handle initialization */
    {
        return 3;                                               /* return error */
    }
    
    res = a_bmm150_iic_spi_write(handle, reg, buf, len);        /* write data */
    if (res != 0)                                               /* check the result */
    {
        return 1;                                               /* return error */
    }
    
    return 0;                                                   /* success return 0 */
}

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
uint8_t bmm150_get_reg(bmm150_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    uint8_t res;
    
    if (handle == NULL)                                        /* check handle */
    {
        return 2;                                              /* return error */
    }
    if (handle->inited != 1)                                   /* check handle initialization */
    {
        return 3;                                              /* return error */
    }
    
    res = a_bmm150_iic_spi_read(handle, reg, buf, len);        /* read data */
    if (res != 0)                                              /* check the result */
    {
        return 1;                                              /* return error */
    }
    
    return 0;                                                  /* success return 0 */
}

/**
 * @brief      get chip's information
 * @param[out] *info pointer to a bmm150 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t bmm150_info(bmm150_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(bmm150_info_t));                         /* initialize bmm150 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "IIC SPI", 8);                         /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
