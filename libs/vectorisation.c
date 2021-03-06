#include <stdio.h>
#include <stdlib.h>
#include "vectorisation.h"
#include "transformee.h"

extern int imgHeight;
extern int imgWidth;

// ADT liste de vecteurs
tp_vects creer_liste()
{
	return(NULL);
}

tp_vects ajouter_vecteur(tp_vects liste, tp_vect vecteur)
{
	tp_vects temp;
	
	temp = malloc(sizeof(t_vects));
	
	temp->vecteur = vecteur;
	temp->suiv = liste;

	return(temp);
}



// ADT vecteurs
tp_vect creer_vecteur()
{
	return(NULL);
};

tp_vect ajouter_point(tp_vect vecteur, int x, int y)
{
	tp_vect temp;

	temp = malloc(sizeof(t_vect));

	temp->x = x;
	temp->y = y;
	temp->suiv = vecteur;

	return(temp);
}



int prochain_point(t_flag **flags, int *x, int *y)
{
	flags[*x][*y] = flags[*x][*y] ^ SQUELETTE;

	int i, j;
	for(i = max((*x)-1, 0); i < min((*x)+2, imgHeight); i++)
	{
		for(j = max((*y)-1, 0); j < min((*y)+2, imgWidth); j++)
		{
			if(flags[i][j] & SQUELETTE)
			{
				*x = i;
				*y = j;
				printf("On regarde %d, %d\n", i, j);
				return(1);
			}
		}
	}
	return(0);
}


tp_vects extraire_vecteurs(t_flag **flags)
{	
		tp_vects liste;
		tp_vect vecteur;
		int x, y;
		int i, j;
		int dir;

		liste = creer_liste();
		for(x = 0; x < imgHeight; x++)
		{
			for(y = 0; y < imgWidth; y++)
			{
				if(flags[x][y] & SQUELETTE)
				{
					vecteur = creer_vecteur();
					vecteur = ajouter_point(vecteur, x, y);
					
					i = x;
					j = y;

					dir = prochain_point(flags, &i, &j);
					while(dir)
					{
						vecteur = ajouter_point(vecteur, i, j);
						dir = prochain_point(flags, &i, &j);
					}

					
					liste = ajouter_vecteur(liste, vecteur);
				}
			}
		}
	return(liste);
}