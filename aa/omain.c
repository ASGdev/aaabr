/* Jeu de test pour les arbres */
/* DE ARAUJO Bastien, SURIER GAROFALO Aurélien */

#include <stdio.h>

int main (int argc, char**argv)
{
  Arbre a ;
  int x ;
  int bool ;


  Arbre  ptrouve = NULL ;

  if (argc != 2)
    {
      fprintf (stderr, "Il manque le parametre nom de fichier\n") ;
      exit (-1) ;
    }

  a = lire_arbre (argv[1]) ;

  printf("***** Informations sur l'arbre *****");

  afficher_arbre (a,0) ;

    printf ("Hauteur %d\n", hauteur_arbre (a)) ;
    printf ("Nombre cles de l'arbre %d\n", nombre_cles_arbre (a)) ;
    nombre_noeuds_par_niveau (a) ;

    bool = EquilibreComplet1 (a) ;

  if (bool == 1)
    printf ("Methode 1: Arbre equilibre complet\n") ;
  else
    printf ("Methode 1: Arbre n'est pas equilibre complet\n") ;

    bool = EquilibreComplet2 (a) ;

  if (bool == 1)
    printf ("Methode 2: Arbre equilibre complet\n") ;
  else
    printf ("Methode 2: Arbre n'est pas equilibre complet\n") ;

    printf("Parcours de l'arbre : \n");

    int *list;
    list = malloc(nombre_cles_arbre (a) * sizeof(int));
    parcourir_arbre_toList(a, list, 0);
    printf("Fin parcours de l'arbre\n");
    for(int i=0; i<nombre_cles_arbre (a); i++){
        printf("%d - ", list[i]);
    }

    //printf("Impression liste triée de l'arbre : \n");
    //imprimer_liste_cle_triee(a);

    printf("***** Opérations sur l'arbre *****");
  /*
    Appels des fonctions de recherche de cles
  */

  printf ("Entrez une cle a rechercher\n") ;

  scanf ("%d", &x) ;

  ptrouve = rechercher_cle_arbre (a, x) ;

  if (ptrouve != NULL)
    printf ("la cle %d est dans l'arbre\n", x) ;
  else
    printf ("la cle %d n'est pas dans l'arbre\n", x) ;

  ptrouve = rechercher_cle_sup_arbre (a, x) ;

  if (ptrouve != NULL)
    printf ("la cle sup de %d est %d\n", x, ptrouve->cle) ;
  else
    printf ("il n'y a pas de cle sup pour %d\n", x) ;

  ptrouve = rechercher_cle_inf_arbre (a, x) ;

  if (ptrouve != NULL)
    printf ("la cle inf de %d est %d\n", x, ptrouve->cle) ;
  else
    printf ("il n'y a pas de cle inf pour %d\n", x) ;

    /*
        Exemple de rotation droite
    */
    Arbre tempR = a;
    afficher_arbre(tempR, 0);
    rotationDroite(tempR);
    afficher_arbre(tempR, 0);

    /*
        Exemple de rotation gauche
    */
    Arbre tempG = a;
    afficher_arbre(tempG, 0);
    rotationGauche(tempG);
    afficher_arbre(tempG, 0);

    /*
        Exemple d'insertion d'une clé dans un arbre : avec et sans équilibrage
    */
    int cle = 5;
    Arbre tempIns1, tempsIns2 = a;
    afficher_arbre(tempIns1);
    ajouter_cle(tempsIns1, cle); // le but est qu eça déséquilibre
    afficher_arbre(tempIns1) // affichage de l'arbre déséquilibré
    ajouter_cle(tempsIns2);


}
