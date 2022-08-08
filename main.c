/* FILE:   FSM_GSM


    Envia un mensaje por medio de modulo
    GSM mediante el uso de una maquina de estados
    Finitos.

*/
#include "driverlib.h"
#include "device.h"
#include <string.h>


#define DEVICE_SYSCLK_FREQ 50000000

//---------------- prototipos de funciones --------------
void UartConfig();
__interrupt void RxHandler();
void gsmStartUp();
//--------------- Variables globales -------------------

// 2: ok recibido.
volatile uint16_t fsmGsmState = 0;
char messageOut[256]; //buffer para mensajes de salida

void main(void){

    while(!SysCtl_setClock(SYSCTL_PLL_ENABLE | SYSCTL_SYSDIV(1) | SYSCTL_IMULT(5)|
                            SYSCTL_OSCSRC_OSC2)){
        SysCtl_resetMCD();
    }

    // ---- GPIO config ----------
    GPIO_setPinConfig(GPIO_4_GPIO4);
    GPIO_setDirectionMode(4, GPIO_DIR_MODE_OUT);

    Interrupt_initModule();
    Interrupt_initVectorTable();
    UartConfig();
    EINT;
    ERTM;

    gsmStartUp(); // se�al de inicio
    strcpy(messageOut, "AT\r\n");
    SCI_writeCharArray(SCIA_BASE,(uint16_t *) messageOut, 5);
    DEVICE_DELAY_US(5000);

    while(fsmGsmState != 2) {
        gsmStartUp(); // se�al de inicio
        SCI_writeCharArray(SCIA_BASE, (uint16_t *) messageOut, 5);
        DEVICE_DELAY_US(5000);
    }
    // si llega aqui es que si responde el modulo GSM
    fsmGsmState = 0; // reiniciar la maquina
    strcpy(messageOut, "AT+CMGF=1\r\n");
    SCI_writeCharArray(SCIA_BASE,(uint16_t *) messageOut, 11);

    while(fsmGsmState != 2);
    fsmGsmState = 0; // reiniciar la maquina

    strcpy(messageOut, "AT+CMGS=\"+50254605224\"\r\n");
    SCI_writeCharArray(SCIA_BASE,(uint16_t *) messageOut, 24);
    strcpy(messageOut, "Hola a todos, hablando desde un micro");
    SCI_writeCharArray(SCIA_BASE,(uint16_t *) messageOut,37);
    while(fsmGsmState != 2);
    fsmGsmState = 0; // reiniciar la maquina

    while(1){
        ESTOP0;
    }


}
//--------------- GSM funciones --------------------


void gsmStartUp(){
    // power on gsm
    GPIO_writePin(4, 0);
    DEVICE_DELAY_US(1000000);
    GPIO_writePin(4, 1);
    DEVICE_DELAY_US(2000000);
    GPIO_writePin(4, 0);
    DEVICE_DELAY_US(3000000);
}


//---------------- UART funciones ------------------

void UartConfig(){

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SCIA);
    //CONF UART GPIO
    GPIO_setPinConfig(GPIO_2_SCIA_TX);
    GPIO_setDirectionMode(2, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(2, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(2, GPIO_QUAL_ASYNC);

    GPIO_setPinConfig(GPIO_3_SCIA_RX);
    GPIO_setDirectionMode(3, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(3, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(3, GPIO_QUAL_ASYNC);
    // SCI module configuration
    SCI_performSoftwareReset(SCIA_BASE); // reset SCIA
    SCI_setConfig(SCIA_BASE, SysCtl_getClock(10000000)/4, 9600, (SCI_CONFIG_WLEN_8 |
                                                        SCI_CONFIG_STOP_ONE |
                                                        SCI_CONFIG_PAR_NONE));
    SCI_resetChannels(SCIA_BASE);
    SCI_resetRxFIFO(SCIA_BASE); // limpiar FIFO Rx
    SCI_resetTxFIFO(SCIA_BASE); // limpiar FIFO Tx
    SCI_clearInterruptStatus(SCIA_BASE, SCI_INT_TXFF | SCI_INT_RXFF); // reiniciar las banderas de interrupciones
    SCI_enableFIFO(SCIA_BASE);
    SCI_enableModule(SCIA_BASE);
    SCI_performSoftwareReset(SCIA_BASE);
    SCI_enableInterrupt(SCIA_BASE, SCI_INT_RXFF ); //habilitar interrupcion de recepcion
    SCI_setFIFOInterruptLevel(SCIA_BASE, SCI_FIFO_TX16, SCI_FIFO_RX1);
    /*---------INTERRUPT------------------*/
    Interrupt_register(INT_SCIA_RX, &RxHandler);
    Interrupt_enable(INT_SCIA_RX);


    return;
}

__interrupt
void RxHandler(){
    uint16_t data;
    SCI_readCharArray(SCIA_BASE,  &data , 1);
    SCI_clearOverflowStatus(SCIA_BASE);
    SCI_clearInterruptStatus(SCIA_BASE, SCI_INT_RXFF);


    switch(data){

        case 'O':
            if(fsmGsmState==0) fsmGsmState = 1;
            break;
        case 'K':
            if(fsmGsmState==1) fsmGsmState = 2;
            break;
        default:
            fsmGsmState = 0;
    }


    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
}

