### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

SPI Pin: SCLK/MOSI/MISO/CS GPIO11/GPIO10/GPIO9/GPIO8.

GPIO Pin: INT GPIO17.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(bmm150 REQUIRED)
```

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
./bmm150 -i

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
./bmm150 -p

bmm150: SPI interface SCK connected to GPIO11(BCM).
bmm150: SPI interface MISO connected to GPIO9(BCM).
bmm150: SPI interface MOSI connected to GPIO10(BCM).
bmm150: SPI interface CS connected to GPIO8(BCM).
bmm150: IIC interface SCL connected to GPIO3(BCM).
bmm150: IIC interface SDA connected to GPIO2(BCM).
bmm150: INT connected to GPIO17(BCM).
```

```shell
./bmm150 -t reg --addr=0 --interface=iic

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
bmm150: set low threshold 83.
bmm150: check low threshold ok.
bmm150: bmm150_set_high_threshold/bmm150_get_high_threshold test.
bmm150: set high threshold -86.
bmm150: check high threshold ok.
bmm150: bmm150_set_repxy_number/bmm150_get_repxy_number test.
bmm150: set repxy number 162.
bmm150: check repxy number ok.
bmm150: bmm150_set_repz_number/bmm150_get_repz_number test.
bmm150: set repz number 85.
bmm150: check repz number ok.
bmm150: bmm150_interrupt_threshold_convert_to_register/bmm150_interrupt_threshold_convert_to_data test.
bmm150: set interrupt threshold 79.30uT.
bmm150: check interrupt threshold 78.00uT.
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
./bmm150 -t read --addr=0 --interface=iic --times=3

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
bmm150: x is 28.23uT.
bmm150: y is 21.92uT.
bmm150: z is -4.23uT.
bmm150: x is 28.60uT.
bmm150: y is 21.91uT.
bmm150: z is -3.84uT.
bmm150: x is 27.86uT.
bmm150: y is 21.17uT.
bmm150: z is -3.84uT.
bmm150: set data rate 6hz.
bmm150: x is 28.98uT.
bmm150: y is 21.92uT.
bmm150: z is -3.08uT.
bmm150: x is 28.97uT.
bmm150: y is 22.29uT.
bmm150: z is -3.85uT.
bmm150: x is 28.60uT.
bmm150: y is 21.54uT.
bmm150: z is -3.46uT.
bmm150: set data rate 8hz.
bmm150: x is 28.23uT.
bmm150: y is 22.29uT.
bmm150: z is -3.85uT.
bmm150: x is 28.23uT.
bmm150: y is 22.29uT.
bmm150: z is -3.46uT.
bmm150: x is 28.23uT.
bmm150: y is 21.55uT.
bmm150: z is -2.31uT.
bmm150: set data rate 10hz.
bmm150: x is 27.86uT.
bmm150: y is 21.92uT.
bmm150: z is -3.46uT.
bmm150: x is 27.86uT.
bmm150: y is 21.55uT.
bmm150: z is -4.24uT.
bmm150: x is 28.23uT.
bmm150: y is 22.29uT.
bmm150: z is -2.69uT.
bmm150: set data rate 15hz.
bmm150: x is 28.24uT.
bmm150: y is 20.81uT.
bmm150: z is -3.47uT.
bmm150: x is 28.98uT.
bmm150: y is 22.29uT.
bmm150: z is -3.08uT.
bmm150: x is 27.87uT.
bmm150: y is 21.18uT.
bmm150: z is -3.85uT.
bmm150: set data rate 20hz.
bmm150: x is 27.87uT.
bmm150: y is 21.92uT.
bmm150: z is -3.86uT.
bmm150: x is 28.24uT.
bmm150: y is 21.92uT.
bmm150: z is -3.47uT.
bmm150: x is 27.87uT.
bmm150: y is 21.92uT.
bmm150: z is -3.86uT.
bmm150: set data rate 25hz.
bmm150: x is 28.62uT.
bmm150: y is 21.18uT.
bmm150: z is -4.25uT.
bmm150: x is 27.87uT.
bmm150: y is 21.18uT.
bmm150: z is -3.09uT.
bmm150: x is 27.50uT.
bmm150: y is 21.18uT.
bmm150: z is -2.70uT.
bmm150: set data rate 30hz.
bmm150: x is 27.88uT.
bmm150: y is 22.30uT.
bmm150: z is -3.09uT.
bmm150: x is 28.25uT.
bmm150: y is 21.56uT.
bmm150: z is -4.64uT.
bmm150: x is 28.25uT.
bmm150: y is 21.93uT.
bmm150: z is -3.48uT.
bmm150: single read test.
bmm150: set data rate 2hz.
bmm150: x is 28.23uT.
bmm150: y is 21.92uT.
bmm150: z is -3.46uT.
bmm150: x is 28.60uT.
bmm150: y is 21.55uT.
bmm150: z is -3.85uT.
bmm150: x is 27.86uT.
bmm150: y is 20.80uT.
bmm150: z is -4.23uT.
bmm150: set data rate 6hz.
bmm150: x is 28.23uT.
bmm150: y is 21.17uT.
bmm150: z is -3.85uT.
bmm150: x is 28.23uT.
bmm150: y is 21.54uT.
bmm150: z is -4.61uT.
bmm150: x is 28.23uT.
bmm150: y is 21.92uT.
bmm150: z is -3.84uT.
bmm150: set data rate 8hz.
bmm150: x is 28.60uT.
bmm150: y is 21.17uT.
bmm150: z is -3.46uT.
bmm150: x is 28.60uT.
bmm150: y is 21.17uT.
bmm150: z is -3.85uT.
bmm150: x is 28.60uT.
bmm150: y is 22.29uT.
bmm150: z is -3.46uT.
bmm150: set data rate 10hz.
bmm150: x is 28.60uT.
bmm150: y is 21.91uT.
bmm150: z is -4.23uT.
bmm150: x is 28.23uT.
bmm150: y is 22.66uT.
bmm150: z is -3.46uT.
bmm150: x is 28.23uT.
bmm150: y is 21.54uT.
bmm150: z is -3.85uT.
bmm150: set data rate 15hz.
bmm150: x is 29.34uT.
bmm150: y is 21.92uT.
bmm150: z is -3.84uT.
bmm150: x is 28.97uT.
bmm150: y is 21.54uT.
bmm150: z is -3.46uT.
bmm150: x is 28.60uT.
bmm150: y is 22.29uT.
bmm150: z is -3.46uT.
bmm150: set data rate 20hz.
bmm150: x is 28.60uT.
bmm150: y is 21.17uT.
bmm150: z is -4.23uT.
bmm150: x is 28.97uT.
bmm150: y is 21.54uT.
bmm150: z is -4.61uT.
bmm150: x is 28.23uT.
bmm150: y is 21.54uT.
bmm150: z is -3.84uT.
bmm150: set data rate 25hz.
bmm150: x is 28.60uT.
bmm150: y is 21.91uT.
bmm150: z is -3.46uT.
bmm150: x is 28.60uT.
bmm150: y is 22.29uT.
bmm150: z is -3.46uT.
bmm150: x is 28.23uT.
bmm150: y is 21.17uT.
bmm150: z is -3.07uT.
bmm150: set data rate 30hz.
bmm150: x is 28.23uT.
bmm150: y is 21.91uT.
bmm150: z is -3.84uT.
bmm150: x is 28.60uT.
bmm150: y is 21.54uT.
bmm150: z is -4.61uT.
bmm150: x is 28.23uT.
bmm150: y is 21.54uT.
bmm150: z is -4.23uT.
bmm150: finish read test.
```

