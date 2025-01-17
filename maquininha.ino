#include <Adafruit_LiquidCrystal.h>
#include <Keypad.h>

// ================================================
//               Configuração do LCD
// ================================================
Adafruit_LiquidCrystal lcd(0);

// ================================================
//           Configuração dos Potenciômetros
// ================================================
const int potCardLeft = A0;  // Esquerdo
const int potCardRight = A1; // Direito

// ================================================
//                Configuração dos Jogadores
// ================================================
const char* nomesCartao[6] = {
  "Verde", "Amarelo", "Vermelho", "Azul", "Cinza", "Roxo"
};

long saldo[6] = {25000, 25000, 25000, 25000, 25000, 25000}; // Saldo inicial dos cartões
int cardLeft = 0;    // Cartão esquerdo
int cardRight = 0;   // Cartão  direito
int prevCardLeft = -1;  // Último cartão no lado esquerdo
int prevCardRight = -1; // Último cartão no lado direito

// ================================================
//           Configuração do Teclado 4x4
// ================================================
const byte ROW_NUM = 4; // Número de linhas
const byte COL_NUM = 4; // Número de colunas

char keys[ROW_NUM][COL_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pin_rows[ROW_NUM] = {5, 4, 3, 2};   // Pinos das linhas
byte pin_column[COL_NUM] = {9, 8, 7, 6}; // Pinos das colunas

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COL_NUM);

// ================================================
//          Variáveis e Notícias Aleatórias
// ================================================
long valorTransacao = 0; // Valor digitado para transações
bool digitando = false;  // Indica se está em modo de digitação



// ================================================
//                    Função Setup
// ================================================
void setup() {
  // Inicialização do LCD
  lcd.begin(16, 2);
  lcd.setBacklight(1);  
  lcd.setCursor(0, 0);
  lcd.print("Iniciando...");
  delay(1000);
  lcd.clear();
  
  //Pin Setup do Buzzer
  pinMode(10, OUTPUT);

  // Inicialização da comunicação serial
  Serial.begin(9600);
  Serial.println("Serial Iniciado.");

  // Configura a semente para gerar números aleatórios
  randomSeed(analogRead(A2));
  random();
}

// ================================================
//                    Função Loop
// ================================================
void loop() {
  // Detecção de cartões através dos potenciômetros
  int potLeftValue = analogRead(potCardLeft);
  int potRightValue = analogRead(potCardRight);

  int detectedCardLeft = map(potLeftValue, 0, 1023, 0, 6);
  int detectedCardRight = map(potRightValue, 0, 1023, 0, 6);

  // Atualiza o estado dos cartões caso haja mudanças
  if (detectedCardLeft != prevCardLeft) {
    cardLeft = detectedCardLeft;
    prevCardLeft = detectedCardLeft;
    Serial.print("Cartão esquerdo: ");
    Serial.println(nomesCartao[cardLeft - 1]);
    if (!digitando) atualizarLCD();
  }

  if (detectedCardRight != prevCardRight) {
    cardRight = detectedCardRight;
    prevCardRight = detectedCardRight;
    Serial.print("Cartão direito: ");
    Serial.println(nomesCartao[cardRight - 1]);
    if (!digitando) atualizarLCD();
  }

  // Leitura do teclado
  char key = keypad.getKey();
  if (key) {
    processarTecla(key);
  }
}

// ================================================
//               Ativa o Buzzer
// ================================================

void ativarBuzzer() {
  // Definindo as frequências das notas (em Hz)
  int notas[] = {262, 294, 330, 349, 392, 440, 494, 523, 554, 587}; // C4, D4, E4, F4, G4, A4, B4, C5, C#5, D5
  int numNotas = sizeof(notas) / sizeof(notas[0]); // Número de notas

  // Tocar uma sequência de 5 notas aleatórias
  for (int i = 0; i < 5; i++) {
    // Gera um índice aleatório para escolher uma nota
    int indice = random(0, numNotas); 
    
    // Toca a nota escolhida aleatoriamente
    tone(10, notas[indice], 400);  // 400ms para cada nota
    delay(100);                    // Pausa entre as notas
  }
  
  noTone(10);  // Desliga o buzzer após a sequência de notas
}


// ================================================
//               Atualiza o Display LCD
// ================================================
void atualizarLCD() {
  lcd.clear();

  if (cardLeft > 0) {
    lcd.setCursor(0, 0);
    lcd.print(nomesCartao[cardLeft - 1]);
    lcd.setCursor(0, 1);
    lcd.print("R$");
    lcd.print(saldo[cardLeft - 1]);
  }

  if (cardRight > 0) {
    lcd.setCursor(8, 0);
    lcd.print(nomesCartao[cardRight - 1]);
    lcd.setCursor(8, 1);
    lcd.print("R$");
    lcd.print(saldo[cardRight - 1]);
  }
}

// ================================================
//             Realiza Transações
// ================================================
void realizarTransacao() {
  if (cardLeft > 0 && cardRight == 0) {
    // Apenas o cartão esquerdo está ativo
    saldo[cardLeft - 1] += valorTransacao;

  } else if (cardRight > 0 && cardLeft == 0) {
    // Apenas o cartão direito está ativo
    if (saldo[cardRight - 1] >= valorTransacao) {
      saldo[cardRight - 1] -= valorTransacao;
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Saldo Insuf!");
      delay(2000);
      atualizarLCD();
      return; // Sai da função sem realizar a transação
    }

  } else if (cardLeft > 0 && cardRight > 0) {
    // Ambos os cartões estão ativos
    if (saldo[cardRight - 1] >= valorTransacao) {
      saldo[cardLeft - 1] += valorTransacao;
      saldo[cardRight - 1] -= valorTransacao;
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Saldo Insuf!");
      delay(2000);
      atualizarLCD();
      return; // Sai da função sem realizar a transação
    }
  }

  valorTransacao = 0;
  digitando = false;
  atualizarLCD();
}
// ================================================
//           Processa as Teclas do Teclado
// ================================================
void processarTecla(char key) {
  if (key >= '0' && key <= '9') {
    if (!digitando) {
      valorTransacao = 0;
      digitando = true;
      lcd.clear();
    }
    valorTransacao = valorTransacao * 10 + (key - '0');
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("R$");
    lcd.print(valorTransacao);

  } else if (key == 'A') { //Transação Padrão
    ativarBuzzer();
    realizarTransacao();

  }
  	
 	else if (key == 'B') {//Transação de Milhar
    ativarBuzzer();  
    valorTransacao *= 1000;  
    realizarTransacao();

  }
  	
  	else if (key == '#') {//+2000 Créditos
    if (cardLeft > 0) {
      ativarBuzzer();
      saldo[cardLeft - 1] += 2000;
      atualizarLCD();
    }

  } else if (key == '*') {//Reset
    for (int i = 0; i < 6; i++) saldo[i] = 25000;
    ativarBuzzer();
    lcd.clear();
    lcd.print("Reset!");
    delay(1000);
    atualizarLCD();

  } else if (key == 'C') {//Cancelar
    ativarBuzzer();
    valorTransacao = 0;
    digitando = false;
    atualizarLCD();

  } else if (key == 'D') {//Gerar evento
    ativarBuzzer();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Evento!");
    delay(2000);
    atualizarLCD();
  }
}
