# Home automation · hardware & firmware

PCBs and ESPHome configurations for connecting existing appliances to Home Assistant.

Each project includes design notes, KiCad sources, firmware configuration, and photographs of the assembled hardware.

<table>
<tr>
<td align="center" width="50%">
<a href="esp32-create-ceiling-fan-tuya/"><img src="esp32-create-ceiling-fan-tuya/images/assembled-pcb-front.jpg" height="240" alt="Assembled ESP32-C3 replacement board"></a>
</td>
<td align="center" width="50%">
<a href="esp32-climarad-v2x/"><img src="esp32-climarad-v2x/images/assembled-pcb-1.png" height="240" alt="Assembled Climarad carrier board with Waveshare modules"></a>
</td>
</tr>
<tr>
<td valign="top">
<strong><a href="esp32-create-ceiling-fan-tuya/">Create ceiling-fan retrofit</a></strong><br>
A replacement PCB with an ESP32-C3 module, support components, and programming connections, fitted to the original fan controller. ESPHome provides fan, light, and buzzer control over Tuya UART.<br><br>
<sub>PCB design · ESP32-C3 · Wi-Fi · Tuya UART</sub>
</td>
<td valign="top">
<strong><a href="esp32-climarad-v2x/">Climarad ventilation interface</a></strong><br>
A carrier PCB connecting existing Ethernet/PoE and isolated RS485 modules, with a printed enclosure and Modbus integration for Home Assistant.<br><br>
<sub>Carrier PCB · ESP32-S3 · Ethernet / PoE · RS485 / Modbus</sub>
</td>
</tr>
</table>

## Design decisions

| Project | Requirement | Approach | Boundary |
|---|---|---|---|
| Ceiling-fan retrofit | Expose the existing fan and light controls in Home Assistant | A custom ESP32-C3 board replaces the Wi-Fi interface and communicates with the retained controller over Tuya UART | Board fit and datapoint mappings are specific to the controller shown |
| Climarad interface | Connect ventilation controls and measurements to Home Assistant; power the interface through PoE | A custom carrier PCB combines Ethernet/PoE and isolated RS485 modules; ESPHome maps Modbus registers into entities | Uses the unit's Modbus interface and requires its device address |

Both projects use ESPHome's firmware framework and protocol components. The Climarad interface uses Waveshare modules for its ESP32, PoE, and isolated RS485 functions.

## Explore the projects

| Project | Hardware | Firmware | Additional material |
|---|---|---|---|
| [Create ceiling fan](esp32-create-ceiling-fan-tuya/) | [KiCad design](esp32-create-ceiling-fan-tuya/kicad/) | [ESPHome configuration](esp32-create-ceiling-fan-tuya/esphome.yaml) | [Original and replacement hardware](esp32-create-ceiling-fan-tuya/#build-gallery) |
| [Climarad Sensa V2X](esp32-climarad-v2x/) | [KiCad design](esp32-climarad-v2x/kicad/) | [ESPHome configuration](esp32-climarad-v2x/esphome.yaml) | [Printable enclosure](esp32-climarad-v2x/case.3mf) |

These are hardware-specific project records. Read the compatibility and configuration notes before adapting a design to another appliance.

## License

- **Design files, documentation, and photographs:** [CC BY-NC 4.0](LICENSES/CC-BY-NC-4.0.txt).
- **Software and ESPHome configurations:** [PolyForm Noncommercial 1.0.0](LICENSES/PolyForm-Noncommercial-1.0.0.txt).

For commercial licensing, contact Ivan Kruglov. See [LICENSE](LICENSE) for scope.
