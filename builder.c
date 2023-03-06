#include <stdio.h>
#include <stdlib.h>

#include "number.h"

#define NL printf("\n")
#define TPL while(getchar()!='\n')

number *erstelltVerketteteListe(FILE *f1)
{
    number *first = NULL;
    number *list;
    number *prev = NULL;

    while(!feof(f1))
    {
        
        list = (number*)malloc(sizeof(number));
        list->name = (char*)malloc(7);
        
        //nicht beim ersten Durchgang
        if (prev != NULL) {
            prev->next=list;

            //nur einmal first deklarieren
            if (first == NULL) {
                first = prev;
            }
        }

        fscanf(f1,"%s %d %lf",list->name,&list->zahl,&list->zehl);

        prev = list;
    }

    //dem letzten Struct in der Liste den Wert NULL fŸr next verpassen
    list->next = NULL;

    //nur das erste Element der Liste Ÿbergeben.
    //Das reicht, denn von diesem wird auf die anderen verwiesen.
    return first;
}

number *sortiertListe(number *current) 
{

    number *prev;
    number *next;
    number *first;

    first = current;
    prev = NULL;
    next = current->next;

    while(1) {

        if (current->next == NULL) {
            break;
        }

        //wenn true dann muss sortiert werden
        if (current->zahl > next->zahl) {
            
            //hier findet die eigentliche Sortierung statt
            if (prev != NULL) {
                prev->next = next;
            } else {
                //first muss neu gesetzt werden da wir die
                //ersten beiden Elemente tauschen
                first = next;
            }
            current->next = next->next;
            next->next = current;

            //wir setzen current wieder auf first und den ganzen
            //Spaß wieder von vorne an.
            prev = NULL;
            current = first;
            next = first->next;
            continue;

        }

        //hier kommt man nur hin wenn keine Sortierung stattgefunden
        //hat. Dann zeigt current auf das nächste Element in der Liste.
        prev = current;
        current = current->next;
        next = current->next;

    }

    return first;

}

void ausgabe(number *pointer)
{

    while(pointer)
    {
        printf("%s %d",pointer->name,pointer->zahl);NL;
        pointer=pointer->next;
    }
}

int main (int argc, char *argv[])
{

    if(argc != 2){
        printf("ERROR 0");NL;return;
    }

    FILE *f1;
    number *pointer;

    f1 = fopen(argv[1],"r");

 	if(f1 == NULL){
        printf("ERROR 1");
        return;
    }

    pointer = erstelltVerketteteListe(f1);

    pointer = sortiertListe(pointer);
        
    ausgabe(pointer);

    return 0;
}

