/*
 * IceGantry
 * 
 * Author: Rob Bultman
 *         FirstBuild
 *         Sept. 27, 2017
 * 
 * License: MIT
 */
 
#include <stdint.h>
#include "InputDebounce.h"

#define BUTTON_DEBOUNCE_DELAY   20   // [ms]

static const uint8_t upPin = 10;
static const uint8_t downPin = 9;
static InputDebounce upBtn;
static InputDebounce downBtn;

static const uint8_t StepX = 2;
static const uint8_t StepY = 3;
static const uint8_t StepZ = 4;
static const uint8_t DirX = 5;
static const uint8_t DirY = 6;
static const uint8_t DirZ = 7;
static const uint8_t enable = 8;

enum {Down, Up, Idle};

uint8_t state = Idle;

#define togglePin(p) digitalWrite(p, digitalRead(p) == HIGH ? LOW : HIGH)

void initOutput(uint8_t pin, uint8_t state) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, state);
}

void upPressed(uint8_t pinIn)
{
  Serial.println("Up pressed");
  state = Up;
}

void upReleased(uint8_t pinIn)
{
  Serial.println("Up released");
  state = Idle;
}

void downPressed(uint8_t pinIn)
{
  Serial.println("Down pressed");
  state = Down;
}

void downReleased(uint8_t pinIn)
{
  Serial.println("Down released");
  state = Idle;
}

void setup() {
  Serial.begin(115200);
  
  initOutput(StepX, 0);
  initOutput(StepY, 0);
  initOutput(StepZ, 0);
  initOutput(DirX, 0);
  initOutput(DirY, 0);
  initOutput(DirZ, 0);
  initOutput(enable, 0);

  pinMode(upPin, INPUT_PULLUP);
  pinMode(downPin, INPUT_PULLUP);

  upBtn.registerCallbacks(upPressed, upReleased, NULL);
  downBtn.registerCallbacks(downPressed, downReleased, NULL);
  
  // setup input buttons (debounced)
  upBtn.setup(upPin, BUTTON_DEBOUNCE_DELAY, InputDebounce::PIM_INT_PULL_UP_RES);
  downBtn.setup(downPin, BUTTON_DEBOUNCE_DELAY, InputDebounce::PIM_INT_PULL_UP_RES); // single-shot pressed-on time duration callback

  Serial.println("Initialization complete.");
}

void loop() {
  unsigned long now = millis();
  
  // poll button state
  upBtn.process(now); // callbacks called in context of this function
  downBtn.process(now);

  // run the stepper
  if (state == Idle) {
    digitalWrite(enable, HIGH);
  } else {
    digitalWrite(enable, LOW);
    digitalWrite(DirX, state);
    digitalWrite(DirY, state);
    togglePin(StepX);
    togglePin(StepY);
  }
}


