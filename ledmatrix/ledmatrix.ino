#include "patterns.ino"

#define PIN_START 0
#define PIN_END 15
// 16 pins for the x and y direction
int xy[4][4];
// 4 pins for the z direction
int z[4];

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
      bool val = &pattern[frame][index];
      // TO BE CONTINUED

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
      xy[i][j] = i * 4 + j;
      pinMode(i * 4 + j, OUTPUT);
    }
  }

  for (size_t i = PIN_END + 1; i < PIN_END + 5; i++) {
    Serial.println(i);
    z[i] = i;
    pinMode(i, OUTPUT);
  }

  run_pattern(*pattern_template, 2000);
}

void loop() {

}