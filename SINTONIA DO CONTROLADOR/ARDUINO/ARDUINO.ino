/*
 Programação para utilização do kit didático de controle pid de temperatura
 
 Objetivo: Realizar a coleta de dados necessários para a sintonia da planta de controle
 
 Funcionamento: Atua a resistência por meio de comando recebido do Labview, mede e envia ao labview a temperatura média do reservatório. 
 
 Sketch desenvolvido pela dupla de TCC Matheus e Andressa, baseando-se em um código disponibilizado pelo professor Sislian

 Data de desenvolvimento: 10/2018

 REV2
 */
 
 //================================================================================================================================================================================================
 // Definições
 //================================================================================================================================================================================================

 #define  LM351  A0 // Define o pino de leitura do LM35
 #define  LM352  A2 // Define o pino de leitura do LM35
 #define  LM353  A4 // Define o pino de leitura do LM35
 
 #define  saida  6  // Define pino 6 para saida PWM (Pino conectado ao relê de estado sólido da resistência)
 
  //================================================================================================================================================================================================
 // Declaração de variáveis
 //================================================================================================================================================================================================

 float T1, T2, T3; // variáveis que armazenam os valores finais das temperaturas
 float Tm;         // variável que armazena a temperatura média
 int out;          // Armazena o valor que deve ser escrito no pino de saída (Relê - Resistência)
 int aux;          // Variável auxiliar

 //================================================================================================================================================================================================
 // Configurações iniciais
 //================================================================================================================================================================================================

 void setup()
 {
  Serial.begin(9600); // Inicia a serial com um baud rate de 9600
 } // End setup 

 //================================================================================================================================================================================================
 // Loop infinito
 //================================================================================================================================================================================================

 void loop ()
 {
  //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  // Leitura do protocolo: conversão e escrita na resistência
                                                                          //  0 1 2 3
  char buffer[] = {' ',' ',' ',' '}; // Inicia um vetor vazio com 4 posições (x x x ;) onde "xxx" é o dado de potência na resistência (0-100)
  
  Serial.readBytesUntil('o', buffer, 4); // lê caracteres do buffer serial (4 bytes de leitura)
  
  aux = atoi(buffer); // Converte um array-caractere ascii para inteiro
  
  out = map(aux, 0, 100, 0, 255); // Converte o sinal de potência na resistência recebido 0-100% para 0-255
  
  analogWrite(saida, out); // Escreve o valor de out na variável saida (Manda de 0-255 para o rele da resistência)
  
  //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  // Leitura das temperaturas em cada sensor LM35
  
  T1 = (float(analogRead(LM351))*5/(1023))/0.01; // Leitura do sensor 1

  T2 = (float(analogRead(LM352))*5/(1023))/0.01; // Leitura do sensor 2

  T3 = (float(analogRead(LM353))*5/(1023))/0.01; // Leitura do sensor 3
  
  //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  // Cálculo da temperatura média no reservatório
  
  Tm = (T1 + T2 + T3) / 3;

  //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  // Envio da temperatura média para o Labview
    
  Serial.print('n');
  Serial.print(Tm); // Imprime na serial o valor da Temperatura média
 
 } // End loop
