#include <stdio.h>
#include <stdlib.h>


#define NUMBER_OF_PARTICIPANTS 20


/* participant functions */
void midnightCherryRedTeslaRoadster() {
  printf("  Greetings from Starman !!\n");
}

void helloFromCow() {
  system("sh script.sh");
}

void idontknowwhatiamdoing() {
 printf("  something happens here \n ");
 }
/* Xander's function */
void saySomething() {
  printf("  Hello!  (by XS :-P)\n");
}

/* Tuur's function */
void tuursFunction(){
  printf("	Kettingregel!!!! ~Godelieve Lemmens \n");
}

/* Bram function */
void functionBram(int i) {
    switch(i) {
        case 0:
            break;
        default:
            printf("Ground control to Major Tom \n");
            functionBram(i-1);
    }
}

/* Riccardo's function*/
void falcon9Core() {
  printf("   Core landed... Sort of...\n");
}

/* Brecht's function */
void landBoosters() {
  printf("  Boosters landed !\n");
}

/* Luka */
void thisFunct(){
  printf("hi  \n");
}

/* Jasper's function */
void werktHet() {
  printf(" Werkt het? \n");
}

/* Leer tellen van 0 tot 2*/
void lerentellen() {
  printf("  Leren tellen tot 10\n");
  for(int i=0; i<3; i++) {
    printf("  %d \n", i);
  }
  printf("  De rest is te moeilijk (╯°□°）╯︵ ┻━┻) \n");
}

/*Bart's function*/
void felicitaties() {
	printf("Aan allen die gecommit hebben, proficiat! Aan allen die niet gecommit hebben, ook proficiat!\n");
}

/* map participant to function */
void executeFunction(int i) {
  switch(i) {
    case 0:
      midnightCherryRedTeslaRoadster();
      break;
    case 10:
      saySomething();
      break;
    case 9:
      falcon9Core();
      break;
    case 1:
      landBoosters();
      break;
    case 8:
      thisFunct();
      break;
    case 2:
      functionBram(5);
      break;
    case 3:
      lerentellen();
      break;
    case 19:
      helloFromCow();
      break;
    case 5:
      werktHet();
      break;
    case 4:
      tuursFunction();
      break;
   case 6:
    idontknowwhatiamdoing();
    break;
   case 11:
	felicitaties();
	break;
    default:
      break;
  }
}


/* MAIN: loop over participants */
int main(void) {
  int i;

  for(i=0;i<NUMBER_OF_PARTICIPANTS;i++) {
    printf("Participant %i:\n", i);
    executeFunction(i);
  }
}
