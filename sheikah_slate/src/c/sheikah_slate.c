#include <pebble.h>
#include <string.h>

#define NUM_RUNES 7
#define UI_COLOR 0x55ffff
#define NUM_NOTCHES 5
#define NUM_WEATHER_ICONS 6 
#define MAX_CHARS 22
// Persistent storage key
#define SETTINGS_KEY 1

#define FRAME_X 17
#define FRAME_Y 29
#define FRAME_SIZE 110
#define TRIFORCE_PIXELS 9

#define DEMO_MODE false
#define DEMO_BATTERY 10
#define DEMO_CHARGING false
#define DEMO_TEMPERATURE 60
#define DEMO_CONDITIONS 2
#define DEMO_RUNE 0
#define DEMO_BLUETOOTH true
#define DEMO_CYCLE true
#define DEMO_CYCLE_POS 4

static Window *s_main_window;

static TextLayer *s_time_layer, *s_date_layer, *s_left_column_layer, *s_right_column_layer;
static BitmapLayer *s_rune_layer, *s_bt_icon_layer, *s_weather_icon_layer,
  *s_splash_left_layer, *s_splash_right_layer, *s_splash_left_eye_layer, *s_splash_right_eye_layer;
static Layer *s_battery_layer, *s_temperature_layer, *s_frame_layer, *s_fringes_layer;

static GFont s_time_font, s_date_font, s_sheikah_font;
static GBitmap *s_rune_bitmap, *s_bt_icon_bitmap_conn, *s_bt_icon_bitmap_disc,
  *s_weather_icon_bitmap, *s_splash_left_bitmap, *s_splash_right_bitmap,
  *s_splash_left_eye_bitmap, *s_splash_right_eye_bitmap;

static uint8_t s_battery_level;
static bool s_charging, s_date_set, s_weather_loaded, s_splash_anim_started;
static int s_cur_frame;
static uint8_t s_weather_minutes_elapsed, s_rune_minutes_elapsed;

typedef enum weather {
  SUNNY,
  PARTLYCLOUDY,
  CLOUDY,
  RAINY,
  SNOWY,
  STORMY
} Weather;

// Demo values
static char s_demo_times[][8] = {
  "05:33",
  "8:22",
  "14:01",
  "20:00",
  "11:59",
  "03:15"
};

static char s_demo_dates[][8] = {
  "Mar 22",
  "Jul 05",
  "Dec 31",
  "Feb 18",
  "Nov 28",
  "Jan 01"
};

static bool s_demo_bluetooth[] = {
  true,
  true,
  true,
  false,
  false,
  false
};

static uint8_t s_demo_battery[] = {
  80,
  50,
  10,
  100,
  70,
  30
};

static bool s_demo_charging[] = {
  false,
  false,
  false,
  false,
  true,
  true
};

static Weather s_demo_weather[] = {
  SUNNY,
  PARTLYCLOUDY,
  CLOUDY,
  STORMY,
  RAINY,
  SNOWY
};

static int s_demo_temperature[] = {
  100,
  80,
  60,
  40,
  90,
  0
};

static uint8_t s_demo_runes[] = {
  0,
  2,
  3,
  4,
  5,
  6
};

// Define settings struct
typedef struct ClaySettings {
  char LeftColumnText[MAX_CHARS];  // text for left column
  char RightColumnText[MAX_CHARS]; // text for right column
  bool RunesToChoose[NUM_RUNES];   // the runes to display
  int RuneChangeRate;              // how often to switch runes
  bool UseCurrentLocation;         // use GPS for weather?
  int WeatherCheckRate;            // how often to check weather
  char Latitude[MAX_CHARS];        // latitude when not using GPS
  char Longitude[MAX_CHARS];       // longitude when not using GPS
  bool TemperatureMetric;          // Celsius or Fahrenheit?
  int Temperature0;                // Coldest temperature
  int Temperature1;                // Cold temperature
  int Temperature2;                // Comfortable temperature
  int Temperature3;                // Hot temperature
  int Temperature4;                // Hottest temperature
  int TEMPERATURE;                 // Current temperature
  Weather CONDITIONS;              // Current weather conditions
  bool AmericanDate;               // use American date format (Jan 01)?
  bool VibrateOnDisc;              // vibrate on bluetooth disconnect?
} ClaySettings;

static ClaySettings settings;

// Runes in the center of the screen
static const uint32_t RUNES[] = {
  RESOURCE_ID_IMAGE_RUNE_BOMB_ROUND,
  RESOURCE_ID_IMAGE_RUNE_BOMB_SQUARE,
  RESOURCE_ID_IMAGE_RUNE_MAGNESIS,
  RESOURCE_ID_IMAGE_RUNE_STASIS,
  RESOURCE_ID_IMAGE_RUNE_CRYONIS,
  RESOURCE_ID_IMAGE_RUNE_CAMERA,
  RESOURCE_ID_IMAGE_RUNE_CYCLE
};

// Weather icons for different weather
static const uint32_t WEATHER_ICONS[] = {
  RESOURCE_ID_IMAGE_WEATHER_SUNNY,  
  RESOURCE_ID_IMAGE_WEATHER_PARTLYCLOUDY,
  RESOURCE_ID_IMAGE_WEATHER_CLOUDY,
  RESOURCE_ID_IMAGE_WEATHER_RAINY,
  RESOURCE_ID_IMAGE_WEATHER_SNOWY,
  RESOURCE_ID_IMAGE_WEATHER_STORMY
};

// mini bitmaps (triforces)
// each bit corresponds to a pixel of the triforce
// they're 9x9, so we hardcode the last pixel later
static const uint8_t top_left[] = {127,187,89,232,23,11,5,6,5};
static const uint8_t top_right[] = {254,221,154,23,232,208,160,96,160};
static const uint8_t bottom_left[] = {5,6,5,11,23,232,89,187,127};
static const uint8_t bottom_right[] = {160,96,160,208,232,23,154,221,254};

static int TEMP_NOTCHES[] = {30, 50, 70, 85, 100};
static int TEMP_ANGLE_NOTCHES[] = {-130, -60, 0, 60, 130};
// Coldest, Cold, Comfortable, Hot, Hottest

static void update_date();

