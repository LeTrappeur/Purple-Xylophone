Purple-Xylophone
================

 Project for the cyberpunkjam from 1st to 10th March 2014
 
[french]
 
Puzzle-game-die-and-retry-vu-de-haut
SFML et BOX2D

Chaque niveau se termine par l'accès au terminal des machines.
Les obstacles sont représentés par les rayons d'action des machines.
One shot = mort.
Chaque niveau représente un étage de l'immeumble.
L'ascenceur symbolise la fin du niveau. 
La fin du jeu se passe tout en haut lorsque le joueur désactive le "cerveau" électrique de l'immeuble.
10 niveaux + 1 niveau boss
Niveaux courts avec possibilité de checkpoints
Tableau en 32*32 1024*768 32 tiles en largeur 24 en hauteur

Le personnage peut changer de combinaisons pendant la partie.
Réserves d'énergie limitées pour changer de couleurs.
Possibilité pour le personnage de ramasser de l'énergie

Les machines peuvent être statiques ou dynamiques (patterns). Avec différentes caract.
Le rayons des machines peut être plein ou non et statique ou mobile.
Les machines détectent les couleurs, le héro peut se cacher en changeant de combinaison.
Les machines peuvent changer de couleurs selon le temps, selon les actions du joueur (ex: intérrupteurs)

Selection RGB des couleurs. (+)
Possibilité de désactiver les tourelles en utilisant de l'énergie(+)

Background

Un héro hors-la-loi qui lutte contre la robotisation.
L'immeuble est le quartier général de conception de robots d'une très grande entreprise.
L'objectif du héro est d'anéantir ce quartier général entièrement robotisé.

Graphismes et sons

PIXEL ART

1 personnage punk animé vu de haut:
	Déplacement
	Changement de couleur
	Mort
	Respawn
	Fin de niveau


1 modèle de tourelle
	Déplacement si dynamique
	Scan
	Attaque

1 modèle d'ascenseur d'animé
	ouvertue et fermeture

Multiple sprites 32*32 décors intérieur d'immeumble 
(murs, sols, salles de serveurs, canalisations, installations électriques, machines de fabrication)

Surcouches de néons

MUSIQUES - BRUITAGES

Thème: sombre, dangereux, année 80, minimaliste, infiltration, discret

Loop de musique assez longue

Tourelle : bruit d'alerte, bruit de déplacement méchanique

Ascenseur : bruit d'ouverture, de fermeture et de mise ne marche

Personnage : bruit de respawn, bruit changement de couleurs de combinaison

Environnement : Bruits de machines, de chocs, d'échappements de fumée, bruits industriels

Jeu : Bruit de console

[/french]

