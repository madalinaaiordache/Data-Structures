
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "UEFAHashtable.c"
#include "UEFALinkedList.c"

#define MAX_STRING_SIZE	2048

// la fotbal sunt 4 pozitii: portar, fundas, mijlocas si atacant
struct InfoFotbalist {
	char nume[MAX_STRING_SIZE];
	char nationalitate[MAX_STRING_SIZE]; //facultate
	char pozitie[MAX_STRING_SIZE]; //mancare_preferata
	char trofeu[MAX_STRING_SIZE];
	int rating;
    int goluri;
    int assists;  // =p t ala care da pasa si altul ia mingea si da gol
    int tackling;  // = cand recuperezi mingea
    int meci_fara_gol;
};

static void
print_fotbalist(struct InfoFotbalist *p_info)
{
	if (p_info == NULL) {
		printf("Fotbalist inexistent!\n");
		return;
	}
	printf("* Nume: %s | ", p_info->nume);
	printf("Nationalitate: %s | ", p_info->nationalitate);
	printf("Pozitie: %s | ", p_info->pozitie);
	printf("Trofeu: %s | ", p_info->trofeu);
	printf("Rating: %d | ", p_info->rating);
	printf("Goluri: %d | ", p_info->goluri);
	printf("Asissts: %d | ", p_info->assists);
	printf("Tackling: %d | ", p_info->tackling);
	printf("Meciuri fara gol: %d\n", p_info->meci_fara_gol);
}

