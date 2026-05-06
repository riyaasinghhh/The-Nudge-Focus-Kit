#include <TM1637Display.h>

const int CLK = 22, DIO = 23, PHONE_SWITCH = 18;
TM1637Display display(CLK, DIO);
unsigned long startTime = 0;
bool isTiming = false;

void setup() {
pinMode(PHONE_SWITCH, INPUT_PULLUP);
display.setBrightness(0x0f);
uint8_t readyData[] = { 0x40, 0x40, 0x40, 0x40 };
display.setSegments(readyData);
}

void loop() {
bool phonePresent = (digitalRead(PHONE_SWITCH) == LOW);
if (phonePresent && !isTiming) {
isTiming = true;
startTime = millis();
} else if (phonePresent && isTiming) {
unsigned long duration = millis() - startTime;
unsigned long totalSecs = duration / 1000;
display.showNumberDecEx((totalSecs / 60) * 100 + (totalSecs % 60), 0x40, true);
} else if (!phonePresent && isTiming) {
isTiming = false;
delay(5000);
display.clear();
uint8_t readyData[] = { 0x40, 0x40, 0x40, 0x40 };
display.setSegments(readyData);
}
}