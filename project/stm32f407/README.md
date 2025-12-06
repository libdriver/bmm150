### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

SPI Pin: SCK/MISO/MOSI/CS  PA5/PA6/PA7/PA4.

GPIO Pin: INT PB0.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. BMM150

#### 3.1 Command Instruction

1. Show bmm150 chip and driver information.

   ```shell
   bmm150 (-i | --information)
   ```

2. Show bmm150 help.

   ```shell
   bmm150 (-h | --help)
   ```

3. Show bmm150 pin connections of the current board.

   ```shell
   bmm150 (-p | --port)
   ```

4. Run bmm150 register test.

   ```shell
   bmm150 (-t reg | --test=reg) [--addr=<0 | 1 | 2 | 3>] [--interface=<iic | spi>]
   ```

5. Run bmm150 read test, num means the test times.

   ```shell
   bmm150 (-t read | --test=read) [--addr=<0 | 1 | 2 | 3>] [--interface=<iic | spi>] [--times=<num>]
   ```

6. Run bmm150 interrupt test, num means the test times, ut means the threshold in ut.

   ```shell
   bmm150 (-t int | --test=int) [--addr=<0 | 1 | 2 | 3>] [--interface=<iic | spi>] [--low-threshold=<ut>] [--high-threshold=<ut>] [--times=<num>]
   ```

8. Run bmm150 basic function, num is the read times.

   ```shell
   bmm150 (-e basic | --example=basic) [--addr=<0 | 1 | 2 | 3>] [--interface=<iic | spi>] [--times=<num>]
   ```

9. Run bmm150 shot function, num is the read times.

   ```shell
   bmm150 (-e shot | --example=shot) [--addr=<0 | 1 | 2 | 3>] [--interface=<iic | spi>] [--times=<num>]
   ```

10. Run bmm150 interrupt function, num means the test times, ut means the threshold in ut.

    ```shell
    bmm150 (-e int | --example=int) [--addr=<0 | 1 | 2 | 3>] [--interface=<iic | spi>] [--low-threshold=<ut>] [--high-threshold=<ut>] [--times=<num>]
    ```

#### 3.2 Command Example

```shell
bmm150 -i

bmm150: chip is Bosch BMM150.
bmm150: manufacturer is Bosch.
bmm150: interface is IIC SPI.
bmm150: driver version is 1.0.
bmm150: min supply voltage is 1.6V.
bmm150: max supply voltage is 3.6V.
bmm150: max current is 20.00mA.
bmm150: max temperature is 85.0C.
bmm150: min temperature is -40.0C.
```

```shell
bmm150 -p

bmm150: SPI interface SCK connected to GPIOA PIN5.
bmm150: SPI interface MISO connected to GPIOA PIN6.
bmm150: SPI interface MOSI connected to GPIOA PIN7.
bmm150: SPI interface CS connected to GPIOA PIN4.
bmm150: IIC interface SCL connected to GPIOB PIN8.
bmm150: IIC interface SDA connected to GPIOB PIN9.
bmm150: INT connected to GPIOB PIN0.
```

