#define PIN_START 0
#define PIN_END 15
// 16 pins for the x and y direction
int xy[4][4];
// 4 pins for the z direction
int z[4];

// Patterns formatted as xy index (4 * x + y), z
int pattern1[][2] = {
  {xy[0][0], z[0]}, {xy[0][1], z[0]}
};

inline void pulse_led(int xy, int z) {
  digitalWrite(xy, HIGH);
  digitalWrite(z, HIGH);
  digitalWrite(xy, LOW);
  digitalWrite(z, LOW);
}

void run_pattern(int *pattern, int duration) {
  int elapsed = 0;
  int last = millis();

  int arr_size = sizeof(&pattern) / sizeof((&pattern)[0]);

  loop:
  while (true) {
    for (size_t i = 0; i < arr_size; i++) {
      if (elapsed >= duration) {
        goto loop_end;
      }

      int xy = (&pattern)[i][0];
      int z = (&pattern)[i][1];
      pulse_led(xy, z);

      // Keep track of time
      int curr = millis();
      elapsed += curr - last;
      last = curr;
    }
  }
  loop_end:
  return;
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

}

void loop() {

}