// draw the triforces in the corner of the rune frame
static void draw_triforce(GContext *ctx, uint8_t corner){
#if defined(PBL_RECT)
  graphics_context_set_stroke_color(ctx, PBL_IF_BW_ELSE(GColorWhite, GColorFromHEX(UI_COLOR)));
  static uint8_t i;
  uint8_t x = 0, y = 0;
  int basex = 0, basey = 0;
  bool pixel_val = false;
  // draw the top left
  if (corner == 0) {
    basex = basex;
    basey = basey;
    for (i = 0; i < TRIFORCE_PIXELS; i++){
      // here, we hardcode the left column
      graphics_context_set_stroke_color(ctx, i == 8 ? GColorBlack : PBL_IF_BW_ELSE(GColorWhite, GColorFromHEX(UI_COLOR)));
      graphics_draw_pixel(ctx, GPoint(basex+x, basey+y));
      x++;
      for (uint8_t j = 0; j < 8; j++) {
        pixel_val = ((top_left[i] >> j) & 1) == 1;
        graphics_context_set_stroke_color(ctx, pixel_val ? PBL_IF_BW_ELSE(GColorWhite, GColorFromHEX(UI_COLOR)) : GColorBlack);
        graphics_draw_pixel(ctx, GPoint(basex+x, basey+y));
        x++;
      }
      y++;
      x=0;
    }
  }
  // draw the top right
  if (corner == 1) {
    basex = basex+FRAME_SIZE-TRIFORCE_PIXELS;
    basey = basey;
    for (i = 0; i < TRIFORCE_PIXELS; i++){
      for (uint8_t j = 0; j < 8; j++) {
        pixel_val = ((top_right[i] >> j) & 1) == 1;
        graphics_context_set_stroke_color(ctx, pixel_val ? PBL_IF_BW_ELSE(GColorWhite, GColorFromHEX(UI_COLOR)) : GColorBlack);
        graphics_draw_pixel(ctx, GPoint(basex+x, basey+y));
        x++;
      }
      // here, we hardcode the right column
      graphics_context_set_stroke_color(ctx, i == 8 ? GColorBlack : PBL_IF_BW_ELSE(GColorWhite, GColorFromHEX(UI_COLOR)));
      graphics_draw_pixel(ctx, GPoint(basex+x, basey+y));
      y++;
      x=0;
    }
  }
  // draw the bottom left
  if (corner == 2) {
    basex = basex;
    basey = basey+FRAME_SIZE-TRIFORCE_PIXELS;
    for (i = 0; i < TRIFORCE_PIXELS; i++){
      // here, we hardcode the left column
      graphics_context_set_stroke_color(ctx, i == 0 ? GColorBlack : PBL_IF_BW_ELSE(GColorWhite, GColorFromHEX(UI_COLOR)));
      graphics_draw_pixel(ctx, GPoint(basex+x, basey+y));
      x++;
      for (uint8_t j = 0; j < 8; j++) {
        pixel_val = ((bottom_left[i] >> j) & 1) == 1;
        graphics_context_set_stroke_color(ctx, pixel_val ? PBL_IF_BW_ELSE(GColorWhite, GColorFromHEX(UI_COLOR)) : GColorBlack);
        graphics_draw_pixel(ctx, GPoint(basex+x, basey+y));
        x++;
      }
      y++;
      x=0;
    }
  }
  // draw the bottom right
  if (corner == 3) {
    basex = basex+FRAME_SIZE-TRIFORCE_PIXELS;
    basey = basey+FRAME_SIZE-TRIFORCE_PIXELS;
    for (i = 0; i < TRIFORCE_PIXELS; i++){
      for (uint8_t j = 0; j < 8; j++) {
        pixel_val = ((bottom_right[i] >> j) & 1) == 1;
        graphics_context_set_stroke_color(ctx, pixel_val ? PBL_IF_BW_ELSE(GColorWhite, GColorFromHEX(UI_COLOR)) : GColorBlack);
        graphics_draw_pixel(ctx, GPoint(basex+x, basey+y));
        x++;
      }
      // here, we hardcode the right column
      graphics_context_set_stroke_color(ctx, i == 0 ? GColorBlack : PBL_IF_BW_ELSE(GColorWhite, GColorFromHEX(UI_COLOR)));
      graphics_draw_pixel(ctx, GPoint(basex+x, basey+y));
      y++;
      x=0;
    }
  }
#endif
}

// rather than having a bitmap, we draw the rune frame
// this is necessary due to aplite memory restrictions
static void draw_frame(Layer *layer, GContext *ctx) {
#if defined(PBL_RECT)
  // draw boxes
  graphics_context_set_stroke_color(ctx, PBL_IF_BW_ELSE(GColorWhite, GColorFromHEX(UI_COLOR)));
  graphics_draw_rect(ctx, GRect(0, 0, FRAME_SIZE, FRAME_SIZE));
  graphics_draw_rect(ctx, GRect(0+3, 0+3, FRAME_SIZE-6, FRAME_SIZE-6));

  // draw triforces in each corner
  draw_triforce(ctx, 0);
  draw_triforce(ctx, 1);
  draw_triforce(ctx, 2);
  draw_triforce(ctx, 3);
#endif
}

// also rather than having a bitmap, we draw the noise
// around the edges of the screen
static void draw_fringes(Layer *layer, GContext *ctx) {
  return;
#if defined(PBL_RECT)
  GRect bounds = layer_get_bounds(layer);
  graphics_context_set_stroke_color(ctx, PBL_IF_BW_ELSE(GColorWhite, GColorFromHEX(UI_COLOR)));
  // srand(4); // we seed the rng to draw the same noise each time
  // bruh i'm so stupid like this seeds rand for everything

  // outermost layer is completely filled
  graphics_draw_rect(ctx, bounds);

  // next layer in has 3/4 of pixels on
  int x = 0, y = 0;
  y = 1;
  for (x = y; x < bounds.size.w-y; x++) {
    if (rand()%4 > 0) {
      graphics_draw_pixel(ctx, GPoint(x,y));
    }
    if (rand()%4 > 0) {
      graphics_draw_pixel(ctx, GPoint(x,bounds.size.h-y-1));
    }
  }
  for (x = y; x < bounds.size.h-y; x++){
    if (rand()%4 > 0) {
      graphics_draw_pixel(ctx, GPoint(y,x));
    }
    if (rand()%4 > 0) {
      graphics_draw_pixel(ctx, GPoint(bounds.size.w-y-1,x));
    }
  }

  // next layer in has 2/3 of pixels on
  y = 2;
  for (x = y; x < bounds.size.w-y; x++) {
    if (rand()%3 > 0) {
      graphics_draw_pixel(ctx, GPoint(x,y));
    }
    if (rand()%3 > 0) {
      graphics_draw_pixel(ctx, GPoint(x,bounds.size.h-y-1));
    }
  }
  for (x = y; x < bounds.size.h-y; x++){
    if (rand()%3 > 0) {
      graphics_draw_pixel(ctx, GPoint(y,x));
    }
    if (rand()%3 > 0) {
      graphics_draw_pixel(ctx, GPoint(bounds.size.w-y-1,x));
    }
  }

  // next layer in has 1/4 of pixels on
  y = 3;
  for (x = y; x < bounds.size.w-y; x++) {
    if (rand()%4 == 0) {
      graphics_draw_pixel(ctx, GPoint(x,y));
    }
    if (rand()%4 == 0) {
      graphics_draw_pixel(ctx, GPoint(x,bounds.size.h-y-1));
    }
  }
  for (x = y; x < bounds.size.h-y; x++){
    if (rand()%4 == 0) {
      graphics_draw_pixel(ctx, GPoint(y,x));
    }
    if (rand()%4 == 0) {
      graphics_draw_pixel(ctx, GPoint(bounds.size.w-y-1,x));
    }
  }
#endif
}

