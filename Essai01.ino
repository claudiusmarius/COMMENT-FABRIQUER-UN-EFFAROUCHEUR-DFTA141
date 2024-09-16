
  // Ce code est un code d'essai pour s'assurer du bon fonctionnement du PIR
  #include <SPI.h>
  #include <MD_AD9833.h>
  #define DATA  9 
  #define CLK   8  
  #define FSYNC1 10  
 
  #define BrochePIR 6
  #define LED1 5
  
  MD_AD9833 AD(DATA, CLK, FSYNC1);

  bool ETATPIR ;
  
  
  void setup() 
  { 
  pinMode(CLK, OUTPUT);    
  pinMode(DATA, OUTPUT);
  pinMode(FSYNC1, OUTPUT);
  
  pinMode(LED1, OUTPUT);
 
  pinMode(BrochePIR, INPUT);
  
  AD.begin();
  } 

  void loop() 
  { 
  
  ETATPIR = digitalRead(BrochePIR);
  
  
  if (ETATPIR  == HIGH )
  {
  digitalWrite (LED1, HIGH);
  missileApproachSound03();
  }
  
  else
  {
  AD.setMode(MD_AD9833::MODE_OFF); 
  digitalWrite (LED1, LOW);
  }
  }
  
  void missileApproachSound03() 
  {
  AD.setMode(MD_AD9833::MODE_TRIANGLE);
  const float baseFreq = 400.0;
  const float maxFreqChange = 800.0;
  const unsigned long duration = 5000;
  const unsigned long approachDuration = duration / 2;

  unsigned long startTime = millis();
  while (millis() - startTime < duration) 
  {
  unsigned long elapsedTime = millis() - startTime;
  float freqChange = maxFreqChange * ((float)elapsedTime / approachDuration);
  float freq = baseFreq + freqChange;
  AD.setFrequency(MD_AD9833::CHAN_0, freq);
  delay(10);
  }
  AD.setMode(MD_AD9833::MODE_OFF);
  ETATPIR == LOW;
  }

   