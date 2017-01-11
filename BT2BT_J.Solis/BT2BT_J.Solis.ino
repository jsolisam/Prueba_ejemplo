#include <SPI.h>
#include <dogm_7036.h>
#include <SoftwareSerial.h>
dogm_7036 DOG;// Nobre de lapnatalla LCD en este caso DOG.

String address = "0006666BB64A";//Direccion MAC de BT
SoftwareSerial bluetooth(7, 8); // RX, TX Pines de arduino para conectar al modulo BT

void setup() {
  Serial.begin(9600);// Comenzar omunicacion serie a 9600 badios.

  
//CONFIGURACION LCD
  DOG.initialize(7,0,0,6,4,1,DOGM163);   //CSB=7, 0, 0 = use Hardware SPI, RS, 4 = RESET, 1 = 5V, EA DOGM163-A (=3 lines)
  DOG.displ_onoff(true);          //turn Display on
  DOG.cursor_onoff(true);         //turn Cursor blinking on
  DOG.contrast(0x08);// contraste de la pantalla.
  DOG.clear_display(); // Borrar display
//FIN CONFIGURACION LCD  

//CONFIGURACION VELOCIDAD BT
  bluetooth.begin(115200);// Comienza la comunicacion BT a 115200 baudios de velocidad.
  bluetooth.print("$$$"); //BT entra en modo comando.
  delay(100);// Tiempo de espera.
  bluetooth.println("U,9600,N"); // Modulo BT se comiucara a una velocidad de 9600.
  delay(100);
  bluetooth.println("---");// Salir del modo comando.
  delay(100);
  bluetooth.begin(9600);// Arrancamos de nuevo el modulo BT, esta vez a 9600. por ser SW
//FIN CONFIGURACION VELOCIDAD BT

//CONECION DE BT1 y BT2
  bluetooth.print("$$$"); 
  delay(100);
  bluetooth.println("C," + address);  // connect. Conectar ambos modulos BT. La C sale en el data no pines.
  delay(3000);
  bluetooth.println("---");
  delay(100);

  while(bluetooth.available()>0)
    bluetooth.read(); 
}
 
void loop() {
  if(Serial.available()>0) {
    int i_num1 = Serial.parseInt();// La variable i_num1 sera el primer numero entero largo escrito en el monitor serial.??????
    int i_num2 = Serial.parseInt();
    
    Serial.print("First num... ");//Monitor serie muestra el primer numero.
    Serial.println(i_num1);//Introducir numero.
    Serial.print("Second num... ");// Monitor serie muestra el segundo numero.
    Serial.println(i_num2);

    String s_num1 = String(i_num1);// El valor de i_num1 lo pasa a un string y lo guarda en el string s_num1???
    String s_num2 = String(i_num2);
    char* c_num1 = s_num1.c_str();// En la direccion c_num1 se alamcena el string s_num1??
    char* c_num2 = s_num2.c_str();

    DOG.clear_display();   // Borrar display.         
    DOG.position(1,1);   //En la posicion 1 de la fila 1          
    DOG.string("First num: "); //Muestra en pantalla Fisrt num:
    DOG.string(c_num1);      // Muestra el valor almacenado en c_num1.
    DOG.position(1,2);             //Posicion 1 de la fila 2. 
    DOG.string("Second num: ");   //Muetra en panatalla : Second num:
    DOG.string(c_num2);     //Muestra el valor guardado en c_num2.
    
    bluetooth.print(i_num1);//BT manda un numero
    bluetooth.print(" ");// Manda un espacio en blanco
    bluetooth.print(i_num2);// BT manda otro numero.

    delay(3000);
    if(bluetooth.available()>0){   
      int i_suma = bluetooth.parseInt();//Almacena en la direccion i_suma el valor mandado/Recogido por blietooth
      String s_suma = String(i_suma);
      char* c_suma = s_suma.c_str();
  
      Serial.print("Sum result... ");// Muestra por el monitor serie sum resul:
      Serial.println(i_suma);// muestra la suma
      
      DOG.position(1,3);  // Posicion 1 de la fila 3             
      DOG.string("Sum result: " ); // Muestra en LCD
      DOG.string(c_suma);   
    }
  }
}


