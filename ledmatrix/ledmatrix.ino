#include "patterns.h"

#define PIN_START 0
#define PIN_END 15
// 16 pins for the x and y direction
int pins_xy[4][4];
// 4 pins for the z direction
int pins_z[4];

inline void pulse_led(int xy, int z) {
  digitalWrite(xy, HIGH);
  digitalWrite(z, HIGH);
  digitalWrite(xy, LOW);
  digitalWrite(z, LOW);
}

void run_pattern(bool *pattern, int duration) {
  // For keeping track of time elapsed
  size_t last = millis();
  size_t curr = millis();

  int frame_count = sizeof(pattern) / sizeof(pattern[0]);
  int frame_duration = duration / frame_count;

  for (size_t frame = 0; frame < frame_count; frame++) {
    int frame_elapsed = 0;
    for (size_t index = 0; index < 64; index++) {
      if (frame_elapsed > frame_duration) {
        break;
      }
      bool val = (&pattern)[frame][index];
      
      size_t pat_x = index % 8;
      size_t pat_y = index / 8;

      size_t led_x = pat_x % 4;
      size_t led_y = pat_y % 4;
      size_t led_z = 0;

      if (pat_x >= 4) {
        led_z += 1;
      }
      if (pat_y >= 4) {
        led_z += 2;
      }

      pulse_led(pins_xy[led_x][led_y], pins_z[led_z]);

      curr = millis();
      frame_elapsed += curr - last;
      last = curr;
    }
  }
}

void setup() {
  Serial.begin(9600);

  // Initialize pins
  for (size_t i = PIN_START; i < (PIN_END + 1) / 4; i++) {
    for (size_t j = 4 * i; j < 4 * (i + 1); j++) {
      Serial.println(i * 4 + j);
      pins_xy[i][j] = i * 4 + j;
      pinMode(i * 4 + j, OUTPUT);
    }
  }

  for (size_t i = PIN_END + 1; i < PIN_END + 5; i++) {
    Serial.println(i);
    pins_z[i] = i;
    pinMode(i, OUTPUT);
  }

  run_pattern(*pat_template, 2000);
}

void loop() {

}
