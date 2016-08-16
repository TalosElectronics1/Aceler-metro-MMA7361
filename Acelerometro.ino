/*
Talos Electronics
Rafael Lozano Rolón 
13/Septiembre/2015 
*/
#include <math.h>//Libreria para operaciones matematicas basicas

//Delcaracion de variables
int Led_Verde=2;//Definir el pin 2 como led verde
int Led_Azul=3;//Definir el pin 3 como led azul
int xVal = 0;//Variable que contendra el valor de X del sensor
int yVal = 0;//Variable que contendra el valor de Y del sensor
int zVal = 0;//Variable que contendra el valor de Z del sensor
double angleYZ = 0;//Variable para el calculo del angulo YZ
double angleXZ = 0;//Variable para el calculo del angulo XZ

void setup() 
{
  analogReference(EXTERNAL);//Referencia externa para los ADC
  Serial.begin(9600);//Comunicacion Serial al 9600 bps
  pinMode(Led_Verde,OUTPUT);//Definir el led verde como salida
  pinMode(Led_Azul,OUTPUT);//Definir el led azul como salida
}


void loop() {
  
  xVal = analogRead(0);//Leer la entrada analogica 0    
  yVal = analogRead(1);//Leer la entrada analogica 1
  zVal = analogRead(2);//Leer la entrada analogica 2
  //Map permite que nuestro rango del ADC varíe entre valores 
  //positivos y negativos
  xVal = map(xVal, 0, 1023, -500, 500); 
  yVal = map(yVal, 0, 1023, -500, 500); 
  zVal = map(zVal, 0, 1023, -500, 500); 
  
  //Calcular angulo en Y
  angleYZ = atan((double)yVal / (double)zVal);
  angleYZ = angleYZ*(57.2958);
  
  //Calcular el angulo en X
  angleXZ = atan((double)xVal / (double)zVal);
  angleXZ = angleXZ*(57.2958);
  
  Serial.write("   Angulo_xz:");
  Serial.print(angleXZ);//Escribir en el monitor serial el valor del angulo
  
  Serial.write("   Angulo_yz:");
  Serial.print(angleYZ);//Escribir en el monitor serial el valor del angulo
  
  Serial.write("   Voltaje_X:");
  Serial.print(xVal);//Escribir en el monitor serial el valor del angulo
  
  Serial.write("   Voltaje_Y:");
  Serial.print(yVal);//Escribir en el monitor serial el valor del angulo
  
  Serial.write("   Voltaje_Z:");
  Serial.print(zVal);//Escribir en el monitor serial el valor del angulo
  
  Serial.write("\n");//salto de linea 
  
  if(angleXZ<0)//condicion angulo x negativo enciende el led
  {
   digitalWrite(Led_Verde,HIGH); //Enciende el led verde
  }else //si es positivo apaga el LED
  {
    digitalWrite(Led_Verde,LOW);//Apaga el led verde
  }
  
  if(angleYZ<0)//condicion angulo Y negativo enciende el led
  {
   digitalWrite(Led_Azul,HIGH);//Enciende el led Azul 
  }else//si es es negativo apaga el led Azul  
  {
   digitalWrite(Led_Azul,LOW); //Enciende el led Azul 
  }
  
  //Esperar 100 ms antes de volver a calcular los angulos
  delay(100); 
}
