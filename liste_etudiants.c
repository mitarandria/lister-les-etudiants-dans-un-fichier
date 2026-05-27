#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct liste
{
  char nom[50];
  char prenom[50];
  char date_de_naissance[28];
  char niveau[10];
  char adresse[50];
};
void lire(struct liste *l);
void ecrire(struct liste *l);//ecriture dans le fichier
void afficher();//ahhichage du contenu
void trier();// tri par ordre alphabetique
void rechercher();//rechercher une ou des personne(s)
void modifier();//modifier l'information d'une personne
void supprimer();//supprimer une personne
int choix();//choisir un action
void lire(struct liste *l)
{
  printf("Nom:");
  scanf(" %49[^\n]", l->nom);
  printf("Prénom:");
  scanf(" %49[^\n]", l->prenom);
  printf("Date de naissance:");
  scanf(" %27[^\n]", l->date_de_naissance);
  printf("Niveau:");
  scanf(" %9s", l->niveau);
  printf("Adresse:");
  scanf(" %49[^\n]", l->adresse);
}
void ecrire(struct liste *l)
{
  FILE *list;
  list = fopen("list", "a");
  if (list == NULL) 
  {
    printf("Erreur lors de l'ouverture du fichier en écriture.\n");
    return;
  }
  fwrite(l, sizeof(struct liste), 1, list);
  fclose(list);
  printf("Enregistrement terminé !\n");
}
void afficher()
{
  struct liste l;
  FILE *list;
  
  int pers;
  pers = 1;
  list = fopen("list", "r");
  if (!list) 
  {
    printf("Aucune donnée trouvée ou le fichier n'existe pas encore.\n");
    return;
  }

  printf("\n%-s ~ %-s ~ %-s ~ %-s ~ %-s\n", "NOM", "PRENOM", "DATE_DE_NAISSANCE", "NIVEAU", "ADRESSE");
  printf("--------------------------------------------------------------------------------\n");
  while (fread(&l, sizeof(struct liste), 1, list) == 1)
  {
      printf("%d) %-s ~ %-s ~ %-s ~ %-s ~ %-s\n",pers,l.nom, l.prenom, l.date_de_naissance, l.niveau, l.adresse);
      pers++;
  }

  fclose(list);
  printf("\nIl y a %d personne(s) enregistrée(s).\n", pers);
}
void trier()
{
  struct liste t[100];
  struct liste temp;
  FILE *list;
  int n = 0;
  list = fopen("list", "rb");
  if (!list) 
  {
    printf("Aucune donnée à trier.\n");
    return;
  }
  while (fread(&t[n], sizeof(struct liste), 1, list) == 1)
  {
    n++;
    if (n >= 100) break;
  }
  fclose(list);
  if (n == 0) return;
  for (int i = 0; i < n - 1; i++)
  {
    for (int j = 0; j < n - i - 1; j++)
    {
      if (strcmp(t[j].nom, t[j+1].nom) > 0)
      {
        temp = t[j];
        t[j] = t[j+1];
        t[j+1] = temp;
      }
    }
  }
  list = fopen("list", "wb");
  if (!list) return;
  for (int i = 0; i < n; i++)
  {
    fwrite(&t[i], sizeof(struct liste), 1, list);
  }
  fclose(list);
}
void rechercher()
{
  struct liste l;
  FILE *list;
  char recherche[50];
  int resultat;
  resultat = 0;
  list = fopen("list", "rb");
  if (!list) 
  {
    printf("Aucune donnée trouvée ou le fichier n'existe pas.\n");
    return;
  }
  printf("Entrez le mot, le nom ou la date à rechercher : ");
  scanf(" %49[^\n]", recherche);
  printf("\nRÉSULTATS DE LA RECHERCHE POUR '%s'...\n", recherche);
  printf(" %-s ~ %-s ~ %-s ~ %-s ~ %-s\n", "NOM", "PRENOM", "DATE DE NAISSANCE", "NIVEAU", "ADRESSE");
  printf("--------------------------------------------------------------------------------\n");
  while (fread(&l, sizeof(struct liste), 1, list) == 1)
  {
    // strstr renvoie un pointeur (différent de NULL) si le mot_cle est trouvé
    if (strstr(l.nom, recherche) != NULL ||strstr(l.prenom, recherche) != NULL ||strstr(l.date_de_naissance,recherche) != NULL || strstr(l.niveau, recherche) != NULL || strstr(l.adresse, recherche) != NULL)
    {
      printf("%-s ~ %-s ~ %-s ~ %-s ~ %-s\n", l.nom, l.prenom, l.date_de_naissance, l.niveau, l.adresse);
      resultat++;
    }
  }
  fclose(list);
  if (resultat == 0)
  {
    printf("Aucun résultat ne correspond à votre recherche.\n");
  }
  else
  {
    printf("\n%d personne(s) trouvée(s).\n", resultat);
  }
}
void modifier()
{
  struct liste t[100];
  FILE *list;
  char modif[50];
  int n,trouve ;
  trouve=0;
  list = fopen("list", "rb");
  if (!list) 
  {
    printf("Aucune donnée à modifier.\n");
    return;
  }
  n=0;
  while (fread(&t[n], sizeof(struct liste), 1, list) == 1) 
  {
    n++;
    if (n >= 100) break;
  }
  fclose(list);
  printf("Entrez le NOM de la personne à modifier : ");
  scanf(" %49[^\n]", modif);
  int i;
  for (i = 0; i < n; i++) 
  {
    if (strcmp(t[i].nom, modif) == 0) 
    {
      trouve = 1;
      printf("\n--- Personne trouvée ! Entrez les nouvelles données ---\n");
      printf("Nouveau nom : ");
      scanf(" %49[^\n]", t[i].nom);
      printf("Nouveau prénom : ");
      scanf(" %49[^\n]", t[i].prenom);
      printf("Nouvelle date de naissance : ");
      scanf(" %27[^\n]", t[i].date_de_naissance);
      printf("Nouveau niveau : ");
      scanf(" %9s", t[i].niveau);
      printf("Nouvelle adresse : ");
      scanf(" %49[^\n]", t[i].adresse);
      break; 
    }
  }
  if (trouve) 
  {
    list = fopen("list", "wb");
    for (i = 0; i < n; i++) 
    {
      fwrite(&t[i], sizeof(struct liste), 1, list);
    }
    fclose(list);
    printf("Modification enregistrée avec succès !\n");
  } 
  else 
  {
    printf("Nom introuvable.\n");
  }
}
void supprimer()
{
  struct liste t[100];
  FILE *list;
  char suppr[50];
  int n;
  int trouve;
  trouve = 0;
  list = fopen("list", "rb");
  if (!list) 
  {
    printf("Aucune donnée à supprimer.\n");
    return;
  }
  n = 0;
  while (fread(&t[n], sizeof(struct liste), 1, list) == 1) 
  {
    n++;
    if (n >= 100) break;
  }
  fclose(list);
  printf("Entrez le NOM exact de la personne à supprimer : ");
  scanf(" %49[^\n]", suppr);
  int i,j;
  for (i = 0; i < n; i++) {
    if (strcmp(t[i].nom, suppr) == 0) 
    {
      trouve = 1;
      for (j = i; j < n - 1; j++) 
      {
        t[j] = t[j + 1];
      }
      n--;
      i--;
    }
  }
  if (trouve) 
  {
    list = fopen("list", "wb");
    for (int i = 0; i < n; i++) 
    {
      fwrite(&t[i], sizeof(struct liste), 1, list);
    }
    fclose(list);
    printf("Suppression réussie !\n");
  } 
  else 
  {
    printf("Aucune personne trouvée avec ce nom.\n");
  }
}
int choix()
{
  int ch;
  printf("\n\"1\" pour ajouter\n");
  printf("\"2\" pour afficher tout\n");
  printf("\"3\" pour rechecher\n");
  printf("\"4\" pour modifier\n");
  printf("\"5\" pour supprimer\n");
  printf("\"6\" pour quitter\n\n");
  printf("Ton choix : ");
  if (scanf("%d", &ch) != 1) {
    // Sécurité au cas où l'utilisateur tape une lettre au lieu d'un chiffre
    while (getchar() != '\n'); 
    return 0;
  }
  return ch;
}
int main()
{
  int ch;
  struct liste l;
  while(1)
  {
    ch = choix();
    if (ch == 1) 
    {
      lire(&l);
      ecrire(&l);
      trier();
    } 
    else if (ch == 2) 
    {
      afficher();
    } 
    else if (ch == 3)
    {
      rechercher();
    }
    else if (ch == 4)
    {
      modifier();
    }
    else if (ch == 5)
    {
      supprimer();
    }
    else if (ch == 6) 
    {
      break;
    }
  }
  return 0;
}