```shell
bmm150 -t reg --addr=0 --interface=iic

bmm150: chip is Bosch BMM150.
bmm150: manufacturer is Bosch.
bmm150: interface is IIC SPI.
bmm150: driver version is 1.0.
bmm150: min supply voltage is 1.6V.
bmm150: max supply voltage is 3.6V.
bmm150: max current is 20.00mA.
bmm150: max temperature is 85.0C.
bmm150: min temperature is -40.0C.
bmm150: start register test.
bmm150: bmm150_set_interface/bmm150_get_interface test.
bmm150: set interface iic.
bmm150: check interface ok.
bmm150: set interface spi.
bmm150: check interface ok.
bmm150: bmm150_set_addr_pin/bmm150_get_addr_pin test.
bmm150: set addr csb sdo 00.
bmm150: check addr pin ok.
bmm150: set addr csb sdo 01.
bmm150: check addr pin ok.
bmm150: set addr csb sdo 10.
bmm150: check addr pin ok.
bmm150: set addr csb sdo 11.
bmm150: check addr pin ok.
bmm150: bmm150_set_power_on/bmm150_get_power_on test.
bmm150: disable power on .
bmm150: check power on ok.
bmm150: enable power on .
bmm150: check power on ok.
bmm150: bmm150_set_spi_wire/bmm150_get_spi_wire test.
bmm150: set spi wire4.
bmm150: check spi wire on ok.
bmm150: set spi wire3.
bmm150: check spi wire on ok.
bmm150: bmm150_set_advanced_self_test/bmm150_get_advanced_self_test test.
bmm150: set advanced self test positive mode.
bmm150: check advanced self test ok.
bmm150: set advanced self test negative mode.
bmm150: check advanced self test ok.
bmm150: set advanced self test normal mode.
bmm150: check advanced self test ok.
bmm150: bmm150_set_data_rate/bmm150_get_data_rate test.
bmm150: set data rate 10hz.
bmm150: check data rate ok.
bmm150: set data rate 2hz.
bmm150: check data rate ok.
bmm150: set data rate 6hz.
bmm150: check data rate ok.
bmm150: set data rate 8hz.
bmm150: check data rate ok.
bmm150: set data rate 15hz.
bmm150: check data rate ok.
bmm150: set data rate 20hz.
bmm150: check data rate ok.
bmm150: set data rate 25hz.
bmm150: check data rate ok.
bmm150: set data rate 30hz.
bmm150: check data rate ok.
bmm150: bmm150_set_mode/bmm150_get_mode test.
bmm150: set normal mode.
bmm150: check mode ok.
bmm150: set forced mode.
bmm150: check mode ok.
bmm150: set sleep mode.
bmm150: check mode ok.
bmm150: bmm150_set_self_test/bmm150_get_self_test test.
bmm150: enable self test.
bmm150: check self test ok.
bmm150: disable self test.
bmm150: check self test ok.
bmm150: bmm150_set_interrupt/bmm150_get_interrupt test.
bmm150: enable data overrun.
bmm150: check interrupt ok.
bmm150: disable data overrun.
bmm150: check interrupt ok.
bmm150: enable overflow.
bmm150: check interrupt ok.
bmm150: disable overflow.
bmm150: check interrupt ok.
bmm150: enable high threshold z.
bmm150: check interrupt ok.
bmm150: disable high threshold z.
bmm150: check interrupt ok.
bmm150: enable high threshold y.
bmm150: check interrupt ok.
bmm150: disable high threshold y.
bmm150: check interrupt ok.
bmm150: enable high threshold x.
bmm150: check interrupt ok.
bmm150: disable high threshold x.
bmm150: check interrupt ok.
bmm150: enable low threshold z.
bmm150: check interrupt ok.
bmm150: disable low threshold z.
bmm150: check interrupt ok.
bmm150: enable low threshold y.
bmm150: check interrupt ok.
bmm150: disable low threshold y.
bmm150: check interrupt ok.
bmm150: enable low threshold x.
bmm150: check interrupt ok.
bmm150: disable low threshold x.
bmm150: check interrupt ok.
bmm150: bmm150_set_data_ready_pin/bmm150_get_data_ready_pin test.
bmm150: enable data ready pin.
bmm150: check data ready pin ok.
bmm150: disable data ready pin.
bmm150: check data ready pin ok.
bmm150: bmm150_set_interrupt_pin/bmm150_get_interrupt_pin test.
bmm150: enable interrupt pin.
bmm150: check interrupt pin ok.
bmm150: disable interrupt pin.
bmm150: check interrupt pin ok.
bmm150: bmm150_set_channel_z/bmm150_get_channel_z test.
bmm150: enable channel z.
bmm150: check channel z ok.
bmm150: disable channel z.
bmm150: check channel z ok.
bmm150: enable channel y.
bmm150: check channel y ok.
bmm150: disable channel y.
bmm150: check channel y ok.
bmm150: enable channel x.
bmm150: check channel x ok.
bmm150: disable channel x.
bmm150: check channel x ok.
bmm150: bmm150_set_data_ready_pin_polarity/bmm150_get_data_ready_pin_polarity test.
bmm150: set data ready pin polarity low.
bmm150: check data ready pin polarity x ok.
bmm150: set data ready pin polarity high.
bmm150: check data ready pin polarity x ok.
bmm150: bmm150_set_interrupt_latch/bmm150_get_interrupt_latch test.
bmm150: enable interrupt latch.
bmm150: check interrupt latch ok.
bmm150: disable interrupt latch.
bmm150: check interrupt latch ok.
bmm150: bmm150_set_interrupt_pin_polarity/bmm150_get_interrupt_pin_polarity test.
bmm150: set interrupt pin polarity low.
bmm150: check interrupt pin polarity ok.
bmm150: set interrupt pin polarity high.
bmm150: check interrupt pin polarity ok.
bmm150: bmm150_set_low_threshold/bmm150_get_low_threshold test.
bmm150: set low threshold 68.
bmm150: check low threshold ok.
bmm150: bmm150_set_high_threshold/bmm150_get_high_threshold test.
bmm150: set high threshold -67.
bmm150: check high threshold ok.
bmm150: bmm150_set_repxy_number/bmm150_get_repxy_number test.
bmm150: set repxy number 184.
bmm150: check repxy number ok.
bmm150: bmm150_set_repz_number/bmm150_get_repz_number test.
bmm150: set repz number 95.
bmm150: check repz number ok.
bmm150: bmm150_interrupt_threshold_convert_to_register/bmm150_interrupt_threshold_convert_to_data test.
bmm150: set interrupt threshold 58.30uT.
bmm150: check interrupt threshold 54.00uT.
bmm150: bmm150_get_self_test_x test.
bmm150: check self test x true.
bmm150: bmm150_get_self_test_y test.
bmm150: check self test y true.
bmm150: bmm150_get_self_test_z test.
bmm150: check self test z true.
bmm150: bmm150_get_data_ready_status test.
bmm150: check data ready status false.
bmm150: bmm150_get_interrupt_status test.
bmm150: check data overrun interrupt status false.
bmm150: check overflow interrupt status false.
bmm150: check high threshold z interrupt status false.
bmm150: check high threshold y interrupt status false.
bmm150: check high threshold x interrupt status false.
bmm150: check low threshold z interrupt status false.
bmm150: check low threshold y interrupt status false.
bmm150: check low threshold x interrupt status false.
bmm150: bmm150_soft_reset test.
bmm150: check soft reset ok.
bmm150: finish register test.
```

