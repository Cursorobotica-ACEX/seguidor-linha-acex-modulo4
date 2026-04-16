// ==============================================================================
// ROBÔ SEGUIDOR DE LINHA - ACEX (Controle PD com Erro Ponderado)
// Baseado na estratégia de 5 sensores e recuperação de linha.
// ==============================================================================

// 1. DECLARAÇÃO DE VARIÁVEIS E PARÂMETROS
// Ganhos do Controlador PD (Precisam ser ajustados na pista)
float Kp = 35.0; 
float Kd = 15.0; 

// Variáveis de controle
float erroAnterior = 0;
int velocidadeBase = 120; // Velocidade em retas (0 a 255)

// Pinos da Ponte H L298N (Sinais e PWM)
const int motorEsq_IN1 = 4;
const int motorEsq_IN2 = 5;
const int motorEsq_ENA = 6; // OBRIGATÓRIO: Pino com '~' para PWM

const int motorDir_IN3 = 7;
const int motorDir_IN4 = 8;
const int motorDir_ENB = 9; // OBRIGATÓRIO: Pino com '~' para PWM

// Pinos dos Sensores (S1=Esquerda Extrema, S3=Centro, S5=Direita Extrema)
const int pinS1 = A0;
const int pinS2 = A1;
const int pinS3 = A2;
const int pinS4 = A3;
const int pinS5 = A4;

void setup() {
  // Configuração dos motores como saída
  pinMode(motorEsq_IN1, OUTPUT);
  pinMode(motorEsq_IN2, OUTPUT);
  pinMode(motorEsq_ENA, OUTPUT);
  pinMode(motorDir_IN3, OUTPUT);
  pinMode(motorDir_IN4, OUTPUT);
  pinMode(motorDir_ENB, OUTPUT);

  // Configuração dos sensores como entrada
  pinMode(pinS1, INPUT);
  pinMode(pinS2, INPUT);
  pinMode(pinS3, INPUT);
  pinMode(pinS4, INPUT);
  pinMode(pinS5, INPUT);

  // Configura a direção inicial dos motores para frente
  digitalWrite(motorEsq_IN1, HIGH);
  digitalWrite(motorEsq_IN2, LOW);
  digitalWrite(motorDir_IN3, HIGH);
  digitalWrite(motorDir_IN4, LOW);
  
  // Breve delay antes de começar a ler a pista
  delay(2000); 
}

void loop() {
  // 2. LEITURA DOS SENSORES (Considerando 1 = detectou a linha preta)
  int s1 = digitalRead(pinS1);
  int s2 = digitalRead(pinS2);
  int s3 = digitalRead(pinS3);
  int s4 = digitalRead(pinS4);
  int s5 = digitalRead(pinS5);

  int somaSensores = s1 + s2 + s3 + s4 + s5;
  float erroAtual = 0;

  // 3. CÁLCULO DO ERRO PONDERADO
  if (somaSensores == 0) {
    // ESTRATÉGIA DE RECUPERAÇÃO: Se perdeu a linha, mantém o último erro conhecido 
    // para o robô continuar girando e reencontrar o trajeto.
    erroAtual = erroAnterior; 
  } else {
    // Cada sensor tem um 'peso': S1(-2), S2(-1), S3(0), S4(+1), S5(+2)
    erroAtual = ((-2 * s1) + (-1 * s2) + (0 * s3) + (1 * s4) + (2 * s5)) / (float)somaSensores;
  }

  // 4. CÁLCULO DO CONTROLADOR PD
  float derivativo = erroAtual - erroAnterior;
  float correcao = (Kp * erroAtual) + (Kd * derivativo);

  // 5. ATUAÇÃO NOS MOTORES COM CONSTRAIN (Limites Físicos)
  int speedEsq = velocidadeBase + correcao;
  int speedDir = velocidadeBase - correcao;

  // A função constrain garante que o valor PWM nunca saia da faixa de 0 a 255
  speedEsq = constrain(speedEsq, 0, 255);
  speedDir = constrain(speedDir, 0, 255);

  analogWrite(motorEsq_ENA, speedEsq);
  analogWrite(motorDir_ENB, speedDir);

  // 6. ATUALIZAÇÃO DO ERRO
  erroAnterior = erroAtual;
  
  // Pequeno delay para estabilizar o ciclo de processamento
  delay(5);
}