[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver BMM150

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/bmm150/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

The BMM150 is a standalone geomagnetic sensor for consumer market applications. lt allows measurements of the magnetic field in three perpendicular axes. Based on Bosch's proprietary FlipCore technology, performance and features of BMM150 are carefully tuned and perfectly match the demanding requirements of all 3-axis mobile applications such as electronic compass. navigation or augmented reality. An evaluation circuitry (ASlC) converts the output of the geomagnetic sensor to digital results which can be read out over the industry standard digital interfaces (SPI and l2C). Package and interfaces of the BMM150 have been designed to match a multitude of hardware requirements. As the sensor features an ultra-small footprint and a flat package, it is ingeniously suited for mobile applications. The wafer level chip scale package (WLCSP) with dimensions of only 1.56 x 1.56 x 0.6 mm³ ensures high flexibility in PCB placement. The BMM150 offers ultra-low voltage operation (Vdd voltage range from 1.62V to 3.6V, Vddio voltage range 1.2V to 3.6V) and can be programmed to optimize functionality, performance and power consumption in customer specific applications. The programmable interrupt engine gives design flexibility to the developer. 

LibDriver BMM150 is a full-featured driver for BMM150, launched by LibDriver. It provides single reading, continuous reading, threshold interrupt and additional features. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
    - [example interrupt](#example-interrupt)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver BMM150 source files.

/interface includes LibDriver BMM150 IIC, SPI platform independent template.

/test includes LibDriver BMM150 driver test code and this code can test the chip necessary function simply.

/example includes LibDriver BMM150 sample code.

/doc includes LibDriver BMM150 offline document.

/datasheet includes BMM150 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface IIC, SPI platform independent template and finish your platform IIC, SPI driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example basic

```C
#include "driver_bmm150_basic.h"

uint8_t res;
uint32_t i;
float ut[3];

/* basic init */
res = bmm150_basic_init(BMM150_INTERFACE_IIC, BMM150_ADDRESS_CSB_SDO_00);
if (res != 0)
{
    return 1;
}

...
    
/* loop */
for (i = 0; i < 3; i++)
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
    bmm150_interface_debug_print("bmm150: %d/%d.\n", i + 1, 3);
    bmm150_interface_debug_print("bmm150: x is %0.3fuT.\n", ut[0]);
    bmm150_interface_debug_print("bmm150: y is %0.3fuT.\n", ut[1]);
    bmm150_interface_debug_print("bmm150: z is %0.3fuT.\n", ut[2]);
    
    ...
        
}

...
    
/* basic deinit */
(void)bmm150_basic_deinit();

return 0;
```

#### example shot

```C
#include "driver_bmm150_shot.h"

uint8_t res;
uint32_t i;
float ut[3];

/* shot init */
res = bmm150_shot_init(BMM150_INTERFACE_IIC, BMM150_ADDRESS_CSB_SDO_00);
if (res != 0)
{
    return 1;
}

...
    
/* loop */
for (i = 0; i < 3; i++)
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
    bmm150_interface_debug_print("bmm150: %d/%d.\n", i + 1, 3);
    bmm150_interface_debug_print("bmm150: x is %0.3fuT.\n", ut[0]);
    bmm150_interface_debug_print("bmm150: y is %0.3fuT.\n", ut[1]);
    bmm150_interface_debug_print("bmm150: z is %0.3fuT.\n", ut[2]);
    
    ...
        
}

...
    
/* shot deinit */
(void)bmm150_shot_deinit();

return 0;
```

#### example interrupt

```C
#include "driver_bmm150_interrupt.h"

uint8_t res;
uint32_t i;
volatile uint8_t g_flag;
uint8_t (*g_gpio_irq)(void) = NULL;
float low_threahold = 6.0f;
float high_threahold = 48.0f;

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

/* gpio init */
res = gpio_interrupt_init();
if (res != 0)
{
    return 1;
}

/* set the interrupt irq */
g_gpio_irq = bmm150_interrupt_irq_handler;

...
    
/* interrupt init */
res = bmm150_interrupt_init(BMM150_INTERFACE_IIC, BMM150_ADDRESS_CSB_SDO_00, low_threahold, high_threahold, a_receive_callback);
if (res != 0)
{
    (void)gpio_interrupt_deinit();
    g_gpio_irq = NULL;

    return 1;
}

...
    
/* set the times */
g_flag = 0;
for (i = 0; i < 3; i++)
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
    
    ...
        
}

...
    
/* gpio deinit */
(void)gpio_interrupt_deinit();
g_gpio_irq = NULL;
(void)bmm150_interrupt_deinit();

return 0;
```

### Document

Online documents: [https://www.libdriver.com/docs/bmm150/index.html](https://www.libdriver.com/docs/bmm150/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.