```shell
bmm150 -t read --addr=0 --interface=iic --times=3

bmm150: chip is Bosch BMM150.
bmm150: manufacturer is Bosch.
bmm150: interface is IIC SPI.
bmm150: driver version is 1.0.
bmm150: min supply voltage is 1.6V.
bmm150: max supply voltage is 3.6V.
bmm150: max current is 20.00mA.
bmm150: max temperature is 85.0C.
bmm150: min temperature is -40.0C.
bmm150: start read test.
bmm150: continuous read test.
bmm150: set data rate 2hz.
bmm150: x is -30.52uT.
bmm150: y is 17.49uT.
bmm150: z is 12.10uT.
bmm150: x is -30.89uT.
bmm150: y is 17.12uT.
bmm150: z is 11.32uT.
bmm150: x is -31.64uT.
bmm150: y is 17.49uT.
bmm150: z is 10.93uT.
bmm150: set data rate 6hz.
bmm150: x is -31.27uT.
bmm150: y is 17.12uT.
bmm150: z is 12.11uT.
bmm150: x is -31.64uT.
bmm150: y is 16.75uT.
bmm150: z is 12.11uT.
bmm150: x is -31.27uT.
bmm150: y is 17.12uT.
bmm150: z is 11.72uT.
bmm150: set data rate 8hz.
bmm150: x is -31.64uT.
bmm150: y is 16.38uT.
bmm150: z is 10.94uT.
bmm150: x is -31.64uT.
bmm150: y is 17.50uT.
bmm150: z is 10.94uT.
bmm150: x is -31.64uT.
bmm150: y is 16.75uT.
bmm150: z is 12.11uT.
bmm150: set data rate 10hz.
bmm150: x is -31.27uT.
bmm150: y is 16.01uT.
bmm150: z is 11.34uT.
bmm150: x is -31.64uT.
bmm150: y is 16.38uT.
bmm150: z is 11.73uT.
bmm150: x is -31.27uT.
bmm150: y is 16.38uT.
bmm150: z is 13.29uT.
bmm150: set data rate 15hz.
bmm150: x is -31.28uT.
bmm150: y is 16.76uT.
bmm150: z is 10.18uT.
bmm150: x is -31.28uT.
bmm150: y is 17.13uT.
bmm150: z is 12.13uT.
bmm150: x is -30.90uT.
bmm150: y is 16.38uT.
bmm150: z is 11.74uT.
bmm150: set data rate 20hz.
bmm150: x is -31.65uT.
bmm150: y is 16.76uT.
bmm150: z is 12.14uT.
bmm150: x is -31.28uT.
bmm150: y is 16.38uT.
bmm150: z is 10.97uT.
bmm150: x is -32.02uT.
bmm150: y is 16.76uT.
bmm150: z is 11.36uT.
bmm150: set data rate 25hz.
bmm150: x is -30.54uT.
bmm150: y is 16.39uT.
bmm150: z is 10.98uT.
bmm150: x is -32.03uT.
bmm150: y is 17.13uT.
bmm150: z is 12.16uT.
bmm150: x is -30.91uT.
bmm150: y is 17.13uT.
bmm150: z is 11.37uT.
bmm150: set data rate 30hz.
bmm150: x is -31.29uT.
bmm150: y is 17.13uT.
bmm150: z is 11.38uT.
bmm150: x is -31.66uT.
bmm150: y is 17.13uT.
bmm150: z is 11.78uT.
bmm150: x is -32.03uT.
bmm150: y is 16.39uT.
bmm150: z is 10.99uT.
bmm150: single read test.
bmm150: set data rate 2hz.
bmm150: x is -32.01uT.
bmm150: y is 16.38uT.
bmm150: z is 11.72uT.
bmm150: x is -33.13uT.
bmm150: y is 17.12uT.
bmm150: z is 11.72uT.
bmm150: x is -32.76uT.
bmm150: y is 16.38uT.
bmm150: z is 10.15uT.
bmm150: set data rate 6hz.
bmm150: x is -32.76uT.
bmm150: y is 17.12uT.
bmm150: z is 11.33uT.
bmm150: x is -32.01uT.
bmm150: y is 16.38uT.
bmm150: z is 10.94uT.
bmm150: x is -32.01uT.
bmm150: y is 16.75uT.
bmm150: z is 11.32uT.
bmm150: set data rate 8hz.
bmm150: x is -32.38uT.
bmm150: y is 16.75uT.
bmm150: z is 10.54uT.
bmm150: x is -33.13uT.
bmm150: y is 16.38uT.
bmm150: z is 11.33uT.
bmm150: x is -32.76uT.
bmm150: y is 17.12uT.
bmm150: z is 10.94uT.
bmm150: set data rate 10hz.
bmm150: x is -31.64uT.
bmm150: y is 16.75uT.
bmm150: z is 9.37uT.
bmm150: x is -32.01uT.
bmm150: y is 17.50uT.
bmm150: z is 10.55uT.
bmm150: x is -32.75uT.
bmm150: y is 16.38uT.
bmm150: z is 10.15uT.
bmm150: set data rate 15hz.
bmm150: x is -32.38uT.
bmm150: y is 16.75uT.
bmm150: z is 11.33uT.
bmm150: x is -33.13uT.
bmm150: y is 16.38uT.
bmm150: z is 10.93uT.
bmm150: x is -32.38uT.
bmm150: y is 16.75uT.
bmm150: z is 10.15uT.
bmm150: set data rate 20hz.
bmm150: x is -31.64uT.
bmm150: y is 17.12uT.
bmm150: z is 10.54uT.
bmm150: x is -32.01uT.
bmm150: y is 17.12uT.
bmm150: z is 11.32uT.
bmm150: x is -32.01uT.
bmm150: y is 16.75uT.
bmm150: z is 11.32uT.
bmm150: set data rate 25hz.
bmm150: x is -32.38uT.
bmm150: y is 16.38uT.
bmm150: z is 10.54uT.
bmm150: x is -32.01uT.
bmm150: y is 16.38uT.
bmm150: z is 10.15uT.
bmm150: x is -32.01uT.
bmm150: y is 17.49uT.
bmm150: z is 10.54uT.
bmm150: set data rate 30hz.
bmm150: x is -32.01uT.
bmm150: y is 16.75uT.
bmm150: z is 10.54uT.
bmm150: x is -32.01uT.
bmm150: y is 17.12uT.
bmm150: z is 10.54uT.
bmm150: x is -32.01uT.
bmm150: y is 16.38uT.
bmm150: z is 10.94uT.
bmm150: finish read test.
```

