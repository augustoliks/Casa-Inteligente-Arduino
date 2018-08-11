#include <SPI.h>
#include <Ethernet.h>
#include <Servo.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //Mac do Arduino
byte ip[] = { 192, 168, 1, 254 }; //IP do Arduino

EthernetServer server(8100); //Selecionar porta de saída
Servo servo;

int led1 = 2;		//Cozinha
int led2 = 3;		//Copa
int led3 = 4;		//Sala
int led4 = 5;		//Lavanderia
int led5 = 6;	  //Quarto
int led6 = 7;		//Banheiro
int ventilador = 8;

String readString = String(30);
String statusLed;

void setup() {
	Ethernet.begin(mac, ip);
	pinMode(led1, OUTPUT);
	pinMode(led2, OUTPUT);
	pinMode(led3, OUTPUT);
	pinMode(led4, OUTPUT);
	pinMode(led5, OUTPUT);
	pinMode(led6, OUTPUT);
	pinMode(ventilador, OUTPUT);
	servo.attach(9);
}

void loop() {
  EthernetClient client = server.available();
 
	if(client){
		while(client.connected()){
      if(client.available()){
        char c = client.read();
        if(readString.length() < 30) {
          readString += (c);
       	}    
       
        if(c == '\n'){
          if(readString.indexOf("led1") >= 0) {
            digitalWrite(led1,!digitalRead(led1));
         	}
         
        	if(readString.indexOf("led2") >= 0) {
            digitalWrite(led2,!digitalRead(led2));
         	}
         
         	if(readString.indexOf("led3") >= 0) {
            digitalWrite(led3,!digitalRead(led3));
         	}
         
          if(readString.indexOf("led4") >= 0) {
            digitalWrite(led4,!digitalRead(led4));
         	}
         
          if(readString.indexOf("led5") >= 0) {
            digitalWrite(led5,!digitalRead(led5));
         	}
         
          if(readString.indexOf("led6") >= 0) {
            digitalWrite(led6,!digitalRead(led6));
         	}

          if(readString.indexOf("garagemUP") >= 0) {
            servo.write(180);
         	}

          if(readString.indexOf("garagemDOWN") >= 0) {
            servo.write(0);
         	}       

          if(readString.indexOf("ventilador") >= 0) {
            digitalWrite(ventilador,!digitalRead(ventilador));
         	}

  				client.println("HTTP/1.1 200 OK");
  				client.println("Content-Type: text/html");
  				client.println();
  				client.println("<!doctype html>");
					
					client.println("<html>");
					client.println("<head>");
					client.println("<title>onLight</title>");
					client.println("<meta name=\"viewport\" content=\"width=320\">");
					client.println("<meta name=\"viewport\" content=\"width=device-width\">");
					client.println("<meta charset=\"utf-8\">");
					client.println("<meta name=\"viewport\" content=\"initial-scale=1.0, user-scalable=no\">");
					client.println("</head>");
					client.println("<body>");
					client.println("<center>");
         
					client.println("<font size=\"10\" face=\"verdana\" color=\"black\">on</font>");
					client.println("<font size=\"10\" face=\"verdana\" color=\"blue\">Light</font><br />");
					
  				if(digitalRead(led1)){
  					statusLed = "Ligado";
  				}

					else{
				    statusLed = "Desligado";
          }
          
					client.println("<td> <form action=\"led1\" method=\"get\">");
  				client.println("<button type=submit style=\"width:200px;\">COZINHA - "+statusLed+"</button>");
  				client.println("</form> <br /></td>");
          
  				if(digitalRead(led2)) {
   					statusLed = "Ligado";
			  	} 
					
					else{
            statusLed = "Desligado";
          }

					client.println("<td> <form action=\"led2\" method=\"get\">");
					client.println("<button type=submit style=\"width:200px;\">COPA - "+statusLed+"</button>");
					client.println("</form> <br /></td>");

  				if(digitalRead(led3)){
   					statusLed = "Ligado" ;
  				} 
					
					else{
          	statusLed = "Desligado";
          }

					client.println("<td> <form action=\"led3\" method=\"get\">");
					client.println("<button type=submit style=\"width:200px;\">SALA - "+statusLed+"</button>");
					client.println("</form> <br /></td>");

  				if(digitalRead(led4)) {
   					statusLed = "Ligado" ;
  				} 
					
					else{
            statusLed = "Desligado";
          }

					client.println("<td> <form action=\"led4\" method=\"get\">");
					client.println("<button type=submit style=\"width:200px;\">LAVANDERIA - "+statusLed+"</button>");
					client.println("</form> <br /></td>");

  				if(digitalRead(led5)){
   					statusLed = "Ligado";
  				}
					
					else{
          	statusLed = "Desligado";
          }
          
					client.println("<td> <form action=\"led5\" method=\"get\">");
					client.println("<button type=submit style=\"width:200px;\">QUARTO - "+statusLed+"</button>");
					client.println("</form> <br /></td>");
  
  				if(digitalRead(led6)) {
   					statusLed = "Ligado" ;
  				} 
					
					else{
            statusLed = "Desligado";
          }

					client.println("<td> <form action=\"led6\" method=\"get\">");
					client.println("<button type=submit style=\"width:200px;\">BANHEIRO - "+statusLed+"</button>");
					client.println("</form> <br /></td>");


  				if(digitalRead(ventilador)) {
   					statusLed = "Ligado" ;
  				} 
					
					else{
          	statusLed = "Desligado";
          }

					client.println("<td> <form action=\"ventilador\" method=\"get\">");
					client.println("<button type=submit style=\"width:200px;\">VENTILADOR - "+statusLed+"</button>");
					client.println("</form> <br /></td>");

          client.println("Abrir");
          client.println("<td> <form action=\"garagemUP\" method=\"get\">");
          client.println("<button type=submit style=\"width:200px;\">GARAGEM" "</button>");
          client.println("</form> <br /></td>");

          client.println("Fechar");
          client.println("<td> <form action=\"garagemDOWN\" method=\"get\">");
          client.println("<button type=submit style=\"width:200px;\">GARAGEM" "</button>");
          client.println("</form> <br /></td>");

          client.println("</center>");  
					client.println("</body>");
					client.println("</html>");  
					readString = "";
					client.stop();
		    }
     	}
  	}
 	}
}
