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
// DONE --------------------------------------------------------------------
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
    char *name = ask_question_string("Vad är varans namn?");
    char *description = ask_question_string("Vad är varans beskrivning? ");
    int price = ask_question_int("vad är varans pris?");
    char *shelf = ask_question_shelf("Vilken Hylla står den på?");

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


void list_db(item_t *items, int *current_items_in_db){
    for(int i = 0; i < *current_items_in_db;i++){
        item_t item = items[i];
        printf("%d. %s\n",(i+1), item.name);
    }
}

void edit_db(item_t *db, int *nr_of_items){
    list_db (db, nr_of_items);
    int x = ask_question_int("Vilken vara vill du ändra?")-1;

    print_item(&db[(x)]);
    printf("Skapa en ny vara!\n");
    item_t i = input_item();
    db[x] = i;
    list_db (db, nr_of_items);
}


char *add_item_to_db(item_t *db, int *nr_of_items){
    if (*nr_of_items < 16){
        db[*nr_of_items] = input_item();
        *nr_of_items = *nr_of_items +1;
        list_db(db,nr_of_items);
        return "DONE";
        
    }else {
        return"Databasen är full, ta bort ett item för att lägga till ett nytt";
    }
}


void remove_item_from_db(item_t *db, int *nr_of_items){
    list_db(db, nr_of_items);
    int x = (ask_question_int("Vilken vara vill du ta bort?") -1);
    
    while (x < *nr_of_items){
    db[x] = db[(x+1)];
    x++;
    }
    *nr_of_items = *nr_of_items -1;
}

// DONE --------------------------------------------------------------------

void event_loop(item_t *db, int *current_items_in_db)
{   
    do{
    char menu_text[] = "\nVad vill du göra?\n"
                        "[L]ägga till en vara\n"
                        "[T]a bort en vara\n"
                        "[R]edigera en vara\n"
                        "Ån[g]ra senaste ändringen\n"
                        "Lista [h]ela varukatalogen\n"
                        "[A]vsluta) \n";
    char *input_str = ask_question_menu(menu_text);

    char option = input_str[0];

    switch (option)
    {
    case 'L':
    case 'l':
        add_item_to_db(db, current_items_in_db);
        break;
    
    default:
        break;
    }
    printf("current item count = %d\n", *current_items_in_db);
    list_db (db, current_items_in_db);
    }while (loop == flase);

}
// TODO -----------------------------------------------------------

int main(void){
    char *array1[] = { "Laser",        "Polka",    "Extra" };
    char *array2[] = { "fÃ¶rnicklad",   "smakande", "ordinÃ¤r" };
    char *array3[] = { "skruvdragare", "kola",     "uppgift" };
    /*
    variabler för db och d:s storlek
    */

    int db_length = 16;
    int *p_db_length = &db_length;
    int items_to_fill = 6;

    int current_items_in_db = (items_to_fill);
    
    item_t db[db_length]; // Array med plats för 16 varor
 //   item_t *p_db = &db; 
    
    for (int i = 0; i < items_to_fill; ++i){
        if (i == 2){
            item_t item = make_item("Aron", "Aron", 222222, "A2");
            db[i] = item;
            continue;
        }
        srandom(time(NULL));
        char *name = magick(array1, array2, array3, 3); 
        char *desc = magick(array1, array2, array3, 3); 
        int price = random() % 200000;
        char shelf[] = { random() % ('Z'-'A') + 'A', random() % 10 + '0', random() % 10 + '0', '\0' };
        
        item_t item = make_item(name, desc, price, shelf);

        db[i] = item;
    }
    
    


    list_db (db,&current_items_in_db);

    event_loop(db, &current_items_in_db);

    return 0;
}


