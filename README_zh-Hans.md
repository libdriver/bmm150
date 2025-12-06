[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver BMM150

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/bmm150/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

BMM150是一款用于消费市场应用的独立地磁传感器。它允许测量三个垂直轴上的磁场。基于博世专有的FlipCore技术，BMM150的性能和功能经过精心调整，完全符合电子罗盘等所有三轴移动应用的苛刻要求。导航或增强现实。评估电路（ASlC）将地磁传感器的输出转换为数字结果，可以通过行业标准数字接口（SPI和l2C）读取。BMM150的封装和接口设计可满足多种硬件要求。由于该传感器具有超小的尺寸面积和扁平的封装，因此非常适合移动应用。晶圆级芯片级封装（WLCSP）的尺寸仅为1.56 x 1.56 x 0.6 mm³，可确保PCB放置的高度灵活性。BMM150提供超低电压操作（Vdd电压范围为1.62V至3.6V，Vddio电压范围为1.2V至3.6V），可以编程以优化客户特定应用中的功能、性能和功耗。可编程中断引擎为开发人员提供了设计灵活性。

LibDriver BMM150是LibDriver推出的BMM150全功能驱动，该驱动提供磁场连读模式读取、磁场单次模式读取和中断检测等功能并且它符合MISRA标准。

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
    - [example interrupt](#example-interrupt)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver BMM150的源文件。

/interface目录包含了LibDriver BMM150与平台无关的IIC, SPI总线模板。

/test目录包含了LibDriver BMM150驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver BMM150编程范例。

/doc目录包含了LibDriver BMM150离线文档。

/datasheet目录包含了BMM150数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

/misra目录包含了LibDriver MISRA代码扫描结果。

### 安装

参考/interface目录下与平台无关的IIC, SPI总线模板，完成指定平台的IIC, SPI总线驱动。

将/src目录，您使用平台的接口驱动和您开发的驱动加入工程，如果您想要使用默认的范例驱动，可以将/example目录加入您的工程。

### 使用

您可以参考/example目录下的编程范例完成适合您的驱动，如果您想要使用默认的编程范例，以下是它们的使用方法。

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

### 文档

在线文档: [https://www.libdriver.com/docs/bmm150/index.html](https://www.libdriver.com/docs/bmm150/index.html)。

离线文档: /doc/html/index.html。

### 贡献

请参考CONTRIBUTING.md。

### 版权

版权 (c) 2015 - 现在 LibDriver 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com。