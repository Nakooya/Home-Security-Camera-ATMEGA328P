#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

//SDA - A4, SCL - A5


const int trigPin = 9;
const int echoPin = 10;
long duration;
int distance;
const int outEcho = 2;
const int outTemp = 3;


void setup() {
   pinMode(LED_BUILTIN, OUTPUT);
  //TEMP
  Serial.begin(9600);
  while (!Serial);
 
  Serial.println("Adafruit MLX90614 test");

  if (!mlx.begin()) {
    Serial.println("Error connecting to MLX sensor. Check wiring.");
    while (1);
  };

  Serial.print("Emissivity = "); Serial.println(mlx.readEmissivity());
  Serial.println("================================================");

  
  /*
   * 
   */ //ULTRASONIC
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(outEcho, OUTPUT);
  pinMode (outTemp, OUTPUT);

}

void loop() {
  digitalWrite(outTemp, LOW);   
  digitalWrite(outEcho, LOW);
  
  /* ULTRASONIC */
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;

  Serial.print("Distance: ");
  Serial.println(distance);
  if (distance <= 30)
  {
      digitalWrite(outEcho, HIGH);
      //delay(5000);
      
      /* TEMPERATURE */
      while(1)  /* TEMPERATURE LOOP */
      {
          Serial.print("Object = "); Serial.print(mlx.readObjectTempC()); Serial.print("*C");
     
          Serial.println();
          delay(500);
          if (mlx.readObjectTempC() >= 33.0 && mlx.readObjectTempC() <= 37.2){
            digitalWrite(outTemp, HIGH);
            Serial.println("SUCCESS");
           
            delay(20000);
            break;
          }
          else
          {
            digitalWrite(outTemp, LOW);
          }
      }  /* TEMPERATURE LOOP END*/
      /* TEMPERATURE END */
   }
     
      
  else
  {
    digitalWrite(outEcho, LOW);
  }

}
