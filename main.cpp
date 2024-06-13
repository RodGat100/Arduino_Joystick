#include <Joystick.h>

// pinos dos potenciômetros
#define Throttle A0
#define RxAxis A1
#define RyAxis A2
#define RzAxis A3
#define ZAxis A4
#define Rudder A5

// pinos dos botões
const int joyButton[10] = {9, 10, 11, 12, 13, 14, 2, 3, 4, 5};  // Pino para cada botão de Joystick

// declara última posição conhecida de cada um dos 10 botões
int lastButtonState[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// declara posição medida de cada botão
int currentButtonState[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// inicializa variáveis para os eixos
int throttle_=0;
int rxAxis_=0;
int ryAxis_=0;
int rzAxis_=0;
int zAxis_=0;
int rudder_=0;


Joystick_ Joystick(0x03, JOYSTICK_TYPE_JOYSTICK,
        6, 0,  // 6 botões e nenhum hat switch
        true,true,true,true,true,true,true,true,true,true,true); // 11 eixos

const bool initAutosendState = true; // Acho que esta linha não está adicionando nada
bool includeZaxis = true;
bool includeRudder = true;

void setup() {
    // Initialize Button Pins
    for (int i = 0; i < 10; i++){
            pinMode(joyButton[i], INPUT_PULLUP);
    }

    Joystick.begin();
    Joystick.setXAxisRange(-1, 1);
    Joystick.setYAxisRange(-1, 1);
    Joystick.setAcceleratorRange(-1,1);
}


void loop()
{
    
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

        
    //currentButton1State = !digitalRead(joyButton1);
    //if (currentButton1State != lastButton1State)
    //{
    //    Joystick.setButton (0, currentButton1State);
    //    lastButton1State = currentButton1State;
    //}
    
    //currentButton2State = !digitalRead(joyButton2);
    //if (currentButton2State != lastButton2State)
    //{
    //    Joystick.setButton (0, currentButton2State);
    //    lastButton2State = currentButton2State;
    //}

    //currentButton3State = !digitalRead(joyButton3);
    //if (currentButton3State != lastButton3State)
    //{
    //    Joystick.setButton (0, currentButton3State);
    //    lastButton3State = currentButton3State;
    //}

    //currentButton4State = !digitalRead(joyButton4);
    //if (currentButton4State != lastButton4State)
    //{
    //    Joystick.setButton (0, currentButton4State);
    //    lastButton4State = currentButton4State;
    //}

    //currentButton5State = !digitalRead(joyButton5);
    //if (currentButton5State != lastButton5State)
    //{
    //    Joystick.setButton (0, currentButton5State);
    //    lastButton5State = currentButton5State;
    //}

    //currentButton6State = !digitalRead(joyButton6);
    //if (currentButton6State != lastButton6State)
    //{
    //    Joystick.setButton (0, currentButton6State);
    //    lastButton6State = currentButton6State;
    //}
 
    // Para os botões que mexem os eixos
    for (int index = 0; index < 10; index++)
    { 
        currentButtonState[index] = !digitalRead(joyButton[index]);
        if (currentButtonState[index] != lastButtonState[index])
        {
            switch (index)
            {
                case 0: // pino 9, flape up
                    if (currentButtonState [index] == 1) {
                        Joystick.setAccelerator(-1);
                    } else {
                        Joystick.setAccelerator(0);
                    }
                    break;
                case 1: // pino 10, flape down
                    if (currentButtonState[index] == 1) {
                        Joystick.setAccelerator(1);
                    } else {
                        Joystick.setAccelerator(0);
                    }
                    break;
                case 6: // pino 2
                    if (currentButtonState == 1) {
                        Joystick.setXAxis(1);
                    } else {
                        Joystick.setYAxis(0);
                    }
                    break;
                case 7: //  pino 3
                    if (currentButtonState == 1) {
                        Joystick.setXAxis(-1);
                    } else {
                        Joystick.setXAxis(0);
                    }
                    break;
                case 8: //  pino 4
                    if (currentButtonState == 1) {
                        Joystick.setYAxis(1);
                    } else {
                        Joystick.setYAxis(0);
                    }
                    break;
                case 9: // pino 5
                    if (currentButtonState == 1) {
                        Joystick.setYAxis(-1);
                    } else {
                        Joystick.setXAxis(0);
                    }
                    break;
                default: // demais pinos
                    Joystick.setButton (0, currentButtonState[index]);
                    break;
            }
        }
        lastButtonState[index] = currentButtonState[index];
    }
    delay(10);
 }
