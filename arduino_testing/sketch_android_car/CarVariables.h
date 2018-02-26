#ifndef CarVariables_h
#define CarVariables_h

/* pin definitions */
#define SERVO_PIN 8
#define ESC_PIN 9

#define FRONT_US_TRIG_PIN 43
#define FRONT_US_ECHO_PIN 42

#define FRONT_RIGHT_US_TRIG_PIN 41
#define FRONT_RIGHT_US_ECHO_PIN 40

#define REAR_US_TRIG_PIN 39
#define REAR_US_ECHO_PIN 38

#define SIDE_FRONT_IR_PIN A0
#define SIDE_REAR_IR_PIN A1
#define REAR_IR_PIN A2

#define ENCODER_DIG_PIN 2 //INT0
#define BT_STATE_PIN 4

#define LEFT_IR_ARRAY_L A8
#define LEFT_IR_ARRAY_R A9
#define RIGHT_IR_ARRAY_L A10
#define RIGHT_IR_ARRAY_R A11
#define WHITE 1
#define BLACK 0

#define OVERRIDE_SIGNAL_PIN 10
#define MAX_WAVELENGTH 995
#define MAX_STEERING_WAVELENGTH 2000
#define OVERRIDE_THROTTLE_PIN 7
#define OVERRIDE_SERVO_PIN 6
#define NEUTRAL_FREQUENCY 1500
#define OVERRIDE_FORWARD_SPEED 120  //was 60
#define OVERRIDE_BACKWARD_SPEED -20  //was -250
#define OVERRIDE_STEER_RIGHT 20  //was 20
#define OVERRIDE_STEER_LEFT -20  //was -20
#define OVERRIDE_FREQ_TOLERANCE 250

/* macro definitions */
//read fast from bluetooth state pin (connected to digital pin 4 of Mega or Uno)
#if defined(__AVR_ATmega2560__)
#define bluetoothConnected (PING & B00100000)
#elif defined(__AVR_ATmega328P__)
#define bluetoothConnected (PIND & B00010000)
#endif

#endif
