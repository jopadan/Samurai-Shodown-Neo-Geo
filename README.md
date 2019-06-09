# PMJ studios: Samurai Shodown

We are a small group, in the first year of a Bachelor's Degree in Video Game Design and Development. As a project we had the objective to create a tribute to the great Samurai Shodown, a classical arcade figthing game.

Samurai Shodown, known as Samurai Spirits is a fighting game developed and published by SNK for their NeoGeo arcade system. It was released in 1993, in a time of great hits such Street Fighter II: The World Warrior, Mortal Kombat, Art of Fighting, and many others. Samurai Shodown difered in it's fast paced combat, more focused on speed and timing than hard to chain combos, and in it's setting, which happens in the late 18th century. 

## Project page
https://github.com/Ap011y0n/Samurai-Shodown-Neo-Geo

## Webpage
https://github.com/Ap011y0n/Samurai-Shodown-Neo-Geo

## Team members
https://github.com/Ap011y0n/Samurai-Shodown-Neo-Geo
· Pol Galan: https://github.com/pgalmor

· Albert Garcia: https://github.com/Ap011y0n

· Pol Juan: https://github.com/Sauko22

## Controls
Gamecontroller (xbox360 or equivalent) / keyboard
(We recommend the use of a gamecontroller since the game was designed for that type of controls in mind)

### Menu, select screen, ending
Start button / Spacebar: Advance between stages(menu->select->fight, ending -> menu).
Select screen: select a character with X, move with joystick.

### Debug
F1: Display all colliders.

F2: P1 wins game (victory screen).

F3: P2 wins game (defeat screen).

F4: P2 GOD mode.

F5: P1 GOD mode.



ESC: Close game.

## Moveset: 

Joystick / WASD: move, jump and crouch.

Slash:     X  Weak Slash     Y  Medium Slash     XY Strong Slash
Kick:      A  Weak Kick      B  Medium Kick      AB Strong Kick

When jump, neutral, forward, backward && crouch: 

	   X  Weak Slash     Y  Strong Slash		
	   A  Weak Kick	     B  Strong Kick 

Block:
Move backwards (opposite of facing direction)

Specials:
(If facing direction = right, otherwise invert -O and O-)

 O-   /  |     Slash 		Annu Mutsube (the low flying attack)
    O    O

|  \   -O     Slash		Leyla Mutsube (the up-to-the-sky attack)
O   O

 -O  \   |   /  O-  Slash 	Amube Yatoro (Summon the bird to attack)
      O  O  O

|   /  O-  kick			Hawk Carry
O  O	


(while hawk carry)

/ or | or \  Slash or Kick     Yatoro Poku   (Rolling Down Attack)
O    O     O

O- or -O Slash or Kick		Kamui Mutsube    (Diagonal Down Arrow Attack)	

Keyboard Variations
### P1 controls:
     X = 1     Y = 2    
     A = 3     B = 4

O 		  |
| = W	O- = A    O = S	  -O = D

### P2 controls:

     X = 7     Y = 8    
     A = 9     B = 0

O 		 |
| = I	O- = J   O = K	  -O = L




## Objective

The first player whose life gets to 0 or the one whose life is lower when the time ends loses a round. The player who wins 2 rounds wins a match.

## Changelog

**0.1:** Added first level with manual camera movement, background music, and one character with basic movement animations and attack animations.

**0.2:** Added different screens (menu, level 2 and victory screen) and system to navigate between them, with a fadeout in between them. Added fx and background music for every screen and improved the movement system, the input system and animations of the character.

**0.3:** Added a second player with same movement system as the first player but without animations or attacks, a particles system and improved fx.

**0.4:** Added a collision system (implementing stage limits and basic hitboxes for the characters and the attacks) and more funcionalities to both characters.

**0.45:** Changed the second character's appearance to be the second version of the first character and added all funcionalities that the first player had to the second one. Added a flip system for the characters to always face each other and a basic automatic camera system. Added a functional UI (just healthbars and timer) with its font system and win/lose conditions. Taken out of the games path the second screen and improved hitboxes and combat.

### Libraries used:
SDL: https://www.libsdl.org/
SDL_Mixer: https://www.libsdl.org/projects/SDL_mixer/
SDL_Image: https://www.libsdl.org/projects/SDL_image/
