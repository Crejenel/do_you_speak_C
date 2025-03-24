#include <stdbool.h>
#include <string.h>
#include "data_validator.h"

/*
* The function checks if a number is within the range [100, 999].
* >> Input: a number 'code' (int)
* >> Output: true (100 <= code <= 999), false (code < 100 || code > 999)
*/
bool verify_sale_code(int code) {

	if (!(99 < code && code < 1000))
	{
		return false;
	}
	return true;
}

/*
* This boolean function validates the entered information for a property.
* >> Validated parameters:
* --> cod_vanzare (int)
* --> tip_proprietate (char)
* --> suprafata_proprietate (double)
* --> pret (double)
* --> nr (int)
* >> Returned value:
* --> true : (99 < cod_vanzare < 1000) && (tip_proprietate = teren/casa/apartament) && (suprafata_proprietate > 0) && pret > 0 && nr > 0
* --> false : if the above conditions are not met
*/
bool validation_input(int cod_vanzare, char tip_proprietate[], double suprafat_proprietate, double pret, int nr) {

	//codul unei proprietati trebuie sa aibe trei cifre
	if (!verify_sale_code(cod_vanzare))
	{
		return false;
	}

	//tipul unei proprietati poate fi : teren, casa sau apartament
	if (!(strcmp(tip_proprietate, "teren") == 0 || strcmp(tip_proprietate, "casa") == 0 || strcmp(tip_proprietate, "apartament") == 0))
	{
		return false;
	}

	//suprafata unei proprietati nu poate fi un numar negativ
	if (!(suprafat_proprietate > 0.0))
	{
		return false;
	}

	//pretul unei proprietati nu poate fi un numar negativ
	if (!(pret > 0.0))
	{
		return false;
	}

	//numarul unei proprietati nu poate fi un numar negativ
	if (!(nr > 0) )
	{
		return false;
	}

	return true;

}

