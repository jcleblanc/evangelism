#include <Bridge.h>
#include <Temboo.h>
#include "TembooAccount.h" // contains Temboo account information, as described below

int led = 13;      // led pin number

void setup(){
  pinMode(led, OUTPUT);
  
  Serial.begin(9600);
  
  // For debugging, wait until a serial console is connected.
  delay(4000);
  while(!Serial);
  Bridge.begin();
}

void loop(){
  Serial.println("Running AcceptPayPalPayment");
    
  TembooChoreo AcceptPayPalPaymentChoreo;

  // invoke the Temboo client
  AcceptPayPalPaymentChoreo.begin();
    
  // set Temboo account credentials
  AcceptPayPalPaymentChoreo.setAccountName(TEMBOO_ACCOUNT);
  AcceptPayPalPaymentChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
  AcceptPayPalPaymentChoreo.setAppKey(TEMBOO_APP_KEY);
    
  AcceptPayPalPaymentChoreo.addInput("ClientID", "AXrysRDeQOaGRw2n6VfaQqfpPWFm5UxSgdS7f-b4QTA-nhFVkWyrg0WPNmMp");
  AcceptPayPalPaymentChoreo.addInput("ClientSecret", "EHMHkRAFFNeLZmsYKvpNgRxIW8Z6gxjTn9zBocpTnFJoulKaNFprCcc9q7eh");
  AcceptPayPalPaymentChoreo.addInput("CancelURL", "http://www.jcleblanc.com/cancel");
  AcceptPayPalPaymentChoreo.addInput("ReturnURL", "http://www.jcleblanc.com/return");
  AcceptPayPalPaymentChoreo.addInput("Currency", "USD");
  AcceptPayPalPaymentChoreo.addInput("Total", "5");
    
  // identify choreo to run
  AcceptPayPalPaymentChoreo.setChoreo("/Library/PayPal/Payments/AcceptPayPalPayment");
    
  // run choreo; when results are available, print them to serial
  AcceptPayPalPaymentChoreo.run();
    
  while(AcceptPayPalPaymentChoreo.available()) {
    char c = AcceptPayPalPaymentChoreo.read();
    Serial.print(c);
  }
  AcceptPayPalPaymentChoreo.close();
    
  //illuminate led on complete
  digitalWrite(led, HIGH);
  delay(10000);
  digitalWrite(led, LOW);
  delay(90000);
}
