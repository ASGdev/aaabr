#include <stdio.h>
#include <stdlib.h>

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

/* structure noeud presentee en cours */

typedef struct n {
  int cle;
  struct n *fgauche, *fdroite;
} noeud ;

/* type Arbre, pointeur vers un noeud */

typedef noeud *Arbre;

/* n nouveau n a ajouter dans l'arbre a */

int feuille (Arbre a)
{
  if (a == NULL)
    return 0 ;
  else
    {
      if ((a->fgauche == NULL) && (a->fdroite == NULL))
	return 1 ;
      else
	return 0 ;
    }
}

Arbre ajouter_noeud (Arbre a, Arbre n)
{
  /* ajouter le noeud n dans l'arbre a */

  if (a == NULL)
    return n ;
  else if (n->cle < a->cle)
	a->fgauche = ajouter_noeud (a->fgauche, n) ;
  else
	a->fdroite = ajouter_noeud (a->fdroite, n) ;
  return a ;

}

Arbre rechercher_cle_arbre (Arbre a, int valeur)
{
  if (a == NULL)
    return NULL ;
  else
    {
      if (a->cle == valeur)
	return a ;
      else
	{
	  if (a->cle < valeur)
	    return rechercher_cle_arbre (a->fdroite, valeur) ;
	  else
	    return rechercher_cle_arbre (a->fgauche, valeur) ;
	}
    }
}

Arbre ajouter_cle (Arbre a, int cle)
{
  Arbre n ;
  Arbre ptrouve ;

  /*
     ajout de la clé. Creation du noeud n qu'on insere
    dans l'arbre a
  */

  ptrouve = rechercher_cle_arbre (a, cle) ;

  if (ptrouve == NULL)
    {
      n = (Arbre ) malloc (sizeof(noeud)) ;
      n->cle = cle;
      n->fgauche = NULL ;
      n->fdroite = NULL ;

      a = ajouter_noeud (a, n) ;
      return a ;
    }
  else
    return a ;
}

void afficher_arbre (Arbre a, int niveau)
{
  /*
    affichage de l'arbre a
    on l'affiche en le penchant sur sa gauche
    la partie droite (haute) se retrouve en l'air
  */

  int i ;

  if (a != NULL)
      {
	afficher_arbre (a->fdroite,niveau+1) ;

	for (i = 0; i < niveau; i++)
	  printf ("\t") ;
	printf (" %d (%d)\n\n", a->cle, niveau) ;

	afficher_arbre (a->fgauche, niveau+1) ;
      }
  return ;
}

int hauteur_arbre (Arbre a)
{
  /*
    calculer la hauteur de l'arbre a
  */

  if (a == NULL)
    return 0 ;
  else
    {
      return 1 +
	     max (hauteur_arbre (a->fgauche), hauteur_arbre (a->fdroite)) ;
    }
}

// NOT SAFE
int ii = 0;
void insert(int* t, int tsize, int v){
    if(ii == tsize){
        ii=0;
    }
    printf("Insert at index %d \n", ii);
    t[ii] = v;
    ii++;
}

void parcourir_arbre (Arbre a, int *t, int niveau)
{
  if (a == NULL)
    return ;

   t [niveau] = t [niveau] + 1 ;

  parcourir_arbre (a->fgauche, t, niveau+1) ;
  parcourir_arbre (a->fdroite, t, niveau+1) ;

  return ;
}

void parcourir_arbre_toList(Arbre a, int *t, int niveau)
{
    if (a == NULL)
    return ;

  printf("- %d - ", a->cle);

  insert(t, 20, a->cle);

  parcourir_arbre_toList(a->fgauche, t, niveau+1) ;
  parcourir_arbre_toList(a->fdroite, t, niveau+1) ;

  return ;
}

void nombre_noeuds_par_niveau (Arbre a)
{
  int i  ;
  int *t ;
  int h  ;

  h = hauteur_arbre (a) ;

  /* Allocation d'un tableau d'entier, une case par niveau */
  t = malloc (h * sizeof (int)) ;

  /* initialisation du tableau */

  for (i = 0; i < h ; i++)
    t[i] = 0 ;

  /*
     Parcourir l'arbre a partir du niveau 0
     le tableau t est passe en parametre
  */

  parcourir_arbre (a, t, 0) ;

  for (i = 0; i < h ; i++)
    printf ("Niveau %d: nombre cles %d\n", i, t[i]) ;

  free (t) ;
  return ;
}

int nombre_cles_arbre (Arbre a)
{
  if (a == NULL)
    return 0 ;
  else
    {
      return 1 + nombre_cles_arbre (a->fgauche) + nombre_cles_arbre (a->fdroite) ;
    }
}



