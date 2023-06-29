#include "patterns.h"

// XY pins act as ground.
// Z pins act as voltage.

// 16 pins for the x and y direction.
int pins_xy[16];
// 4 pins for the z direction.
int pins_z[4];

// We pulse to avoid unwanted activations of other LEDs.
void pulse_led(int xy, int z) {
  pinMode(xy, OUTPUT);
  pinMode(z, OUTPUT);
  digitalWrite(xy, LOW);
  digitalWrite(z, HIGH);
  pinMode(xy, INPUT);
  pinMode(z, INPUT);
}

void run_pattern(bool *pattern, size_t frame_count, size_t duration) {
  // For keeping track of time elapsed.
  size_t last = millis();
  size_t curr = millis();

  size_t frame_duration = duration / frame_count;

  for (size_t frame = 0; frame < frame_count; frame++) {
    size_t frame_elapsed = 0;
    while (frame_elapsed < frame_duration) {
        for (size_t index = 0; index < 64; index++) {
        bool val = (&pattern)[frame][index];

        if (!val) {
          continue;
        }
        
        // Coordinates as seen on the pattern.
        size_t pat_x = index % 8;
        size_t pat_y = index / 8;
  
        // Coordinates transferred to the LED matrix.
        size_t led_x = pat_x % 4;
        size_t led_y = pat_y % 4;
        size_t led_xy = led_y * 4 + led_x;
        size_t led_z = 0;
  
        if (pat_x >= 4) {
          led_z += 1;
        }
        if (pat_y >= 4) {
          led_z += 2;
        }
  
        pulse_led(pins_xy[led_xy], pins_z[led_z]);
  
        curr = millis();
        frame_elapsed += curr - last;
        last = curr;
      }
    }
  }
}



void setup() {

  // Pins 14 and up are treated as analog pins for digitalWrite().
  for (int xy = 0; xy < 16; xy++) {
    pins_xy[xy] = xy;
  }
  for (int z = 0; z < 4; z++) {
    pins_z[z] = z + 16;
  }

  size_t frame_count = sizeof(pat_dot) / sizeof(pat_dot[0]);
  run_pattern(*pat_dot, frame_count, 50000);


//  for (size_t z = 0; z < 4; z++) {
//    for (size_t xy = 0; xy < 16; xy++) {
//      pinMode(pins_xy[xy], OUTPUT);
//      pinMode(pins_z[z], OUTPUT);
//      digitalWrite(pins_xy[xy], LOW);
//      digitalWrite(pins_z[z], HIGH);
//
//      delay(500);
//
//      pinMode(pins_xy[xy], INPUT);
//      pinMode(pins_z[z], INPUT);
//    }
//  }
}

void loop() {
}
