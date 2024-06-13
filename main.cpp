#include <Joystick.h>

// pinos dos potenciômetros
#define Throttle A0
#define RxAxis A1
#define RyAxis A2
#define RzAxis A3
#define ZAxis A4
#define Rudder A5

// pinos dos botões
#define JoyButton1 9
#define JoyButton2 10
#define JoyButton3 11
#define JoyButton4 12
#define JoyButton5 13
#define JoyButton6 14 // Favor inserir pino correto, só pus um número para a sintaxe ficar correta

// pinos dos botões que controlam eixos
#define XButtonPlus 2  // Checar se esses 4 pinos estão corretos
#define XButtonMinus 3
#define YButtonPlus 4
#define YButtonMinus 5


Joystick_ Joystick(0x03, JOYSTICK_TYPE_JOYSTICK,
        6, 0,  // 6 botões e nenhum hat switch
        true,true,true,true,true,true,true,true,true,true,true); // 11 eixos

const bool initAutosendState = true;

int throttle_=0;
int rxAxis_=0;
int ryAxis_=0;
int rzAxis_=0;
int zAxis_=0;
int rudder_=0;
int lastButton1State=0;
int lastButton2State=0;
int lastButton3State=0;
int lastButton4State=0;
int lastButton5State=0;
int lastButton6State=0;
int currentButton1State;
int currentButton2State;
int currentButton3State;
int currentButton4State;
int currentButton5State;
int currentButton6State;
int currentButtonState;
int lastButtonState[4] = {0,0,0,0};
 
bool includeZaxis = true;
bool includeRudder = true;

void setup() {
  // Initialize Button Pins

    pinMode(JoyButton1, INPUT_PULLUP);
    pinMode(JoyButton2, INPUT_PULLUP);
    pinMode(JoyButton3, INPUT_PULLUP);
    pinMode(JoyButton4, INPUT_PULLUP);
    pinMode(JoyButton5, INPUT_PULLUP);
    pinMode(XButtonPlus, INPUT_PULLUP);
    pinMode(XButtonMinus, INPUT_PULLUP);
    pinMode(YButtonPlus, INPUT_PULLUP);
    pinMode(YButtonMinus, INPUT_PULLUP);

    Joystick.begin();
    Joystick.setXAxisRange(-1, 1);
    Joystick.setYAxisRange(-1, 1);
}


void loop() {
    
    // medição dos 6 eixos analógicos em 10 bits,
    // mapeia para 8 bits e e envia para Joystick

    throttle_ = analogRead(Throttle);
    throttle_ = map(throttle_,0,1023,0,255);
    Joystick.setThrottle(throttle_);

    rxAxis_ = analogRead(RxAxis);
    rxAxis_ = map(rxAxis_,0,1023,0,255);
    Joystick.setRxAxis(rxAxis_);

    ryAxis_ = analogRead(RyAxis);
    ryAxis_ = map(ryAxis_,0,1023,0,255);
    Joystick.setRyAxis(ryAxis_);

    rzAxis_ = analogRead(RzAxis);
    rzAxis_ = map(rzAxis_,0,1023,0,255);
    Joystick.setRzAxis(rzAxis_);

    zAxis_ = analogRead(ZAxis);
    zAxis_ = map(zAxis_,0,1023,0,255);
    Joystick.setZAxis(zAxis_);
 
    rudder_ = analogRead(Rudder);
    rudder_ = map(rudder_,0,1023,0,255);
    Joystick.setRudder(rudder_);
    
    // Faz leitura dos 6 botões, se estado do botão mudou,
    // atualiza posição do botão no Joystick

    currentButton1State = !digitalRead(joybutton1);
    if (currentButton1State != lastButton1State)
    {
        Joystick.setButton (0, currentButton1State);
        lastButton1State = currentButton1State;
    }
    
    currentButton2State = !digitalRead(joybutton2);
    if (currentButton2State != lastButton2State)
    {
        Joystick.setButton (0, currentButton2State);
        lastButton2State = currentButton2State;
    }

    currentButton3State = !digitalRead(joybutton3);
    if (currentButton3State != lastButton3State)
    {
        Joystick.setButton (0, currentButton3State);
        lastButton3State = currentButton3State;
    }

    currentButton4State = !digitalRead(joybutton4);
    if (currentButton4State != lastButton4State)
    {
        Joystick.setButton (0, currentButton4State);
        lastButton4State = currentButton4State;
    }

    currentButton5State = !digitalRead(joybutton5);
    if (currentButton5State != lastButton5State)
    {
        Joystick.setButton (0, currentButton5State);
        lastButton5State = currentButton5State;
    }

    currentButton6State = !digitalRead(joybutton6);
    if (currentButton6State != lastButton6State)
    {
        Joystick.setButton (0, currentButton6State);
        lastButton6State = currentButton6State;
    }
 

   
    // Para os botões que mexem os eixos
    for (int index = 0; index < 4; index++)
            {
        currentButtonState = !digitalRead(index + 2); // O 2 está aí pois o 1o pino é o 2, e só funciona se for para os pinos subsequentes 3,4,5
        if (currentButtonState != lastButtonState[index])
        {
            switch (index) {
                case 0: // XButtonPlus
                    if (currentButtonState == 1) {
                        Joystick.setXAxis(1);
                    } else {
                        Joystick.setYAxis(0);
                    }
                    break;
                case 1: // XButtonMinus
                    if (currentButtonState == 1) {
                        Joystick.setXAxis(-1);
                    } else {
                        Joystick.setXAxis(0);
                    }
                    break;
                case 2: // YButtonPlus
                    if (currentButtonState == 1) {
                        Joystick.setYAxis(1);
                    } else {
                        Joystick.setYAxis(0);
                    }
                    break;
                case 3: // YButton2
                    if (currentButtonState == 1) {
                        Joystick.setYAxis(-1);
                    } else {
                        Joystick.setXAxis(0);
                    }
                    break;
            }
        lastButtonState[index] = currentButtonState;
    }
    delay(10);
 }