Arbre cle_superieure_arbre (Arbre a, int valeur, Arbre *sup)
{
  if (a == NULL)
    return *sup ;

  if (valeur < a->cle)
    {
      *sup = a ;
      return cle_superieure_arbre (a->fgauche, valeur, sup) ;
    }
  else
    {
      return cle_superieure_arbre (a->fdroite, valeur, sup) ;
    }
}


Arbre rechercher_cle_sup_arbre (Arbre a, int valeur)
{
  Arbre ptrouve ;
  Arbre psup = NULL ;

  ptrouve = cle_superieure_arbre (a, valeur, &psup) ;
  return ptrouve ;

}

Arbre cle_inferieure_arbre (Arbre a, int valeur, Arbre *inf)
{
  if (a == NULL)
    return *inf ;

  if (valeur > a->cle)
    {
      *inf = a ;
      return cle_inferieure_arbre (a->fdroite, valeur, inf) ;
    }
  else
    {
      return cle_inferieure_arbre (a->fgauche, valeur, inf) ;
    }
}

Arbre rechercher_cle_inf_arbre (Arbre a, int valeur)
{
  Arbre ptrouve ;
  Arbre pinf = NULL ;

  ptrouve = cle_inferieure_arbre (a, valeur, &pinf) ;
  return ptrouve ;

}

int EquilibreComplet1 (Arbre a)
{
  int h ;
  int nbcles;

  int p = 1 ;

  h = hauteur_arbre (a) ;
  p = (p << h) - 1  ;

  nbcles = nombre_cles_arbre (a) ;

  if (p == nbcles)
    return 1 ;
  else
    return 0 ;
}

int EquilibreComplet2 (Arbre a)
{

  if (a == NULL)
    return 1 ;

  if ((a->fgauche != NULL && a->fdroite == NULL) || (a->fgauche == NULL && a->fdroite != NULL))
    return 0 ;

  return (EquilibreComplet2 (a->fgauche) && EquilibreComplet2 (a->fdroite)) ;
}

Arbre lire_arbre (char *nom_fichier)
{
  FILE *f ;
  int cle;
  Arbre a = NULL;

  f = fopen (nom_fichier, "r") ;

  while (fscanf (f, "%d", &cle) != EOF)
    {
      a = ajouter_cle (a, cle) ;
    }

  fclose (f) ;

  return a ;
}


Arbre detruire_cle_arbre_2(Arbre a, int cle){

    int *t;
    t = malloc(nombre_cles_arbre(a) * sizeof(int));

    parcourir_arbre_toList(a, t, 0);


    Arbre b = NULL;

    for(int i = 0; i<nombre_cles_arbre(a); i++){
        if(t[i] != cle){
            b = ajouter_cle(b, t[i]);
            printf("Insertion clé %d\n", t[i]);
        }
    }



    return b;

}



Arbre detruire_cle_arbre (Arbre a, int cle)
{
  /*
    Destruction d'une clé
  */
  Arbre b = a;
  // recherche si la clé est présente, dans le cas échéant l'arbre inchangé est retourné.
  Arbre aSuppr = rechercher_cle_arbre (a, cle);
  Arbre c = NULL;
  if (aSuppr == NULL){
    return a;
  } else {
    // si feuille
    if(feuille(aSuppr)){
        Arbre sauvdr;
        Arbre currentNode;
        int cleParent;

        if(aSuppr->cle == a->cle){
            return NULL;
        }
        if(aSuppr->cle < a->cle){
            sauvdr = a->fdroite;
            currentNode = a->fgauche;
            //cleParent =  rechercher_cle_sup_arbre(a->fgauche, aSuppr->cle)->cle;

        } else {
            sauvdr = a->fgauche;
            currentNode = a->fdroite;
            //cleParent = rechercher_cle_sup_arbre(a->fdroite, aSuppr->cle)->cle;
        }

            ajouter_cle(sauvdr, a->cle);

            printf("// %d , %d, %d //\n", currentNode->cle, aSuppr->cle);
            while(currentNode->cle > aSuppr->cle){
                printf("Rentre");
                ajouter_noeud(sauvdr, currentNode);

                currentNode = currentNode->fgauche;
            }
        cleParent = currentNode->cle;
        printf("CurrentNode key is : %d\n", currentNode->cle);
        if(aSuppr->cle < cleParent){
                ajouter_noeud(sauvdr, currentNode->fdroite);
            } else {
                ajouter_noeud(sauvdr, currentNode->fgauche);
            }
            ajouter_cle(sauvdr, cleParent);
            return sauvdr;

        }

    }
}

int trouver_cle_min (Arbre a)
{
  /*
    Retourne la clé minimale (celle qui est toute à gauche)
  */

  if (a->fgauche == NULL){
    return a->cle;
  } else {
    trouver_cle_min(a->fgauche);
  }

}

void imprimer_liste_cle_triee (Arbre a)
{
  /*
    parcours en ordre infixe
  */
    if (a == NULL)
        return ;

    imprimer_liste_cle_triee (a->fgauche) ;
    printf("- %d - ", a->cle);
    imprimer_liste_cle_triee (a->fdroite) ;

    return ;
}

