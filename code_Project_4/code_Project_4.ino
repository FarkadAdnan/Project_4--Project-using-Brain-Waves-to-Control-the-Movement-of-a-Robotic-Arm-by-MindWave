/*
 By:Farkad Adnan
 E-mail: farkad.hpfa95@gmail.com
 inst : farkadadnan
 #farkadadnan , #farkad_adnan , فرقد عدنان#
 FaceBook: كتاب عالم الاردوينو
 inst : arduinobook
 #كتاب_عالم_الاردوينو  #كتاب_عالم_الآردوينو 
 */
#include <Servo.h>
Servo menique;
Servo anular;
Servo medio;
Servo indice;
Servo pulgar;

int meniqueH = 90;
int meniqueL = 180;
int anularH = 60;
int anularL = 180;
int medioH = 120;
int medioL = 0;
int indiceH = 92;
int indiceL = 180;
int pulgarH = 176;
int pulgarL = 20;

#define LED 13             
#define BAUDRATE 57600    
#define DEBUGOUTPUT 0      
#define powercontrol 10  
byte generatedChecksum = 0;
byte checksum = 0; 
int payloadLength = 0;
byte payloadData[64] = {0};
byte poorQuality = 0;
byte attention = 0;
byte meditation = 0;

long lastReceivedPacket = 0;
boolean bigPacket = false;

void setup() {
  menique.attach(11);  
  anular.attach(9);
  medio.attach(5);  
  indice.attach(6);
  pulgar.attach(10);
  
  pinMode(LED, OUTPUT);
  Serial.begin(BAUDRATE);     

}

byte ReadOneByte() {
  int ByteRead;

  while(!Serial.available());
  ByteRead = Serial.read();
#if DEBUGOUTPUT  
#endif

  return ByteRead;
}

void loop() {

  if(ReadOneByte() == 170) {
    if(ReadOneByte() == 170) {

      payloadLength = ReadOneByte();
      if(payloadLength > 169)                 
          return;

      generatedChecksum = 0;        
      for(int i = 0; i < payloadLength; i++) {  
        payloadData[i] = ReadOneByte();         
        generatedChecksum += payloadData[i];
      }   

      checksum = ReadOneByte();                    
      generatedChecksum = 255 - generatedChecksum;  
        if(checksum == generatedChecksum) {    

        poorQuality = 200;
        attention = 0;
        meditation = 0;

        for(int i = 0; i < payloadLength; i++) { 
          switch (payloadData[i]) {
          case 2:
            i++;            
            poorQuality = payloadData[i];
            bigPacket = true;            
            break;
          case 4:
            i++;
            attention = payloadData[i];                        
            break;
          case 5:
            i++;
            meditation = payloadData[i];
            break;
          case 0x80:
            i = i + 3;
            break;
          case 0x83:
            i = i + 25;      
            break;
          default:
            break;
          } 
        } 

#if !DEBUGOUTPUT
        if(bigPacket) {
          if(poorQuality == 0)
            digitalWrite(LED, HIGH);
          else
            digitalWrite(LED, LOW);
          lastReceivedPacket = millis();
          switch(attention / 10) {
          case 0:
            menique.write(meniqueH);
            anular.write(anularH);
            medio.write(medioH);
            indice.write(indiceH);
            pulgar.write(pulgarH);          
            break;
          case 1:
            menique.write(meniqueH);
            anular.write(anularH);
            medio.write(medioH);
            indice.write(indiceL);
            pulgar.write(pulgarH);
            break;
          case 2:
            menique.write(meniqueH);
            anular.write(anularH);
            medio.write(medioL);
            indice.write(indiceL);
            pulgar.write(pulgarH);
            break;
          case 3:              
            menique.write(meniqueH);
            anular.write(anularL);
            medio.write(medioL);
            indice.write(indiceL);
            pulgar.write(pulgarH);             
            break;
          case 4:
            menique.write(meniqueL);
            anular.write(anularL);
            medio.write(medioL);
            indice.write(indiceL);
            pulgar.write(pulgarH);             
            break;
          case 5:
            menique.write(meniqueL);
            anular.write(anularL);
            medio.write(medioL);
            indice.write(indiceL);
            pulgar.write(pulgarL);             
            break;
          case 6:              
            menique.write(meniqueH);
            anular.write(anularH);
            medio.write(medioH);
            indice.write(indiceH);
            pulgar.write(pulgarL);              
            break;
          case 7:
            menique.write(meniqueL);
            anular.write(anularH);
            medio.write(medioH);
            indice.write(indiceL);
            pulgar.write(pulgarH);             
            break;    
          case 8:
            menique.write(meniqueH);
            anular.write(anularH);
            medio.write(medioH);
            indice.write(indiceL);
            pulgar.write(pulgarL);
            break;
          case 9:
            menique.write(meniqueL);
            anular.write(anularL);
            medio.write(medioL);
            indice.write(indiceL);
            pulgar.write(pulgarL);  
            break;
          case 10:
            menique.write(meniqueL);
            anular.write(anularL);
            medio.write(medioL);
            indice.write(indiceL);
            pulgar.write(pulgarL);  
            break;           
          }                     
        }
#endif        
        bigPacket = false;        
      }
      else {}
    } 
  }
}
