const int MAX_NUMBER = 255;
const int LED_AMOUNT = 8;
const int LED_DISPLACEMENT = 2;
const unsigned long DELAY = 1000;
int current = 0;
unsigned long lastTime = 0;


void setup() {
  Serial.begin(9600);
  for(int i = 0; i < LED_AMOUNT; i++)
    pinMode(i + LED_DISPLACEMENT, OUTPUT);

  lastTime = millis();
}

void loop() {
  unsigned long currentTime = millis();
  if(currentTime >= lastTime + DELAY)
  {
    display(current);
    setNextNumber();
    lastTime = currentTime;
  }
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
