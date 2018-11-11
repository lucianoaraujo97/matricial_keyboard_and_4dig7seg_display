/*
 * Codigo para utilizar teclado matricial de 16 botoes com apenas uma porta analogica em vez de 8 portas digitais
 * Calculos, hardware e software feitos por: Luciano Ytalo Gonçalves Araujo
 * Data: 27 de setembro de 2018
 */

 /*
 * Codigo para imprimir numeros em display de 4 digitos e 7 segmentos (ate 16 no momento)
 * Calculos, hardware e software feitos por: Luciano Ytalo Gonçalves Araujo
 * Data: 28 de setembro de 2018
 */

//VARIAVEIS PARA A LEITURA ANALOGICA:

int but = 0; //variavel para mostrar o botao pressionado

float vs1 = 1.25; //vs1 a vs16: tensoes teoricas para a saida dos botoes
float vs2 = 1.67;
float vs3 = 2.50;
float vs4 = 5.00;
float vs5 = 1.18;
float vs6 = 1.55;
float vs7 = 2.25;
float vs8 = 4.10;
float vs9 = 1.13;
float vs10 = 1.45;
float vs11 = 2.05;
float vs12 = 3.47;
float vs13 = 1.07;
float vs14 = 1.37;
float vs15 = 1.88;
float vs16 = 3.01;

float voutt[16] = {vs1, vs2, vs3, vs4, vs5, vs6, vs7, vs8, vs9, vs10, vs11, vs12, vs13, vs14, vs15, vs16}; //Vout teorico

int voutp = A0; //porta analogica usada

float vout10b = 0; //valor bruto lido por A0

float voutmapped = 0; //valor remapeado de vout10b usado para comparacoes *100

float voutr = 0; //vout medido real

int i = 0; //contador

int butp = 0; //valor provisorio para a leitura do botao

float diff = 5; //diferenca entre v teorico mais proximo do pratico

float difft = 0; //valor arbitrario de diff para obtencao do valor pratico em relacao ao teorico 

float buth = 0; //botao pressionado pela ultima vez


//___________________________________________________________________________________________________________________


//VARIAVEIS E FUNCOES PARA O DIGPLAY 4DIG7SEG:


int A = 10; //A a G: segmentos de LED do display
int B = 2;
int C = 3;
int D = 4;
int E = 5;
int F = 6;
int G = 7;
int d = 0; //tempo p/ o visor segurar o numero
int dig4 = 8; //ultimo digito do display
int dig3 = 9; //penultimo digito do display
int num = 0; //numero a ser exibido no display. ALTERAR ESTA VARIAVEL PARA ALTERAR O VALOR DO DISPLAY
int t = 10; //temporizador para o multiplexador
unsigned long currentmillis = 0;
unsigned long previousmillis = 0;
const long interval = 500;
int ledState = LOW;

void nnull(){ //para ser usado quando nenhum valor for utilizado
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  currentmillis = millis();
  if (currentmillis - previousmillis >= interval) {
    previousmillis = currentmillis;
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(G, ledState);
  }
}
void n0(){ //n0 a n9: combinacoes para numeros do display
  delay(d);
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, LOW);
}
void n1(){
  delay(d);
  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
}
void n2(){
  delay(d);
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, LOW);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, LOW);
  digitalWrite(G, HIGH);
}
void n3(){
  delay(d);
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, HIGH);
}
void n4(){
  delay(d);
  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}
void n5(){
  delay(d);
  digitalWrite(A, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, LOW);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}
void n6(){
  delay(d);
  digitalWrite(A, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}
void n7(){
  delay(d);
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
}
void n8(){
  delay(d);
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}
void n9(){
  delay(d);
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, LOW);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}
void null(){ //visor para quando o valor for nulo
  digitalWrite(dig3, LOW);
  digitalWrite(dig4, LOW);
  nnull();
}
void smallerthan10(){ // imprimir numero menor que 10
  digitalWrite(dig4, LOW);
  digitalWrite(dig3, HIGH);
  delay(t);
  digitalWrite(dig4, HIGH);
  digitalWrite(dig3, HIGH);
  delay(t);
}
void greaterthan10pt1(){ //imprimir o utimo digito de numero maior que 10
  digitalWrite(dig4, LOW);
  digitalWrite(dig3, HIGH);
  delay(t);
}
void greaterthan10pt2(){ //imprimir o penutimo digito de numero maior que 10
  digitalWrite(dig4, HIGH);
  digitalWrite(dig3, LOW);
  delay(t);
}


