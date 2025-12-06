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
 * @file      main.c
 * @brief     main source file
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
#include "driver_bmm150_read_test.h"
#include "driver_bmm150_interrupt_test.h"
#include "driver_bmm150_interrupt.h"
#include "driver_bmm150_basic.h"
#include "driver_bmm150_shot.h"
#include "shell.h"
#include "clock.h"
#include "delay.h"
#include "gpio.h"
#include "uart.h"
#include "getopt.h"
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];                        /**< uart buffer */
volatile uint16_t g_len;                   /**< uart buffer length */
volatile uint8_t g_flag;                   /**< interrupt flag */
uint8_t (*g_gpio_irq)(void) = NULL;        /**< gpio irq */

/**
 * @brief exti 0 irq
 * @note  none
 */
void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

/**
 * @brief     gpio exti callback
 * @param[in] pin gpio pin
 * @note      none
 */
void HAL_GPIO_EXTI_Callback(uint16_t pin)
{
    if (pin == GPIO_PIN_0)
    {
        if (g_gpio_irq != NULL)
        {
            g_gpio_irq();
        }
    }
}

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
            g_flag = 1;
            
            break;
        }
        case BMM150_INTERRUPT_STATUS_HIGH_THRESHOLD_Y :
        {
            bmm150_interface_debug_print("bmm150: irq high threshold y.\n");
            g_flag = 1;
            
            break;
        }
        case BMM150_INTERRUPT_STATUS_HIGH_THRESHOLD_X :
        {
            bmm150_interface_debug_print("bmm150: irq high threshold x.\n");
            g_flag = 1;
            
            break;
        }
        case BMM150_INTERRUPT_STATUS_LOW_THRESHOLD_Z :
        {
            bmm150_interface_debug_print("bmm150: irq low threshold z.\n");
            g_flag = 1;
            
            break;
        }
        case BMM150_INTERRUPT_STATUS_LOW_THRESHOLD_Y :
        {
            bmm150_interface_debug_print("bmm150: irq low threshold y.\n");
            g_flag = 1;
            
            break;
        }
        case BMM150_INTERRUPT_STATUS_LOW_THRESHOLD_X :
        {
            bmm150_interface_debug_print("bmm150: irq low threshold x.\n");
            g_flag = 1;
            
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
 * @brief     bmm150 full function
 * @param[in] argc arg numbers
 * @param[in] **argv arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t bmm150(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"addr", required_argument, NULL, 1},
        {"high-threshold", required_argument, NULL, 2},
        {"interface", required_argument, NULL, 3},
        {"low-threshold", required_argument, NULL, 4},
        {"times", required_argument, NULL, 5},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint32_t times = 3;
    float low_threahold = 6.0f;
    float high_threahold = 48.0f;
    bmm150_address_t addr = BMM150_ADDRESS_CSB_SDO_00;
    bmm150_interface_t interface = BMM150_INTERFACE_IIC;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* addr */
            case 1 :
            {
                /* set the addr pin */
                if (strcmp("0", optarg) == 0)
                {
                    addr = BMM150_ADDRESS_CSB_SDO_00;
                }
                else if (strcmp("1", optarg) == 1)
                {
                    addr = BMM150_ADDRESS_CSB_SDO_01;
                }
                else if (strcmp("2", optarg) == 2)
                {
                    addr = BMM150_ADDRESS_CSB_SDO_10;
                }
                else if (strcmp("3", optarg) == 3)
                {
                    addr = BMM150_ADDRESS_CSB_SDO_11;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* high threahold */
            case 2 :
            {
                /* convert high threahold */
                high_threahold = (float)atof(optarg);
                
                break;
            }
            
            /* interface */
            case 3 :
            {
                /* set the interface */
                if (strcmp("iic", optarg) == 0)
                {
                    interface = BMM150_INTERFACE_IIC;
                }
                else if (strcmp("spi", optarg) == 0)
                {
                    interface = BMM150_INTERFACE_SPI;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* low threahold */
            case 4 :
            {
                /* convert low threahold */
                low_threahold = (float)atof(optarg);
                
                break;
            }

            /* running times */
            case 5 :
            {
                /* set the times */
                times = atol(optarg);
                
                break;
            } 
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_reg", type) == 0)
    {
        uint8_t res;
        
        /* run register test */
        res = bmm150_register_test(interface, addr);
        if (res != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("t_read", type) == 0)
    {
        uint8_t res;
        
        /* read test */
        res = bmm150_read_test(interface, addr, times);
        if (res != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("t_int", type) == 0)
    {
        uint8_t res;
        
        /* gpio init */
        res = gpio_interrupt_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* set the gpio irq */
        g_gpio_irq = bmm150_interrupt_test_irq_handler;
        
        /* run interrupt test */
        res = bmm150_interrupt_test(interface, addr, low_threahold, high_threahold, times);
        if (res != 0)
        {
            (void)gpio_interrupt_deinit();
            g_gpio_irq = NULL;
            
            return 1;
        }
        
        /* gpio deinit */
        (void)gpio_interrupt_deinit();
        g_gpio_irq = NULL;
        
        return 0;
    }
    else if (strcmp("e_basic", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        float ut[3];
        
        /* basic init */
        res = bmm150_basic_init(interface, addr);
        if (res != 0)
        {
            return 1;
        }
        
        /* loop */
        for (i = 0; i < times; i++)
        {
            /* delay 1000ms */
            bmm150_interface_delay_ms(1000);
            
            /* read data */
            res = bmm150_basic_read((float *)ut);
            if (res != 0)
            {
                (void)bmm150_basic_deinit();
                
                return 1;
            }
            
            /* output */
            bmm150_interface_debug_print("bmm150: %d/%d.\n", i + 1, times);
            bmm150_interface_debug_print("bmm150: x is %0.3fuT.\n", ut[0]);
            bmm150_interface_debug_print("bmm150: y is %0.3fuT.\n", ut[1]);
            bmm150_interface_debug_print("bmm150: z is %0.3fuT.\n", ut[2]);
        }
        
        /* basic deinit */
        (void)bmm150_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_shot", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        float ut[3];
        
        /* shot init */
        res = bmm150_shot_init(interface, addr);
        if (res != 0)
        {
            return 1;
        }
        
        /* loop */
        for (i = 0; i < times; i++)
        {
            /* delay 1000ms */
            bmm150_interface_delay_ms(1000);
            
            /* read data */
            res = bmm150_shot_read((float *)ut);
            if (res != 0)
            {
                (void)bmm150_shot_deinit();
                
                return 1;
            }
            
            /* output */
            bmm150_interface_debug_print("bmm150: %d/%d.\n", i + 1, times);
            bmm150_interface_debug_print("bmm150: x is %0.3fuT.\n", ut[0]);
            bmm150_interface_debug_print("bmm150: y is %0.3fuT.\n", ut[1]);
            bmm150_interface_debug_print("bmm150: z is %0.3fuT.\n", ut[2]);
        }
        
        /* shot deinit */
        (void)bmm150_shot_deinit();
        
        return 0;
    }
    else if (strcmp("e_int", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        
        /* gpio init */
        res = gpio_interrupt_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* set the interrupt irq */
        g_gpio_irq = bmm150_interrupt_irq_handler;
        
        /* interrupt init */
        res = bmm150_interrupt_init(interface, addr, low_threahold, high_threahold, a_receive_callback);
        if (res != 0)
        {
            (void)gpio_interrupt_deinit();
            g_gpio_irq = NULL;
            
            return 1;
        }
        
        /* set the times */
        g_flag = 0;
        for (i = 0; i < times; i++)
        {
            float ut[3];
            
            /* delay 1000ms */
            bmm150_interface_delay_ms(1000);
            
            if (g_flag != 0)
            {
                bmm150_interface_debug_print("bmm150: find interrupt.\n");
                
                g_flag = 0;
            }
            
            /* read data */
            res = bmm150_interrupt_read(ut);
            if (res != 0)
            {
                bmm150_interface_debug_print("bmm150: read failed.\n");
                (void)gpio_interrupt_deinit();
                g_gpio_irq = NULL;
                (void)bmm150_interrupt_deinit();
                
                return 1;
            }
            
            /* output */
            bmm150_interface_debug_print("bmm150: x is %0.2fuT.\n", ut[0]);
            bmm150_interface_debug_print("bmm150: y is %0.2fuT.\n", ut[1]);
            bmm150_interface_debug_print("bmm150: z is %0.2fuT.\n", ut[2]);
        }
        
        /* gpio deinit */
        (void)gpio_interrupt_deinit();
        g_gpio_irq = NULL;
        (void)bmm150_interrupt_deinit();
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        bmm150_interface_debug_print("Usage:\n");
        bmm150_interface_debug_print("  bmm150 (-i | --information)\n");
        bmm150_interface_debug_print("  bmm150 (-h | --help)\n");
        bmm150_interface_debug_print("  bmm150 (-p | --port)\n");
        bmm150_interface_debug_print("  bmm150 (-t reg | --test=reg) [--addr=<0 | 1 | 2 | 3>] [--interface=<iic | spi>]\n");
        bmm150_interface_debug_print("  bmm150 (-t read | --test=read) [--addr=<0 | 1 | 2 | 3>] [--interface=<iic | spi>] [--times=<num>]\n");
        bmm150_interface_debug_print("  bmm150 (-t int | --test=int) [--addr=<0 | 1 | 2 | 3>] [--interface=<iic | spi>]\n");
        bmm150_interface_debug_print("         [--low-threshold=<ut>] [--high-threshold=<ut>] [--times=<num>]\n");
        bmm150_interface_debug_print("  bmm150 (-e basic | --example=basic) [--addr=<0 | 1 | 2 | 3>] [--interface=<iic | spi>] [--times=<num>]\n");
        bmm150_interface_debug_print("  bmm150 (-e shot | --example=shot) [--addr=<0 | 1 | 2 | 3>] [--interface=<iic | spi>] [--times=<num>]\n");
        bmm150_interface_debug_print("  bmm150 (-e int | --example=int) [--addr=<0 | 1 | 2 | 3>] [--interface=<iic | spi>]\n");
        bmm150_interface_debug_print("         [--low-threshold=<ut>] [--high-threshold=<ut>] [--times=<num>]\n");
        bmm150_interface_debug_print("\n");
        bmm150_interface_debug_print("Options:\n");
        bmm150_interface_debug_print("      --addr=<0 | 1 | 2 | 3>         Set the chip address.([default: 0])\n");
        bmm150_interface_debug_print("  -e <basic | shot | int>, --example=<basic | shot | int>\n");
        bmm150_interface_debug_print("                                     Run the driver example.\n");
        bmm150_interface_debug_print("  -h, --help                         Show the help.\n");
        bmm150_interface_debug_print("      --high-threshold=<ut>          Set the interrupt high threshold in ut.([default: 48.0])\n");
        bmm150_interface_debug_print("  -i, --information                  Show the chip information.\n");
        bmm150_interface_debug_print("      --interface=<iic | spi>        Set the chip interface.([default: iic])\n");
        bmm150_interface_debug_print("      --low-threshold=<ut>           Set the interrupt low threshold in ut.([default: 6.0])\n");
        bmm150_interface_debug_print("  -p, --port                         Display the pin connections of the current board.\n");
        bmm150_interface_debug_print("  -t <reg | read | int>, --test=<reg | read | int>\n");
        bmm150_interface_debug_print("                                     Run the driver test.\n");
        bmm150_interface_debug_print("      --times=<num>                  Set the running times.([default: 3])\n");

        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        bmm150_info_t info;
        
        /* print bmm150 info */
        bmm150_info(&info);
        bmm150_interface_debug_print("bmm150: chip is %s.\n", info.chip_name);
        bmm150_interface_debug_print("bmm150: manufacturer is %s.\n", info.manufacturer_name);
        bmm150_interface_debug_print("bmm150: interface is %s.\n", info.interface);
        bmm150_interface_debug_print("bmm150: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        bmm150_interface_debug_print("bmm150: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        bmm150_interface_debug_print("bmm150: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        bmm150_interface_debug_print("bmm150: max current is %0.2fmA.\n", info.max_current_ma);
        bmm150_interface_debug_print("bmm150: max temperature is %0.1fC.\n", info.temperature_max);
        bmm150_interface_debug_print("bmm150: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        bmm150_interface_debug_print("bmm150: SPI interface SCK connected to GPIOA PIN5.\n");
        bmm150_interface_debug_print("bmm150: SPI interface MISO connected to GPIOA PIN6.\n");
        bmm150_interface_debug_print("bmm150: SPI interface MOSI connected to GPIOA PIN7.\n");
        bmm150_interface_debug_print("bmm150: SPI interface CS connected to GPIOA PIN4.\n");
        bmm150_interface_debug_print("bmm150: IIC interface SCL connected to GPIOB PIN8.\n");
        bmm150_interface_debug_print("bmm150: IIC interface SDA connected to GPIOB PIN9.\n");
        bmm150_interface_debug_print("bmm150: INT connected to GPIOB PIN0.\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;
    
    /* stm32f407 clock init and hal init */
    clock_init();
    
    /* delay init */
    delay_init();
    
    /* uart init */
    uart_init(115200);
    
    /* shell init && register bmm150 function */
    shell_init();
    shell_register("bmm150", bmm150);
    uart_print("bmm150: welcome to libdriver bmm150.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart_read(g_buf, 256);
        if (g_len != 0)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart_print("bmm150: run failed.\n");
            }
            else if (res == 2)
            {
                uart_print("bmm150: unknown command.\n");
            }
            else if (res == 3)
            {
                uart_print("bmm150: length is too long.\n");
            }
            else if (res == 4)
            {
                uart_print("bmm150: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart_print("bmm150: param is invalid.\n");
            }
            else
            {
                uart_print("bmm150: unknown status code.\n");
            }
            uart_flush();
        }
        delay_ms(100);
    }
}
