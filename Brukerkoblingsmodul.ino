const int button1 = 2; //knapp til venstre
const int button2 = 3; //knapp til høyre

const int Red1 = 8; //signal til rødt LED
const int Red2 = 9; //signal til rødt LED
const int greenLed1 = 10; //signal til grønt LED
const int greenLed2 = 11; //signal til grønt LED
const int synthOut = 12; //signal til annet arduino-brett
                        
int entered[3]; //lager en rekke for knappene som blir trykket av bruker

void setup(){
  
  pinMode(button1, INPUT_PULLUP); //button 1 er input
  pinMode(button2, INPUT_PULLUP); //button 2 er input
  
  pinMode(Red1, OUTPUT); //rødt LED er output
  pinMode(Red2, OUTPUT);
  pinMode(greenLed1, OUTPUT); // grønt LED er output
  pinMode(greenLed2, OUTPUT);
  pinMode(synthOut, OUTPUT); //signal til synth er output
  
}

void loop(){
  if (digitalRead(button1) == LOW){ //hvis knapp til venstre trykkes
    checkEntered1(1); //kall på checkEntered1 og gi det verdi 1
    delay(250);  
  }
  else if (digitalRead(button2) == LOW){ //hvis knapp til høyre trykkes
    checkEntered1(2); //kall på checkEntered1 og gi det verdi 2
    delay(250); 
  }
}

void checkEntered1(int button){ //sjekk første elementet i entered[] 
  if (entered[0] != 0){ //hvis det allerede er blitt trykket
    checkEntered2(button); //gå videre til checkEntered2
  }
  
  else if(entered[0] == 0){ //ikke blitt definert med et tall
    entered[0] = button; //sett første elemtent som knapp presset ned
    digitalWrite(Red1, HIGH); // skrur av  rødt LED
    digitalWrite(Red2, HIGH); // skrur av  rødt LED
    digitalWrite(greenLed1, LOW); //skrur av grønt LED
    digitalWrite(greenLed2, LOW); // skrur av  grønt LED
  }
}

void checkEntered2(int button){ //sjekk andre elementet i entered[]
  
 if (entered[1] == 0){ //ikke blitt definert med et tall
   entered[1] = button; //sett siste element som knapp presset ned
   if (entered[0]==entered[1]){ //hvis samme knapp har blitt presset
     digitalWrite(Red1,LOW); // skrur av  rødt LED
     digitalWrite(Red2,LOW); // skrur av  rødt LED
     entered[0]=0; //nullstill entered[]
     entered[1]=0; // --
   }
   else{
     digitalWrite(Red1, LOW); // skrur av  rødt LED
     digitalWrite(Red2, LOW); // skrur av  rødt LED
     digitalWrite(greenLed1, HIGH); // skrur på grønt LED
     digitalWrite(greenLed2, HIGH); // skrur på grønt LED
     digitalWrite(synthOut, HIGH); // sender signal til annet arduino-brett
     entered[0]=0; //nullstill entered[]
     entered[1]=0; // --
     delay(30000); // 30 sek med grønt lys
     digitalWrite(greenLed1, LOW); // skrur av grønt LED
     digitalWrite(greenLed2, LOW); // skrur av grønt LED
   } 
  }
}
