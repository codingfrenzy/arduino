
                 // a  b  c  d  e   f   g
        // LED PIN: 7, 6, 4, 1, 3,  8,  9
int segments[] =   {9, 8, 5, 2, 4, 10, 11};

int digits[][7] = {{1, 1, 1, 1, 1, 1, 0}, // 0
                   {0, 1, 1, 0, 0, 0, 0}, // 1
                   {1, 1, 0, 1, 1, 0, 1}, // 2
                   {1, 1, 1, 1, 0, 0, 1}, // 3
                   {0, 1, 1, 0, 0, 1, 1}, // 4
                   {1, 0, 1, 1, 0, 1, 1}, // 5
                   {1, 0, 1, 1, 1, 1, 1}, // 6
                   {1, 1, 1, 0, 0, 0, 0}, // 7
                   {1, 1, 1, 1, 1, 1, 1}, // 8
                   {1, 1, 1, 1, 0, 1, 1}, // 9
                   };

int ledPin = 22;
int leftDigitPin = 16;
int rightDigitPin = 15;

int workModePin = 13;
int freeModePin = 12;
int brightness = 10;

int workTime = 25;
int freeTime = 10;

unsigned long timeSinceStart;

void setup(){
  // set pins to output
  for(int i = 0; i < 7; i++) {
    pinMode(segments[i], OUTPUT);
  }

  pinMode(leftDigitPin, OUTPUT);
  pinMode(rightDigitPin, OUTPUT);
  pinMode(workModePin, OUTPUT);
  pinMode(freeModePin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  digitalWrite(leftDigitPin, HIGH);
  digitalWrite(rightDigitPin, HIGH);
}

void loop() {
  timeSinceStart = millis();
  long secondsElapsed = timeSinceStart / 60000;

  int timer = workTime - secondsElapsed;
  if(timer < 0){
    timer = secondsElapsed - workTime;
    freeMode();
  } else {
    workMode();
  }

  display(timer);
}

void display(int number){
  while(number >= 100) {
    number = number % 10;
  }
  
  int right = number % 10;
  displayRight(right);
  delay(10);
  int left = number / 10;
  displayLeft(left);
  delay(10);
}
void displayLeft(int number) {
  digitalWrite(leftDigitPin, HIGH);
  digitalWrite(rightDigitPin, HIGH);
  displayDigit(number);
  digitalWrite(leftDigitPin, LOW);
}
void displayRight(int number) {
  digitalWrite(leftDigitPin, HIGH);
  digitalWrite(rightDigitPin, HIGH);
  displayDigit(number);
  digitalWrite(rightDigitPin, LOW);
}
void displayDigit(int number) {
  for(int i = 0; i < 7; i++) {
    if (digits[number][i] == 1) {
      digitalWrite(segments[i], HIGH);
    } else {
      digitalWrite(segments[i], LOW);
    }
  }
}
void workMode() {
  analogWrite(workModePin, brightness);
  digitalWrite(freeModePin, LOW);
}
void freeMode() {
  digitalWrite(workModePin, LOW);
  analogWrite(freeModePin, brightness);
}

