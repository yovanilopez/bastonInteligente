/*
  Ethernet Monitor Analogo
 By: http://www.elprofegarcia.com/
 Este programa usa el Modulo Ethernet de Arduino para monitorear las entradas analogicas A0-A5
 
 Conexiones:
 * Ethernet shield usa los pins 10, 11, 12, 13
 * Monitorea los pines Analogos de A0 a A5
 
Se debe conectar el modulo a la red local y se debe asignar una IP fija que no coincida
con los equipos de la red que ya estan funcionando pero dede estar dentro de la SubRed.
puede monitorear la IP de su PC dentro de la ventana de comandos CMD con el comando ipconfig
*/

#include <SPI.h>
#include <Ethernet.h>
const int Trigger = 5;   //Pin digital 5 para el Trigger del sensor
const int Echo = 6;  //Pin digital 6 para el Echo del sensor
int contador=0;
int buzzer=3;
int contador1=0;
int contador2=0;
int buzzDelay =1000;



                               // Introduzca una direcciÛn MAC y la direcciÛn IP para el controlador
byte mac[] = { 
0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,0,50); // Esta direccion IP debe ser cambiada obligatoriamente 
                              // dependiendo de la subred de su Area Local y es la que 
 #include <Ultrasonic.h>
//Ultrasonic ultrasonic(5,6);
#include <TimeLib.h>             // usara para conectarse por el Navegador.


EthernetServer server(80);    // Puerto 80 por defecto para HTTP

void setup() {
  Ethernet.begin(mac, ip);    //inicializa la conexiÛn Ethernet y el servidor
  server.begin();
    Serial.begin(9600);//iniciailzamos la comunicación
  pinMode(Trigger, OUTPUT); //pin como salida
  pinMode(Echo, INPUT);  //pin como entrada
   pinMode(buzzer, OUTPUT);
   
  
  digitalWrite(Trigger, LOW);//Inicializamos el pin con 0
  setTime(11,0,0,14,9,2022);
  delay (9600);
}

void loop() {

   String dataString = "";

//int t = ultrasonic.distanceRead();
  String tiempo=String(hour())+ ":" + dato(minute())+ ":"+ dato(second());
 
    String fecha=String(year())+ ":" + dato(month())+ ":"+ dato(day());
   
  EthernetClient cliente = server.available(); // Inicializa cliente como servidor ethernet
  if (cliente) {
    boolean currentLineIsBlank = true;
    while (cliente.connected()) {
      if (cliente.available()) {
        char c = cliente.read();
        if (c == '\n' && currentLineIsBlank) { 
          cliente.println("HTTP/1.1 200 OK");
          cliente.println("Content-Type: text/html");   // Envia el encabezado en codigo HTML estandar
          cliente.println("Connection: close"); 
    cliente.println("Refresh: 3");  // refresca la pagina automaticamente cada 3 segundos
          cliente.println();
          // style=background-color:rgb(255,0,0);
          cliente.println("<!DOCTYPE HTML>"); 
          cliente.println("<html  style=background-color:#d63384;>");
          cliente.println("<HEAD>");
          cliente.println("<TITLE>IOT</TITLE>");
          cliente.println("</HEAD>");
          cliente.println("<BODY style=text-align:center >");
          cliente.println("<hr />");
          cliente.println("<H1>BASTON INTELIGENTE</H1>");
          cliente.println("<br />");  
          cliente.println("<H2>REGISTROS</H2>");
          cliente.println("<br />");  
          cliente.println("Lectura Baston");  
          cliente.println("<br />");
          cliente.println("<br />");   
       

       if(cliente){
       long t; //timepo que demora en llegar el eco
  long d; //distancia en centimetros

  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  
  t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm

    if (d<=50){
 /*     digitalWrite(buzzer,HIGH);
      delay(buzzDelay);
        digitalWrite(buzzer,LOW);
      delay(buzzDelay);*/
    contador=contador;
      contador++;
       } ;

        if (d>=50 && d<=150){
    contador1=contador1;
      contador1++;
       } 

       
        if (d>=0 && d<=150){
         digitalWrite(buzzer,HIGH);
      delay(buzzDelay);
        digitalWrite(buzzer,LOW);
      delay(buzzDelay);
      contador2=contador2;
      contador2++;

      
       } 
       
       
       
       
       
       
       /*else{
        digitalWrite(led,LOW);
      
         digitalWrite(buzzer,LOW);
         contador++;
        delay (2000);
      
       };
   /*    if (digitalRead(led)== HIGH){
      
        contador++;
        delay (2000);
     
       };*/

   cliente.print("<br />");
  cliente.println("Distancia: ");
  cliente.print(d);      //Enviamos serialmente el valor de la distancia
  cliente.println("cm");
   cliente.println("<br />");
  cliente.print("fecha: ");
  cliente.println(fecha);      //Enviamos serialmente el valor de la distancia
   cliente.println("<br />");
  cliente.print("tiempo:");
  cliente.println(tiempo);
  cliente.println("<br />");
  cliente.print("<H1>Objetos Encontrados a 50CM</H1>");
  cliente.println(contador);
    cliente.println("<br />");
  cliente.print("<H1 >Objetos Encontrados a 120CM</H1>");
  cliente.println(contador1);
   cliente.print("<H1>Sonido Buzzer</H1>");
  cliente.println(contador2);
 
 
  delay(100);     
     

     
   //  delay(2000);           // Da tiempo al Servidor para que reciba los datos 15ms
  // cliente.stop();
         
}     
          
          cliente.println("<br />"); 
         cliente.print("<H3 style=text-align:left >EDWIN GIOVANNI LOPEZ Y LOPEZ</H3>");
          cliente.println("</html>");
          break;
        }
        if (c == '\n') {
           currentLineIsBlank = true;
        } 
        else if (c != '\r') {
           currentLineIsBlank = false;
        }
      }
    }
   delay(15);           // Da tiempo al Servidor para que reciba los datos 15ms
  cliente.stop();     // cierra la conexion
  }
}

String dato(int digit){

  String dt=String("0")+ digit;
  return dt.substring(dt.length()-2);
}
