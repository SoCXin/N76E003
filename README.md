# [N76E003](https://github.com/sochub/N76E003)

[![sites](http://182.61.61.133/link/resources/SoC.png)](https://stop.stops.top) 

#### [Vendor](https://github.com/sochub/Vendor)：[nuvoton](https://github.com/sochub/nuvoton)
#### [MCS51](https://github.com/sochub/MCS51)：[8051](https://github.com/sochub/8051)
#### [Level](https://github.com/sochub/Level)：16MHz 

## [N76E003简介](https://github.com/sochub/N76E003/wiki)

N76E003是新唐高速1T 8051 单片机产品，18 KB Flash ROM、1 KB SRAM，支持2.4V - 5.5V宽工作电压，具备高抗干扰能力7KV ESD/4KV EFT。

N76E003 在20 pin封装下提供高达18根I/O脚位；周边包含双串口、SPI、I²C、6通道PWM输出；内建优于同类产品之 < 2% 误差之高精确度16 MHz RC晶振与高分辨率8通道12位ADC；

N76E003是低成本高可靠性单片机的代表，价格在同规格产品很有竞争力，各种外设齐全，具备自我唤醒欠压检测等功能。

[![sites](docs/N76E003.png)](http://www.nuvoton.com.cn/hq/products/microcontrollers/8bit-8051-mcus/low-pin-count-8051-series/n76e003/?__locale=zh)

关键特性：

* 超高性价比低成本MCU
* 接口全面，兼容性强

### [资源组成](https://github.com/sochub/N76E003)

* [文档](docs/)
* [固件](firmware/)
	* [IAR工程](firmware/IAR)
	* [Keil工程](firmware/Keil)
	* [SDCC工程](firmware/SDCC)
	* [ISP引导工程](firmware/ISP)
* [硬件](hardware/)
	* [kicad资源](hardware/kicad/)
	* [AD资源](hardware/AD/)
* [工具](tools)

#### [外部资源](https://github.com/sochub/N76E003)

* [官方硬件资料](http://www.nuvoton.com.cn/hq/support/tool-and-software/development-tool-hardware/development-kit/?__locale=zh)
* [官方开源代码](https://github.com/OpenNuvoton/N76E003-BSP)

#### [硬件资源](https://github.com/sochub/N76E003)

* N76E003AS20 封装：TSSOP20 (4.4mm x 6.5mm)

[![sites](docs/TSSOP20.png)](http://www.qitas.cn)
[![sites](hardware/AD/N76E003-SCH.png)](http://www.qitas.cn)
[![sites](hardware/AD/N76E003-PCB.png)](http://www.qitas.cn)

TSSOP20封装兼容升级替换可选[STM32F030F4](https://github.com/sochub/STM32F030F4)

* N76E003AQ20 封装：QFN20 (3mm x 3mm, O.4mm pitch)
* N76E003BQ20 封装：QFN20 (3mm x 3mm, O.5mm pitch)

[![sites](docs/QFN20.png)](http://www.qitas.cn)
[![sites](hardware/AD/N76E003AQ.png)](http://www.qitas.cn)

### [选型建议](https://github.com/sochub)

[N76E003](https://github.com/sochub/N76E003)在规模产品中十分有竞争力，各种外设全面，厂商提供源码工具，但是在开源硬件中少见，对于SDCC编译的资源不是很多。

* 同系替换方案[N76E](https://www.nuvoton.com/hq/products/microcontrollers/8bit-8051-mcus/low-pin-count-8051-series/?__locale=zh)
* 兼容替换方案[STM8S003F3P6](https://github.com/sochub/STM8S003)
* 兼容替换方案[C8051F330](https://github.com/sochub/C8051F330)

##  [SoC资源平台](http://www.qitas.cn)