```shell
./bmm150 -t int --addr=0 --interface=iic --low-threshold=6 --high-threshold=48 --times=3

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
./bmm150 -e basic --addr=0 --interface=iic --times=3

bmm150: 1/3.
bmm150: x is 26.401uT.
bmm150: y is 23.798uT.
bmm150: z is -2.713uT.
bmm150: 2/3.
bmm150: x is 26.404uT.
bmm150: y is 24.172uT.
bmm150: z is -2.327uT.
bmm150: 3/3.
bmm150: x is 26.033uT.
bmm150: y is 23.801uT.
bmm150: z is -2.716uT.
```

```shell
./bmm150 -e shot --addr=0 --interface=iic --times=3

bmm150: 1/3.
bmm150: x is 26.012uT.
bmm150: y is 24.154uT.
bmm150: z is -3.086uT.
bmm150: 2/3.
bmm150: x is 26.010uT.
bmm150: y is 23.781uT.
bmm150: z is -2.698uT.
bmm150: 3/3.
bmm150: x is 26.010uT.
bmm150: y is 23.780uT.
bmm150: z is -2.313uT.
```

```shell
./bmm150 -e int --addr=0 --interface=iic --low-threshold=6 --high-threshold=48 --times=3

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
./bmm150 -h

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

#### 3.3 Command Problem

1. There is some unknown problem in the iic interface of bmm150 on the raspberry board, interrupt  command will run failed.

2. There is some unknown problem in the spi interface of bmm150 on the raspberry board, all commands will run failed.
