#include <stdio.h>
#include <stdlib.h>

#define max(a,b) ((a)>(b)?(a):(b))

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
    return ptrouve ;
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

void parcourir_arbre (Arbre a, int *t, int niveau)
{
  if (a == NULL)
    return ;
  
  t [niveau] = t [niveau] + 1 ;
  parcourir_arbre (a->fgauche, t, niveau+1) ;
  parcourir_arbre (a->fdroite, t, niveau+1) ;  

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

Arbre detruire_cle_arbre (Arbre a, int cle)
{
  /*
    a completer
  */

  
}

int trouver_cle_min (Arbre a)
{
  /*
    a completer
  */

  
}

void imprimer_liste_cle_triee (Arbre a)
{
  /*
    a completer
  */

  

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
  /*
    a completer
  */

  
}

Arbre union_deux_arbres (Arbre a1, Arbre a2)
{
  /*
    a completer
  */

  
}

int inclusion_arbre (Arbre a1, Arbre a2)
{
  /*
    a completer
  */
  

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

  printf ("Hauteur %d\n", hauteur_arbre (a)) ;

  nombre_noeuds_par_niveau (a) ;

  printf ("Nombre cles de l'arbre %d\n", nombre_cles_arbre (a)) ;

  bool = EquilibreComplet1 (a) ;

  if (bool = 1)
    printf ("Methode 1: Arbre equilibre complet\n") ;
  else
    printf ("Methode 1: Arbre n'est pas equilibre complet\n") ;

    bool = EquilibreComplet2 (a) ;

  if (bool = 1)
    printf ("Methode 2: Arbre equilibre complet\n") ;
  else
    printf ("Methode 2: Arbre n'est pas equilibre complet\n") ;


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
}