// lerp between points a and b with percent c
static int lerp(int a, int b, float c){
  return (int)(a * (1.0 - c) + b * c);
}

// unlerp between points a and b with value c
static float unlerp(int a, int b, int c){
  int b_n = b - a; // normalized b
  int c_n = c - a; // normalized c
  return ((float)c_n) / ((float)(b_n));
}

// update the batter display layer
static void battery_callback(BatteryChargeState state) {
  s_battery_level = state.charge_percent;
  s_charging = state.is_charging;

  layer_mark_dirty(s_battery_layer); // tells system to re-render at next opportunity
}

static void dither(Layer *layer, GContext *ctx) {
  // Dither it up
  GBitmap *fb = graphics_capture_frame_buffer(ctx);
  GRect frame = layer_get_frame(layer);
  for (uint16_t y = frame.origin.y; y < frame.origin.y + frame.size.h; y++) {
    GBitmapDataRowInfo info = gbitmap_get_data_row_info(fb, y);
    for (uint16_t x = frame.origin.x; x < frame.origin.x + frame.size.w; x++) {
      uint8_t pixel_color = ((x + (y & 1)) & 1);
      uint16_t byte = (x >> 3); // x / 8
      uint8_t bit = x & 7; // x % 8
      uint8_t *byte_mod = &info.data[byte];
      if (!(*byte_mod & (1 << bit))) {
        continue;
      }
      *byte_mod ^= (-pixel_color ^ *byte_mod) & (1 << bit);
    }
  }
  graphics_release_frame_buffer(ctx, fb);
}

// display battery as stamina bar
static void battery_update_proc(Layer *layer, GContext *ctx) {
  GRect bounds = layer_get_bounds(layer);
  uint8_t cur_battery = DEMO_MODE ? (DEMO_CYCLE ? s_demo_battery[DEMO_CYCLE_POS] : DEMO_BATTERY) : s_battery_level;
  GColor curColor = PBL_IF_BW_ELSE(GColorWhite, GColorFromHEX(0x00FF00)); // green when battery is healthy
  if (cur_battery <= 10){ // red when running out of "stamina"
    curColor = PBL_IF_BW_ELSE(GColorWhite, GColorFromHEX(0xFF0000));
  }
  bool charging = DEMO_MODE ? (DEMO_CYCLE ? s_demo_charging[DEMO_CYCLE_POS] : DEMO_CHARGING) : s_charging;
  if (charging){ // yellow when charging (values are weird when charging tho)
    curColor = PBL_IF_BW_ELSE(GColorWhite, GColorFromHEX(0xFFFF00));
  }

  int length = (cur_battery * TRIG_MAX_ANGLE) / 100; // get percent around circle

  // fill grey background
  if (charging) {
    graphics_context_set_fill_color(ctx, PBL_IF_BW_ELSE(GColorWhite, GColorFromHEX(0x555555)));
  } else {
    graphics_context_set_fill_color(ctx, PBL_IF_BW_ELSE(GColorBlack, GColorFromHEX(0x555555)));
  }
  graphics_fill_radial(ctx, bounds, GOvalScaleModeFitCircle, 7, 0, TRIG_MAX_ANGLE);
#if defined(PBL_BW)
  dither(layer, ctx);
#endif

  // then fill up stamina bar counterclockwise
  graphics_context_set_fill_color(ctx, curColor);
  graphics_fill_radial(ctx, bounds, GOvalScaleModeFitCircle, 7, TRIG_MAX_ANGLE-length, TRIG_MAX_ANGLE);

#if defined(PBL_BW)
  if (!charging && cur_battery <= 10) {
    dither(layer, ctx);
  }
#endif
}

// moves a bitmap by delta_x and delta_y
static void move_bitmap(BitmapLayer *bitmap_to_move, int delta_x, int delta_y){
  GRect new_frame = layer_get_frame(bitmap_layer_get_layer(bitmap_to_move));
  new_frame.origin = GPoint(new_frame.origin.x+delta_x,new_frame.origin.y+delta_y);
  layer_set_frame(bitmap_layer_get_layer(bitmap_to_move),new_frame);
}

// animate the splash screen
static void splash_anim_handler(void *context) {
  if (s_cur_frame < 2) { // move "wings" of the eye
    move_bitmap(s_splash_left_layer, -4, 0);
    move_bitmap(s_splash_right_layer, 4, 0);

    s_cur_frame++;

    app_timer_register(1, splash_anim_handler, NULL);
  } else if (s_cur_frame == 2) { // wait
    s_cur_frame++;
    app_timer_register(400, splash_anim_handler, NULL);
  } else if(s_cur_frame < 7) { // split eye down middle and fly off screen
    int to_move = s_cur_frame * 3;
    move_bitmap(s_splash_left_layer, -to_move, 0);
    move_bitmap(s_splash_right_layer, to_move, 0);
    move_bitmap(s_splash_left_eye_layer, -to_move, 0);
    move_bitmap(s_splash_right_eye_layer, to_move, 0);

    s_cur_frame++;

    app_timer_register(50, splash_anim_handler, NULL);
  } else if (s_cur_frame == 7) { // wings off screen, so unload them
    // why now? because the text doesn't load until the wings are unloaded
    // memory restrictions I guess?
    bitmap_layer_destroy(s_splash_left_layer);
    s_splash_left_layer = NULL;
    bitmap_layer_destroy(s_splash_right_layer);
    s_splash_right_layer = NULL;
    gbitmap_destroy(s_splash_left_bitmap);
    s_splash_left_bitmap = NULL;
    gbitmap_destroy(s_splash_right_bitmap);
    s_splash_right_bitmap = NULL;

    move_bitmap(s_splash_left_eye_layer, -s_cur_frame * 3, 0);
    move_bitmap(s_splash_right_eye_layer, s_cur_frame * 3, 0);

    s_cur_frame++;
    app_timer_register(50, splash_anim_handler, NULL);
  } else { // all off screen, so unload
    bitmap_layer_destroy(s_splash_left_eye_layer);
    s_splash_left_eye_layer = NULL;
    bitmap_layer_destroy(s_splash_right_eye_layer);
    s_splash_right_eye_layer = NULL;
    gbitmap_destroy(s_splash_left_eye_bitmap);
    s_splash_left_eye_bitmap = NULL;
    gbitmap_destroy(s_splash_right_eye_bitmap);
    s_splash_right_eye_bitmap = NULL;
  }
}

