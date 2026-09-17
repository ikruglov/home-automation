# Water-meter firmware

Development configuration for the [custom water-meter board](../README.md).
Uses ESPHome **2026.7.4**, ESP32-C6, and ESP-IDF.

## Build

From the repository root:

```sh
cd esp32-water-meter/firmware
python3 -m venv .venv
source .venv/bin/activate
python -m pip install -r requirements.txt
test -f secrets.yaml || cp secrets.example.yaml secrets.yaml
esphome config esphome.yaml
esphome compile esphome.yaml
```

The example credentials are sufficient for compilation. Before installing,
replace the Wi-Fi settings, API encryption key, and OTA password in
`secrets.yaml`. Generate an API key with:

```sh
python -c 'import base64, secrets; print(base64.b64encode(secrets.token_bytes(32)).decode())'
```

`secrets.yaml`, `.esphome/`, and `.venv/` are ignored. Compilation does not
flash hardware. The public API port is 6053; the private configuration used
a different port. Configuration validation and C++ source generation passed; compilation is not yet
verified for this export.

## Sensor and backup-power scope

The 18650 is intended to maintain counting during loss of USB power. Wi-Fi is
the current transport; no Zigbee implementation is included.

Only SENSOR_1 on GPIO5 is counted. SENSOR_2 on GPIO4 is routed in hardware but
not configured here. Using the two sensors to reject repeated boundary crossings
requires sequence logic and suitable sensor placement; the current 200 ms
debounce is not that two-sensor implementation.

## Configuration

| Substitution | Default | Purpose |
|---|---|---|
| `liters_per_pulse` | `1` | Meter-specific pulse-to-volume conversion |
| `pulse_debounce` | `200ms` | Filter sensor transitions |
| `persist_coalesce` | `15s` | Delay before requesting a preference flush |
| `charger_debounce` | `2s` | Filter charger-status changes |

The initial-reading entity provides an offset in m³. Changing it changes the
reported total. Counter reset also changes the cumulative entities; these are
configuration operations, not normal consumption events.

The counter is restored from preferences. Persistence is delayed, so abrupt
power loss can lose recent counts; the loss window needs hardware verification.
The battery ADC uses the board's 2:1 scaling. Charger-status decoding assumes
the charge/full signal meanings used by this design.

## USB and logging

`usb_dp.h` controls the ESP32-C6 USB Serial/JTAG D+ pull-up. Firmware disables
it early during startup and enables it when GPIO6 detects USB power. Logs use
**UART0**, not USB Serial/JTAG, so the logger does not override that control.
Serial logging requires a UART adapter on the board's debug connection.

This helper and all executable control logic are retained from the private
configuration. Development commentary was condensed; no claim of completed
USB compliance, battery-life testing, or end-to-end metering validation is made.
