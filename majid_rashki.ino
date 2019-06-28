#include <SoftwareSerial.h>
#include <string.h>
using namespace std;

#define TX_PIN  7
#define RX_PIN  8

#define GPS_RESET   9

SoftwareSerial SerialGsm( 8 , 7 );
char first[ 100 ] ="GET /hadi/signal.php?value=";
char second[ 50 ] = " HTTP/1.1\r\nHost: jalambadani.ir\r\n\r\n";
int data;
void init_AT();
void second_init_AT();
void setup() {
  pinMode(10, INPUT); // Setup for leads off detection LO +
  pinMode(11, INPUT); // Setup for leads off detection LO -
  
  pinMode( GPS_RESET , OUTPUT );

  digitalWrite( GPS_RESET , HIGH );
  
  Serial.begin(9600);
  Serial.println("Testing GSM SIM800L");
  SerialGsm.begin( 9600 );
}
void loop () {
  ///*
  //internet
  if((digitalRead(10) == 1)||(digitalRead(11) == 1)){
    Serial.println('!');
  }
  else{
    Serial.println(analogRead(A0));
    data = analogRead( A0 );
    init_AT();
  }
}
  //*/
  /////////////////////////////////////////////////////////////
  /*
  //Serial
  if((digitalRead(10) == 1)||(digitalRead(11) == 1)){
    Serial.println('!');
  }
  else{
    // send the value of analog input 0:
      Serial.println(analogRead(A0));
  }
  //Wait for a bit to keep serial data from saturating
  delay(1);
}
  */
  ///////////////////////////////////////////////////////////////
void receive_message() {
  while( SerialGsm.available() > 0 ) {
    Serial.write( SerialGsm.read() );
  }
}
void init_AT() {
  char str_data[ 15 ];
  itoa( data , str_data , 10 );
  strcat( first , str_data );
  digitalWrite( GPS_RESET , LOW );
  delay( 300 );
  digitalWrite( GPS_RESET , HIGH );
  delay( 3000 );
  SerialGsm.println( "AT" );
  delay( 5000 );
  receive_message();
  SerialGsm.print( "AT+CSTT=" );
  SerialGsm.print( '"' );
  SerialGsm.print( "mtnirancell" );  
  SerialGsm.println( '"' );
  delay( 2000 );
  receive_message();
  delay( 1000 );
  SerialGsm.println( "AT+CIICR");
  delay( 1500 );
  receive_message();
  SerialGsm.println( "AT+CIFSR");
  delay( 3000 );
  receive_message();
  SerialGsm.print("AT+CIPSTART=");
  SerialGsm.print('"');
  SerialGsm.print("TCP");
  SerialGsm.print('"');
  SerialGsm.print(",");
  SerialGsm.print('"');
  SerialGsm.print("jalambadani.ir");
  SerialGsm.print('"');
  SerialGsm.print(",");
  SerialGsm.println("80");
  delay( 3000 );
  receive_message();
  SerialGsm.print("AT+CIPSEND=100\r\n");
  delay( 5000 );
  receive_message();
  strcat( first , second );
  delay( 1000 );
  SerialGsm.print( first );
  delay( 1000 );
   SerialGsm.println( "\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n" );
  delay( 10000 );
  receive_message();
  SerialGsm.println("AT+CIPCLOSE\r\n");
  delay( 300 );
  receive_message();
}
///finish V1.0 code