// open the watchface by starting animation
static void init_splash_anim() {
  s_cur_frame = 0;
  s_splash_anim_started = true;
  app_timer_register(1, splash_anim_handler, NULL);
}

// bluetooth status change
static void bluetooth_callback(bool connected) {
  // change sheikah sensor to represent bluetooth connection
  if (DEMO_MODE) {
    connected = (DEMO_CYCLE ? s_demo_bluetooth[DEMO_CYCLE_POS] : DEMO_BLUETOOTH);
  }

  bitmap_layer_set_bitmap(s_bt_icon_layer, connected ? s_bt_icon_bitmap_conn : s_bt_icon_bitmap_disc);

  if (!connected) {
    if (settings.VibrateOnDisc) {
      vibes_double_pulse();
    }
    if (!s_splash_anim_started && s_date_set){
      init_splash_anim();
    }
  }
}

// returns the length of a char array
static int get_text_length(const char * text) {
  int result = 0;
  while (text[result] != '\0') { // end of char array
    result ++;
    if (result > MAX_CHARS/2) return MAX_CHARS/2; // cap at max length
  }
  return result;
}

// fills in column with text
static void set_column_text(char * column, const char * text) {
  int text_length = get_text_length(text);
  int i = 0;
  while (i < MAX_CHARS/2) {
    column[i*2] = text[i%text_length]; // repeat string if we run out
    column[i*2+1] = ' '; // add spaces to make vertical
    i++;
  }
}

// fills column with random letters
static void set_column_random(char * column) {
  int i = 0;
  while (i < MAX_CHARS/2) {
    column[i*2] = 'A' + (rand() % 26);
    column[i*2+1] = ' '; // add spaces to make vertical
    i++;
  }
}

// default clay settings
static void default_settings() {
  set_column_random(settings.LeftColumnText);     // random text
  set_column_random(settings.RightColumnText);    // random text
  for (int i = 0; i < NUM_RUNES; i++)             // all runes active
    settings.RunesToChoose[i] = true;
  settings.RuneChangeRate = 60;                   // update every hour
  settings.UseCurrentLocation = true;             // use GPS for weather
  settings.WeatherCheckRate = 30;                 // check every 30 mins
  strcpy(settings.Latitude, "42.36");             // MIT latitude
  strcpy(settings.Latitude, "-71.1");             // MIT longitude
  settings.TemperatureMetric = false;             // use fahrenheit
  settings.Temperature0 = 30;                     // I know I need to bundle up
  settings.Temperature1 = 50;                     // A big coat is sufficient
  settings.Temperature2 = 70;                     // Ah, so nice
  settings.Temperature3 = 85;                     // time to pull out shorts
  settings.Temperature4 = 100;                    // oh god give me some AC please
  settings.TEMPERATURE = rand()%120;              // mystery temperature
  settings.CONDITIONS = rand()%NUM_WEATHER_ICONS; // mystery weather
  settings.AmericanDate = true;                   // Jan 01 by default
  settings.VibrateOnDisc = true;                  // vibrate by default
}

// Pick the next rune to display
static void pick_new_rune(){
  uint8_t i;
  uint8_t total_runes = 0;
  for (i = 0; i < NUM_RUNES; i++) { // count how many are active
    if (settings.RunesToChoose[i]) {
      total_runes++;
    } 
  }
  if (total_runes == 0) { // if none, then pretend all are
    total_runes = NUM_RUNES;
    i = rand()%total_runes;
  } else { // there's < 7 to choose from
    i = 0;
    uint8_t rune_to_choose = rand()%total_runes;
    while (i < NUM_RUNES) { // could be while true, but just in case
      if (settings.RunesToChoose[i]) { // this rune is active, so
        if (rune_to_choose == 0) { // we hit the random number
          break;
        } else { // we didn't hit the random, number, maybe it's the next
          rune_to_choose--;
        }
      }
      i++;
    }
  }
  if (DEMO_MODE) {
    i = (DEMO_CYCLE ? s_demo_runes[DEMO_CYCLE_POS] : DEMO_RUNE);
  }
  gbitmap_destroy(s_rune_bitmap); // unload our old rune
  s_rune_bitmap = gbitmap_create_with_resource(RUNES[i]);
  bitmap_layer_set_bitmap(s_rune_layer, s_rune_bitmap); // and toss in the next
  s_rune_minutes_elapsed = 0; // reset our counter for updating the rune
}

// update display after reading from clay/weather
static void update_display(){
#if defined(PBL_RECT)
  // set column texts
  text_layer_set_text(s_left_column_layer, settings.LeftColumnText);
  text_layer_set_text(s_right_column_layer, settings.RightColumnText);

  // set the next rune
  pick_new_rune();
#endif

  // redraw the temperature
  layer_mark_dirty(s_temperature_layer);

  // update the date format
  s_date_set = false;

  // update the weather icon
  gbitmap_destroy(s_weather_icon_bitmap);
  s_weather_icon_bitmap = gbitmap_create_with_resource(WEATHER_ICONS[settings.CONDITIONS]);
  bitmap_layer_set_bitmap(s_weather_icon_layer, s_weather_icon_bitmap);
}

// Read settings from persistent storage
static void load_settings() {
  // Load the default settings
  default_settings();
  // Read settings from persistent storage, if they exist
  persist_read_data(SETTINGS_KEY, &settings, sizeof(settings));
}

// Save the settings to persistent storage
static void save_settings() {
  persist_write_data(SETTINGS_KEY, &settings, sizeof(settings));
  // Update the display based on new settings
  update_display();
}

// Ask the app for weather
static void request_weather(){
  DictionaryIterator *iter;
  AppMessageResult result = app_message_outbox_begin(&iter);

  if (result == APP_MSG_OK) {
    // tell the app whether to use current location, celsius, and also the lat and lon
    dict_write_uint8(iter, MESSAGE_KEY_UseCurrentLocation, settings.UseCurrentLocation);
    dict_write_uint8(iter, MESSAGE_KEY_TemperatureMetric, settings.TemperatureMetric);
    dict_write_cstring(iter, MESSAGE_KEY_Latitude, settings.Latitude);
    dict_write_cstring(iter, MESSAGE_KEY_Longitude, settings.Longitude);

    // Send the message
    result = app_message_outbox_send();
  }
}

