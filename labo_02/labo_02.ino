const int potPin = A1;
const int buttonPin = 2;
const int ledPins[] = { 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

bool buttonState = true;
bool lastButtonState = false;
unsigned long currentTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);

  for (int i = 0; i < 10; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  Serial.println("Setup completed");
}

void loop() {
  // Lecture du bouton avec anti-rebond
  bool reading = digitalRead(buttonPin) == LOW;
  if (reading != lastButtonState) {
    currentTime = millis();
  }
  if ((millis() - currentTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState) {
        afficherProgression();
      }
    }
  }
  lastButtonState = reading;

  // Lecture et mapping du potentiomètre
  int potValue = analogRead(potPin);
  int progress = map(potValue, 0, 1023, 0, 20);
  controlLEDs(progress);
}

void afficherProgression() {
  int potValue = analogRead(potPin);
  int progress = map(potValue, 0, 1023, 0, 20);
  int pourcentage = map(progress, 0, 20, 0, 100);

  String bar;

  Serial.print("[");
  for (int i = 0; i < 20; i++) {
    bar += (i < progress) ? '#' : '.';
  }
  Serial.print(bar);
  Serial.print("] ");
  Serial.print(pourcentage);
  Serial.println("%");
}

void controlLEDs(int progress) {
  int pourcentage = map(progress, 0, 20, 0, 100);

  for (int i = 0; i < 10; i++) {
    digitalWrite(ledPins[i], pourcentage >= (i * 10) ? HIGH : LOW);
  }
}
