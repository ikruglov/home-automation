# Water-meter hardware

Open `water-meter.kicad_pro` with **KiCad 10** and matching standard libraries.
The schematic and PCB use file-format versions `20260306` and `20260206`.

Included:

- Schematic, PCB layout, and project settings.
- Project-local FS8205A and JLCImport symbols used by this design.
- Three JLCImport footprints and their referenced 3D models.
- Project-relative library tables and model paths.

The design also references **Espressif's `PCM_Espressif` library** for the
ESP32-C6 module. Install that library separately for library-based editing and
updates; placed symbols and footprints are embedded in the design files. Its
3D model currently uses the original `KICAD8_3RD_PARTY` variable. Configure that
variable for the installed library location, or update the model path locally.
Standard models use `KICAD10_3DMODEL_DIR`.

This export changes local library/model paths, not the circuit or routing.
The custom symbol library contains only the symbols needed here; unrelated
private-project libraries are excluded. Production outputs and editor state
are not included.

## Open work

The private design's TODO still lists **F1 value/selection** as unresolved.
The firmware development notes describe modifications to the sensor input
and USB power handling; reconcile those with the assembled revision before
using these files to build another board.

KiCad ERC/DRC and schematic-to-PCB agreement have not been checked for this
export. Regenerate manufacturing outputs only after reviewing the design.

## Protection-circuit references

The PCB's stored pad nets place Q6 (AO3401A, LCSC C347476) in the battery
positive connection, with its gate referenced to BAT−: the intended reverse
insertion protection stage. Q1 is a separate MOSFET in the USB/battery power
path. See the [Q6 datasheet](https://www.lcsc.com/datasheet/C347476.pdf).

U5 is labelled DW01A in the schematic and carries LCSC C686633. Its OD/OC
outputs drive Q5, the dual battery-disconnect MOSFET. The
[datasheet linked to C686633](https://www.lcsc.com/datasheet/C686633.pdf)
identifies the part as DW01 and documents overcharge, overdischarge,
overcurrent, and short-circuit detection. Confirm the fitted variant before
relying on specific thresholds; no thresholds are claimed on the project page.

F1 is a resettable fuse in the battery-positive path. USBLC6 protection and
SMAJ12A TVS devices are also present at the external interfaces/sensor supply.
Protection functions are identified from the design; fault performance has not
been independently verified for this export.