void parcourir_arbre_largeur (Arbre a)
{
  /*
    a completer
    Utiliser une file, voir cours
  */



}

Arbre intersection_deux_arbres (Arbre a1, Arbre a2)
{

  Arbre temp = NULL;
  int* interlist;
  interlist = malloc(max(nombre_cles_arbre(a1), nombre_cles_arbre(a2)) * sizeof(int));

  parcourir_arbre_toList(a1, interlist, 0);

  for(int i=0; i<nombre_cles_arbre(a1); i++){
    printf("test clé %d\n", interlist[i]);
    if(rechercher_cle_arbre (a2, interlist[i]) != NULL){
        temp = ajouter_cle(temp, interlist[i]);
    }
  }
    return temp;
}

Arbre union_deux_arbres (Arbre a1, Arbre a2)
{

  int* a2list;
  a2list = malloc(nombre_cles_arbre(a2) * sizeof(int));

  ii=0;
  parcourir_arbre_toList(a2, a2list, 0);

  for(int i=0; i<nombre_cles_arbre(a2); i++){
    ajouter_cle(a1, a2list[i]);
  }

    return a1;
}

int inclusion_arbre (Arbre a1, Arbre a2)
{

  int nbclesa1 = nombre_cles_arbre(a1);
    int nbclesa2 = nombre_cles_arbre(a2);

    if(nbclesa2 < nbclesa1)
        return 0;

    int* a1list;
  a1list = malloc(nbclesa1 * sizeof(int));

  ii=0;
 parcourir_arbre_toList(a1, a1list, 0);


  for(int i = 0; i< nbclesa1; i++){
    Arbre temp = rechercher_cle_arbre (a2, a1list[i]);
    if(temp == NULL){
        return 0;
    }

  }

  return 1;
}

int main (int argc, char**argv)
{
  Arbre a ;
  int x ;
  int bool ;


  Arbre  ptrouve = NULL ;

  if (argc != 2)
    {
      fprintf (stderr, "il manque le parametre nom de fichier\n") ;
      exit (-1) ;
    }

  a = lire_arbre (argv[1]) ;

  afficher_arbre (a,0) ;

  //printf("Trouve clé min : %d", trouver_cle_min(a));

  imprimer_liste_cle_triee(a);
  printf("\n");
  Arbre b = NULL;
  ii=0;
  b = ajouter_cle(b, 46);
  imprimer_liste_cle_triee(b);
  printf("\n");
  printf("Inclus : %d", inclusion_arbre(b, a));

//  printf ("Hauteur %d\n", hauteur_arbre (a)) ;
//
//  nombre_noeuds_par_niveau (a) ;
//
//  printf ("Nombre cles de l'arbre %d\n", nombre_cles_arbre (a)) ;
//
//
//
//  bool = EquilibreComplet1 (a) ;
//
//  if (bool == 1)
//    printf ("Methode 1: Arbre equilibre complet\n") ;
//  else
//    printf ("Methode 1: Arbre n'est pas equilibre complet\n") ;
//
//    bool = EquilibreComplet2 (a) ;
//
//  if (bool == 1)
//    printf ("Methode 2: Arbre equilibre complet\n") ;
//  else
//    printf ("Methode 2: Arbre n'est pas equilibre complet\n") ;
//
//    printf("Parcours de l'arbre : \n");
//
//    int *list;
//    list = malloc(nombre_cles_arbre (a) * sizeof(int));
//    parcourir_arbre_toList(a, list, 0);
//    printf("Fin parcours de l'arbre\n");
//    for(int i=0; i<nombre_cles_arbre (a); i++){
//        printf("%d - ", list[i]);
//    }
//
    //printf("Impression liste triée de l'arbre : \n");
    //imprimer_liste_cle_triee(a);



  /*
    Appels des fonctions de recherche de cles
  */

//  printf ("Entrez une cle a rechercher\n") ;
//
//  scanf ("%d", &x) ;
//
//  ptrouve = rechercher_cle_arbre (a, x) ;
//
//  if (ptrouve != NULL)
//    printf ("la cle %d est dans l'arbre\n", x) ;
//  else
//    printf ("la cle %d n'est pas dans l'arbre\n", x) ;
//
//  ptrouve = rechercher_cle_sup_arbre (a, x) ;
//
//  if (ptrouve != NULL)
//    printf ("la cle sup de %d est %d\n", x, ptrouve->cle) ;
//  else
//    printf ("il n'y a pas de cle sup pour %d\n", x) ;
//
//  ptrouve = rechercher_cle_inf_arbre (a, x) ;
//
//  if (ptrouve != NULL)
//    printf ("la cle inf de %d est %d\n", x, ptrouve->cle) ;
//  else
//    printf ("il n'y a pas de cle inf pour %d\n", x) ;




}
