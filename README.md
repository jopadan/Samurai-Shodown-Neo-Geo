# PMJ studios: Samurai Shodown

We are a small group, in the first year of a Bachelor's Degree in Video Game Design and Development. As a project we had the objective to create a tribute to the great Samurai Shodown, a classical arcade figthing game.

Samurai Shodown, known as Samurai Spirits is a fighting game developed and published by SNK for their NeoGeo arcade system. It was released in 1993, in a time of great hits such Street Fighter II: The World Warrior, Mortal Kombat, Art of Fighting, and many others. Samurai Shodown difered in it's fast paced combat, more focused on speed and timing than hard to chain combos, and in it's setting, which happens in the late 18th century. 

## Controls
### Debug
F1: Display all colliders.

F2: P1 wins game (victory screen).

F3: P2 wins game (defeat screen).

F4: P2 GOD mode.

F5: P1 GOD mode.

Spacebar: Advance between stages(menu, victory, defeat).

ESC: Close game.

## Implemented movements: 
### P1 controls:

WASD: move, jump and crouch.

1: Sword attack.

2: Kick.

Down(S)-> Face direction(D or A) -> 1 : Special move.

3: (Special move shortcut).

Down(S) -> 1 : Crouch attack.

Back when hitted (opposite direction of opponent): Block.

### P2 controls:

IJKL: move, jump and crouch.

7: Sword attack.

8: Kick.

Down(K)-> Face direction(J or L) -> 7 : Special move.

9: (Special move shortcut).

Down(K) -> 7 : Crouch attack.

Back when hitted (opposite direction of opponent): Block.

## Objective

The first player whose life gets to 0 or the one whose life is lower when the time ends loses the match.

## Changelog

0.1: Added first level with manual camera movement, background music, and one character with basic movement animations and attack animations.
0.2: Added different screens (menu, level 2 and victory screen) and system to navigate between them, with a fadeout in between them. Added fx and background music for every screen and improved the movement system, the input system and animations of the character.
0.3: Added a second player with same movement system as the first player but without animations or attacks, a particles system and improved fx.
0.4: Added a collision system (implementing stage limits and basic hitboxes for the characters and the attacks) and more funcionalities to both characters.
0.45: Changed the second character's appearance to be the second version of the first character and added all funcionalities that the first player had to the second one. Added a flip system for the characters to always face each other and a basic automatic camera system. Added a functional UI (just healthbars and timer) with its font system and win/lose conditions. Taken out of the games path the second screen and improved hitboxes and combat.

## Project page and team members
https://github.com/Ap011y0n/Samurai-Shodown-Neo-Geo

· Pol Galan: https://github.com/pgalmor

· Albert Garcia: https://github.com/Ap011y0n

· Pol Juan: https://github.com/Sauko22
