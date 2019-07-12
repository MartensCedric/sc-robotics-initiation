const int MAX_NUMBER = 255;
const int LED_AMOUNT = 8;
const int LED_DISPLACEMENT = 2;
const int POTENTIOMETER_PIN = A0;
const int RESET_PIN = 10;
const int RESET = 1;
unsigned long delayAmount = 1000;
int current = 0;
int incomingByte = -1;
unsigned long lastTime = 0;


void setup() {
  Serial.begin(9600);
  for(int i = 0; i < LED_AMOUNT; i++)
    pinMode(i + LED_DISPLACEMENT, OUTPUT);

  pinMode(RESET_PIN, INPUT);
  pinMode(13, OUTPUT);

  lastTime = millis();
}

void loop() {
  unsigned long currentTime = millis();
  delayAmount = analogRead(POTENTIOMETER_PIN) + 100;
  
  if(Serial.available() > 0)
  {
    incomingByte = Serial.read();
    Serial.print("Got : ");
    Serial.print(incomingByte, DEC);
  }
  
  if(digitalRead(RESET_PIN) == HIGH || incomingByte == RESET)
  {
    reset();
    digitalWrite(13, HIGH);
  }
  else
    digitalWrite(13, LOW);
    
  if(currentTime >= lastTime + delayAmount)
  {
    display(current);
    setNextNumber();
    lastTime = currentTime;
  }

  incomingByte = -1;
}

void display(int number)
{
  for(int i = LED_AMOUNT - 1; i >= 0; i--)
  {
    int baseTwo =  1 << (LED_AMOUNT - i - 1);
    
    boolean on = (number | baseTwo) == number;
    digitalWrite(i + LED_DISPLACEMENT, on ? HIGH : LOW);
  }
}

int setNextNumber()
{
  if(current < MAX_NUMBER)
    current += 1;
  else
    current = 0;
}
void reset()
{
  current = 0;
  lastTime = millis();
}
