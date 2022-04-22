#include <stdio.h>
#include <stdlib.h>
#include <time.h> //Für Random Generator

static struct Knoten{
        int wert;
        struct Knoten *folgendesElement;
    };
    
static struct Knoten *kopf, *schwanz, *speicherfeld; //Damit man beim initialisieren nicht immer static struct Knoten hinschreiben muss

void erstelleStack(){
    kopf = (struct Knoten*)malloc(sizeof(struct Knoten)); //Speicher für Kopf wird reserviert
    schwanz = (struct Knoten*) malloc(sizeof(struct Knoten)); //Speicher für Schwanz wird rerviert
    kopf->wert = 0; //Kopf bekommt den Wert 0
    kopf->folgendesElement = schwanz; //Der Kopf zweigt auf den Schwanz, Stack ist also leer
    schwanz->folgendesElement = schwanz; //Der Schwanz zeigt auf sich selbst, da er das letzte Element ist

}

void elementRein(int daten){
    speicherfeld = (struct Knoten*) malloc(sizeof *speicherfeld);//Speicher für ein Speicherfeld rervieren
    speicherfeld-> wert = daten; //Im Speicherfeld werden die mitgegebenen Daten gespeichert
    speicherfeld->folgendesElement = kopf->folgendesElement; //Das Speicherfeld wird zwischen den Kopf und das was nach dem Kopf kommt "geschoben" / Funktionsweise eines Stacks
    kopf->folgendesElement = speicherfeld; //Nach dem Kopf kommt das neue Speicherfeld
    
}

int elementRaus(){
    int daten=0;
    speicherfeld = kopf->folgendesElement; //Mit Element ist das gemeint was nach dem Kopf kommt
    kopf->folgendesElement = speicherfeld->folgendesElement; //Das Element nach dem Kopf ist das Element NACH dem Speicherfeld / Das Element wird "rausgezogen"
    daten = speicherfeld->wert; //Der Wert des Speicherfeldes wird in daten gespeichert
    free(speicherfeld);
    return daten;
}

int istStackLeer(){
    if(kopf->folgendesElement == schwanz){ //Wenn das Element nach dem Kopf der Schwanz ist (Stack leer)
        return 1;
    }
    else return 0;
}

void stackAusgeben(int laengeStack){ 
    //Um den Stack komplett auszugeben, muss man ihn kompett leeren, da man sonst nicht an die Werte ran kommt
    int daten[laengeStack]; //Array zur Zwischenspeicherung

    for(int i=laengeStack-1; i >= 0; i--) daten[i] = elementRaus(); //Elemente aus Stack in Array einfuegen
    
    printf("\nStack ausgabe: \n");
    for(int i=0; i < laengeStack; i++){
        elementRein(daten[i]); //Stack wieder befuellen
        printf(" Element %d: %d \n", i, daten[i]);
    }
    printf("\n");
}


void main(){
    erstelleStack();
    int data = 0;
    srand(time(NULL)); //Sequenz für Random Nummer Generator soll immer unterschiedlich sein

    printf("Stack fuellen: \n");
    for(int i=0;i<10;i++){ //Stack mit 10 Werten befüllen
        data=(int)(rand()%100+1); //Random Wert von 100 bis 1 in data speichern
        elementRein(data); //Wert von data in Stack speichern/pushen
        printf(" Element %d: %d \n", i, data);
    }

    stackAusgeben(10);

    printf("Stack leeren: \n");
    int i = 9;
    while(istStackLeer() == 0){ //Solange der Stack nicht leer 
        printf(" Element %d: %d \n", i, elementRaus());
        i--;
    }
    //Zum beweis:
    if(istStackLeer() == 1){
        printf("\nStack wurde erfolgreich geleert! \n");
    }

}