// Received data! Either for weather or settings
static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  // Left column text
  Tuple *left_column_text_t = dict_find(iterator, MESSAGE_KEY_LeftColumnText);
  if(left_column_text_t) {
    char * left_col_text = left_column_text_t->value->cstring;
    if (strlen(left_col_text) == 0) { // empty string, so give random
      set_column_random(settings.LeftColumnText);
    } else { // otherwise fill with what's in settings
      set_column_text(settings.LeftColumnText, left_col_text);
    }
  }

  // Right column text
  Tuple *right_column_text_t = dict_find(iterator, MESSAGE_KEY_RightColumnText);
  if(right_column_text_t) {
    char * right_col_text = right_column_text_t->value->cstring;
    if (strlen(right_col_text) == 0) { // empty string, so give random
      set_column_random(settings.RightColumnText);
    } else {
      set_column_text(settings.RightColumnText, right_col_text);
    }
  }

  // Rune display
  for (uint8_t i = 0; i < NUM_RUNES; i++) { // go through each rune and update the settings
    Tuple *runes_to_choose_t = dict_find(iterator, MESSAGE_KEY_RunesToChoose+i);
    if(runes_to_choose_t) {
      uint8_t runes_to_choose = runes_to_choose_t->value->uint8;
      settings.RunesToChoose[i] = runes_to_choose == 1;
    }
  }

  // Rune update rate
  Tuple *rune_change_rate_t = dict_find(iterator, MESSAGE_KEY_RuneChangeRate);
  if(rune_change_rate_t) {
    settings.RuneChangeRate = rune_change_rate_t->value->int32;
  }

  // Use current location
  Tuple *use_current_location_t = dict_find(iterator, MESSAGE_KEY_UseCurrentLocation);
  if(use_current_location_t) {
    settings.UseCurrentLocation = use_current_location_t->value->int32 == 1;
  }

  // Weather update rate
  Tuple *weather_check_rate_t = dict_find(iterator, MESSAGE_KEY_WeatherCheckRate);
  if(weather_check_rate_t) {
    settings.WeatherCheckRate = weather_check_rate_t->value->int32;
  }

  // Latitude to use when weather is non GPS
  Tuple *latitude_t = dict_find(iterator, MESSAGE_KEY_Latitude);
  if(latitude_t) {
    strcpy(settings.Latitude,latitude_t->value->cstring);
  }

  // Longitude to use when weather is non GPS
  Tuple *longitude_t = dict_find(iterator, MESSAGE_KEY_Longitude);
  if(longitude_t) {
    strcpy(settings.Longitude,longitude_t->value->cstring);
  }

  // Celsius or Fahrenheit?
  Tuple *temperature_metric_t = dict_find(iterator, MESSAGE_KEY_TemperatureMetric);
  if(temperature_metric_t) {
    settings.TemperatureMetric = temperature_metric_t->value->int32 == 1;
  }

  // Coldest temperature
  Tuple *temperature_0_t = dict_find(iterator, MESSAGE_KEY_Temperature0);
  if(temperature_0_t) {
    settings.Temperature0 = atoi(temperature_0_t->value->cstring);
  }

  // Cold temperature
  Tuple *temperature_1_t = dict_find(iterator, MESSAGE_KEY_Temperature1);
  if(temperature_1_t) {
    settings.Temperature1 = atoi(temperature_1_t->value->cstring);
  }

  // Comfortable temperature
  Tuple *temperature_2_t = dict_find(iterator, MESSAGE_KEY_Temperature2);
  if(temperature_2_t) {
    settings.Temperature2 = atoi(temperature_2_t->value->cstring);
  }

  // Hot temperature
  Tuple *temperature_3_t = dict_find(iterator, MESSAGE_KEY_Temperature3);
  if(temperature_3_t) {
    settings.Temperature3 = atoi(temperature_3_t->value->cstring);
  }

  // Hottest temperature
  Tuple *temperature_4_t = dict_find(iterator, MESSAGE_KEY_Temperature4);
  if(temperature_4_t) {
    settings.Temperature4 = atoi(temperature_4_t->value->cstring);
  }

  // Current temperature and weather conditions
  Tuple *temp_tuple = dict_find(iterator, MESSAGE_KEY_TEMPERATURE);
  Tuple *conditions_tuple = dict_find(iterator, MESSAGE_KEY_CONDITIONS);

  // if weather data is available, use it
  if (DEMO_MODE) {
    settings.TEMPERATURE = (DEMO_CYCLE ? s_demo_temperature[DEMO_CYCLE_POS] : DEMO_TEMPERATURE);
    settings.CONDITIONS = (DEMO_CYCLE ? s_demo_weather[DEMO_CYCLE_POS] : DEMO_CONDITIONS);
    if (s_date_set && !s_weather_loaded && !s_splash_anim_started) {
      init_splash_anim();
    }
    s_weather_loaded = true;
  } else {
    if (temp_tuple && conditions_tuple) {
      settings.TEMPERATURE = (int)temp_tuple->value->int32;
      settings.CONDITIONS = (Weather)conditions_tuple->value->int32;

      // If everything is loaded, start the animation
      if (s_date_set && !s_weather_loaded && !s_splash_anim_started) {
        init_splash_anim();
      }
      s_weather_loaded = true;
    } else { // we weren't given weather, so either settings were updated or we were poked. Request it now
      request_weather();
    }
  }

  // American date format?
  Tuple *american_date_t = dict_find(iterator, MESSAGE_KEY_AmericanDate);
  if(american_date_t) {
    settings.AmericanDate = american_date_t->value->int32 == 1;
  }

  Tuple *vibrate_on_disc_t = dict_find(iterator, MESSAGE_KEY_VibrateOnDisc);
  if(vibrate_on_disc_t) {
    settings.VibrateOnDisc = vibrate_on_disc_t->value->int32 == 1;
  }

  save_settings(); // save the new settings! Current weather included
}

// Message failed to receive
static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

// Message failed to send
static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

// Message sent successfully
static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}

// Get the temperature gauge angle
static int get_temp_angle(){
  if (settings.TEMPERATURE <= TEMP_NOTCHES[0]){ // colder than cold, hit max left
    return TEMP_ANGLE_NOTCHES[0];
  }
  if (settings.TEMPERATURE >= TEMP_NOTCHES[NUM_NOTCHES-1]){ // hotter than hot, hit max right
    return TEMP_ANGLE_NOTCHES[NUM_NOTCHES-1];
  }

  static uint8_t i;
  for (i = 1; i < NUM_NOTCHES; i++){
    if (settings.TEMPERATURE < TEMP_NOTCHES[i]){
      // converts temperature to angles
      return (lerp(TEMP_ANGLE_NOTCHES[i-1],TEMP_ANGLE_NOTCHES[i],unlerp(TEMP_NOTCHES[i-1],TEMP_NOTCHES[i],settings.TEMPERATURE)));
    }
  }
  return 0;
}

