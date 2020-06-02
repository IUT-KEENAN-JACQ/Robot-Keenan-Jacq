#ifndef IO_H
#define IO_H

//Affectation des pins des LEDS
#define JACK _RA1
#define LED_ORANGE _LATC10 
#define LED_BLEUE _LATG7
#define LED_BLANCHE _LATG6
// Prototypes fonctions
void InitIO();

//Définitions des pins pour les hacheurs moteurs
#define MOTEUR1_IN1 _LATB14
#define MOTEUR1_IN2 _LATB15
#define MOTEUR6_IN1 _LATC6
#define MOTEUR6_IN2 _LATC7

//Configuration spécifique du moteur gauche
#define MOTEUR_GAUCHE_INH MOTEUR1_IN1
#define MOTEUR_GAUCHE_INL MOTEUR1_IN2
#define MOTEUR_GAUCHE_ENL IOCON1bits.PENL
#define MOTEUR_GAUCHE_ENH IOCON1bits.PENH
#define MOTEUR_GAUCHE_DUTY_CYCLE PDC1

#define MOTEUR_DROITE_INH MOTEUR6_IN1
#define MOTEUR_DROITE_INL MOTEUR6_IN2
#define MOTEUR_DROITE_ENL IOCON6bits.PENL
#define MOTEUR_DROITE_ENH IOCON6bits.PENH
#define MOTEUR_DROITE_DUTY_CYCLE PDC6

#define FCY 40000000

#endif /* IO_H */