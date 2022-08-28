/* FILE:   FSM_GSM


    Envia un mensaje por medio de modulo
    GSM mediante el uso de una maquina de estados
    Finitos.

*/
#include "driverlib.h"
#include "device.h"
#include <string.h>


//---------------- prototipos de funciones --------------
void UartConfig();
__interrupt void RxHandler();
void gsmStartUp();
void gsmSend(char* mychar,uint16_t length, uint16_t delay, uint16_t try,uint16_t flag2See);
//--------------- Variables globales -------------------

// 2: ok recibido.
volatile uint16_t fsmGsmState = 0;
/*
 * 0: esperando una respuesta
 * 1: se recibio o
 * ...
 * 10: envio de mensaje
 *
 * */
volatile uint16_t flags_rx = 0x0000;
/**
 *     bit 0 = gsm responde (1 si, 0 no)
 *     bit 1 = espera de mensaje a enviar
 *     bit 2 = mensaje enviado con exito
 */
#define OK_BIT 0
#define SEND_BIT 1
#define OKSEND_BIT 2
uint16_t mainFsm = 0;
/*
 * 0: estado inicial
 * 1: GSM se encuentra activo, colocar en modo texto el modulo
 * 2: Se envia el mensaje
 * */
//char messageOut[256]; //buffer para mensajes de salida

void main(void){
    // configurar el reloj, 50Mhz, con el oscilador interno
    while(!SysCtl_setClock(SYSCTL_PLL_ENABLE | SYSCTL_SYSDIV(1) | SYSCTL_IMULT(10)|
                            SYSCTL_OSCSRC_OSC2)){
        SysCtl_resetMCD();
    }

    // ---- GPIO config ----------
    GPIO_setPinConfig(GPIO_4_GPIO4);
    GPIO_setDirectionMode(4, GPIO_DIR_MODE_OUT);
    // ---- configuraciones de interrupciones
    Interrupt_initModule();
    Interrupt_initVectorTable();
    UartConfig();
    // habilitar interrupciones.
    EINT;
    ERTM;
    // señal de inicio modulo gsm
    //gsmStartUp(); // señal de inicio

    while(1){
        switch (mainFsm){
            case 0:
                //mandar a encender el modulo

                // confirmar que este activo el modulo
                gsmSend("AT\r\n",4, 5 , 10, OK_BIT);

                // si se levanta la bandera entonces
                // se cambia al estado 2.
                if (flags_rx << OK_BIT){
                    mainFsm = 1;
                    flags_rx &= ~(1<<OK_BIT); //apagar el bit ok
                }
                break;
            case 1:
                // fsm activa, se configura en modo texto
                gsmSend("AT+CMGF=1\r\n", 11 , 5, 200, OK_BIT);
                // se procede a mandar el mensaje
                if (flags_rx << OK_BIT){
                    mainFsm = 2;
                    flags_rx &= ~(1<<OK_BIT); //apagar el bit ok
                }
                //levantar servicios IP
                break;
            case 2:
                // enviar el sms
                flags_rx &= ~(1<<SEND_BIT);
                gsmSend("AT+CMGS=\"+50254605224\"\r\n", 24 , 5, 1, SEND_BIT);
                DEVICE_DELAY_US(1000000);
                // si es 0 se sale, de lo contrario se procede a
                // escribir el mensaje.
                if (fsmGsmState<<SEND_BIT) mainFsm = 3;
                break;

            case 3:
                // escribir el mensaje
                gsmSend("Mensajes desde el TMS320F0023C\x1a", 31, 5, 1, OKSEND_BIT);
                DEVICE_DELAY_US(5000000);
                if(OKSEND_BIT) mainFsm =4;

                //levatar servicio HTTP
                break;

            default:
                break;

        }
        //delay 100ms
        DEVICE_DELAY_US(100000);
    }

}


/*
 * Envia el mensaje especificado, hasta que se coloque en 1
 * la bandera especificada, o bien se agoten los intentos
 *
 * mychar: mensaje a enviar por uart
 * length: largo de la cadena de caracteres
 * delay: tiempo de espera en ms entre intento e intento
 * try: cantidad de intentos que se realizarán
 * flag2See: numero de bit a revisar para comprobar que se haya
 *           ejecutado bien el comando.
 *
 * */
void gsmSend(char* mychar,uint16_t length, uint16_t delay, uint16_t try,uint16_t flag2See){
    uint16_t counter = 0x00;

    while(!(flags_rx&1<<flag2See) && counter<try){
        // se manda la cadaena de caracteres
        SCI_writeCharArray(SCIA_BASE,(uint16_t *) mychar, length);
        // se espera la respuesta
        counter++;
        DEVICE_DELAY_US(50000);
    }

    return;
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


    switch(fsmGsmState){

        case 0:

            if(data=='O') fsmGsmState = 1; //esperando a que entre una k
            //else if (data =='+') fsmGsmState = 20;
            else if (data=='>')fsmGsmState = 10;
            else
                fsmGsmState = 0;
            break;

        case 1:

            if(data=='K'){
                flags_rx |= 1; //se coloca en 1 el bit 0
                fsmGsmState = 0;
            }
            break;
        case 10:
            // se esta esperando a enviar el mensaje
            if(data == ' '){
                fsmGsmState =11;
                flags_rx |= 1 << SEND_BIT;
            }
            break;
        case 11:
            if(data =='+') fsmGsmState = 12;
            else fsmGsmState = 0;
            break;
        case 12:
            if(data == 'C') fsmGsmState = 13;
            else fsmGsmState = 0;
            break;
        case 13:
            if(data == 'M') fsmGsmState = 14;
            else fsmGsmState = 0;
            break;
        case 14:
            if(data == 'G') fsmGsmState = 15;
            else fsmGsmState = 0;
            break;
        case 15:

            if(data == 'S') flags_rx |= 1<<OKSEND_BIT;
            fsmGsmState = 0;

            break;
        default:
            fsmGsmState = 0;
    }


    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
}