// update the temperature gauge
static void temperature_update_proc(Layer *layer, GContext *ctx) {
  // update the temperature notches
  TEMP_NOTCHES[0] = settings.Temperature0;
  TEMP_NOTCHES[1] = settings.Temperature1;
  TEMP_NOTCHES[2] = settings.Temperature2;
  TEMP_NOTCHES[3] = settings.Temperature3;
  TEMP_NOTCHES[4] = settings.Temperature4;

  GRect bounds = layer_get_bounds(layer);
  GPoint center = grect_center_point(&bounds);

  // clear out the meter
  graphics_context_set_fill_color(ctx, GColorFromHEX(0x000000));
  graphics_fill_radial(ctx, bounds, GOvalScaleModeFitCircle, 10, DEG_TO_TRIGANGLE(-130), DEG_TO_TRIGANGLE(130));
#if defined(PBL_COLOR)
  if (settings.TEMPERATURE <= TEMP_NOTCHES[0]) { // turn the whole meter ice cold
    graphics_context_set_fill_color(ctx, GColorFromHEX(0xAAFFFF));
    graphics_fill_radial(ctx, bounds, GOvalScaleModeFitCircle, 5, DEG_TO_TRIGANGLE(-130), DEG_TO_TRIGANGLE(130));
  } else if (settings.TEMPERATURE >= TEMP_NOTCHES[NUM_NOTCHES-1]) { // turn the whole meter fiery hot
    graphics_context_set_fill_color(ctx, GColorFromHEX(0xFF5500));
    graphics_fill_radial(ctx, bounds, GOvalScaleModeFitCircle, 5, DEG_TO_TRIGANGLE(-130), DEG_TO_TRIGANGLE(130));
  } else {
    // meter background
    graphics_context_set_fill_color(ctx, GColorFromHEX(0x555555));
    graphics_fill_radial(ctx, bounds, GOvalScaleModeFitCircle, 5, DEG_TO_TRIGANGLE(-130), DEG_TO_TRIGANGLE(130));

    // cold section
    graphics_context_set_fill_color(ctx, GColorFromHEX(0x00FFFF));
    graphics_fill_radial(ctx, bounds, GOvalScaleModeFitCircle, 5, DEG_TO_TRIGANGLE(-130), DEG_TO_TRIGANGLE(-60));

    // hot section
    graphics_context_set_fill_color(ctx, GColorFromHEX(0xFFAA00));
    graphics_fill_radial(ctx, bounds, GOvalScaleModeFitCircle, 5, DEG_TO_TRIGANGLE(60), DEG_TO_TRIGANGLE(130));

    if (settings.TEMPERATURE <= TEMP_NOTCHES[1]){ // add cold trim to the meter
      graphics_context_set_fill_color(ctx, GColorFromHEX(0x00FFFF));
      if (settings.TEMPERATURE <= (TEMP_NOTCHES[1] + TEMP_NOTCHES[0]) / 2) // larger if colder
        graphics_fill_radial(ctx, bounds, GOvalScaleModeFitCircle, 2, DEG_TO_TRIGANGLE(-130), DEG_TO_TRIGANGLE(130));
      else
        graphics_fill_radial(ctx, bounds, GOvalScaleModeFitCircle, 1, DEG_TO_TRIGANGLE(-130), DEG_TO_TRIGANGLE(130));
    } else if (settings.TEMPERATURE >= TEMP_NOTCHES[NUM_NOTCHES-2]){ // add hot trim to the meter
      graphics_context_set_fill_color(ctx, GColorFromHEX(0xFFAA00));
      if (settings.TEMPERATURE >= (TEMP_NOTCHES[NUM_NOTCHES-2] + TEMP_NOTCHES[NUM_NOTCHES-1])/2) // larger if hotter
        graphics_fill_radial(ctx, bounds, GOvalScaleModeFitCircle, 2, DEG_TO_TRIGANGLE(-130), DEG_TO_TRIGANGLE(130));
      else
        graphics_fill_radial(ctx, bounds, GOvalScaleModeFitCircle, 1, DEG_TO_TRIGANGLE(-130), DEG_TO_TRIGANGLE(130));
    }
  }
#else
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_radial(ctx, bounds, GOvalScaleModeFitCircle, 5, DEG_TO_TRIGANGLE(-130), DEG_TO_TRIGANGLE(130));
#endif

  // draw the ticks
  graphics_context_set_stroke_color(ctx, GColorFromHEX(0x000000));
  graphics_context_set_stroke_width(ctx, 1);
  static uint8_t i;
  for (i = 0; i < 9; i++){
    graphics_draw_line(ctx, center, 
    gpoint_from_polar(bounds, GOvalScaleModeFillCircle, DEG_TO_TRIGANGLE(-120+30*i)));
  }

  // draw the needle
  GRect small_bounds = grect_crop(bounds, 3);
  int temp_angle = get_temp_angle();
#if defined(PBL_BW)
  graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_context_set_stroke_width(ctx, 4);
  graphics_draw_line(ctx, center, 
                     gpoint_from_polar(small_bounds, GOvalScaleModeFitCircle, DEG_TO_TRIGANGLE(temp_angle)));
#endif
  graphics_context_set_stroke_color(ctx, PBL_IF_BW_ELSE(GColorWhite, GColorFromHEX(UI_COLOR)));
  graphics_context_set_stroke_width(ctx, 2);
  graphics_draw_line(ctx, center, 
                     gpoint_from_polar(small_bounds, GOvalScaleModeFitCircle, DEG_TO_TRIGANGLE(temp_angle)));
  graphics_context_set_fill_color(ctx, PBL_IF_BW_ELSE(GColorWhite, GColorFromHEX(UI_COLOR)));
  graphics_fill_circle(ctx, center, 2);
}

// Something is taking too long! start the animation
static void splash_timeout() {
  if (!s_splash_anim_started) {
    init_splash_anim();
  }
}

// setup the display
static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // Watchface Resources
  // time
#if defined(PBL_ROUND)
  s_time_layer = text_layer_create(GRect(0, 20, bounds.size.w, 48));
  s_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_BOTW_48));
#else
  s_time_layer = text_layer_create(GRect(0, -2, bounds.size.w, 24));
  s_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_BOTW_24));
#endif
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, PBL_IF_BW_ELSE(GColorWhite, GColorFromHEX(UI_COLOR)));
  text_layer_set_font(s_time_layer, s_time_font);
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);

  // date
#if defined(PBL_ROUND)
  s_date_layer = text_layer_create(GRect(0, 100, bounds.size.w, 48));
  s_date_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_BOTW_48));
#else
  s_date_layer = text_layer_create(GRect(0, 140, bounds.size.w, 22));
  s_date_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_BOTW_22));
#endif
  text_layer_set_background_color(s_date_layer, GColorClear);
  text_layer_set_text_color(s_date_layer, PBL_IF_BW_ELSE(GColorWhite, GColorFromHEX(UI_COLOR)));
  text_layer_set_font(s_date_layer, s_date_font);
  text_layer_set_text_alignment(s_date_layer, GTextAlignmentCenter);

