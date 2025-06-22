# esp32-create-ceiling-fan-tuya

Schematic, PCB design, and ESPHome configuration for integrating [Create
Ceiling Fan](https://www.create-store.com/uk/2401-buy-ceiling-fans) into Home
Assistant.

I've designed a custom PCB with an ESP32-c3 chip, which completely replaces the
WBR3 and daughter boards. I then used ESPHome to flash the chip with the Tuya
config.

Note: The fan should already have WiFi. Plus, unfortunately, the same Create
Ceiling Fan model has different underlying control modules. So, for this repo
to be practical, your fan should be exactly like mine. See the attached
pictures.

## Source code
* [esphome.yaml](esphome.yaml) - ESPHome YAML configuration file
* [kicad](kicad) - KiCad PCB source code

## Pictures

### Original PCB

Note: There is no daughter board with 5v<->3.3v logic.

* original PCB

![](images/original-pcb-front.jpg "Original PCB front")
![](images/original-pcb-back.jpg "Original PCB back")

* original PCB installed  

![](images/original-pcb-installed.jpg "Original PCB installed")

### New PCB

* schematics

![](images/schematics.png "Schematics")

* PCB design

![](images/pcb-design-front.png "PCB design front")
![](images/pcb-design-back.png "PCB design back")

* assembled PCB

![](images/assembled-pcb-front.jpg "Assembled PCB front")
![](images/assembled-pcb-back.jpg "Assembled PCB back")

* installed PCB

![](images/installed-pcb-1.jpg "PCB installed 1")
![](images/installed-pcb-2.jpg "PCB installed 2")
