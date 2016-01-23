#include <pebble.h>

Window *window;
TextLayer *text_layer;

char buffer[] = "00:00";

void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);
  text_layer_set_text(text_layer, buffer);
}

void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  
}

void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  
}

void select_click_handler(ClickRecognizerRef recognzier, void *context) {
  text_layer_set_text(text_layer, "Emergency triggered.\n You have %S seconds to cancel. Press up button to cancel");
}

void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
}

void window_load(Window* window) {
  text_layer = text_layer_create(GRect(0, 53, 132, 168));
  text_layer_set_background_color(text_layer, GColorClear);
  text_layer_set_text_color(text_layer, GColorBlack);
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_LECO_20_BOLD_NUMBERS));
  text_layer_set_text(text_layer, "Press the select button to trigger emergency");
  layer_add_child(window_get_root_layer(window), (Layer*) text_layer);

}

void window_unload(Window* window) {
  
}

void init() {
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  window_set_click_config_provider(window, click_config_provider);
  window_stack_push(window, true);
  
}

void deinit() {
  tick_timer_service_unsubscribe();
  text_layer_destroy(text_layer);
  window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
