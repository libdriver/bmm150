[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver BMM150

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/bmm150/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

BMM150是一款用於消費市場應用的獨立地磁感測器。 它允許量測三個垂直軸上的磁場。 基於博世專有的FlipCore科技，BMM150的效能和功能經過精心調整，完全符合電子羅盤等所有三軸移動應用的苛刻要求。 導航或增強現實。 評估電路（ASlC）將地磁感測器的輸出轉換為數位結果，可以通過行業標準數位介面（SPI和l2C）讀取。 BMM150的封裝和介面設計可滿足多種硬體要求。 由於該感測器具有超小的尺寸面積和扁平的封裝，囙此非常適合移動應用。 晶圓級晶片級封裝（WLCSP）的尺寸僅為1.56 x 1.56 x 0.6 mm³，可確保PCB放置的高度靈活性。 BMM150提供超低電壓操作（Vdd電壓範圍為1.62V至3.6V，Vddio電壓範圍為1.2V至3.6V），可以程式設計以優化客戶特定應用中的功能、效能和功耗。 可程式設計中斷引擎為開發人員提供了設計靈活性。

LibDriver BMM150是LibDriver推出的BMM150全功能驅動，該驅動提供磁場連讀模式讀取、磁場單次模式讀取和中斷檢測等功能並且它符合MISRA標準。

### 目錄

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
    - [example interrupt](#example-interrupt)
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver BMM150的源文件。

/interface目錄包含了LibDriver BMM150與平台無關的IIC, SPI總線模板。

/test目錄包含了LibDriver BMM150驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver BMM150編程範例。

/doc目錄包含了LibDriver BMM150離線文檔。

/datasheet目錄包含了BMM150數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

/misra目錄包含了LibDriver MISRA程式碼掃描結果。

### 安裝

參考/interface目錄下與平台無關的IIC, SPI總線模板，完成指定平台的IIC, SPI總線驅動。

將/src目錄，您使用平臺的介面驅動和您開發的驅動加入工程，如果您想要使用默認的範例驅動，可以將/example目錄加入您的工程。

### 使用

您可以參考/example目錄下的程式設計範例完成適合您的驅動，如果您想要使用默認的程式設計範例，以下是它們的使用方法。

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

### 文檔

在線文檔: [https://www.libdriver.com/docs/bmm150/index.html](https://www.libdriver.com/docs/bmm150/index.html)。

離線文檔: /doc/html/index.html。

### 貢獻

請參攷CONTRIBUTING.md。

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com。