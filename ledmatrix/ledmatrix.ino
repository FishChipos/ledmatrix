#include "patterns.h"

// XY pins act as ground.
// Z pins act as voltage.

// 16 pins for the x and y direction.
int pins_xy[16];
// 4 pins for the z direction.
int pins_z[4];

// We pulse to avoid unwanted activations of other LEDs.
void pulse_led(int xy, int z) {
  // Output input bullshittery to prevent shorts and stuff
  pinMode(xy, OUTPUT);
  pinMode(z, OUTPUT);
  digitalWrite(xy, LOW);
  digitalWrite(z, HIGH);
  pinMode(xy, INPUT);
  pinMode(z, INPUT);
}

void run_pattern(Byte *pattern, size_t frame_count, size_t duration) {
  size_t frame_duration = duration / frame_count;

  for (size_t frame = 0; frame < frame_count; frame++) {
    // For timekeeping.
    size_t last = millis();
    size_t curr = millis();
    size_t frame_elapsed = 0;

    // Run frame for specified time.
    while (frame_elapsed < frame_duration) {

      // Loop through bytes in the frame.
      for (size_t index = 0; index < 8; index++) {
        Byte byte = *(pattern + index + 8 * frame);

        // Loop through bits in the byte.
        for (int bit = 0, mask = 128; bit < 8; bit++, mask = mask >> 1) {
          // Get the value of the bit.
          bool val = byte & mask;

          if (!val) {
            continue;
          }

          // Each layer has 2 bytes so to get the z just divide by 2.
          size_t z = index / 2;

          // The bit is divided by 4, and if its the second byte in that layer then offset by 2.
          size_t y = (bit / 4) + (index % 2) * 2;
          // The x can purely be gotten from the bit, as it's value just ranges from 0 to 7.
          size_t x = (bit % 4);

          // 4 pixels per row so y contributes 4 to the index.
          size_t xy = 4 * y + x;

          pulse_led(pins_xy[xy], pins_z[z]);

          // Get time that has elapsed on this bit.
          curr = millis();
          frame_elapsed += curr - last;
          last = curr;
        }
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

//  size_t frame_count = sizeof(pat_gradient) / sizeof(pat_gradient[0]);
//  run_pattern(*pat_gradient, frame_count, 3000);

  size_t frame_count = sizeof(pat_box) / sizeof(pat_box[0]);
  run_pattern(*pat_box, frame_count, 2000);

  frame_count = sizeof(pat_spin) / sizeof(pat_spin[0]);
  run_pattern(*pat_spin, frame_count, 2000);

  frame_count = sizeof(pat_shootcorner) / sizeof(pat_shootcorner[0]);
  run_pattern(*pat_shootcorner, frame_count, 30000);


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
