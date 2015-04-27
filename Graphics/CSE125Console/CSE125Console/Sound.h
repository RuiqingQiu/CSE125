//
//  Sound.h
//  CSE125 
//
//  Created by Mingshan Wang on 12/12/14.
//  Copyright (c) 2014 Ruiqing Qiu. All rights reserved.
//


#include <iostream>
#include <stdio.h>
#include <al.h>
#include <alc.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <Gl/glu.h>
//#include <GLUT/GLUT.h>

extern int play(int, char **, char* filepath);
extern int playApplause(int, char **, char* filepath);
extern int playTurnback(int, char **, char* filepath);
extern void stopPlaying();
extern int playBoo(int, char **, char* filepath);

