/*
* Sample code from the Particle webhooks example
* To test that connections are set up correctly..
*/

          

int led = D7; //LED pin


void setup()
{
    pinMode(led, OUTPUT);
    
}



void loop() 
{
  // Make some random data
  String data = String(random(10,50));
  
  // Turn the LED on to indicate transmitting data
  digitalWrite(led, HIGH);
  
  // Trigger the integration
  Particle.publish("Temperature", data, PRIVATE);
  
  // Turn the LED off to indicate complete
  digitalWrite(led, LOW);
  
  // Wait 30 seconds
  delay(30000);
}
  