void setup() {


//SETUP PARA A LEITURA ANALOGICA:

  Serial.begin(9600);

  pinMode(voutp, INPUT); //declarando a porta analogica usada como porta de entrada
  

//___________________________________________________________________________________________________________________



//CONFIGURACOES DOS PINOS PARA O DIGPLAY 4DIG7SEG:

  
  
  pinMode(A, OUTPUT);  //A a G: configura os pinos dos LEDs como saida
  pinMode(B, OUTPUT);  
  pinMode(C, OUTPUT);  
  pinMode(D, OUTPUT);  
  pinMode(E, OUTPUT);  
  pinMode(F, OUTPUT);  
  pinMode(G, OUTPUT);  
  pinMode(dig3, OUTPUT);  //dig3 e 4: responsaveis pela simulacao do GND comutado (multiplexacao)
  pinMode(dig4, OUTPUT); 


}

void loop() {


//CODIGO PARA A LEITURA ANALOGICA:

  digitalWrite(dig4, HIGH); //para permitir que GND volte a zero para a multiplexacao pelo leitor do teclado
  digitalWrite(dig3, HIGH); //para permitir que GND volte a zero para a multiplexacao pelo leitor do teclado
  delay(1); //para estabilizar a leitura

  vout10b = analogRead(voutp); //recebendo valor da porta analogica
  voutmapped = map(vout10b, 0, 1023, 0, 500); //remapeando o valor da porta analogica entre 0V e 5V
  voutr = (float)voutmapped/100.0;

  for(i=0; i<16; i++){ //busca o valor mais proximo do botao pressionado
    
    if(voutr < 0.5){ //condicao para caso nenhum botao esteja sendo pressionado
      butp = 0;
      diff = 5; //reseta a proximidade do utimo botao apertado
      break;
    }

    difft = abs(voutr - voutt[i]); //preenchendo a variavel que checa o valor mais proximo entre pratico e teorico

    if(difft<diff){ //checa se a tensao de saida corresponde se aproximou de um valor mais provavel
      diff = difft;
      butp = i + 1; //botao mais provavel de ter sido pressionado ate o momento
    }
    
  }

  but = butp; //botao lido

  Serial.println(voutr);
 
  delay(1);
  
  
  

//___________________________________________________________________________________________________________________


  num = but; //recebe o valor a ser mostrado no visor. ESTA LINHA E' A RESPONSAVEL POR CONECTAR OS DOIS CODIGOS


//___________________________________________________________________________________________________________________



//FUNCAO PARA O DIGPLAY 4DIG7SEG:

  
  switch(num){ //escolhe um numero a ser mostrado no visor
    
    case 0:
      null();
      break;

     case 1:
      smallerthan10();
      n1();
      break;

     case 2:
      smallerthan10();
      n2();
      break;
     
     case 3:
      smallerthan10();
      n3();
      break;
      
     case 4:
      smallerthan10();
      n4();
      break;

     case 5:
      smallerthan10();
      n5();
      break;

     case 6:
      smallerthan10();
      n6();
      break;

     case 7:
      smallerthan10();
      n7();
      break;

     case 8:
      smallerthan10();
      n8();
      break;

     case 9:
      smallerthan10();
      n9();
      break;

     case 10:
      greaterthan10pt1();
      n1();
      greaterthan10pt2();
      n0();
      break;

     case 11:
      greaterthan10pt1();
      n1();
      greaterthan10pt2();
      n1();
      break;

     case 12:
      greaterthan10pt1();
      n1();
      greaterthan10pt2();
      n2();
      break;

     case 13:
      greaterthan10pt1();
      n1();
      greaterthan10pt2();
      n3();
      break;

     case 14:
      greaterthan10pt1();
      n1();
      greaterthan10pt2();
      n4();
      break;

     case 15:
      greaterthan10pt1();
      n1();
      greaterthan10pt2();
      n5();
      break;

     case 16:
      greaterthan10pt1();
      n1();
      greaterthan10pt2();
      n6();
      break;
  }


}
