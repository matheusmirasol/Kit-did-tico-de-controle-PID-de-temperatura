 /*
 Programação para utilização do kit didático de controle pid de temperatura
 
 Objetivo: Realizar a coleta de dados necessários para a comparação do desempenho de métodos de sintonia
 
 Funcionamento: Recebe a saída do bloco PID do Labview, mede a temperatura média do reservatório e envia ao Labview  
 
 Sketch desenvolvido pela dupla de TCC Matheus e Andressa, baseando-se em um código disponibilizado pelo professor Sislian

 Data de desenvolvimento: 10/2018

 REV3
 */

//================================================================================================================================================================================================
// Definições
//================================================================================================================================================================================================

#define  LM351  A0    // Define o pino do sensor LM35 (1)
#define  LM352  A2    // Define o pino do sensor LM35 (2)
#define  LM353  A4    // Define o pino do sensor LM35 (3)
#define  PIN_OUTPUT 6 // Define o pino de saída do controlador onde o relê de estado sólido é conectado

//================================================================================================================================================================================================
// Declaração de variáveis
//================================================================================================================================================================================================

float T1;          // variável que armazena a temperatura DO LM351
float T2;          // variável que armazena a temperatura DO LM352
float T3;          // variável que armazena a temperatura DO LM353
float Temperatura; // variável que armazena a temperatura média
int Resposta;      // variável que armazena a resposta (saída) do bloco PId do Labview
int resposta; 
//================================================================================================================================================================================================
// CONFIGURAÇÕES INICIAIS
//================================================================================================================================================================================================

void setup()
{ 
  pinMode(6, OUTPUT);
  Serial.begin(9600); // Inicia a serial com um baud rate de 9600
} // End setup

//================================================================================================================================================================================================
// LOOP INFINITO
//================================================================================================================================================================================================

void loop ()
{
 //================================================================================================================================================================================================
 // Recebe a saída do bloco PID do Labview e atua a resistência
 
 char buffer[] = {' ',' ',' ',' '};     // Cria um vetor vazio
 Serial.readBytesUntil('o', buffer, 4); // Lê caracteres do buffer serial (4 bytes de leitura)
 resposta = atoi(buffer);               // Converte um array-caractere ascii para inteiro
 Resposta = map(resposta, 0, 100, 0, 255);
 analogWrite(PIN_OUTPUT, Resposta); // Atua a resistência de acordo com a saída do bloco PID do Labview
 
 //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 // LEITURA DA TEMPERATURA DA PANELA
  
 T1 = (float(analogRead(LM351))*5/(1023))/0.01; // REALIZA A MEDIDA NO LM35 (1)

 T2 = (float(analogRead(LM352))*5/(1023))/0.01; // REALIZA A MEDIDA NO LM35 (2)

 T3 = (float(analogRead(LM353))*5/(1023))/0.01; // REALIZA A MEDIDA NO LM35 (3)

 //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 // CÁLCULO DA TEMPERATURA MÉDIA
  
 Temperatura = (T1 + T2 + T3) / 3; // Calcula a temperatura média no reservatório
  
 //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 // Envia, ao Labview, a temperatura média no reservatório
  
 Serial.print('n');
 Serial.print(Temperatura); // IMPRIME NA SERIAL O VALOR DA TEMPERATURA MÉDIA

 delay(50);
  
} // END LOOP
