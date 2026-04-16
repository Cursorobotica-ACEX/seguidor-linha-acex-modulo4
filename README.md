# Robô Seguidor de Linha - Controle PD 🏎️

Este projeto implementa o código de controle e a estrutura de um robô seguidor de linha competitivo, desenvolvido para o **Módulo 4 da disciplina de ACEX**. 

O sistema utiliza uma matriz de 5 sensores infravermelhos e um algoritmo de **Controle Proporcional-Derivativo (PD)** para garantir uma navegação suave, de alta velocidade e com rápida correção de trajetória em curvas fechadas, superando os métodos tradicionais de controle "liga-desliga" (Bang-Bang).

## 📋 Sumário

- [Funcionalidades](#-funcionalidades)
- [Metodologia e Controle](#-metodologia-e-controle)
- [Estrutura do Repositório](#-estrutura-do-repositório)
- [Pré-requisitos (Hardware e Software)](#-pré-requisitos)
- [Instalação e Uso](#-instalação-e-uso)
- [Estratégia de Ajuste (Tuning)](#-estratégia-de-ajuste-tuning)
- [Tecnologias Utilizadas](#-tecnologias-utilizadas)
- [Licença](#-licença)

---

## 🚀 Funcionalidades

- **Detecção de Linha de Alta Resolução:** Utilização de 5 sensores IR para calcular a posição exata da linha sob o robô.
- **Controle PD Dinâmico:** Ajuste contínuo da velocidade dos motores com base no erro atual (Proporcional) e na taxa de variação do erro (Derivativo).
- **Estratégia de Recuperação (Último Erro):** Memória direcional que permite ao robô continuar a girar no sentido correto caso perca momentaneamente a linha em alta velocidade.
- **Proteção de Hardware:** Uso da função `constrain` para garantir que os valores de PWM nunca ultrapassem os limites físicos da Ponte H (0 a 255).

---

## 🧠 Metodologia e Controle

### Cálculo do Erro Ponderado
Em vez de leituras binárias, cada sensor possui um "peso" dependendo da sua distância do centro (-2, -1, 0, +1, +2). A média ponderada das leituras cria um valor de erro fracionado, permitindo que o robô entenda exatamente a sua posição relativa em relação à linha preta.

### Algoritmo PD
- **Termo Proporcional (Kp):** Aplica uma força de correção diretamente proporcional à distância do robô em relação ao centro da linha.
- **Termo Derivativo (Kd):** Funciona como um amortecedor, lendo a rapidez com que o robô se aproxima ou se afasta da linha, reduzindo oscilações e prevenindo que o robô ultrapasse a linha em curvas rápidas (overshoot).
- **Nota:** O termo Integral (Ki) foi intencionalmente removido para evitar o efeito de *windup* (acúmulo de erros) em pistas de alta velocidade.

---

## 📂 Estrutura do Repositório

```text
acex-seguidor-de-linha/
├── README.md                # Este arquivo
├── code/                    # Código-fonte principal
│   └── seguidor_pd_acex.ino # Algoritmo em C++ para Arduino
├── docs/                    # Documentação e regras da competição
│   └── roteiro_acex.

## 📋 Pré-requisitos e Materiais (Kit da Equipe)

Para reproduzir este projeto, utilizamos o kit padrão definido no formato presencial do minicurso:

**Estrutura Mecânica:**
* 1x Chassi (Acrílico ou impresso em 3D)
* 2x Motores DC com caixa de redução (6V, 200 RPM) com rodas acopladas
* 1x Roda giratória (roda boba/esfera) para apoio
* 1x Suporte para Bateria/Pilhas
* Parafusos (M3), porcas, espaçadores e abraçadeiras de nylon

**Eletrônica:**
* 1x Arduino Nano (com cabo USB)
* 1x Ponte H (L298N ou TB6612FNG)
* 5x Sensores IR reflexivos (TCRT5000 com módulo comparador LM393)
* 1x Protoboard (400 pontos)
* 2x Capacitores Eletrolíticos (1000μF / 16V para estabilização de ruído)
* Jumpers (Macho-Macho, Macho-Fêmea, Fêmea-Fêmea)
* 1x Chave liga/desliga

**Alimentação:**
* 1x Bateria recarregável (7,4V LiPo ou 2 células 18650)

**Software e Ferramentas:**
* **Arduino IDE (2.x):** Para compilar e enviar o código para a placa.
* **C_robot Simulator:** Para simulações e testes virtuais (opcional).
* **Git:** Para controle de versão do código.