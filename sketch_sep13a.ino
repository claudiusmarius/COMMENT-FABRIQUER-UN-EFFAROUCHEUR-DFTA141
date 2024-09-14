  //https://www.youtube.com/c/ClaudeDufourmont
  //Seeeduino XIAO + AD9833 + PAM8403 + HC-SR501
  // Code pour alimentation extérieure hors USB
  #include <SPI.h>
  #include <MD_AD9833.h>
  #include <Adafruit_NeoPixel.h>
  #define DATA  9 
  #define CLK   8  
  #define FSYNC1 10  
  #define DINEOPIXEL      7
  #define N_LEDS 8
  Adafruit_NeoPixel strip(N_LEDS, DINEOPIXEL, NEO_GRB + NEO_KHZ800);
  
  #define BrochePIR 6
  // La broche PIR passe à HIGH lorsqu'elle détecte quelquechose (mais ATTENTION le capteur PIR met un certain temps à s'initialiser après tout redémarrage du Seeeduino XIAO)
  
  #define D3 3
  #define D4 4
  #define LED1 5
  
  #define D1 1
  // D1 est branché sur le point milieu (2) de J1, si ce point milieu est strappé avec la point (1) de J1, D1 est relié à GND via R3 (1K) donc D1 =0, ANAD1 < 200 donc ETATANAD1 = LOW, 
  // Nous sommes forcés en pénombre pour inhiber par forçage la fonction sonore
  // Si le point milieu (2) de J1 est relié au point (3) de J1, R4 est strappée D1 est donc dépendant de LDR03 (valeur très faible en cas de résistance exposée à la lumière)


  MD_AD9833 AD(DATA, CLK, FSYNC1);

  bool ETATPIR ;
  bool ETATD3 ;
  bool ETATD4 ;
  int ANAD1;
  bool ETATANAD1;
  
  void setup() 
  { 
  pinMode(CLK, OUTPUT);    
  pinMode(DATA, OUTPUT);
  pinMode(FSYNC1, OUTPUT);
  
  pinMode(DINEOPIXEL, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(D3, INPUT_PULLUP);
  pinMode(D4, INPUT_PULLUP);
  
  pinMode(BrochePIR, INPUT);
  pinMode(D1, INPUT);
  
  AD.begin();
  } 

  void loop() 
  { 
  ANAD1 = analogRead (D1);
  if (ANAD1 > 200)                  //hors pénombre
  
  {
  ETATANAD1 = HIGH;
  }
  else
  {
  ETATANAD1 = LOW;   
  }
  
  ETATPIR = digitalRead(BrochePIR);
  ETATD3 =  !digitalRead(D3);
  ETATD4 =  !digitalRead(D4);

  if (ETATPIR && ETATD4 == HIGH)
  {
  digitalWrite (LED1, HIGH);
  NEOPIXEL ();
  }
  
  if (ETATPIR  == HIGH && ETATD3 == HIGH && ETATANAD1 == HIGH) //PIR détection + D3 strappé à zéro (AUTORISATION PIR)+ Pas de pénombre
  // ----------------------- NOTA : POUR L'INSTANT D2 N'EST PAS UTILISE DANS CE CODE ET SUR LE PCB DFT_#A141-----------------------------------------------------------------
  {
  digitalWrite (LED1, HIGH);
 
  bonusRoundSound();
  gameOverSound();                             
  bonusRoundSound();
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

  void gameOverSound() {
  AD.setMode(MD_AD9833::MODE_TRIANGLE);
  const float startFreq = 2000.0;
  const float endFreq = 300.0;
  const unsigned long rampDuration = 1000;

  for (float freq = startFreq; freq >= endFreq; freq -= 20.0) 
  {
  AD.setFrequency(MD_AD9833::CHAN_0, freq);
  delay(rampDuration / ((startFreq - endFreq) / 20.0));
  }
  AD.setMode(MD_AD9833::MODE_OFF);
  }

  void bonusRoundSound() 
  {
  AD.setMode(MD_AD9833::MODE_SQUARE1);
  const float centerFreq = 1000.0;
  const float modulationFreq = 20.0;
  const float modulationDepth = 500.0;
  const unsigned long duration = 400;

  for (unsigned long startTime = millis(); millis() - startTime < duration; ) 
  {
  float freq = centerFreq + modulationDepth * sin(2 * PI * modulationFreq * (millis() - startTime) / 1000.0);
  AD.setFrequency(MD_AD9833::CHAN_0, freq);
  }
  AD.setMode(MD_AD9833::MODE_OFF);
  }

  void NEOPIXEL ()
  {
  int nombre = 15;
  
  for (int j =0; j <nombre; j++)
  {
  NEOPIXELRouge ();
  }
  
  for (int j =0; j <nombre; j++)
  {
  NEOPIXELVert ();
  }

  for (int j =0; j <nombre; j++)
  {
  NEOPIXELBleu ();
  }
  delay(1);
  
  for (int j =0; j <nombre; j++)
  {
  NEOPIXELRouge ();
  }
  
  for (int j =0; j <nombre; j++)
  {
  NEOPIXELVert ();
  }

  for (int j =0; j <nombre; j++)
  {
  NEOPIXELBleu ();
  }

  }
  
  void NEOPIXELRouge ()
  {
  for (int i = 0; i <= N_LEDS -1; i++) 
  {
  strip.setPixelColor(i, 255, 0, 0);
  strip.show ();
  }
  strip.clear ();
  strip.show();
  digitalWrite (LED1, LOW);
  }

  void NEOPIXELVert ()
  {
  for (int i = 0; i <= N_LEDS -1; i++) 
  {
  strip.setPixelColor(i, 0, 255, 0);
  strip.show ();
  }
  strip.clear ();
  strip.show();
  digitalWrite (LED1, LOW);
  }

  void NEOPIXELBleu ()
  {
  for (int i = 0; i <= N_LEDS -1; i++) 
  {
  strip.setPixelColor(i, 0, 0, 255);
  strip.show ();
  }
  strip.clear ();
  strip.show();
  digitalWrite (LED1, LOW);
  }
