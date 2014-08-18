
#include <SD.h>
#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //physical mac address
byte ip[] = { 192, 168, 0, 13 }; // ip in lan
EthernetServer server(80); //server port


char incomingChar = 'a';


//////////////////////

void setup(){

  Serial.begin(9600);

  Serial.print("Starting SD..");
  if(!SD.begin(4)) Serial.println("failed");
  else Serial.println("ok");

  Ethernet.begin(mac, ip);
  //digitalWrite(10,HIGH);

  server.begin();
  Serial.println("Ready");
  
  pinMode(2,OUTPUT);
  
  delay(500);

  
}

void loop(){
  // Create a client connection
  EthernetClient client = server.available();
  if (client) {
    String readString; 
    while (client.connected()) {
      if (client.available()) {
        
        
        char c = client.read();
        readString += c;
        
       
        //if HTTP request has ended
        if (c == '\n') {

          client.println("HTTP/1.1 200 OK"); //send new page
          
          File myFileCss = SD.open("STYLE.CSS");
          
          readFileCss(client, myFileCss);

          File myFileHtml = SD.open("INDEX~1.HTM");
          
          readFileHtml(client, myFileHtml); 
          
          File myFileJs = SD.open("MAIN.JS");
          
          readFileJs(client, myFileJs); 
          
          
          client.stop();
            
        }
    
      }
      
    }
    readString.replace("HTTP/1.1","");
    readString.replace("GET /","");
    readString.trim();
    
    if(readString.equals("?do=on")){
      Serial.print("on..");
      digitalWrite(2,LOW);
    
    }
    
    if(readString.equals("?do=off")){
      digitalWrite(2,HIGH);
      
    }
    
  } 
  
  if (Serial.available() > 0) {
	// lee el byte entrante:
	incomingChar = Serial.read();

	// dice lo que ha recibido:
        if(incomingChar!=10){ 
	  Serial.print("He recibido: ");
          Serial.println(incomingChar);
        }
     }
}

void readFileCss(EthernetClient client, File myFileCss){
  
  if (myFileCss) {
            byte clientBuf[64];
            int clientCount = 0;
            client.println();
            client.println("<style>");
            client.println();
            // read from the file until there's nothing else in it:
            while (myFileCss.available()) {
              clientBuf[clientCount] = myFileCss.read();
              clientCount++;

              if(clientCount > 63)
              {
                // Serial.println("Packet");
                client.write(clientBuf,64);
                clientCount = 0;
              }
            }
            // close the file:
            if(clientCount > 0) client.write(clientBuf,clientCount);   
            myFileCss.close();
            client.println();
            client.println("</style>");
          }

}

void readFileHtml(EthernetClient client, File myFileHtml){
  
  if (myFileHtml) {
            byte clientBuf[64];
            int clientCount = 0;
            
            client.println();
            // read from the file until there's nothing else in it:
            while (myFileHtml.available()) {
              clientBuf[clientCount] = myFileHtml.read();
              clientCount++;

              if(clientCount > 63)
              {
                // Serial.println("Packet");
                client.write(clientBuf,64);
                clientCount = 0;
              }
            }
            // close the file:
            if(clientCount > 0) client.write(clientBuf,clientCount);   
            myFileHtml.close();

          }

}

void readFileJs(EthernetClient client, File myFileJs){
  
  if (myFileJs) {
            byte clientBuf[64];
            int clientCount = 0;
            client.println();
            client.println("<script>");
            client.println();
            // read from the file until there's nothing else in it:
            while (myFileJs.available()) {
              clientBuf[clientCount] = myFileJs.read();
              clientCount++;

              if(clientCount > 63)
              {
                // Serial.println("Packet");
                client.write(clientBuf,64);
                clientCount = 0;
              }
            }
            // close the file:
            if(clientCount > 0) client.write(clientBuf,clientCount);   
            myFileJs.close();
            client.println();
            client.println("</script>");
          }

}


