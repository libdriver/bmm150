[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver BMM150

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/bmm150/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

BMM150은 소비자 시장 애플리케이션을 위한 독립형 지자기 센서입니다. 3개의 수직 축에서 자기장을 측정할 수 있습니다. 보쉬의 독점 기술인 FlipCore 기술을 기반으로 하는 BMM150의 성능과 기능은 세심하게 조정되어 전자 나침반, 내비게이션, 증강 현실 등 모든 3축 모바일 애플리케이션의 까다로운 요구 사항을 완벽하게 충족합니다. 평가 회로(ASIC)는 지자기 센서의 출력을 디지털 결과로 변환하여 산업 표준 디지털 인터페이스(SPI 및 I2C)를 통해 판독할 수 있습니다. BMM150의 패키지와 인터페이스는 다양한 하드웨어 요구 사항을 충족하도록 설계되었습니다. 초소형 풋프린트와 플랫 패키지를 특징으로 하는 이 센서는 모바일 애플리케이션에 매우 적합합니다. 1.56 x 1.56 x 0.6 mm³ 크기의 웨이퍼 레벨 칩 스케일 패키지(WLCSP)는 PCB 배치 시 높은 유연성을 보장합니다. BMM150은 초저전압 동작(Vdd 전압 범위 1.62V ~ 3.6V, Vddio 전압 범위 1.2V ~ 3.6V)을 제공하며, 고객 맞춤형 애플리케이션에서 기능, 성능 및 전력 소비를 최적화하도록 프로그래밍할 수 있습니다. 프로그래밍 가능한 인터럽트 엔진은 개발자에게 설계 유연성을 제공합니다.

LibDriver BMM150은 LibDriver에서 출시한 BMM150용 모든 기능을 갖춘 드라이버입니다. 단일 판독, 연속 판독, 임계값 인터럽트 및 추가 기능을 제공합니다. LibDriver는 MISRA를 준수합니다.

### 콘텐츠

  - [설명](#설명)
  - [설치](#설치)
  - [사용](#사용)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
    - [example interrupt](#example-interrupt)
  - [문서](#문서)
  - [기고](#기고)
  - [저작권](#저작권)
  - [문의하기](#문의하기)

### 설명

/src 디렉토리에는 LibDriver BMM150의 소스 파일이 포함되어 있습니다.

/interface 디렉토리에는 LibDriver BMM150용 플랫폼 독립적인 IIC, SPI버스 템플릿이 포함되어 있습니다.

/test 디렉토리에는 LibDriver BMM150드라이버 테스트 프로그램이 포함되어 있어 칩의 필요한 기능을 간단히 테스트할 수 있습니다.

/example 디렉토리에는 LibDriver BMM150프로그래밍 예제가 포함되어 있습니다.

/doc 디렉토리에는 LibDriver BMM150오프라인 문서가 포함되어 있습니다.

/datasheet 디렉토리에는 BMM150데이터시트가 있습니다.

/project 디렉토리에는 일반적으로 사용되는 Linux 및 마이크로컨트롤러 개발 보드의 프로젝트 샘플이 포함되어 있습니다. 모든 프로젝트는 디버깅 방법으로 셸 스크립트를 사용하며, 자세한 내용은 각 프로젝트의 README.md를 참조하십시오.

/misra 에는 LibDriver misra 코드 검색 결과가 포함됩니다.

### 설치

/interface 디렉토리에서 플랫폼 독립적인IIC, SPI버스 템플릿을 참조하여 지정된 플랫폼에 대한IIC, SPI버스 드라이버를 완성하십시오.

/src 디렉터리, 플랫폼용 인터페이스 드라이버 및 자체 드라이버를 프로젝트에 추가합니다. 기본 예제 드라이버를 사용하려면 /example 디렉터리를 프로젝트에 추가합니다.

### 사용

/example 디렉터리의 예제를 참조하여 자신만의 드라이버를 완성할 수 있습니다. 기본 프로그래밍 예제를 사용하려는 경우 사용 방법은 다음과 같습니다.

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

```c
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

### 문서

온라인 문서: [https://www.libdriver.com/docs/bmm150/index.html](https://www.libdriver.com/docs/bmm150/index.html).

오프라인 문서: /doc/html/index.html.

### 기고

CONTRIBUTING.md 를 참조하십시오.

### 저작권

저작권 (c) 2015 - 지금 LibDriver 판권 소유

MIT 라이선스(MIT)

이 소프트웨어 및 관련 문서 파일("소프트웨어")의 사본을 얻은 모든 사람은 이에 따라 무제한 사용, 복제, 수정, 통합, 출판, 배포, 2차 라이선스를 포함하여 소프트웨어를 처분할 수 있는 권리가 부여됩니다. 소프트웨어의 사본에 대한 라이선스 및/또는 판매, 그리고 소프트웨어가 위와 같이 배포된 사람의 권리에 대한 2차 라이선스는 다음 조건에 따릅니다.

위의 저작권 표시 및 이 허가 표시는 이 소프트웨어의 모든 사본 또는 내용에 포함됩니다.

이 소프트웨어는 상품성, 특정 목적에의 적합성 및 비침해에 대한 보증을 포함하되 이에 국한되지 않는 어떠한 종류의 명시적 또는 묵시적 보증 없이 "있는 그대로" 제공됩니다. 어떤 경우에도 저자 또는 저작권 소유자는 계약, 불법 행위 또는 기타 방식에 관계없이 소프트웨어 및 기타 소프트웨어 사용으로 인해 발생하거나 이와 관련하여 발생하는 청구, 손해 또는 기타 책임에 대해 책임을 지지 않습니다.

### 문의하기

연락주세요lishifenging@outlook.com.