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
        
        size_t z = index / 16;
        
        size_t y = (index % 16) / 4;
        size_t x = (index % 16) % 4;
        size_t xy = 4 * y + x;
  
        pulse_led(pins_xy[xy], pins_z[z]);
  
        curr = millis();
        frame_elapsed += curr - last;
        last = curr;
      }
    }
  }
}



void setup() {

  // Initialize pins.
  // Serial.println("XY Pins");
  // for (size_t i = 0; i < (PIN_END - PIN_START + 1) / 4; i++) {
  //   for (size_t j = 0; j < 4; j++) {
  //     Serial.println(i * 4 + j);
  //     pins_xy[i][j] = i * 4 + j;
  //     pinMode(i * 4 + j, OUTPUT);
  //   }
  // }

  // Serial.println("Z Pins");
  // for (size_t i = PIN_END + 1; i < PIN_END + 5; i++) {
  //   Serial.println(i);
  //   pins_z[i] = i; 
  //   pinMode(i, OUTPUT);
  // }

  // Pins 14 and up are treated as analog pins for digitalWrite().
  for (int xy = 0; xy < 16; xy++) {
    pins_xy[xy] = xy;
  }
  for (int z = 0; z < 4; z++) {
    pins_z[z] = z + 16;
  }

  size_t frame_count = sizeof(pat_box) / sizeof(pat_box[0]);
  run_pattern(*pat_box, frame_count, 5000);


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

//  digitalWrite(0, LOW);
//  digitalWrite(12, LOW);
//  digitalWrite(13, HIGH);
//  digitalWrite(14, LOW);
//  digitalWrite(16, HIGH);
//  delay(1000);
//  digitalWrite(12, HIGH);
}

void loop() {
   //pulse_led(pins_xy[0], pins_z[0]);
   //pulse_led(pins_xy[0], pins_z[1]);
}
