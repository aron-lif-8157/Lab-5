#include <stdio.h>
#include "utils.h"
#include <time.h>
#include <stdlib.h>


typedef struct item item_t;

struct item
{
    char *name;
    char *description;
    int price;
    char *shelf;
};

void print_menu(){
    printf("\n"
           "[L]Ã¤gga till en vara\n"
           "[T]a bort en vara\n"
           "[R]edigera en vara\n"
           "Ãn[g]ra senaste Ã¤ndringen\n"
           "Lista [h]ela varukatalogen\n"
           "[A]vsluta\n"
           "\n");
}

void print_item(item_t *item){
        printf ("Name:  %s\n", item->name);
        printf("Desc:  %s\n", item->description);
        printf("Price: %d,%d", (item->price/100), (item->price%100));
        puts(" SEK");
        printf("Shelf: %s\n",item->shelf);

}

item_t make_item(char *name, char *description, int price, char *shelf){
    item_t item = {name, description, price, shelf};
    return item;
} 

item_t input_item(void){
    char *name = ask_question_string("Vad Ã¤r varans namn?");
    char *description = ask_question_string("Vad Ã¤r varans beskrivning? ");
    int price = ask_question_int("vad Ã¤r varans pris?");
    char *shelf = ask_question_shelf("Vilken Hylla stÃ¥r den pÃ¥?");

    return make_item(name, description, price, shelf);
}

char *magick (char *array1[], char *array2[], char *array3[], int arrayLength){
    int bufSize = 255;
    //int counter = 10;
    char buf[bufSize];
    srandom(time(NULL));
    char *first_name =  array1[random() % arrayLength];
    char *second_name = array2[random() % arrayLength];
    char *third_name = array3[random() % arrayLength];

    strcpy(buf,first_name);
    strcat(buf,"-");
    strcat (buf, second_name);
    strcat(buf," ");
    strcat (buf, third_name);
    strcat(buf,"\0");

    return strdup(buf);
}

void list_db(item_t *db, int *nr_of_items){
    for(int i = 0; i < *nr_of_items;i++){
        item_t item = db[i];
        printf("%d. %s\n",(i+1), item.name);
    }
}

void edit_db(item_t *db, int *nr_of_items){
    list_db(db, nr_of_items);
    int x = ask_question_int("Vilken vara vill du Ã¤ndra?")-1;

    print_item(&db[(x)]);
    printf("Skapa en ny vara!\n");
    item_t i = input_item();
    db[x] = i;
    list_db(db, nr_of_items);
}

char *add_item_to_db(item_t *db, int *nr_of_items){
    if(*nr_of_items < 16){
        db[*nr_of_items] = input_item();
        *nr_of_items = *nr_of_items +1;
        list_db(db, nr_of_items);
        return "DONE";
    }else{
        return "Databasen Ã¤r full, ta bort en vara fÃ¶rst!";
    }

}

void remove_item_from_db(item_t *db, int *nr_of_items){
    list_db(db, nr_of_items);
    int x = (ask_question_int("Vilken vara vill du ta bort?")-1);
    while(x < *nr_of_items){
        db[x] = db[(x+1)];
        x++;
    }
    *nr_of_items = *nr_of_items-1;
}
int main(void){
    char *array1[] = { "Laser",        "Polka",    "Extra" };
    char *array2[] = { "fÃ¶rnicklad",   "smakande", "ordinÃ¤r" };
    char *array3[] = { "skruvdragare", "kola",     "uppgift" };
    
    item_t db[16]; // Array med plats fÃ¶r 16 varor
    int nr_of_items = 0;

    for (int i = 0; i < 16; ++i){
        srandom(time(NULL));
        char *name = magick(array1, array2, array3, 3); 
        char *desc = magick(array1, array2, array3, 3); 
        int price = random() % 200000;
        char shelf[] = { random() % ('Z'-'A') + 'A', random() % 10 + '0', random() % 10 + '0', '\0' };
        
        item_t item = make_item(name, desc, price, shelf);

        db[i] = item;
        nr_of_items++;
    }


    bool loop = true;
    while(loop == true){
        print_menu();
        char *temp = ask_question_menu("Vad vill du gÃ¶ra?");
        char c = toupper(temp[0]);
        if(c == 'A'){
            loop = false;
        }else if(c == 'L'){
            printf("%s\n",add_item_to_db(db, &nr_of_items));
        }else if(c == 'T'){
            remove_item_from_db(db, &nr_of_items);
        }else if(c == 'R'){
            edit_db(db, &nr_of_items);
        }else if(c == 'G'){
            printf("Not yet implemented!");
        }else if(c == 'H'){
            list_db(db, &nr_of_items);
        }else{
            printf("Wrong command");
        }
    }
    return 0;
}