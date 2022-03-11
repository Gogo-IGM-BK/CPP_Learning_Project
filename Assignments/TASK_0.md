# Se familiariser avec l'existant

## A- Exécution

Compilez et lancez le programme.

Allez dans le fichier `tower_sim.cpp` et recherchez la fonction responsable de gérer les inputs du programme.
Sur quelle touche faut-il appuyer pour ajouter un avion ?
```
Pour l'ajout d'un avion on appuie sur la touche 'C'
```

Comment faire pour quitter le programme ?

```
On peut quitter le programme avec les touches ‘X’ et ‘Q’
````

A quoi sert la touche 'F' ?

```
La touche ‘F’ permet de basculer vers le pleine écran.
```

Ajoutez un avion à la simulation et attendez.
Que est le comportement de l'avion ?
```
Si on ajoute un avion a la simulation, il va faire un atterrissage sur la piste, aller dans un terminal et puis retourner sur la piste pour décoller.
```
Quelles informations s'affichent dans la console ?

```
les informations afficher dans la console sont 

KL3190 is now landing...
now servicing KL3190...
done servicing KL3190
KL3190 lift off

```

Ajoutez maintenant quatre avions d'un coup dans la simulation.
Que fait chacun des avions ?

```
Chacun des avions fait la même chose, cependant certains avions peuvent être en vol stationnaire le temps qu’un terminal se libère, ils vont donc volez en cercle autour de l’aéroport en attendant qu’un terminal se libère.
````

## B- Analyse du code

Listez les classes du programme à la racine du dossier src/.
Pour chacune d'entre elle, expliquez ce qu'elle représente et son rôle dans le programme.

```
Les différents fichiers présents à la racine du programme sont :

- aircraft : cette classe représente un avion, son rôle est de construire un avion qui va être associé a une tour de contrôle,
- aircraft_types : réunis les différents options pour les avions, qui sont sa vitesse au sol ou dans les airs, sa texture et son accélération maximale, ce qui va permettre de spécifier le type d’un avion,
- airport : cette classe représente un aéroport, son rôle est de permettre aux avions d’aller vers un terminal,
- airport_type : représente le type d’aéroport,
- geometry : permet de créer des points de 2 ou 3 dimensions,
- runway : la piste d’atterrissage de notre aéroport,
- terminal : représente un terminal,
- tower : cette classe représente une tour de contrôle.
- tower_sim : c’est cette classe qui s’occuper de gérer toute la simulation de notre projet,
- waypoint : va permettre de simuler une suite de point représentant le chemin de notre avion.

```

Pour les classes `Tower`, `Aircaft`, `Airport` et `Terminal`, listez leurs fonctions-membre publiques et expliquez précisément à quoi elles servent.
Réalisez ensuite un schéma présentant comment ces différentes classes intéragissent ensemble.


```

Les fonctions publics de la classe Tower sont :

- get_instructions : cette fonction permet de récupérer la liste de points que l’avion devait parcourir, afin de poursuivre une route qui lui est propre, de le rapprocher d’un terminal ou de le faire attendre en vol stationnaire.
- arrived_at_terminal : cette fonction permet de signaler que l’avion est bien arrivé à un terminal.

Les fonctions publics de la classe Aircraft sont :

- get_flight_num : cette fonction est juste un getter sur le numéro de vol de notre avion. -distance_to : renvoie la position de notre avion par rapport a un point donné en parametre.
- display : permet d’afficher l’image représentant l’avion dans notre simulation,
- move: qui permet de gérer le déplacement de l’avion. 

Les fonctions publics de la classe Airport sont :

- get_tower : qui se charge juste de renvoyer la tour de contrôle de l’aéroport, 
- display : qui permet d’afficher l’aéroport,
- move : qui se charge d’effectuer les déplacements de ce qui se passe au niveau des terminaux.

Les fonctions publics de la classe Terminal sont :

- in_use : permet de prévenir si le terminal est en utilisation,
- is_servicing : indique si le terminal est en service, c’est a dire qu’un avion est à quai ou non,
- start_service : qui permet de signaler que l’avion donné en paramètre est en train de se faire servir,
- finish_service : qui permet de prévenir que l’avion fourni en paramètre a fini son service,
- move : qui permet d’incrémenter le compteur du temps que l’avion passes dans le terminal.
- assign_craft : elle permet d'assigner le champs current_aircraft 

```

Quelles classes et fonctions sont impliquées dans la génération du chemin d'un avion ?
```
Les classes qui sont impliqués dans la génération du chemin d’un avion sont : 

- waypoints : qui est une liste permettant de stocker les étapes du chemin que l’avion va devoir parcourir,
- aircraft : c’est dans cette classe que les waypoints vont être stockés,
- tower : qui va donner a l’avion le chemin qu’il devra parcourir, soit un cercle autour de l’aéroport, ou sinon un chemin vers un terminal.
Les fonctions qui sont impliqués sont donc :
- get_circle : fonction de tower, qui renvoie un cercle que l’avion devra parcourir,
- get_instructions : qui va soit renvoyer un chemin vers le terminal, soit la fonction get_circle, ou sinon une liste vide s’il n y a rien a faire.

```

Quel conteneur de la librairie standard a été choisi pour représenter le chemin ?
Expliquez les intérêts de ce choix.



## C- Bidouillons !

1) Déterminez à quel endroit du code sont définies les vitesses maximales et accélération de chaque avion.
Le Concorde est censé pouvoir voler plus vite que les autres avions.
Modifiez le programme pour tenir compte de cela.

