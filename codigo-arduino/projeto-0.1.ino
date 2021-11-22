#include <SoftwareSerial.h>
 
SoftwareSerial bluetooth(10, 11); // RX, TX do Arduino
String command = "";
char b1;
   
float cm,duracao; // comprimento da onda

byte pinoTransmissor=9; // trig
byte pinoReceptor=8; //echo


void setup()
{
  // sensor
  pinMode(pinoTransmissor, OUTPUT); // transmissor
  pinMode(pinoReceptor, INPUT);     // receptor
  //porta serial
  Serial.begin(9600);
  bluetooth.begin(9600);
}

void loop()
{
 
  
  cm =  distancia(); // distancia em centímetros
  // acende o LED de acordo com os intervalos
  if(cm >0 && cm<=30){ // acende vermelho
  

    //Serial.println("pare ");
     
    bluetooth.write("pare");  
     delay(500);

 
  // Lê os dados do bluetooth
  if (bluetooth.available()>0) { // Se existem dados para leitura
   
    b1 = bluetooth.read(); //Variável para armazenar o dado atual
    command += b1; //Variável para armazenar todos os dados
   
    if (b1 == '\n'){ //Se o dado atual for um pulador de linha (\n)
      Serial.print(command + '\n'); //Printa o comando
      command = ""; //Limpa o comando para futuras leituras
    }
  }
  }
  else if (cm >31 && cm<=100) { // acende verde
  
  
     bluetooth.write("pare");  
     delay(1000);

 
  // Lê os dados do bluetooth
  if (bluetooth.available()>0) { // Se existem dados para leitura
   
    b1 = bluetooth.read(); //Variável para armazenar o dado atual
    command += b1; //Variável para armazenar todos os dados
   
    if (b1 == '\n'){ //Se o dado atual for um pulador de linha (\n)
      Serial.print(command + '\n'); //Printa o comando
      command = ""; //Limpa o comando para futuras leituras
    }
  }
      
  }
  else if (cm >101 && cm<=200) { // acende azul
    

  

         bluetooth.write(" algo proximo"); 
     delay(2000);

 
  // Lê os dados do bluetooth
  if (bluetooth.available()>0) { // Se existem dados para leitura
   
    b1 = bluetooth.read(); //Variável para armazenar o dado atual
    command += b1; //Variável para armazenar todos os dados
   
    if (b1 == '\n'){ //Se o dado atual for um pulador de linha (\n)
      Serial.print(command + '\n'); //Printa o comando
      command = ""; //Limpa o comando para futuras leituras
    }
  }
    
  }else if(cm>201){
  
      
         bluetooth.write("algo vindo");  
     delay(4000);

 
  // Lê os dados do bluetooth
  if (bluetooth.available()>0) { // Se existem dados para leitura
   
    b1 = bluetooth.read(); //Variável para armazenar o dado atual
    command += b1; //Variável para armazenar todos os dados
   
    if (b1 == '\n'){ //Se o dado atual for um pulador de linha (\n)
      Serial.print(command + '\n'); //Printa o comando
      command = ""; //Limpa o comando para futuras leituras
    }
  }
  }
  // distancia

}
// funcao que calcula distancia
float distancia()
{  
  // apenas para limpar o pino transmissor, cortar o sinal e aguardar 5us segundos  
  // (recomendado p/ melhor funcionamento) 
  digitalWrite(pinoTransmissor, LOW);
  delayMicroseconds(5); 
  // envio do pulso de ultrassom 
  digitalWrite(pinoTransmissor, HIGH); 
  // aguarda 10 microsegundos / tempo para o pulso ir e vol/j tar para a leitura
  delayMicroseconds(10);
  // desliga o pino que envia para habiliar o pino que recebe
  digitalWrite(pinoTransmissor, LOW);
  // calcula a duracao em microsegundos do pulso para ir e voltar 
  duracao = pulseIn(pinoReceptor, HIGH);
  // velocidade do som 343 m/s -> 34300 cm / 1000000 us -> 0.00343
  float calcDistancia= (duracao/2) * 0.0343; // em centímetro
  if (calcDistancia>=331){ // fora do limite do sensor
      calcDistancia=0;
  }
  return calcDistancia;  
   
}
