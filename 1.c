/// cat.c
#include <stdio.h>
#include <stdlib.h>

void cat(char *filename, int *count) // skapar funktionen som tar emot ett filnamn som är en string
{
  FILE *f = fopen(filename, "r"); // sparar pointern till filnamnet och att vi ska läsa ur den (r)
  int c = fgetc(f); //lärser in ett ecken från filen    
    int counter = count;
    printf("==== %s ====\n", filename);
    printf("%d",counter);
  while (c != EOF) // while loopen kommer köras så länge datan inte nått end of file
  {
    fputc(c, stdout); // skriver ut värdet vi tog emot i stdout vilket är terminalen
        if (c == '\n'){
        count ++;
        printf("%d: ",count);
    }
    c = fgetc(f); // hämtar nästa data
  }

  fclose(f);    // stänger filen
}

int main(int argc, char *argv[])    // kallar på main funktionen som tar in ett argument
{
    int count = 1;
    int *count_p = count;
  if (argc < 2) 
  {
    fprintf(stdout, "Usage: %s fil1 ...\n", argv[0]);
  }
  else
  {
    for (int i = 1; i < argc; ++i)
    {
      cat(argv[i], count_p);
    }
  }

  return 0;
}
