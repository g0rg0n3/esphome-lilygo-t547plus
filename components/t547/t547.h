#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/core/version.h"
#include "esphome/components/display/display_buffer.h"

#include "epd_driver.h"

namespace esphome {
namespace t547 {

class T547 : public display::DisplayBuffer {
 public:
  T547() = default;

  void set_greyscale(bool greyscale) { this->greyscale_ = greyscale; }

  // Component methods
  float get_setup_priority() const override;
  void dump_config() override;
  void setup() override;
  void update() override;

  // DisplayBuffer methods
#if ESPHOME_VERSION_CODE >= VERSION_CODE(2022,6,0)
  display::DisplayType get_display_type() override { return get_greyscale() ? display::DisplayType::DISPLAY_TYPE_GRAYSCALE : display::DisplayType::DISPLAY_TYPE_BINARY; }
#endif
  // Draw the actual pixel
  void draw_absolute_pixel_internal(int x, int y, Color color) override;

  void display();
  void clean();

  uint8_t get_panel_state() const { return this->panel_on_; }
  bool get_greyscale() const { return this->greyscale_; }

 protected:
  int get_width_internal() override { return 960; }
  int get_height_internal() override { return 540; }
  size_t get_buffer_length_();

  void eink_off_();
  void eink_on_();

  uint8_t panel_on_ = 0;
  uint8_t temperature_ = 0;
  bool greyscale_ = true;
};

}  // namespace t547
}  // namespace esphome