#if defined(PBL_RECT)
  // left column
  s_left_column_layer = text_layer_create(GRect(0, -4, 16, bounds.size.h+8));
  // create and load rune font
  s_sheikah_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_SHEIKAH_RUNES_16));
  // stylize the text
  text_layer_set_background_color(s_left_column_layer, GColorClear);
  text_layer_set_text_color(s_left_column_layer, PBL_IF_BW_ELSE(GColorWhite, GColorFromHEX(UI_COLOR)));
  text_layer_set_font(s_left_column_layer, s_sheikah_font);
  text_layer_set_text_alignment(s_left_column_layer, GTextAlignmentLeft);
  text_layer_set_overflow_mode(s_left_column_layer, GTextOverflowModeWordWrap);

  // right column
  s_right_column_layer = text_layer_create(GRect(bounds.size.w-14, -4, 16, bounds.size.h+8));
  // stylize the text
  text_layer_set_background_color(s_right_column_layer, GColorClear);
  text_layer_set_text_color(s_right_column_layer, PBL_IF_BW_ELSE(GColorWhite, GColorFromHEX(UI_COLOR)));
  text_layer_set_font(s_right_column_layer, s_sheikah_font);
  text_layer_set_text_alignment(s_right_column_layer, GTextAlignmentLeft);
  text_layer_set_overflow_mode(s_right_column_layer, GTextOverflowModeWordWrap);

  // rune border
  s_frame_layer = layer_create(GRect(FRAME_X, FRAME_Y, FRAME_SIZE, FRAME_SIZE));
  layer_set_update_proc(s_frame_layer, draw_frame);

  // fringes around the screen
  s_fringes_layer = layer_create(bounds);
  layer_set_update_proc(s_fringes_layer, draw_fringes);
  layer_mark_dirty(s_fringes_layer);

  // runes
  s_rune_layer = bitmap_layer_create(GRect(20,32,102,102));
  s_rune_bitmap = gbitmap_create_with_resource(RUNES[rand() % NUM_RUNES]);
  bitmap_layer_set_bitmap(s_rune_layer, s_rune_bitmap);
#endif
  // bitmap_layer_set_compositing_mode(s_rune_layer, GCompOpSet);

  // bluetooth icon
#if defined(PBL_ROUND)
  s_bt_icon_layer = bitmap_layer_create(GRect(30,78,25,24));
#else
  s_bt_icon_layer = bitmap_layer_create(GRect(16,1,25,24));
#endif
  s_bt_icon_bitmap_conn = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BT_CONN);
  s_bt_icon_bitmap_disc = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BT_DISC);
  // update bluetooth icon
  bluetooth_callback(connection_service_peek_pebble_app_connection());

  // battery stamina wheel
  #if defined(PBL_ROUND)
    s_battery_layer = layer_create(GRect(122, 79, 22, 22));
  #else
    s_battery_layer = layer_create(GRect(105, 2, 22, 22));
  #endif
  // assign update procedure to battery layer
  layer_set_update_proc(s_battery_layer, battery_update_proc);

  // weather icon
#if defined(PBL_ROUND)
  s_weather_icon_layer = bitmap_layer_create(GRect(61,78,24,24));
#else
  s_weather_icon_layer = bitmap_layer_create(GRect(16,143,24,24));
#endif
  s_weather_icon_bitmap = gbitmap_create_with_resource(WEATHER_ICONS[rand() % NUM_WEATHER_ICONS]);
  bitmap_layer_set_bitmap(s_weather_icon_layer, s_weather_icon_bitmap);

  // temperature
#if defined(PBL_ROUND)
  s_temperature_layer = layer_create(GRect(92, 79, 22, 22));
#else
  s_temperature_layer = layer_create(GRect(105, 145, 22, 22));
#endif
  layer_set_update_proc(s_temperature_layer, temperature_update_proc);

  // Loading Screen
  // left wing of splash layer
#if defined(PBL_ROUND)
  s_splash_left_layer = bitmap_layer_create(GRect(28,33,46,114));
#else
  s_splash_left_layer = bitmap_layer_create(GRect(10,27,46,114));
#endif
  s_splash_left_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_SPLASH_LEFT);
  bitmap_layer_set_bitmap(s_splash_left_layer, s_splash_left_bitmap);
  bitmap_layer_set_compositing_mode(s_splash_left_layer, GCompOpSet);

  // right wing of splash layer
#if defined(PBL_ROUND)
  s_splash_right_layer = bitmap_layer_create(GRect(105,33,46,109));
#else
  s_splash_right_layer = bitmap_layer_create(GRect(87,27,46,109));
#endif
  s_splash_right_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_SPLASH_RIGHT);
  bitmap_layer_set_bitmap(s_splash_right_layer, s_splash_right_bitmap);
  bitmap_layer_set_compositing_mode(s_splash_right_layer, GCompOpSet);

  // left half of splash layer eye
#if defined(PBL_ROUND)
  s_splash_left_eye_layer = bitmap_layer_create(GRect(18,6,72,168));
#else
  s_splash_left_eye_layer = bitmap_layer_create(GRect(0,0,72,168));
#endif
  s_splash_left_eye_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_SPLASH_EYE_LEFT);
  bitmap_layer_set_bitmap(s_splash_left_eye_layer, s_splash_left_eye_bitmap);

  // right half of splash layer eye
#if defined(PBL_ROUND)
  s_splash_right_eye_layer = bitmap_layer_create(GRect(90,6,72,168));
#else
  s_splash_right_eye_layer = bitmap_layer_create(GRect(72,0,72,168));
#endif
  s_splash_right_eye_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_SPLASH_EYE_RIGHT);
  bitmap_layer_set_bitmap(s_splash_right_eye_layer, s_splash_right_eye_bitmap);

  // add layers
#if defined(PBL_RECT)
  layer_add_child(window_layer, bitmap_layer_get_layer(s_rune_layer)); // runes below the frame
  layer_add_child(window_layer, s_frame_layer);
  layer_add_child(window_layer, text_layer_get_layer(s_left_column_layer)); // everything else on top of frame
  layer_add_child(window_layer, text_layer_get_layer(s_right_column_layer));
#endif
  layer_add_child(window_layer, text_layer_get_layer(s_time_layer));
  layer_add_child(window_layer, text_layer_get_layer(s_date_layer));
  layer_add_child(window_layer, s_battery_layer);
  layer_add_child(window_layer, s_temperature_layer);
  layer_add_child(window_layer, bitmap_layer_get_layer(s_weather_icon_layer));
  layer_add_child(window_layer, bitmap_layer_get_layer(s_bt_icon_layer));
  layer_add_child(window_layer, bitmap_layer_get_layer(s_splash_left_eye_layer)); // splash covers everything at start
  layer_add_child(window_layer, bitmap_layer_get_layer(s_splash_right_eye_layer));
  layer_add_child(window_layer, bitmap_layer_get_layer(s_splash_left_layer));
  layer_add_child(window_layer, bitmap_layer_get_layer(s_splash_right_layer));// fringes cover everything
