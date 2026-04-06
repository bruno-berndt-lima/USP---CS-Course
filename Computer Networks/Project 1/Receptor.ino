#define PINO_RX 13
#define PINO_TX 13
#define BAUD_RATE 8
#define HALF_BAUD 1000/(2*BAUD_RATE)

#define PINO_RTS 7
#define PINO_CTS 8

//#include "Temporizador.h" 

char letra[10]; //Variavel global para leitura dos 9 bits
int it = 0; // Iterador de posicao atual do bit

//Temporizador inicio
void configuraTemporizador(int baud_rate){
  int frequencia;
  frequencia = constrain(baud_rate,1,1500);
  //set timer1 interrupt
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  //OCR1A = contador;// = (16*10^6) / (10*1024) - 1 (must be <65536)
  OCR1A = ((16 * pow(10,6))/(1024*frequencia)) - 1;
  // turn on CTC mode (clear time on compare)
  TCCR1B |= (1 << WGM12);
  // Turn T1 off
  TCCR1B &= 0xF8;
  // Disable interrupts
  TIMSK1 = 0;
  TIFR1 = 0;
}

void iniciaTemporizador(){
  Serial.println("T1 iniciado");
  TCNT1 = 0;//initialize counter value to 0
  TIFR1 = 0;
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);
}

void paraTemporizador(){
  Serial.println("T1 parado");
    // Turn T1 off
  TCCR1B &= 0xF8;
  TIMSK1 = 0;
}
//Temporizador fim


// Calcula bit de paridade - Par ou impar
bool bitParidade(String letra){
	int numOnes = 0; // Contador da quantidade de 1s
 	for (int i = 0; i < 9; i++) {
    	if (letra[i] == '1') {
      		numOnes++;
    	}
  	}
  	bool paridadePar = (numOnes % 2 == 0); //Verifica se o numero de 1s eh par ou impar
  	return paridadePar; //Retorna 1 caso par, 0 c.c.
}

// Rotina de interrupcao do timer1
// O que fazer toda vez que 1s passou?
ISR(TIMER1_COMPA_vect){
  //>>>> Codigo Aqui <<<<
  if(it < 9){ // 9 bits de leitura
  	if(digitalRead(PINO_RX) == HIGH){ // Caso a leitura do dado seja 'HIGH', o bit eh 1
  		letra[it] = '1';
  	} 
  	else{ // Bit atual = 0 c.c.
   		letra[it] = '0';
  	}
  }
  it++; // Incrementa o iterador de posicao
  
}

// Funcao que espera a flag RTS ser ligada para ligar a flag CTS
bool handShake(){
  	if(digitalRead(PINO_RTS) == HIGH){
      	delay(200); // Delay para visualizacao do funcionamento pelos LEDs
      	digitalWrite(PINO_CTS, HIGH);
      	return true;
  	}
  	return false;
}

// Funcao para retornar o caracter recebido a partir da sequencia de bits
char retornaLetra(char letra[]){
  double l = 0;
  for(int x = 7; x >= 0; x--){
  	l += ((int)letra[x]-'0') * pow(2, (7-x)); // Soma dos bits em uma variavel double
  }
  int l2 = (int) l + 1; // O arduino possui um problema de transformacao de double para int que perde uma unidade
  return char(l2);
}



// Executada uma vez quando o Arduino reseta
void setup(){
  //desabilita interrupcoes
  noInterrupts();
  // Configura porta serial (Serial Monitor - Ctrl + Shift + M)
  Serial.begin(9600);

  // habilita interrupcoes
  interrupts();
  
  
  configuraTemporizador(BAUD_RATE);

  //Definição pinos receptor
  //dados
  pinMode(PINO_RX, INPUT); 
  //flag receptor
  pinMode(PINO_RTS, INPUT);
  
  //flag emissor
  pinMode(PINO_CTS, OUTPUT);
  digitalWrite(PINO_CTS, LOW);
  
}


// O loop() eh executado continuamente (como um while(true))
void loop ( ) {
  //>>>> Codigo Aqui <<<<
  
  digitalWrite(PINO_CTS, LOW);
  if(handShake()){    
    //Inicializa posição de leitura  
    it = 0;
    //Delay para iniciar contador do receptor
    delay(HALF_BAUD);
    //Inicializa temporizador
    iniciaTemporizador();
    //Espera a leitura dos 9 bits (8 do caracter e 1 de paridade)
    while(it < 9) {
      Serial.print("");
    };
    //Para o temporizador apos a leitura dos 9 bits
    paraTemporizador();

    //Espera a flag do emissor RTS ser alterada para 0
    while(digitalRead(PINO_RTS));
    
    //Delay para visualizacao em LED das flags RTS e CTS
    delay(200);
    //Altera a flag do receptor para 0
    digitalWrite(PINO_CTS, LOW);   
      
    letra[9] = '\0';
    //Verifica a paridade do conteúdo
    if(bitParidade(letra)){ // Caso par: imprime o caracter
      Serial.print("Letra recebida: ");
      Serial.println(retornaLetra(letra));
    } 
    else { // Caso impar: imprime que houve um erro e a sequencia de bits para verificao da paridade
      Serial.println("Erro na paridade da sequencia "); 
      Serial.println(letra); 
    }
  }  
}
