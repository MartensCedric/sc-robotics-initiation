const int MAX_NUMBER = 255;
const int LED_AMOUNT = 8;
const unsigned long DELAY = 1000;
int current = 0;
unsigned long lastTime = 0;


void setup() {
  for(int i = 0; i < LED_AMOUNT; i++)
    pinMode(i, OUTPUT);

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
  for(int i = 0; i < LED_AMOUNT; i++)
  {
    boolean on = (number << (LED_AMOUNT - (i+1))) & 1;
    digitalWrite(i, on ? HIGH : LOW);
  }
}

int setNextNumber()
{
  if(current < MAX_NUMBER)
    current += 1;
  else
    current = 0;
}