#if defined(PBL_RECT)
  layer_add_child(window_layer, s_fringes_layer);
#endif

  update_display(); // and update the display to fill in everything
}

// unload everything!
static void main_window_unload(Window *window) {
  // unload regular layers
  if (s_battery_layer != NULL)
    layer_destroy(s_battery_layer);
  if (s_temperature_layer != NULL)
    layer_destroy(s_temperature_layer);
  if (s_frame_layer != NULL)
    layer_destroy(s_frame_layer);
  if (s_fringes_layer != NULL)
    layer_destroy(s_fringes_layer);

  // unload text layers
  if (s_time_layer != NULL)
    text_layer_destroy(s_time_layer);
  if (s_date_layer != NULL)
    text_layer_destroy(s_date_layer);
  if (s_left_column_layer != NULL)
    text_layer_destroy(s_left_column_layer);
  if (s_right_column_layer != NULL)
    text_layer_destroy(s_right_column_layer);

  // unload custom fonts
  if (s_time_font != NULL)
    fonts_unload_custom_font(s_time_font);
  if (s_date_font != NULL)
    fonts_unload_custom_font(s_date_font);
  if (s_sheikah_font != NULL)
    fonts_unload_custom_font(s_sheikah_font);

  // unload bitmap layers
  if (s_rune_layer != NULL)
    bitmap_layer_destroy(s_rune_layer);
  if (s_bt_icon_layer != NULL)
    bitmap_layer_destroy(s_bt_icon_layer);
  if (s_weather_icon_layer != NULL)
    bitmap_layer_destroy(s_weather_icon_layer);

  // unload gbitmaps
  if (s_rune_bitmap != NULL)
    gbitmap_destroy(s_rune_bitmap);
  if (s_bt_icon_bitmap_conn != NULL)
    gbitmap_destroy(s_bt_icon_bitmap_conn);
  if (s_bt_icon_bitmap_disc != NULL)
    gbitmap_destroy(s_bt_icon_bitmap_disc);
  if (s_weather_icon_bitmap != NULL)
    gbitmap_destroy(s_weather_icon_bitmap);

  // splash layers might already be destroyed
  if (s_splash_left_layer != NULL)
    bitmap_layer_destroy(s_splash_left_layer);
  if (s_splash_right_layer != NULL)
    bitmap_layer_destroy(s_splash_right_layer);
  if (s_splash_left_eye_layer != NULL)
    bitmap_layer_destroy(s_splash_left_eye_layer);
  if (s_splash_right_eye_layer != NULL)
    bitmap_layer_destroy(s_splash_right_eye_layer);
  if (s_splash_left_eye_bitmap != NULL)
    gbitmap_destroy(s_splash_left_eye_bitmap);
  if (s_splash_right_eye_bitmap != NULL)
    gbitmap_destroy(s_splash_right_eye_bitmap);
  if (s_splash_left_bitmap != NULL)
    gbitmap_destroy(s_splash_left_bitmap);
  if (s_splash_right_bitmap != NULL)
    gbitmap_destroy(s_splash_right_bitmap);
}

// update the time display
static void update_time() {
  if (DEMO_MODE && DEMO_CYCLE) {
    text_layer_set_text(s_time_layer, s_demo_times[DEMO_CYCLE_POS]);
  } else {
    time_t temp = time(NULL);
    struct tm *tick_time = localtime(&temp);

    // put hours and minutes into buffer
    static char s_buffer[8];
    strftime(s_buffer, sizeof(s_buffer), clock_is_24h_style() ?
                                          "%H:%M" : "%I:%M", tick_time);
    // display it
    text_layer_set_text(s_time_layer, s_buffer);  
  }
}

static void update_date(struct tm *tick_time){
  if (DEMO_MODE && DEMO_CYCLE) {
    text_layer_set_text(s_date_layer, s_demo_dates[DEMO_CYCLE_POS]);
  } else {
    static char s_date_buffer[8];
    if (settings.AmericanDate) {
      strftime(s_date_buffer, sizeof(s_date_buffer), "%b %d", tick_time); // displayed as "Jan 01"
    } else {
      strftime(s_date_buffer, sizeof(s_date_buffer), "%d %b", tick_time); // displayed as "01 Jan"
    }

    text_layer_set_text(s_date_layer, s_date_buffer);
  }
}

// this fires every minute
static void tick_handler(struct tm *tick_time, TimeUnits units_changes) {
  update_time(); // display the time

  // update the rune
  if (settings.RuneChangeRate > 0) { // if 0, user doesn't want to change
    s_rune_minutes_elapsed++;
    if (s_rune_minutes_elapsed >= settings.RuneChangeRate) { // it's time
      pick_new_rune();
    }
  }

  // update the weather
  s_weather_minutes_elapsed++;
  if (s_weather_minutes_elapsed >= settings.WeatherCheckRate) { // time to check the weather
    // get the weather
    request_weather();

    s_weather_minutes_elapsed = 0;
  } 

  // update date on first call, or at midnight (00:00)
  if (!s_date_set || (tick_time->tm_min == 0 && tick_time->tm_hour == 0)) {
    update_date(tick_time);
    // if this is the last to load, then animate!
    if (!s_splash_anim_started && !s_date_set && (s_weather_loaded || !connection_service_peek_pebble_app_connection())) {
      init_splash_anim();
    }
    s_date_set = true;
  }
}

// classic init, you know we need it
static void init() {
  load_settings();

  // setup window
  s_main_window = window_create();

  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  window_set_background_color(s_main_window, GColorBlack);

  window_stack_push(s_main_window, true);

  // set up tick_handler to run every minute
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  // want to display time at the start
  update_time();

  // callback for battery level updates
  battery_state_service_subscribe(battery_callback);
  // display battery at the start
  battery_callback(battery_state_service_peek());

  // callback for bluetooth connection updates
  connection_service_subscribe((ConnectionHandlers) {
    .pebble_app_connection_handler = bluetooth_callback
  });

  // callback for timeout if things take too long to load
  app_timer_register(5000, splash_timeout, NULL);

  // Register callbacks for settings/weather updates
  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);

  // Open AppMessage
  const int inbox_size = 256; // maaaaybe overkill, but 128 isn't enough
  const int outbox_size = 256;
  app_message_open(inbox_size, outbox_size);
}

// classic deinit, you know we need this too
static void deinit() {
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
