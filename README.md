# 2D-Physics-Pinball
 Alexandre Carreras and Carlos Arnau plataformer game for Game Development

 Github Project Link:
 https://github.com/TheGewehr/B-platformer


 Controls:

 A key -> Move to the left
 D key -> Move to the right
 Space -> Use spring
 I key -> Debug for seeing the colliders


Dev's diary:

As a final conclusion, this first assignment of the plataformer game is not as good ad we wished, he had ton of problems during the development of the game that stopped us to implement basic functionalities. Next we are going to expose those problems and detailing a little bit with what we tried to sort out them.

1. Box2D library implementation: At the begining we wanted to use Box2D to add the Physics needed in the character interaction with the map. Despite we added the Box2D library following the instructions given, our project didn't recognized the library and we weren't able to use the library normally. At first we dind't gave up, but after trying to add the library several times and using different templates the library continued being ignored by the project. Currently we created a branch to store the Box2D implementation in case that we find a solution in the future.

2. Colliders and player animations: Given that Box2D dind't work, we decided to change our strategy and we tried to use SDL to accomplish our goal, but yet another time and after checking that we did it correctly, the project dind't recognize the collisions that we created and the animations dind't work either. 
In consequence we passed this last week that we had to complete the project trying to implement the basic physics and animations into the game, failing another time. Finally we figured out that the player movement dind't work at the player.cpp but worked in the ModuleCollisions.cpp. So against the clock we implemented some movements to the character in a super basic way and in the wrong place.
