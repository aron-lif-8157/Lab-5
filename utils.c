#include <stdio.h>
#include <string.h>
#include "utils.h"
#include <stdbool.h>


typedef union{
    int int_value;
    float float_value;
    char *string_value;
} answer_t;


bool is_number(char *str)
{
    int str_len = strlen(str);
    int ascii_list [] = {48,49,50,51,52,53,54,55,56,57}; // 10 steg
    int ascii_minus = 45;
    
    /*
    Om strängen är tom så returnerar den falsk
    */
    if (str_len == 0){
      return false;
    }
    /*
    sign loopen går igenom varje tecken i strängen
    */
    for ( int sign = 0; sign < str_len; sign++){
        int input = str[sign];
        /* 
        kollar om du bara skrivit in ett minus
        */
        if (str[0] == ascii_minus && str_len == 1){
          return false;
        /*
        kollar om första tecknet är minus
        */
        } else if(str[sign] == ascii_minus && sign == 0){
          continue;
        }

        for (int ascii_check = 0; ascii_check < 11; ascii_check++){
            if (ascii_check == 10) {
                return false;
            }
            else if (input == ascii_list[ascii_check]){
                break;
            }
            /*
            kollar om nuvarande tecknet är minus
            */
            else if (input == ascii_minus){
              return false;
            }

        }
    }
    return true;
}



extern char *strdup(const char *);
typedef bool(*check_func)(char *);
typedef answer_t(*convert_func)(char *);

answer_t ask_question(char *question, check_func check, convert_func convert){
    int buf_siz = 30;
    char buf[buf_siz];
    bool is_right_type = false;
    answer_t conversions;

    while(is_right_type == false){
        println(question);
        read_string(buf, buf_siz);
        is_right_type = (check (buf));
    }
    conversions = convert (buf);
    //print(buf);
    return conversions;
}

int ask_question_int(char *question){
    answer_t answer = ask_question(question, (check_func)(is_number), (convert_func)(atoi));
    return answer.int_value; //svaret som ett heltal
}


bool not_empty(char *str){
    return strlen(str) > 0;
}

bool is_shelf(char *str){
    if(strlen(str) > 0){
        if(str[0] >= 'A' && str[0] <= 'Z'){

            char temp = str[0];
            str[0] = str[1];
            if (is_number (str) == true){
                str[0] = temp;
                return true;
            }
        }
    }
    return false;
}

bool is_menu_char (char *str){
    char menu_char[] = "LlTtRrGgHhAa";
    if (strlen (str) >= 2){
        return false;
    }
    for (int i = 0; i <= strlen(menu_char); i++){
        if (str[0] == (menu_char[i])){
            return true;
        }            
    }

    return false;
}


char *ask_question_menu(char *question){
    return ask_question (question, (check_func)(is_menu_char), (convert_func)(strdup)).string_value;
}

char *ask_question_string(char *question){
    return ask_question(question, (check_func)(not_empty), (convert_func) strdup).string_value;
}

char *ask_question_shelf(char *question){
    return ask_question(question, (check_func)(is_shelf), (convert_func)(strdup)).string_value;

/*    bool done = false;
    char *hylla;
    while (done == false){
    hylla = ask_question_string("Walla brorsan vad är din hylla?");
    done = is_shelf(hylla);
    
    }
    return hylla;   */
}

int clear_input_buffer(int c){
    do{
        c = getchar();
    } 
    while(c != '\n' && c != EOF && c != '\0');
    putchar('\n');
    return 0;
}

int read_string(char *buf, int buf_siz){
    char c = 0;
    int count = 0;
    do{
        if(count >= (buf_siz-1)){
            clear_input_buffer(*buf);
        }
        c = getchar();
        buf[count] = c;
        count++;
    }
    while(c != '\n' && c != EOF && c != '\0' && buf_siz > count);

    count = count - 1;
    buf[count] = '\0';

    return count;
}

void print(char *str)
{
  char *end = str;
  while (*end != '\0'){
    char current = *end;
    printf("%c",current);
    ++end;
  }
}

void println(char *input){
    print(input);
    printf("\n");
}