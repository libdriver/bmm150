[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver BMM150

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/bmm150/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

Der BMM150 ist ein eigenständiger geomagnetischer Sensor für Anwendungen im Consumer-Bereich. Er ermöglicht die Messung des Magnetfelds in drei zueinander senkrechten Achsen. Basierend auf der proprietären FlipCore-Technologie von Bosch sind Leistung und Funktionen des BMM150 präzise abgestimmt und erfüllen optimal die hohen Anforderungen aller mobilen 3-Achsen-Anwendungen wie elektronische Kompasse, Navigationssysteme oder Augmented Reality. Eine Auswertungsschaltung (ASlC) wandelt die Messwerte des geomagnetischen Sensors in digitale Ergebnisse um, die über die branchenüblichen digitalen Schnittstellen (SPI und I2C) ausgelesen werden können. Gehäuse und Schnittstellen des BMM150 sind für eine Vielzahl von Hardwareanforderungen ausgelegt. Dank seiner extrem kleinen Abmessungen und des flachen Gehäuses eignet sich der Sensor hervorragend für mobile Anwendungen. Das Wafer-Level Chip Scale Package (WLCSP) mit Abmessungen von nur 1,56 x 1,56 x 0,6 mm³ gewährleistet hohe Flexibilität bei der Leiterplattenplatzierung. Der BMM150 ermöglicht den Betrieb mit extrem niedriger Spannung (Vdd-Spannungsbereich von 1,62 V bis 3,6 V, Vddio-Spannungsbereich von 1,2 V bis 3,6 V) und kann zur Optimierung von Funktionalität, Leistung und Stromverbrauch in kundenspezifischen Anwendungen programmiert werden. Die programmierbare Interrupt-Engine bietet dem Entwickler hohe Flexibilität bei der Gestaltung.

LibDriver BMM150 ist ein umfassender Treiber für BMM150, entwickelt von LibDriver. Er bietet Einzel- und Dauermessung, Schwellenwertunterbrechung und weitere Funktionen. LibDriver ist MISRA-konform.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
    - [example interrupt](#example-interrupt)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver BMM150-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver BMM150 IIC, SPI.

/test enthält den Testcode des LibDriver BMM150-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver BMM150-Beispielcode.

/doc enthält das LibDriver BMM150-Offlinedokument.

/Datenblatt enthält BMM150-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige IIC, SPI-Schnittstellenvorlage und stellen Sie Ihren Plattform-IIC, SPI-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

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

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/bmm150/index.html](https://www.libdriver.com/docs/bmm150/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.