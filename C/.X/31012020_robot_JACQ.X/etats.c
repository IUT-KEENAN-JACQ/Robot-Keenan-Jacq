#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <time.h>
#include "etats.h"
#include "ChipConfig.h"
#include "IO.h"
#include "timer.h"
#include "PWM.h"
#include "Robot.h"
#include "ADC.h"
#include "main.h"
#include "Toolbox.h"

unsigned char nextStateRobot=0;
unsigned char stateRobot;
int compteurInverseur=0;


void OperatingSystemLoop(void) {
    if(JACK){
            switch (stateRobot) {
                case STATE_ATTENTE:
                    timestamp = 0;
                    PWMSetSpeedConsigne(0, MOTEUR_DROITE);
                    PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
                    stateRobot = STATE_ATTENTE_EN_COURS;

                case STATE_ATTENTE_EN_COURS:
                    SetNextRobotStateInAutomaticMode();
                    break;
                
                case STATE_TRACE:
                    PWMSetSpeedConsigne(-39, MOTEUR_DROITE);
                    PWMSetSpeedConsigne(42.6, MOTEUR_GAUCHE);
                    stateRobot = STATE_TRACE_EN_COURS;
                    LED_BLANCHE = 0;
                    LED_BLEUE = 1;
                    break;
                case STATE_TRACE_EN_COURS:
                    SetNextRobotStateInAutomaticMode();
                    break; 

                case STATE_AVANCE:
                    PWMSetSpeedConsigne(-25, MOTEUR_DROITE);                  
                    PWMSetSpeedConsigne(26.5, MOTEUR_GAUCHE);
                    stateRobot = STATE_AVANCE_EN_COURS;
                    compteurInverseur++;
                    LED_BLANCHE = 0;
                    LED_BLEUE = 0;
                    break;
                case STATE_AVANCE_EN_COURS:
                    SetNextRobotStateInAutomaticMode();
                    break;
                    
                case STATE_LEGER_DROIT:
                    PWMSetSpeedConsigne(-15, MOTEUR_DROITE);
                    PWMSetSpeedConsigne(10, MOTEUR_GAUCHE);
                    stateRobot = STATE_LEGER_DROIT_EN_COURS;
                    LED_BLANCHE = 0;
                    LED_BLEUE = 0;
                    break;
                case STATE_LEGER_DROIT_EN_COURS:
                    SetNextRobotStateInAutomaticMode();
                    break;
                    
                case STATE_LEGER_GAUCHE:
                    PWMSetSpeedConsigne(-10, MOTEUR_DROITE);
                    PWMSetSpeedConsigne(15, MOTEUR_GAUCHE);
                    stateRobot = STATE_LEGER_GAUCHE_EN_COURS;
                    LED_BLANCHE = 0;
                    LED_BLEUE = 0;
                    break;
                case STATE_LEGER_GAUCHE_EN_COURS:
                    SetNextRobotStateInAutomaticMode();
                    break;

                case STATE_TOURNE_GAUCHE:
                    PWMSetSpeedConsigne(0, MOTEUR_DROITE);
                    PWMSetSpeedConsigne(15, MOTEUR_GAUCHE);
                    stateRobot = STATE_TOURNE_GAUCHE_EN_COURS;
                    LED_BLANCHE = 0;
                    LED_BLEUE = 0;
                    break;
                case STATE_TOURNE_GAUCHE_EN_COURS:
                    SetNextRobotStateInAutomaticMode();
                    break;

                case STATE_TOURNE_DROITE:
                    PWMSetSpeedConsigne(-15, MOTEUR_DROITE);
                    PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
                    stateRobot = STATE_TOURNE_DROITE_EN_COURS;
                    LED_BLANCHE = 0;
                    LED_BLEUE = 0;
                    break;
                case STATE_TOURNE_DROITE_EN_COURS:
                    SetNextRobotStateInAutomaticMode();
                    break;

                case STATE_TOURNE_SUR_PLACE_GAUCHE:
                    PWMSetSpeedConsigne(-10, MOTEUR_DROITE);
                    PWMSetSpeedConsigne(-10, MOTEUR_GAUCHE);
                    stateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS;
                    LED_BLANCHE = 0;
                    LED_BLEUE = 0;
                    break;
                case STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS:
                    SetNextRobotStateInAutomaticMode();
                    break;

                case STATE_TOURNE_SUR_PLACE_DROITE:
                    PWMSetSpeedConsigne(10, MOTEUR_DROITE);
                    PWMSetSpeedConsigne(10, MOTEUR_GAUCHE);
                    stateRobot = STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS;
                    LED_BLANCHE = 0;
                    LED_BLEUE = 0;
                    break;
                case STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS:
                    SetNextRobotStateInAutomaticMode();
                    break;
            }
        }
        else
        {

        PWMSetSpeedConsigne(0, MOTEUR_DROITE);
        PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
        LED_BLANCHE = 1;
        LED_BLEUE = 0;
        stateRobot = STATE_ATTENTE;   
        }
    }
            
        void SetNextRobotStateInAutomaticMode() 
            {
                unsigned char positionObstacle = PAS_D_OBSTACLE;

                //Détermination de la position des obstacles en fonction des télémètres
                if (robotState.distanceTelemetreDroit < 25 && robotState.distanceTelemetreGauche < 25)
                    positionObstacle = OBSTACLE_EN_FACE;
                else if (robotState.distanceTelemetreDroit < 30 &&
                        robotState.distanceTelemetreCentre > 20 &&
                        robotState.distanceTelemetreGauche > 30) //Obstacle à droite
                    positionObstacle = OBSTACLE_A_DROITE;
                else if (robotState.distanceTelemetreDroit > 30 &&
                        robotState.distanceTelemetreCentre > 20 &&
                        robotState.distanceTelemetreGauche < 30) //Obstacle à gauche
                    positionObstacle = OBSTACLE_A_GAUCHE;
                else if (robotState.distanceTelemetreCentre < 30) //Obstacle en face
                    positionObstacle = OBSTACLE_EN_FACE;
                else if (robotState.distanceTelemetreDroit2 < 10 && robotState.distanceTelemetreGauche2 < 10)
                        if (robotState.distanceTelemetreDroit2 < robotState.distanceTelemetreGauche2)
                             positionObstacle= OBSTACLE_COTE_DROIT;
                        else positionObstacle= OBSTACLE_COTE_GAUCHE;
                else if (robotState.distanceTelemetreDroit2 < 15)
                    positionObstacle = OBSTACLE_COTE_DROIT;
                else if (robotState.distanceTelemetreGauche2 < 15)
                    positionObstacle = OBSTACLE_COTE_GAUCHE;
                else if (robotState.distanceTelemetreDroit < 50 ||
                        robotState.distanceTelemetreCentre < 60 ||
                        robotState.distanceTelemetreGauche < 50 ||
                        robotState.distanceTelemetreGauche2 < 40 ||
                        robotState.distanceTelemetreDroit2 < 40)
                    positionObstacle = OBSTACLE_SOON;
                else positionObstacle = PAS_D_OBSTACLE;

                //Détermination de l?état à venir du robot
                if (positionObstacle == PAS_D_OBSTACLE)
                    nextStateRobot = STATE_TRACE;
                else if (positionObstacle == OBSTACLE_SOON)
                    nextStateRobot = STATE_AVANCE;
                else if (positionObstacle == OBSTACLE_COTE_GAUCHE)
                    nextStateRobot = STATE_LEGER_GAUCHE;
                else if (positionObstacle == OBSTACLE_COTE_DROIT)
                    nextStateRobot = STATE_LEGER_DROIT;
                else if (positionObstacle == OBSTACLE_A_DROITE)
                    nextStateRobot = STATE_TOURNE_GAUCHE;
                else if (positionObstacle == OBSTACLE_A_GAUCHE)
                    nextStateRobot = STATE_TOURNE_DROITE;
                else if (positionObstacle == OBSTACLE_EN_FACE && compteurInverseur%2==0)
                    {
                        nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
                    }
                else if (positionObstacle == OBSTACLE_EN_FACE && compteurInverseur%2==1)
                    {
                        nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
                    }
                if (nextStateRobot != stateRobot - 1)
                    {
                        stateRobot = nextStateRobot;
                    }
            }
