[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/BEkQoRPC)
# Unidad 4 - Sistemas Operativos

Nombre del estudiante: Andres Martinez  
ID: 000396102
---

# Documentación del Proyecto y Bitácora
This is a continuation of the game, found in this repository: [Link](https://github.com/hacUPB/sc-2410-evalu3-iiKesler). For this project, I will be adding sounds while using threads.

## First Steps
First of all, I need to understand how threads work, for the looks of it, it's sort of a coroutine, this threads happen at the same time that the game is running. However, it looks like if they gte out of control, it can create a lot of issues. I'm going to start by adding first the background music, since it works in its own separate thread, it hopefully will be easy to manage. After this, it's a question of adding all the other sounds by using semaphores.

#### Adding a new SDL2 library
For this "update" of the game, I have to add a new library, it's the "Mix" library

![image](https://github.com/hacUPB/sc-2410-evalu4-iiKesler/assets/89699466/a2be6f2f-af8f-474a-8a08-3eb91c2bfd58)

And once again, I'm going for the dev version, since it's the one we've been using for the other libraries as well.

And since we added a new library, that means we also have to add a new flag to our linker in the Makefile, it looks like this:

`-lSDL2_mixer`

And with this, we now have the build working properly.

## SFX sounds
So, I got the background music to work, it plays as soon as the game starts, and it sounds good enough, now, I have to add the SFX for the rest of the game. First of all, I'll add the sound for when the ball bounces off of the paddle.

Great, it works as expected, and it wasn't that hard to put together, I also created its own class, so I can keep everything organized. For now, it works fine, I'll add now the sound for when someone picks up a power.

Okay, it looks like it works fine for now, I did the same process, and it works as fine so onto the next one, now I want to add a sound for when someone scores.

I can't lie, it does sound weird whenever I listen to the sounds, and sometimes it's hard to tell them apart, but I think it's working for now. Lastly, I'll have to add when the ball bounces off the walls and the rectangles that act as a goalie area in the game.

Okay, whenever I listen to the sounds, I think it's only the wall-bounce sounds that's playing, I don't know why this is it, but I'll try to figure it out.
