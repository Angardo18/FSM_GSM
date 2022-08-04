/* FILE:   FSM_GSM


    Envia un mensaje por medio de modulo
    GSM mediante el uso de una maquina de estados
    Finitos.

*/
#include "driverlib.h"
#include "device.h"


//---------------- prototipos de funciones --------------
void UartConfig();
__interrupt void RxHandler();


void main(void){

    while(!SysCtl_setClock(SYSCTL_PLL_ENABLE | SYSCTL_SYSDIV(1) | SYSCTL_IMULT(5)|
                            SYSCTL_OSCSRC_OSC2)){
        SysCtl_resetMCD();
    }


    UartConfig();

    Interrupt_initModule();
    Interrupt_initVectorTable();
}


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
    SCI_setConfig(SCIA_BASE, SysCtl_getClock(10000000)/4, 115200, (SCI_CONFIG_WLEN_8 |
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
    return;
}

__interrupt
void RxHandler(){
    flag =1;
    SCI_readCharArray(SCIA_BASE,  datos , 16);
    SCI_clearOverflowStatus(SCIA_BASE);
    SCI_clearInterruptStatus(SCIA_BASE, SCI_INT_RXFF);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
}