```shell
bmm150 -t int --addr=0 --interface=iic --low-threshold=6 --high-threshold=48 --times=3

bmm150: chip is Bosch BMM150.
bmm150: manufacturer is Bosch.
bmm150: interface is IIC SPI.
bmm150: driver version is 1.0.
bmm150: min supply voltage is 1.6V.
bmm150: max supply voltage is 3.6V.
bmm150: max current is 20.00mA.
bmm150: max temperature is 85.0C.
bmm150: min temperature is -40.0C.
bmm150: start interrupt test.
bmm150: irq low threshold x.
bmm150: irq low threshold z.
bmm150: find interrupt.
bmm150: irq low threshold z.
bmm150: x is -32.01uT.
bmm150: y is 16.38uT.
bmm150: z is 10.93uT.
bmm150: irq low threshold x.
bmm150: irq low threshold z.
bmm150: find interrupt.
bmm150: x is -32.38uT.
bmm150: y is 16.75uT.
bmm150: z is 9.76uT.
bmm150: irq low threshold x.
bmm150: irq low threshold z.
bmm150: find interrupt.
bmm150: x is -32.75uT.
bmm150: y is 16.38uT.
bmm150: z is 9.75uT.
bmm150: finish interrupt test.
```

```shell
bmm150 -e basic --addr=0 --interface=iic --times=3

bmm150: 1/3.
bmm150: x is -38.393uT.
bmm150: y is 12.301uT.
bmm150: z is 3.552uT.
bmm150: 2/3.
bmm150: x is -38.397uT.
bmm150: y is 12.302uT.
bmm150: z is 3.554uT.
bmm150: 3/3.
bmm150: x is -39.141uT.
bmm150: y is 11.929uT.
bmm150: z is 2.764uT.
```

