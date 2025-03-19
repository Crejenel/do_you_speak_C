#ifndef SERVICE_H
#define SERVICE_H

char* delete_property_by_code(int code_delete_property);

char* add_property_to_sistem(int cod_vanzare, char tip_proprietate[], double suprafat_proprietate, double pret, char strada[], int nr, char localitate[]);

bool is_digit_or_double(char* s);

bool is_digit(char* s);

bool yes_or_no(char* s);

void delete_space(char* s);

double convert_char_to_double(char* s);

char* update_property_service(int input, char* update);

struct property get_one_property(int code_sale);

struct storage* filtering_property(char* criterio, char* value, char* greater);

struct storage* sorting_property(char* sorting);


#endif;