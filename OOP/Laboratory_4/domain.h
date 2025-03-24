#ifndef DOMAIN_H
#define DOMAIN_H

struct address {

	char strada[30];
	int nr;
	char localitate[30];

};
struct property {

	int cod_vanzare;
	char tip_proprietate[11];
	double suprafata_proprietate;
	double pret;
	int reducere;
	struct address adresa;
}; 

#endif