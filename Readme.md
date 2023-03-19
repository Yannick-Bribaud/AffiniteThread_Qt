# Affinité

Ce projet vous permettra d'observer le mécanisme de l'affinité des threads.

## Objectifs

Vous apprendrez :

- comment afficher le thread avec lequel un objet a une affinité
- comment réaliser le bon appel à une fonction pour qu'elle s'exécute dans le thread souhaité.

## Analyse

Au démarrage de l'application, l'identifiant du thread de l'application est affiché. Il n'y a qu'un thread.

Lorsque le contrôleur est instancié, dans son constructeur (1) l'identifiant du thread est affiché. Il n'y a toujours qu'un seul thread dans l'application. De plus la règle d'affinité de thread dit qu'un enfant a la même affinité que son parent, c'est donc le même identifiant de thread que pour l'application.

La fonction `Controller::start()` est appelée.

L'identifiant du thread est à nouveau affiché (2). Le même raisonnement que ci-dessus s'applique.

Un objet `o1` est instancié. Le même raisonnement s'applique toujours.

Un thread `t2` est créé. Son identifiant est affiché (3).

Un objet `o2` est créé (4). L'identifiant du thread est affiché. L'objet a la même affinité de thread que son parent, qui est le contrôleur. C'est donc l'identifiant du thread de l'application qui est affiché.

L'affinité de thread de `o2` est changée pour `t2` (5). 

L'identifiant du thread auquel `o2` est rattaché est affiché (6). Chose surprenante, il s'agit toujours du même identifiant, alors que nous venons de modifier l'affinité de thread. Cela s'explique par le fait que lorsque l'on apelle la fonction `o2->thread()` on ne fait qu'un *branchement* dans la fonction `QObject::thread()` qui s'exécute dans le thread courant (celui de `this`, donc de l'instance de Controller). Nous n'utilisons pas la règle de l'affinité de thread. 

La fonction `Objet::debugObjet()` est appelée (7) pour lui faire afficher l'identifiant du thread auquel il est rattaché. Nous obtenons le même résultat que précédemment, pour les mêmes raisons.

L'identifiant du thread auquel est rattaché `o2` est affiché en utilisant un signal (8). Cette fois-ci l'identifiant du thread t2 est affiché. Cela s'explique par le fait que nous avons utilisé un signal, donc la règle de l'affinité de thread s'applique. Puisqu'un signal est utilisé, l'appel passe par la run-loop, le thread dans lequel la fonction est exécutée correspond au thread de l'objet appelé (o2) puisque l'appelant (`this` = Controller) et l'appelé (`o2`) n'ont pas la même affinité de thread.

La fonction `Objet::debugObjet()` est ensuite appelée en utilisant un signal (9). Nous observons le même résultat que ci-dessus, pour les mêmes raisons.

Enfin, la fonction `Objet::debugObjetFiable()` est appelée. L'identifiant du thread affiché est celui de `t2`. La fonction `Objet::debugObjetFiable()` agit comme **Proxy** et permet de conserver un appel de fonction simple de côté de l'appelant, et d'exécuter la fonction dans le bon thread (celui de l'appelé) tout en conservant la complexité sémantique dans le code de la classe appelée.

## Synthèse

En fonction du type d'appel de fonction vous n'obtenez pas le même résultat. Souvent vous penserez avoir fait le travail en modifiant l'affinité de thread d'un objet, mais si vous ne faites pas le bon appel, en passant par la run-loop, vous n'utiliserez même le second thread. En conséquence, habituez-vous à créer des fonctions Proxy pour forcer les appels de fonctions à s'exécuter sur la run-loop de l'objet appelé, tout en conservant une sémantique simple dans vos applications.