```
Les vitesses maximales des avions se trouvent dans la classe aircraft_types, plus précisément dans la méthode init_aircraft_types.

```
2) Identifiez quelle variable contrôle le framerate de la simulation.
Ajoutez deux nouveaux inputs au programme permettant d'augmenter ou de diminuer cette valeur.
Essayez maintenant de mettre en pause le programme en manipulant ce framerate. Que se passe-t-il ?\
Ajoutez une nouvelle fonctionnalité au programme pour mettre le programme en pause, et qui ne passe pas par le framerate.

```
Il y a un problème si on essaie de mettre les framerate à 0, il faut donc passer par un boolean qui nous dira si on est en pause ou non, et en fonction de sa valeur on effectuera un move ou pas.
```

3) Identifiez quelle variable contrôle le temps de débarquement des avions et doublez-le.

```
On a modifié le fichier config.hpp, on a augmenté le SERVICES_CYCLES à 40
```


4) Lorsqu'un avion a décollé, il réattérit peu de temps après.
Faites en sorte qu'à la place, il soit retiré du programme.\
Indices :\
A quel endroit pouvez-vous savoir que l'avion doit être supprimé ?\
Pourquoi n'est-il pas sûr de procéder au retrait de l'avion dans cette fonction ?
A quel endroit de la callstack pourriez-vous le faire à la place ?\
Que devez-vous modifier pour transmettre l'information de la première à la seconde fonction ?

```
On peu savoir que l’avion doit être supprimé via la méthode move de notre Aircraft. Il n’est évidemment pas sur de le faire à cet endroit du code car on ne supprimera pas les références qui ont été faites sur celui-ci.
Il faudrait le faire là ou tous les apppels a move sont faits, c ‘est à dire dans la méthode timer de la classe opengl_interface.
Il faut changer la signature de la méthode move et renvoyer un boolean qui nous dira si oui ou non il faudra supprimé l’item.
```

5) Lorsqu'un objet de type `Displayable` est créé, il faut ajouter celui-ci manuellement dans la liste des objets à afficher.
Il faut également penser à le supprimer de cette liste avant de le détruire.
Faites en sorte que l'ajout et la suppression de `display_queue` soit "automatiquement gérée" lorsqu'un `Displayable` est créé ou détruit.
Pourquoi n'est-il pas spécialement pertinent d'en faire de même pour `DynamicObject` ?

```
Il n est pas très pertinent de faire ça avec les DynamicObject car comme le décrit son nom, il est plus efficace de l’allouer directement, donc qu’il soit « gérer automatiquement » n’est pas bénéfique.
```

6) La tour de contrôle a besoin de stocker pour tout `Aircraft` le `Terminal` qui lui est actuellement attribué, afin de pouvoir le libérer une fois que l'avion décolle.
Cette information est actuellement enregistrée dans un `std::vector<std::pair<const Aircraft*, size_t>>` (size_t représentant l'indice du terminal).
Cela fait que la recherche du terminal associé à un avion est réalisée en temps linéaire, par rapport au nombre total de terminaux.
Cela n'est pas grave tant que ce nombre est petit, mais pour préparer l'avenir, on aimerait bien remplacer le vector par un conteneur qui garantira des opérations efficaces, même s'il y a beaucoup de terminaux.\
Modifiez le code afin d'utiliser un conteneur STL plus adapté. Normalement, à la fin, la fonction `find_craft_and_terminal(const Aicraft&)` ne devrait plus être nécessaire.

## D- Théorie

1) Comment a-t-on fait pour que seule la classe `Tower` puisse réserver un terminal de l'aéroport ?

```
Pour que seule la classe Tower puisse réserver des terminal de l’aéroport il a fallut faire en sorte de garder les terminaux réservables et lui passer un champ faisant référence a l aéroport, ainsi il peut regarder quel terminal est libre et ainsi le réserver ou non.

```

2) En regardant le contenu de la fonction `void Aircraft::turn(Point3D direction)`, pourquoi selon-vous ne sommes-nous pas passer par une réference ?
Pensez-vous qu'il soit possible d'éviter la copie du `Point3D` passé en paramètre ?

```
En regardant la fonction « void Aircraft::turn(Point3D direction », nous ne sommes pas passer par références, car nous voulons garder notre point sans aucune modification, or la fonction cap_length modifiera la valeur de celui-ci.
```
## E- Bonus

Le temps qui s'écoule dans la simulation dépend du framerate du programme.
La fonction move() n'utilise pas le vrai temps. Faites en sorte que si.
Par conséquent, lorsque vous augmentez le framerate, la simulation s'exécute plus rapidement, et si vous le diminuez, celle-ci s'exécute plus lentement.

Dans la plupart des jeux ou logiciels que vous utilisez, lorsque le framerate diminue, vous ne le ressentez quasiment pas (en tout cas, tant que celui-ci ne diminue pas trop).
Pour avoir ce type de résultat, les fonctions d'update prennent généralement en paramètre le temps qui s'est écoulé depuis la dernière frame, et l'utilise pour calculer le mouvement des entités.

Recherchez sur Internet comment obtenir le temps courant en C++ et arrangez-vous pour calculer le dt (delta time) qui s'écoule entre deux frames.
Lorsque le programme tourne bien, celui-ci devrait être quasiment égale à 1/framerate.
Cependant, si le programme se met à ramer et que la callback de glutTimerFunc est appelée en retard (oui oui, c'est possible), alors votre dt devrait être supérieur à 1/framerate.

Passez ensuite cette valeur à la fonction `move` des `DynamicObject`, et utilisez-la pour calculer les nouvelles positions de chaque avion.
Vérifiez maintenant en exécutant le programme que, lorsque augmentez le framerate du programme, vous n'augmentez pas la vitesse de la simulation.

Ajoutez ensuite deux nouveaux inputs permettant d'accélérer ou de ralentir la simulation.
