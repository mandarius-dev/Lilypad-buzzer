// Pines used for the components
int lightPin = A2;
int lightPinPower = A4;
int buttonPin = 10;
int buzzerPin = 7;
int ledPin = 5;

// The delay between bips 
int buzzerDelayTime = 700;

// Control variable. Used for detecting if the switch is presed
// LOW  - If the button is presed
// HIGH - If the button in NOT pressed 
int buttonPresed;

// Control variable. Used to make sure that the numberPres is incremented only once
int increment=0;

// Number of timese that the button has been presed
int numberPres=0;

// Control variable. Used to determin if the buzzer bips
// 1 - The buzzre bips
// 0 - The buzzer dose NOT bep
int buzzerActivated=0;

// The number of beps(random)
int numberBips;

// The upper and lower that can be generated for the number of beps
int minBips=1;
int maxBips=10;

// Notes and their frequencies
const int C = 1046;
const int D = 1175;
const int E = 1319;
const int F = 1397;
const int G = 1568;
const int A = 1760;
const int B = 1976;
const int C1 = 2093;
const int D1 = 2349;

// The startup melody (played on setup)
int numberStartUp=5;
int startUpMelody[]={C,E,D,F,C1};
int startUpDuration[]={300,300,300,300,300};

// The WIN melody (played when you WIN)
int numberWin=4;
int winMelody[]={A,B,A,C1};
int winDuration[]={300,300,300,500};

// The LOSE melody (played when you LOSE)
int numberLose=3;
int loseMelody[]={E,D,C};
int loseDuration[]={300,300,500};


void setup()
{
    Serial.begin(9600);

    // Set the pins 
    pinMode(buzzerPin, OUTPUT);
    pinMode(ledPin, OUTPUT);
    pinMode(buttonPin, INPUT);
    pinMode(lightPin, INPUT);
    pinMode(lightPinPower, OUTPUT);
    digitalWrite(lightPinPower, HIGH);

    // Sets the button pin as HIGH 
    digitalWrite(buttonPin, HIGH);

    // Play the startup melody
    melody(numberStartUp,startUpMelody,startUpDuration);    
}

// Melody player
// numberNotes - number of notes
// notes       - notes that needs to be played
// duration    - duration between notes
void melody(int numberNotes,int *notes,int *duration)
{
  for(int i=0;i<numberNotes;i++)
  {
    tone(buzzerPin,notes[i]);
    delay(duration[i]);
    noTone(buzzerPin);
  }
  delay(1000);
}

// Play a specific note for a number of times
// n    - number of times that the note has to be played
// note - the note that is played
void sound_buzzer(int n,int note)
{
  digitalWrite(ledPin,HIGH);
  for(int i=0;i<n;i++)
  {
    tone(buzzerPin,note);
    delay(buzzerDelayTime);
    noTone(buzzerPin);
  }
  digitalWrite(ledPin,LOW);
}

// Main loop of the program
void loop()
{
  // If the button is presd
  if(!buzzerActivated)
  {
    numberBips=random(minBips,maxBips);
    sound_buzzer(numberBips,G);
    buzzerActivated=1;
  }
  else
  {
    if(buzzerActivated)
    {
      buttonPresed=digitalRead(buttonPin);
      if(buttonPresed==LOW)
      {
        // Increments the number of prees only once 
        if(!increment)
        {
          numberPres++;
          tone(buzzerPin,G);
          delay(400);
          noTone(buzzerPin);
          increment=1;
        }
      }
      else
        increment=0;

      // Confirms the number of preses
      if(analogRead(lightPin)<15)
      {
        // Checks the number of button preses with the number of beps generated
        if(numberPres==numberBips)
        {
          Serial.println("Win");
          melody(numberWin,winMelody,winDuration);
          buzzerActivated=0;
          numberPres=0;
        }
        else
        {
          Serial.println("Lose");
          melody(numberLose,loseMelody,loseDuration);
          buzzerActivated=0;
          numberPres=0;
        } 
      }
    }
  }
}
