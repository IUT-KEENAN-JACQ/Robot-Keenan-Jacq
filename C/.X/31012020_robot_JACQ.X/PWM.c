//Partie PWM
#include <xc.h> // library xc.h inclut tous les uC
#include "IO.h"
#include "PWM.h"
#include "Robot.h"
#include "ToolBox.h"
#include "etats.h"

#define PWMPER 40.0
unsigned char accelerationGauche = 10;
unsigned char accelerationDroite = 10;
unsigned char freinDroite = 7;
unsigned char freinGauche = 12;


void InitPWM(void)
{
    PTCON2bits.PCLKDIV = 0b000; //Divide by 1
    PTPER = 100*PWMPER; //Période en pourcentage

    //Réglage PWM moteur 1 sur hacheur 1
    IOCON1bits.POLH = 1; //High = 1 and active on low =0
    IOCON1bits.POLL = 1; //High = 1
    IOCON1bits.PMOD = 0b01; //Set PWM Mode to Redundant
    FCLCON1 = 0x0003; //Désactive la gestion des faults

    //Reglage PWM moteur 2 sur hacheur 6
    IOCON6bits.POLH = 1; //High = 1
    IOCON6bits.POLL = 1; //High = 1
    IOCON6bits.PMOD = 0b01; //Set PWM Mode to Redundant
    FCLCON6 = 0x0003; //Désactive la gestion des faults

    /* Enable PWM Module */
    PTCONbits.PTEN = 1;
}

void PWMUpdateSpeed()
    {
    // Cette fonction est appelée sur timer et permet de suivre des rampes d?accélération
    if (robotState.vitesseDroiteCommandeCourante < robotState.vitesseDroiteConsigne)
        robotState.vitesseDroiteCommandeCourante = Min(
        robotState.vitesseDroiteCommandeCourante + freinDroite,
        robotState.vitesseDroiteConsigne);
    if (robotState.vitesseDroiteCommandeCourante > robotState.vitesseDroiteConsigne)
        robotState.vitesseDroiteCommandeCourante = Max(
        robotState.vitesseDroiteCommandeCourante - accelerationDroite,
        robotState.vitesseDroiteConsigne);

    if (robotState.vitesseDroiteCommandeCourante > 0)
    {
        MOTEUR_DROITE_ENL = 0; //pilotage de la pin en mode IO
        MOTEUR_DROITE_INL = 1; //Mise à 1 de la pin
        MOTEUR_DROITE_ENH = 1; //Pilotage de la pin en mode PWM
    }
    else
    {
        MOTEUR_DROITE_ENH = 0; //pilotage de la pin en mode IO
        MOTEUR_DROITE_INH = 1; //Mise à 1 de la pin
        MOTEUR_DROITE_ENL = 1; //Pilotage de la pin en mode PWM
    }
        MOTEUR_DROITE_DUTY_CYCLE = Abs(robotState.vitesseDroiteCommandeCourante)*PWMPER;

    if (robotState.vitesseGaucheCommandeCourante < robotState.vitesseGaucheConsigne)
        robotState.vitesseGaucheCommandeCourante = Min(
        robotState.vitesseGaucheCommandeCourante + freinGauche,
        robotState.vitesseGaucheConsigne);
    if (robotState.vitesseGaucheCommandeCourante > robotState.vitesseGaucheConsigne)
        robotState.vitesseGaucheCommandeCourante = Max(
        robotState.vitesseGaucheCommandeCourante - accelerationGauche,
        robotState.vitesseGaucheConsigne);

    if (robotState.vitesseGaucheCommandeCourante > 0)
    {
        MOTEUR_GAUCHE_ENL = 0; //pilotage de la pin en mode IO
        MOTEUR_GAUCHE_INL = 1; //Mise à 1 de la pin
        MOTEUR_GAUCHE_ENH = 1; //Pilotage de la pin en mode PWM
    }
    else
    {
        MOTEUR_GAUCHE_ENH = 0; //pilotage de la pin en mode IO
        MOTEUR_GAUCHE_INH = 1; //Mise à 1 de la pin
        MOTEUR_GAUCHE_ENL = 1; //Pilotage de la pin en mode PWM
    }
        MOTEUR_GAUCHE_DUTY_CYCLE = Abs(robotState.vitesseGaucheCommandeCourante) * PWMPER;
    }

void PWMSetSpeedConsigne (float vitesseEnPourcents, char moteur)
{ 
    if (moteur == MOTEUR_DROITE)
        robotState.vitesseDroiteConsigne = vitesseEnPourcents;
    else if (moteur == MOTEUR_GAUCHE)
        robotState.vitesseGaucheConsigne = vitesseEnPourcents;
}
