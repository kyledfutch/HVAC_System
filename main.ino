// EML 4804 Mechatronic Systems
// Kyle Futch
// Exam 1

int on_off = 25; // on/off set to pin 25
int mode = 26; // heating and cooling mode set to pin 26
int temp_sensor = A0; // TMP36 set to pin A0

int in0 = 27; // input 0 set to pin 27
int in1 = 28; // input 1 set to pin 28
int in2 = 29; // input 2 set to pin 29
int in3 = 30; // input 3 set to pin 30
int in4 = 31; // input 4 set to pin 31
int in5 = 32; // input 5 set to pin 32
int in6 = 33; // input 6 set to pin 33

int on_off_led = 34; // on off LED set to pin 34 
int heater_led = 35; // heater LED set to pin 35
int cool_led = 36; // cooling LED set to pin 36
int fan_led = 37; // fan LED set to pin 37

int out0 = 38; // output 0 set to pin 38
int out1 = 39; // output 1 set to pin 39
int out2 = 40; // output 2 set to pin 40
int out3 = 41; // output 3 set to pin 41
int out4 = 42; // output 4 set to pin 42
int out5 = 43; // output 5 set to pin 43
int out6 = 44; // output 6 set to pin 44

unsigned long shutdown_time = 30; // time for cooldown 
bool is_cooldown = false; // boolean to track if system is in cooldown

void setup() {
  pinMode(on_off, INPUT); // on off set to input
  pinMode(mode, INPUT); // heating or cooling mode set to input
  pinMode(temp_sensor, INPUT); // TMP36 set to input

  pinMode(in0, INPUT); // input 0 set to input
  pinMode(in1, INPUT); // input 1 set to input
  pinMode(in2, INPUT); // input 2 set to input
  pinMode(in3, INPUT); // input 3 set to input
  pinMode(in4, INPUT); // input 4 set to input
  pinMode(in5, INPUT); // input 5 set to input
  pinMode(in6, INPUT); // input 6 set to input

  pinMode(on_off_led, OUTPUT); // on off LED set to output
  pinMode(heater_led, OUTPUT); // heater LED set to output
  pinMode(cool_led, OUTPUT); // cooling LED set to output
  pinMode(fan_led, OUTPUT); // fan LED set to output

  pinMode(out0, OUTPUT); // output 0 set to output
  pinMode(out1, OUTPUT); // output 1 set to output
  pinMode(out2, OUTPUT); // output 2 set to output
  pinMode(out3, OUTPUT); // output 3 set to output
  pinMode(out4, OUTPUT); // output 4 set to output
  pinMode(out5, OUTPUT); // output 5 set to output
  pinMode(out6, OUTPUT); // output 6 set to output

  Serial.begin(9600); // serial baud rate of 9600
}

void loop() {
  int system_state = digitalRead(on_off); // system_state reads on_off
  int mode_state = digitalRead(mode); // mode_state reads mode 

  int desired_temp = 0; // desired_temp is inputted temp with wires
  desired_temp |= digitalRead(in0) << 0; // reads input 0 and shifts 0 bits
  desired_temp |= digitalRead(in1) << 1; // reads input 1 and shifts 1 bit
  desired_temp |= digitalRead(in2) << 2; // reads input 2 and shifts 2 bits
  desired_temp |= digitalRead(in3) << 3; // reads input 3 and shifts 3 bits
  desired_temp |= digitalRead(in4) << 4; // reads input 4 and shifts 4 bits
  desired_temp |= digitalRead(in5) << 5; // reads input 5 and shifts 5 bits
  desired_temp |= digitalRead(in6) << 6; // reads input 6 and shifts 6 bits

  int temp_value = analogRead(temp_sensor); // temp_value reads TMP36 value
  float v = temp_value * (5.0 / 1023.0); // v calculates voltage
  float temp_C = v * 100; // temp_C calculates temp using calculated voltage
  int curr_temp = int(temp_C); // curr_temp changes float to int
  Serial.print("Room temp: "); // prints room temp to serial monitor
  Serial.println(curr_temp); // prints temp with newline

  Serial.print("Binary: "); // prints binary to serial monitor
  for (int i = 6; i >= 0; i--) { // loop through bits from highest to lowest
    Serial.print((curr_temp >> i) & 1); // prints curr_temp in binary
  }
  Serial.println(); // newline
  Serial.print("Desired temp: "); // prints desired temp
  Serial.println(desired_temp); // prints inputted value

  delay(5000); // delays 5 secs because otherwise it'd print thru a million times a minute

  digitalWrite(out0, (int(curr_temp) >> 0) & 1); // output bit 0 to pin 38
  digitalWrite(out1, (int(curr_temp) >> 1) & 1); // output bit 1 to pin 39
  digitalWrite(out2, (int(curr_temp) >> 2) & 1); // output bit 2 to pin 40
  digitalWrite(out3, (int(curr_temp) >> 3) & 1); // output bit 3 to pin 41
  digitalWrite(out4, (int(curr_temp) >> 4) & 1); // output bit 4 to pin 42
  digitalWrite(out5, (int(curr_temp) >> 5) & 1); // output bit 5 to pin 43
  digitalWrite(out6, (int(curr_temp) >> 6) & 1); // output bit 6 to pin 44

  if (system_state == HIGH) { // if on/off is set to 5V
    digitalWrite(on_off_led, HIGH); // turn on on/off LED
    digitalWrite(fan_led, HIGH); // fan will always be on if system is on
    if(!is_cooldown || millis() - shutdown_time > 30000) { // if system is in cooldown or less than 30 secs passed
      if((desired_temp - curr_temp > 2) || (curr_temp - desired_temp > 2)) { // if temp is NOT 2 degrees higher or lower
        digitalWrite(fan_led, HIGH); // turn on fan LED
        if(mode_state == HIGH) { // if mode is set to 5V (heater)
          digitalWrite(heater_led, HIGH); // turn on heater LED
          digitalWrite(cool_led, LOW); // turn off cooling LED
        }
        else {  // if mode is set to GND (cooling)
          digitalWrite(heater_led, LOW); // turn off heater LED
          digitalWrite(cool_led, HIGH); // turn on cooling LED
        }
      }
      else { // if temp is outside range
        digitalWrite(fan_led, LOW); // turn off fan LED
        digitalWrite(heater_led, LOW); // turn off heater LED
        digitalWrite(cool_led, LOW); // turn off cooling LED
      }
    }
  }
  else { // if on off is set to GND
    digitalWrite(on_off_led, LOW); // turn off on off LED
    digitalWrite(heater_led, LOW); // turn off heating LED
    digitalWrite(cool_led, LOW); // turn off cooling LED
    if (!is_cooldown) {
      is_cooldown = true; // cooldown bool is set to true
      digitalWrite(fan_led, HIGH); // turn on fan LED
      delay(15000); // delay 15 seconds for fan
      digitalWrite(fan_led, LOW); // turn off fan LED

      delay(30000); // delay 30 seconds for cooldown
      is_cooldown = false; // after 30 seconds no longer in cooldown
    }
  }
}
