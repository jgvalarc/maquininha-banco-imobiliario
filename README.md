
# Simulador de Máquina de Cartões - Banco Imobiliário

Este projeto é um simulador de uma máquina de cartões de banco imobiliário, utilizando um microcontrolador Arduino. Ele permite realizar transações entre cartões, visualizar saldos e interagir com o sistema por meio de um teclado 4x4 e um display LCD.

## Funcionalidades

### 1. **Cartões**
   - O sistema simula 6 cartões de jogadores com saldos iniciais de R$ 25.000,00.
   - Cada cartão é identificado por um nome colorido: "Verde", "Amarelo", "Vermelho", "Azul", "Cinza" e "Roxo".
   - O sistema simula a inserção dos cartões através de potenciômetros (para representar a escolha de um cartão).

### 2. **Display LCD**
   - O display LCD exibe as informações dos cartões ativos (esquerdo e direito), incluindo o nome e o saldo atual.
   - A tela é constantemente atualizada com o saldo de cada cartão conforme as transações são realizadas.

### 3. **Teclado 4x4**
   - O sistema utiliza um teclado matricial 4x4 para realizar interações, como:
     - **Teclas numéricas (0-9)**: Para inserir o valor da transação.
     - **Tecla 'A'**: Para realizar uma transação padrão entre cartões.
     - **Tecla 'B'**: Para realizar uma transação de milhar (multiplicando o valor por 1000).
     - **Tecla '#'**: Para adicionar R$ 2000 ao saldo do cartão esquerdo.
     - **Tecla '*'**: Para resetar os saldos de todos os cartões para o valor inicial de R$ 25.000.
     - **Tecla 'C'**: Para cancelar a transação atual.
     - **Tecla 'D'**: Para gerar um evento aleatório no sistema.

### 4. **Buzzer**
   - O sistema utiliza um buzzer para emitir uma sequência de notas musicais aleatórias sempre que uma transação ou evento é realizado, proporcionando um feedback sonoro para o usuário.

### 5. **Transações**
   - **Transações entre cartões**: O sistema permite que o jogador movimente valores entre dois cartões ativos (esquerdo e direito). As transações são verificadas para garantir que o saldo do cartão de origem seja suficiente.
   - **Adicionar créditos**: É possível adicionar R$ 2000 ao saldo do cartão esquerdo utilizando a tecla `#`.
   - **Resetar**: A tecla `*` reinicia os saldos de todos os cartões para o valor inicial de R$ 25.000.

### 6. **Eventos Aleatórios**
   - A tecla `D` gera um evento aleatório no sistema, com um feedback visual no display e um som gerado pelo buzzer.

## Como Funciona

1. **Configuração Inicial**: O sistema inicializa o display LCD e a comunicação serial. Após isso, o jogador pode inserir os cartões nos potenciômetros (esquerdo e direito).
2. **Escolha do Cartão**: O sistema detecta o cartão inserido em cada lado, exibindo o nome do jogador e o saldo correspondente no LCD.
3. **Interação com o Teclado**: O jogador pode utilizar o teclado 4x4 para inserir valores de transações, realizar ações como adicionar créditos ou resetar os saldos, e ouvir o feedback sonoro através do buzzer.
4. **Transações**: Quando o valor da transação é inserido e a tecla 'A' é pressionada, o sistema processa a transação, movendo valores entre os cartões de acordo com as regras.

## Componentes Utilizados

- **Arduino**: Microcontrolador utilizado para controlar o sistema.
- **Display LCD**: Tela para exibição das informações.
- **Teclado 4x4**: Teclado matricial utilizado para entrada do usuário.
- **Potenciômetros**: Sensores analógicos para detectar a inserção dos cartões.
- **Buzzer**: Dispositivo de som para feedback sonoro.

## Como Rodar

1. **Pré-requisitos**:
   - Placa Arduino (por exemplo, Arduino Uno).
   - Biblioteca `Adafruit_LiquidCrystal` para o LCD.
   - Biblioteca `Keypad` para o teclado 4x4.

2. **Instruções**:
   - Faça o download do código-fonte e carregue no seu Arduino.
   - Conecte os componentes de acordo com o esquema descrito no código.
   - Ao iniciar, o sistema estará pronto para uso. Ajuste os potenciômetros para simular os cartões e comece a interagir com o teclado.

## Exemplo de Funcionamento

- O jogador escolhe um cartão ao rotacionar os potenciômetros.
- O valor da transação é inserido utilizando as teclas numéricas.
- O valor é transferido entre os cartões ao pressionar a tecla 'A'.
- O saldo é exibido no LCD e o buzzer emite um som quando uma ação é realizada.
