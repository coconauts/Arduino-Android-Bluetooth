#include <SoftwareSerial.h>
 
SoftwareSerial Genotronex(10, 11); // TX, RX

#define MAX_BUFFER 4
 
int motor = 9;    
int speed = 0;
char data;
char* buffer;
boolean receiving = false;
int pos;

void setup()  { 
  Genotronex.begin(9600);
  Genotronex.println("Bluetooth On");
  pinMode(motor, OUTPUT);
  
   buffer = new char[MAX_BUFFER];
} 

void loop()  { 
  
   if (Genotronex.available()){
        
        data=Genotronex.read();
        
         switch(data) {
            //3: End of transmission
            case 3:  receiving = false;  
                    speed = buffer2int(buffer);
                               
                    Genotronex.print("Received: ");
                    Genotronex.print(buffer);
                    Genotronex.print(", Speed: ");
                    Genotronex.println(speed);

                     break; //end message
            default: if (receiving == false) resetData();
                    buffer[pos] = data;
                    pos++;
                     receiving = true;          
          }
   }  
  analogWrite(motor, speed); 
  delay(10);                            
}

 void resetData(){
   for (int i=0; i<=pos; i++) buffer[i] = 0; 
   pos = 0;
}
    
int buffer2int(char* buffer){
  int i;
  sscanf(buffer, "%d", &i);
  return i;
  
}