int
main()
{
	hashtable_t *ht_fotbalisti;
	struct InfoFotbalist informatii_fotbalisti[5];
	struct InfoFotbalist *p_infoFotbalist;
	int current_key;

	/* Initializare structuri informatii fotbalisti. */
	strcpy(informatii_fotbalisti[0].nume, "Philipp Lahm");
	strcpy(informatii_fotbalisti[0].nationalitate, "germana");
	strcpy(informatii_fotbalisti[0].pozitie, "fundas");
	strcpy(informatii_fotbalisti[0].trofeu, "FIFA Club World Cup");
	informatii_fotbalisti[0].rating = 88;
	informatii_fotbalisti[0].goluri = 0;
	informatii_fotbalisti[0].assists = 0;
	informatii_fotbalisti[0].tackling = 15;
	informatii_fotbalisti[0].meci_fara_gol = 10;

	strcpy(informatii_fotbalisti[1].nume, "Karim Benzema");
	strcpy(informatii_fotbalisti[1].nationalitate, "franceza");
	strcpy(informatii_fotbalisti[1].pozitie, "atacant");
	strcpy(informatii_fotbalisti[1].trofeu, "French Player of the Year");
	informatii_fotbalisti[1].rating = 150;
	informatii_fotbalisti[1].goluri = 25;
	informatii_fotbalisti[1].assists = 40;
	informatii_fotbalisti[1].tackling = 0;
	informatii_fotbalisti[1].meci_fara_gol = 0;

	strcpy(informatii_fotbalisti[2].nume, "Andrea Pirlo");
	strcpy(informatii_fotbalisti[2].nationalitate, "italiana");
	strcpy(informatii_fotbalisti[2].pozitie, "atacant");
	strcpy(informatii_fotbalisti[2].trofeu, "UEFA Super Cup");
	informatii_fotbalisti[2].rating = 205;
	informatii_fotbalisti[2].goluri = 12;
	informatii_fotbalisti[2].assists = 11;
	informatii_fotbalisti[2].tackling = 0;
	informatii_fotbalisti[2].meci_fara_gol = 0;


	strcpy(informatii_fotbalisti[3].nume, "Arda Turan");
	strcpy(informatii_fotbalisti[3].nationalitate, "turca");
	strcpy(informatii_fotbalisti[3].pozitie, "mijlocas");
	strcpy(informatii_fotbalisti[3].trofeu, "Europa Lleague Winner");
	informatii_fotbalisti[3].rating = 220;
	informatii_fotbalisti[3].goluri = 9;
	informatii_fotbalisti[3].assists = 5;
	informatii_fotbalisti[3].tackling = 0;
	informatii_fotbalisti[3].meci_fara_gol = 0;

	strcpy(informatii_fotbalisti[4].nume, "Thiago Silva");
	strcpy(informatii_fotbalisti[4].nationalitate, "braziliana");
	strcpy(informatii_fotbalisti[4].pozitie, "portar");
	strcpy(informatii_fotbalisti[4].trofeu, "Confederations Cup");
	informatii_fotbalisti[4].rating = 215;
	informatii_fotbalisti[4].goluri = 0;
	informatii_fotbalisti[4].assists = 0;
	informatii_fotbalisti[4].tackling = 8;
	informatii_fotbalisti[4].meci_fara_gol = 7;

	/* Initializare hashtable_t. */
	ht_fotbalisti = ht_create(10, hash_function_string,
				compare_function_strings);

	/* Put si get pentru o singura cheie. */
	ht_put(ht_fotbalisti, "Philipp Lahm", strlen("Philipp Lahm") + 1, &informatii_fotbalisti[0],
		sizeof(informatii_fotbalisti[0]));
	p_infoFotbalist = ht_get(ht_fotbalisti, "Philipp Lahm");
	printf("# 1\n");
	printf("Output:\n");
	print_fotbalist(p_infoFotbalist);


	/* Put si get pentru chei unice. */
	ht_put(ht_fotbalisti, "Karim Benzema", strlen("Karim Benzema") + 1, &informatii_fotbalisti[1],
		sizeof(informatii_fotbalisti[1]));
	ht_put(ht_fotbalisti, "Andrea Pirlo", strlen("Andrea Pirlo") + 1,
		&informatii_fotbalisti[2], sizeof(informatii_fotbalisti[2]));
	ht_put(ht_fotbalisti, "Arda Turan", strlen("Arda Turan") + 1,
		&informatii_fotbalisti[3], sizeof(informatii_fotbalisti[3]));
	ht_put(ht_fotbalisti, "Thiago Silva", strlen("Thiago Silva") + 1,
		&informatii_fotbalisti[4], sizeof(informatii_fotbalisti[4]));

	p_infoFotbalist = ht_get(ht_fotbalisti, "Karim Benzema");
	printf("\n# 2\n");
	printf("Output:\n");
	print_fotbalist(p_infoFotbalist);

	p_infoFotbalist = ht_get(ht_fotbalisti, "Andrea Pirlo");
	printf("\n# 3\n");
	printf("Output:\n");
	print_fotbalist(p_infoFotbalist);

	p_infoFotbalist = ht_get(ht_fotbalisti, "Arda Turan");
	printf("\n# 4\n");
	printf("Output:\n");
	print_fotbalist(p_infoFotbalist);

	p_infoFotbalist = ht_get(ht_fotbalisti, "Thiago Silva");
	printf("\n# 5\n");
	printf("Output:\n");
	print_fotbalist(p_infoFotbalist);

	

	/* Remove entry din hashtable_t. */
	ht_remove_entry(ht_fotbalisti, "Philipp Lahm");

	p_infoFotbalist = ht_get(ht_fotbalisti, "Philipp Lahm");
	printf("\n# 6\n");
	printf("Output:\n");
	print_fotbalist(p_infoFotbalist);
	printf("Output asteptat:\n");
	printf("Fotbalist inexistent!\n");

	ht_remove_entry(ht_fotbalisti, "Karim Benzema");

	p_infoFotbalist = ht_get(ht_fotbalisti, "Karim Benzema");
	printf("\n# 7\n");
	printf("Output:\n");
	print_fotbalist(p_infoFotbalist);
	printf("Output asteptat:\n");
	printf("Fotbalist inexistent!\n");


	ht_free(ht_fotbalisti);

	return 0;
}
