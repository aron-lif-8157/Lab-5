/// cat.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void cat(char *filename) // skapar funktionen som tar emot ett filnamn som är en string
{
  FILE *f = fopen(filename, "r"); // sparar pointern till filnamnet och att vi ska läsa ur den (r)
  int c = fgetc(f); //lärser in ett ecken från filen    

  while (c != EOF) // while loopen kommer köras så länge datan inte nått end of file
  {
    fputc(c, stdout); // skriver ut värdet vi tog emot i stdout vilket är terminalen
    c = fgetc(f); // hämtar nästa data
    }
  fclose(f);    // stänger filen
}

void print_menu(){
    char menu_text[] = "[L]ägga till en vara\n"
                        "[T]a bort en vara\n"
                        "[R]edigera en vara\n"
                        "Ån[g]ra senaste ändringen\n"
                        "Lista [h]ela varukatalogen\n"
                        "[A]vsluta) \n";
    for (int i = 0; i < strlen(menu_text); i++){
        fputc (menu_text[i],stdout);
    }

    
}



void ask_question_menu(){
    print_menu();
    char *str = ask_question_is_menu_char("Vad vill du göra?: ");
}

int main(int argc, char *argv[])    // kallar på main funktionen som tar in ett argument
{
    ask_question_menu();

  return 0;
}