```shell
bmm150 -e shot --addr=0 --interface=iic --times=3

bmm150: 1/3.
bmm150: x is -38.364uT.
bmm150: y is 12.291uT.
bmm150: z is 3.139uT.
bmm150: 2/3.
bmm150: x is -38.736uT.
bmm150: y is 11.919uT.
bmm150: z is 1.962uT.
bmm150: 3/3.
bmm150: x is -38.364uT.
bmm150: y is 12.664uT.
bmm150: z is 2.355uT.
```

```shell
bmm150 -e int --addr=0 --interface=iic --low-threshold=6 --high-threshold=48 --times=3

bmm150: irq low threshold x.
bmm150: irq low threshold z.
bmm150: find interrupt.
bmm150: x is -38.36uT.
bmm150: y is 12.29uT.
bmm150: z is 1.57uT.
bmm150: irq low threshold z.
bmm150: irq low threshold x..
bmm150: find interrupt.
bmm150: x is -38.36uT.
bmm150: y is 12.66uT.
bmm150: z is 1.96uT.
bmm150: irq low threshold z.
bmm150: irq low threshold x.
bmm150: find interrupt.
bmm150: x is -38.36uT.
bmm150: y is 12.66uT.
bmm150: z is 1.96uT.
```

```shell
bmm150 -h

Usage:
  bmm150 (-i | --information)
  bmm150 (-h | --help)
  bmm150 (-p | --port)
  bmm150 (-t reg | --test=reg) [--addr=<0 | 1 | 2 | 3>] [--interface=<iic | spi>]
  bmm150 (-t read | --test=read) [--addr=<0 | 1 | 2 | 3>] [--interface=<iic | spi>] [--times=<num>]
  bmm150 (-t int | --test=int) [--addr=<0 | 1 | 2 | 3>] [--interface=<iic | spi>]
         [--low-threshold=<ut>] [--high-threshold=<ut>] [--times=<num>]
  bmm150 (-e basic | --example=basic) [--addr=<0 | 1 | 2 | 3>] [--interface=<iic | spi>] [--times=<num>]
  bmm150 (-e shot | --example=shot) [--addr=<0 | 1 | 2 | 3>] [--interface=<iic | spi>] [--times=<num>]
  bmm150 (-e int | --example=int) [--addr=<0 | 1 | 2 | 3>] [--interface=<iic | spi>]
         [--low-threshold=<ut>] [--high-threshold=<ut>] [--times=<num>]

Options:
      --addr=<0 | 1 | 2 | 3>         Set the chip address.([default: 0])
  -e <basic | shot | int>, --example=<basic | shot | int>
                                     Run the driver example.
  -h, --help                         Show the help.
      --high-threshold=<ut>          Set the interrupt high threshold in ut.([default: 48.0])
  -i, --information                  Show the chip information.
      --interface=<iic | spi>        Set the chip interface.([default: iic])
      --low-threshold=<ut>           Set the interrupt low threshold in ut.([default: 6.0])
  -p, --port                         Display the pin connections of the current board.
  -t <reg | read | int>, --test=<reg | read | int>
                                     Run the driver test.
      --times=<num>                  Set the running times.([default: 3])
```

