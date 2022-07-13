/*
--Simon says--------------------
Description: This game plays a sequence of LED lights and the user needs to remember them.
             If the user can correctly follow 5 patterns, they win
Date:June 12 2020
By:Sam
*/

// set the pins where the buttons, LEDs and buzzer connect
int button[] = {2, 4, 6, 8};
int LED[] = {3, 5, 7, 9};
int music[] = {262, 330, 392, 494};

int winRounds = 5;
int pattern[5];

int buzzerPin = 10;

int buttonPressed = 4;
int numberOfPassedRounds = 1;

long time = 0;
long timeLimit = 2000;

boolean start = false;

void setup()
{

    // set all of the button pins to input_pullup (use the builtin pullup resistors)
    pinMode(button[0], INPUT);
    pinMode(button[1], INPUT);
    pinMode(button[2], INPUT);
    pinMode(button[3], INPUT);

    pinMode(LED[0], OUTPUT);
    pinMode(LED[1], OUTPUT);
    pinMode(LED[2], OUTPUT);
    pinMode(LED[3], OUTPUT);
    // All LED pins become output pins
    pinMode(buzzerPin, OUTPUT);
}
void loop()
{

    if (start == false)
    {
        startPattern();
        numberOfPassedRounds = 0;
        delay(1500);
        start = true;
    }
    for (int i = 0; i <= numberOfPassedRounds; i++)
    {
        LEDflash(pattern[i]);
        delay(150);
        LEDsOff();
        delay(150);
    }

    for (int i = 0; i <= numberOfPassedRounds; i++)
    {

        time = millis();

        while (true)
        {
            buttonPressed = checkButton();

            if (buttonPressed < 4)
            {

                LEDflash(buttonPressed);

                if (buttonPressed == pattern[i])
                {
                    delay(300);
                    LEDsOff();
                    break;
                }
                else
                {
                    losePattern();
                    break;
                }
            }
            else
            {
                LEDsOff();
            }

            if (millis() - time > timeLimit)
            {
                losePattern();
                break;
            }
        }
    }

    numberOfPassedRounds = numberOfPassedRounds + 1;

    if (numberOfPassedRounds >= winRounds)
    {
        winPattern();
    }

    delay(1000);
}

void LEDflash(int LEDNumber)
{
    digitalWrite(LED[LEDNumber], HIGH);
    tone(buzzerPin, music[LEDNumber]);
}

void LEDsOff()
{
    digitalWrite(LED[0], LOW);
    digitalWrite(LED[1], LOW);
    digitalWrite(LED[2], LOW);
    digitalWrite(LED[3], LOW);

    noTone(buzzerPin);
}

int checkButton()
{

    if (digitalRead(button[0]) == HIGH)
    {
        return 0;
    }
    else if (digitalRead(button[1]) == HIGH)
    {
        return 1;
    }
    else if (digitalRead(button[2]) == HIGH)
    {
        return 2;
    }
    else if (digitalRead(button[3]) == HIGH)
    {
        return 3;
    }
    else
    {
        return 4;
    }
}

void startPattern()
{

    randomSeed(analogRead(A0));
  	
    for(int i=0;i<=winRounds;i++){
		pattern[i] = round(random(0,4));

    }
  	

    for (int i = 0; i <= 3; i++)
    {

        tone(buzzerPin, music[i], 150);

        digitalWrite(LED[0], HIGH);
        digitalWrite(LED[1], HIGH);
        digitalWrite(LED[2], HIGH);
        digitalWrite(LED[3], HIGH);

        delay(100);

        digitalWrite(LED[0], LOW);
        digitalWrite(LED[1], LOW);
        digitalWrite(LED[2], LOW);
        digitalWrite(LED[3], LOW);

        delay(100);
    }
}

void winPattern()
{

    for (int j = 0; j <= 3; j++)
    {
        digitalWrite(LED[j], HIGH);
    }

    tone(buzzerPin, 1358, 150);
    delay(175);
    tone(buzzerPin, 9867, 150);
    delay(175);
    tone(buzzerPin, 2637, 150);
    delay(175);
    tone(buzzerPin, 7093, 150);
    delay(175);
    tone(buzzerPin, 2959, 150);
    delay(175);
    tone(buzzerPin, 4135, 500);
    delay(500);

    do
    {
        buttonPressed = checkButton();
    } while (buttonPressed > 3);
    delay(100);

    start = false;
}

void losePattern()
{

    for (int j = 0; j <= 3; j++)
    {
        digitalWrite(LED[j], HIGH);
    }

    tone(buzzerPin, 100, 250);
    delay(275);
    tone(buzzerPin, 73, 250);
    delay(275);
    tone(buzzerPin, 55, 150);
    delay(175);
    tone(buzzerPin, 98, 500);
    delay(500);

    do
    {
        buttonPressed - checkButton();
    } while (buttonPressed > 3);
    delay(200);

    start = false;
}