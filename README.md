# Simulateur d'interaction électrostatiques
**Deadline : 20/06 à 0h00**  
**À envoyer par mail à olivier.cros@yncrea.fr et yannick.lambert@yncrea.fr**

Protocole à suivre -> ANSSI C (C89)  
Librairie graphique -> OpenGL | GTK  

Un champ complet (représenté par un rectangle)
Il y a différentes charges (fixes et mobiles)

Objectif -> calculer numériquement les intéractions électrostatiques entre plusieurs particules chargées afin de déterminer les grandeurs physiques caractéristiques (champ électrique, force de Coulomb, mouvement d'une ou plusieurs particules etc...) d'une géométrie donnée.

A partir d'un modèle électrostatique simple, le programme calculera et affichera le mouvement des charges mobiles ainsi que les forces de Coulomb.

## Les fonctionnalités
* Représenter les outils et interactions électromagnétiques dans un moteur de simulation dédié
* Ajouter une charge fixe
* Ajouter une charge mobile
* Lancer une simulation pour un temps donné
* Afficher le résultat au moyen d’une interface graphique
* Générer un champ et des charges placées manuellement ou aléatoirement
* L’affichage de la force de Coulomb associé à chaque charge en sélectionnant la charge en question
* La visualisation du mouvement des charges mobiles
* En bonus vous pourrez afficher également les lignes de champ et le potentiel électrostatique

## Les contraintes
* On ne considérera que des charges électriques ponctuelles. Une masse et un nombre fini de charges élémentaires seront affectés à chaque point.
* Le programme devra permettre la saisie du nombre et de la position des charges ainsi que leur état (fixe ou mobile).
* Afin de modéliser les interactions entre les charges, on prendra un modèle simple en deux parties :
  * Une partie statique ou l'on calaculera les forces s'appliquant sur chaque charge dans le cadre de l'électrostatique
  * Une partie dynamique où l'on calculera le déplacement des charges par appalication du principe fondamental de la dynamique.
* Pour que le point précédent reste valable, il faudra tenir compte des petites variations temporelles et spatiales. L'échelle de temps sera donc un élément à prendre en compte (via une variable, par exemple).
* Rendre un fichier de documentation décrivant les étapes nécessaires pour compiler le binaire de l'outil.



