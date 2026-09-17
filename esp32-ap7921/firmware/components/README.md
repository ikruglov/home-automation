# Local ESPHome components

These directories contain components vendored from ESPHome **2026.7.4**, with
local changes for this controller. They override the corresponding built-in
components through `external_components` in `../esphome.yaml`.

| Component | Local changes |
|---|---|
| `ethernet` | CH390 type and SPI configuration, Espressif CH390 driver dependency, reset timing and receive-task stack configuration |
| `pcf8574` | `preserve_outputs`: read and adopt the existing port state without the initial output write |
| `bl0939` | Internal temperature and VT input voltage decoding; disable anti-creep for this current-only measurement circuit |

The PCF8574 option assumes every pin is an output. Template switches are used
because ordinary GPIO switches can write their initial levels during setup.

The BL0939 change is intended for this board's current-only circuit. The VT
reading is a voltage, not a temperature; a thermistor conversion would need its
own configuration. Only die temperature is enabled here.

Ethernet uses Espressif's [`espressif/ch390`](https://components.espressif.com/components/espressif/ch390)
driver, pinned to **0.4.1**. That dependency is fetched at build time rather than
copied into this directory. The separately pinned TM1650 component is fetched
from [trip5/esphome-tm1650](https://github.com/trip5/esphome-tm1650).

The local component source is unchanged from the working private configuration.
Upstream submission of reusable changes is planned.
