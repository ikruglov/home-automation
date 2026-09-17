# AP7921 firmware

ESPHome configuration for the ESP32-C6 replacement controller installed in the
[AP7921 retrofit](../README.md). This targets the replacement board, not the
original APC controller.

## Build

Use Python 3.11 or newer and ESPHome **2026.7.4**:

```sh
cd esp32-ap7921/firmware
python3 -m venv .venv
. .venv/bin/activate
python -m pip install -r requirements.txt
cp secrets.example.yaml secrets.yaml
```

Replace both dummy credentials in `secrets.yaml` before installing firmware.
Generate an API encryption key with:

```sh
python -c 'import base64, secrets; print(base64.b64encode(secrets.token_bytes(32)).decode())'
```

Use a separate, unique OTA password. Then validate and build:

```sh
esphome config esphome.yaml
esphome compile esphome.yaml
```

Compilation downloads the ESP-IDF toolchain and dependencies. The TM1650
component is pinned to commit `5c1f2490f87fbff75e097f4131b7d80884f38ad7`;
the CH390 component dependency is pinned in `components/ethernet/__init__.py`.
Build commands do not flash a device.

Ethernet uses DHCP. The default device name is `ap7921`, and the Home Assistant
native API uses port 6053. Edit the name in `esphome.yaml` if needed.
`secrets.yaml`, virtual environments, and build outputs are ignored by Git.

## Configuration layout

| File | Responsibility |
|---|---|
| `esphome.yaml` | Board configuration, packages, component sources, API and OTA |
| `common.yaml` | Connectivity status, uptime, restart button, Home Assistant time |
| `pdu/ethernet.yaml` | CH390H SPI Ethernet |
| `pdu/i2c.yaml` | Separate display and relay buses |
| `pdu/display.yaml` | Current display, brightness, orientation, IP scrolling |
| `pdu/outlets.yaml`, `pdu/outlet.yaml` | Eight outlets, persisted state, startup delays and restrictions |
| `pdu/cold_start.h` | RTC marker for detecting loss of power |
| `pdu/bl0939.yaml` | Total input current, die temperature and estimated apparent power |
| `pdu/load.yaml` | Load thresholds and indications |
| `pdu/psu.yaml` | Both internal supply voltages |
| `pdu/status_led.yaml` | Network and hardware-fault indication |
| `pdu/buttons.yaml` | Local button gestures and recovery settings |
| [components/](components/) | Local Ethernet, PCF8574 and BL0939 modifications |

## Behaviour and measurements

The relay expander stays powered during a controller reset. The local PCF8574
component adopts its existing outputs, and template switches avoid forcing new
levels during startup. The `preserve_outputs` option assumes **all expander pins
are outputs**.

Cold-start settings apply after power loss: each outlet can remain off, turn on,
or restore its previous state after an independent delay. The RTC marker is
cross-checked against the expander's live state. Retention of that marker through
an EN-pin reset is an assumption noted in `cold_start.h`; do not treat the marker
alone as proof of the reset cause.

Hold Action for five seconds to scroll the IP address, or ten seconds to rotate
the display. Safe mode is configured for ten unsuccessful boots, a ten-second
good-boot window, and a sixty-second recovery timeout.

Current includes the PDU's own consumption. The current multiplier and supply
voltage scaling are retained from this board and are not universal calibration
constants. `nominal_voltage` defaults to **230 V**. Estimated apparent power is
current multiplied by that assumed voltage, expressed in VA; it is not measured
real power. Temperature is the metering chip's die temperature.

A missing current reading becomes unavailable after 35 seconds. Load indications
clear and outlet turn-on restrictions do not block on an unavailable reading.
These software restrictions are not a replacement for electrical protection.

## Differences from the home configuration

The public configuration uses an example device name, the standard API port,
a nominal 230 V assumption, and dummy credentials. The estimated-power entity
is labelled as apparent power in VA. Private installation measurements and
hardware design notes have been removed from comments. GPIO assignments,
current calibration, outlet control, and local component code are retained.
