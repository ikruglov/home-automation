#pragma once

#include <esp_attr.h>
#include <cstdint>

// Distinguishing a cold start from a reset is not possible through
// esp_reset_reason(): the ESP32-C6 has no ESP_RST_EXT case at all, so an EN-pin
// reset reports ESP_RST_POWERON exactly like applying power (see
// components/esp_system/port/soc/esp32c6/reset_reason.c).
//
// RTC_NOINIT_ATTR memory gives the distinction the reset reason cannot. It is
// SRAM in the always-on RTC domain that the startup code deliberately does not
// initialise, so its contents survive anything that does not remove power -
// software restart, OTA reboot, EN-pin reset. A genuine cold start leaves it
// holding whatever the SRAM powers up with, which will not be our magic value.
//
// NOTE: that RTC SRAM survives an EN-pin reset specifically is inference from
// how the part is built - EN does not gate the RTC domain's supply - not
// something confirmed on this board. Verify it before relying on the ON/OFF
// policies: switch an outlet on, press Reset, and check it stays on.

namespace pdu {

RTC_NOINIT_ATTR uint32_t cold_start_marker;

// Arbitrary; only has to be a value uninitialised SRAM is unlikely to hold.
constexpr uint32_t COLD_START_MAGIC = 0x50445531;  // "PDU1"

/// True when this boot follows an actual loss of power, false after a reset or
/// a software restart. Latched on first call - the marker is stamped there, so
/// every later call in the same boot returns the same answer.
inline bool is_cold_start() {
  static const bool cold = [] {
    const bool result = cold_start_marker != COLD_START_MAGIC;
    cold_start_marker = COLD_START_MAGIC;
    return result;
  }();
  return cold;
}

}  // namespace pdu
