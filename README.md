# IceGantry
This is a very simple project for the control of two stepper motors using a 
double-throw switch. Two discrete push buttons could be used as well.

Connect the common pin of the SPDT switch to circuit ground and the other
two pins to the inputs on the Arduino.

```
        +-----+
        |     +---+  Connect to D9 on Arduino
        |     |
+-------+     +---+  Connect to GND pin on Arduino
        |     |
        |     +---+  Connect to D10 on Arduino
        +-----+

        Switch
```

You can use any pins of your choice, just make sure to connect the center pin to GND.

Other pins used in the sketch:
- D2 - Step X output to the stepper driver
- D3 - Step Y output to the stepper driver
- D4 - Step Z output to the stepper driver
- D5 - Direction X output to the stepper driver
- D6 - Direction Y output to the stepper driver
- D7 - Direction Z output to the stepper driver
- D8 - Enable output to the stepper driver

Any stepper motor driver that uses a direction and step input could be used, such as the 
[EasyDriver](https://www.sparkfun.com/products/12779) or the 
[gShield](https://www.adafruit.com/product/1750?gclid=CjwKCAjwmK3OBRBKEiwAOL6t1EWBDebI5Kcy3BjVDWzX_mSrlm1fpOo8eC_xFEqXSacyycUPgRhR-RoCtSQQAvD_BwE).

Uses the [InputOutput](https://github.com/Mokolea/InputDebounce) library.

The ASCII diagram was created with the awesome [asciiflow](http://asciiflow.com/).
