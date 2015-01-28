int THRESHOLD_VALUE = 500;

// Digital Output Pins
int LED_ACTIVE = 0;
int LED_HIT = 0;
int LED_1 = 0;
int LED_2 = 0;
int LED_3 = 0;
int LED_4 = 0;
int LED_5 = 0;
int LED_6 = 0;

// Analog Input Pins
int FSR_LEFT_PEC = 0;
int FSR_RIGHT_PEC = 0;
int FSR_ABS = 0;
int FSR_LEFT_SHLDR = 0;
int FSR_RIGHT_SHLDR = 0;
int FSR_BACK = 0;

// Analog Input Values
int leftPecAV;
int rightPecAV;
int absAV;
int leftShldrAV;
int rightShldrAV;
int backAV;

int life_left = 6;
boolean game_finished = false;
int hits = 0;
boolean left_pec_hit = false;
boolean right_pec_hit = false;
boolean abs_hit = false;
boolean left_shldr_hit = false;
boolean right_shldr_hit = false;
boolean back_hit = false;

void setup(){
  Serial.begin(115200);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(LED_5, OUTPUT);
  pinMode(LED_6, OUTPUT);
  pinMode(LED_ACTIVE, OUTPUT);
  pinMode(LED_HIT, OUTPUT);
}

void resetGame(){
  game_finished = false;
  life_left = 6;
}

void changeLEDS(){
  int num_off = 6 - life_left;
  if (num_off)
  for (int i = 0; i < 6 - life_left)
}

void handleHit(){
  if (hits - life_left <= 0){
    game_finished = true;
    digitalWrite(LED_ACTIVE, LOW);
  }
  if (leftPecAV > THRESHOLD_VALUE) hit++;
  if (rightPecAV > THRESHOLD_VALUE) hit++;
  if (absAV > THRESHOLD_VALUE) hit++;
  if (leftShldrAV > THRESHOLD_VALUE) hit++;
  if (rightShldrAV > THRESHOLD_VALUE) hit++;
  if (backAV > THRESHOLD_VALUE) hit++;
  changeLEDS();
}

void checkBluetooth(){
  char cmd;
  if (bluetooth.available()){
    cmd = (char)bluetooth.read();
    if (cmd == 'R') resetGame();
  }
}

void resetFlags(){
  hits = 0;
  left_pec_hit = false;
  right_pec_hit = false;
  abs_hit = false;
  left_shldr_hit = false;
  right_shldr_hit = false;
  back_hit = false;
}

void loop(){
  
  if (!game_finished){

    leftPecAV = analogRead(FSR_LEFT_PEC);
    rightPecAV = analogRead(FSR_RIGHT_PEC);
    absAV = analogRead(FSR_ABS);
    leftShldrAV = analogRead(FSR_LEFT_SHLDR);
    rightShldrAV = analogRead(FSR_RIGHT_SHLDR);
    backAV = analogRead(FSR_BACK);

    if (leftPecAV > THRESHOLD_VALUE) hits++;
    if (rightPecAV > THRESHOLD_VALUE) hits++;
    if (absAV > THRESHOLD_VALUE) hits++;
    if (leftShldrAV > THRESHOLD_VALUE) hits++;
    if (rightShldrAV > THRESHOLD_VALUE) hits++;
    if (backAV > THRESHOLD_VALUE) hits++;

    if (hits > 0) handleHit();

    resetFlags();
  }

  checkBluetooth();
}