[← All projects](../README.md)

# Create ceiling-fan retrofit

**A custom ESP32-C3 interface board and ESPHome configuration for fan, light, and buzzer control in Home Assistant.**

<img src="images/assembled-pcb-front.jpg" width="280" alt="Assembled replacement PCB, front: ESP32-C3 module, flash and reset buttons, and programming connections">
<img src="images/assembled-pcb-back.jpg" width="280" alt="Assembled replacement PCB, back">

*The assembled replacement board, front and back.*

## Design

The PCB replaces the WBR3 Wi-Fi module and associated daughterboard arrangement in the [Create ceiling fan](https://www.create-store.com/uk/2401-buy-ceiling-fans) shown below. The replacement uses an ESP32-C3 running ESPHome and communicates with the existing appliance controller through the Tuya UART protocol.

The fan's existing controller remains responsible for appliance control; ESPHome provides the [Tuya MCU protocol component](https://esphome.io/components/tuya/).

## PCB design

The replacement board combines the ESP32-C3 module, support components, flash/reset buttons, and programming connections in the footprint shown below. Components and routing occupy both sides of the board; the module's antenna area is marked at the top of the layout.

<a href="images/pcb-design-front.png"><img src="images/pcb-design-front.png" width="320" alt="Front PCB layout showing ESP32-C3 placement, antenna area, buttons, and programming header"></a>
<a href="images/pcb-design-back.png"><img src="images/pcb-design-back.png" width="320" alt="Back PCB layout showing support components and routing"></a>

*Front and back layout views. Select either image for full resolution.*

[PCB source](kicad/create-celing-fan.kicad_pcb) · [Schematic source](kicad/create-celing-fan.kicad_sch) · [KiCad project](kicad/create-celing-fan.kicad_pro)

<details>
<summary>View the schematic</summary>

![Replacement interface-board schematic](images/schematics.png)

</details>

### Fit in the original controller

<img src="images/installed-pcb-1.jpg" width="560" alt="Custom ESP32-C3 interface board fitted to the original ceiling-fan controller assembly">

*The replacement interface board fitted to the existing controller assembly. The board outline and connection positions need to suit this hardware; the original motor and light controller remains in place.*

## System overview

```mermaid
flowchart LR
    HA[Home Assistant] <-->|Wi-Fi / ESPHome API| ESP[Custom ESP32-C3 board]
    ESP <-->|Tuya UART · 9600 baud| MCU[Existing fan controller]
    MCU --> FAN[Fan]
    MCU --> LIGHT[Light]
```

The published configuration disables UART logging to leave that serial interface available for communication with the fan controller. Fan, light, and buzzer entities use `ALWAYS_OFF` as their configured restore mode.

## Published firmware capabilities

The [ESPHome configuration](esphome.yaml) maps the following Tuya datapoints:

| Function | Datapoint(s) | Configuration |
|---|---|---|
| Fan | 60, 62, 63 | On/off, six speed levels, direction |
| Light | 20, 22 | On/off and brightness |
| Buzzer | 66 | On/off |

It also exposes connection status, Wi-Fi signal, uptime, and a restart button. Color-temperature settings are commented out in the published YAML and are not presented here as an implemented feature.

## Compatibility and sources

**Match the controller hardware, not just the fan's product name.** This project was developed for a fan that already had Wi-Fi. The original project notes identify different controller modules sold under the same Create model name; compare your hardware with the original-board photographs below.

| File | Contents |
|---|---|
| [esphome.yaml](esphome.yaml) | ESP32-C3 configuration and Tuya datapoint mappings |
| [kicad/](kicad/) | Schematic, PCB layout, KiCad project, and component CSV |

Before adapting the configuration, replace the `XXX` Wi-Fi placeholders and review device naming, API encryption, and OTA authentication. GPIO assignments and datapoint mappings describe the hardware shown here.

The photographs document assembly and fitment to the original controller. They do not establish compatibility with other controller revisions.

## Build gallery

<details>
<summary>Additional installation photograph</summary>

![Replacement board fitted to the controller, second view](images/installed-pcb-2.jpg)

</details>

### Original hardware

<details>
<summary>Original board and installation — compare these before adapting the design</summary>

The original photographed assembly does not have a separate 5 V ↔ 3.3 V logic daughterboard.

![Original controller PCB, front](images/original-pcb-front.jpg)
![Original controller PCB, back](images/original-pcb-back.jpg)
![Original controller installed](images/original-pcb-installed.jpg)

</details>
