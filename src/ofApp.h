//The General concept behind this project is to create an ocean and night sky in the general synthwave style and have it react to the facial expression of the user. This is done in an attempt to visually represent the 'Sea of emotions' that humans feel

//Although multiple skulls can be created by multiple users being present, the  program will remain reactive to only one


#pragma once

#include "ofMain.h"
#include "Grid.hpp"
#include "ofxFaceTracker2.h"
#include "ofxAssimpModelLoader.h"


//this defines the amount of rows that are present (How far from the camera the ocean extends)
//goes back 20*200=4000
#define nGrids 200

class ofApp : public ofBaseApp{
   
    
    public:
        void setup();
        void update();
        void draw();
    void keyPressed(int key);
    

    
    //these hold the ratio between the center to the mouth edge and across the entire mouth
    float MouthRatio, MouthOpenRatio;
    
    //these hold the distance between the mouth places
    float distLeftMouthRight, distCenterMouth, distMouthOpen;
    
    //these hold the positions for the mouth places
    glm::vec2 lMouthCorner, rMouthCorner, MouthCenter, lCMouth, rCMouth, mouthTop, mouthBottom;
    
    //these variables set for the range of the eye, adapting to what shocked and angry looks like on each person
    float minEye, maxEye, midEye;
    
    //This holds the value for the color of the skull
    ofColor skullColor;
    
    //draws the red moon if the skull is not present
    bool MOON;
    
    //These are the points responsible for measuring the height of the eyebrows
    glm::vec2 lBrowC, lBrowE, lEyeC, lEyeE, rBrowC, rBrowE, rEyeC, rEyeE;
    
    //These hold the values for the distance between the eyebrow points and the eye points
    float lDistC, lDistE, rDistC, rDistE;
    
    //These hold the value of the ratio between the edge and the center values for each eye
    //this is what makes it possible for the program to work at whatever range (THEORETICALLY FUCK)
    float lRatio, rRatio;
    
    //This holds the value for the average of the above ratios
    float averageBrowtoEye;
    
    //these variables control the modifications made based on the eyebrows relative to the eyes
    float waveHeight, waveReach, waveSpeed;
    
    //this is the skull in the sky
    ofxAssimpModelLoader skull, shadow;
    
    // stores the info on the current file.
    string curFileInfo;
    
    //this intiates the video from the camera on the laptop
    ofVideoGrabber grabber;
    //this is the tracker for the faces
    ofxFaceTracker2 tracker;
    

 //this sets the amount og the grid class to be present.
    //ENSURE THIS EQUALS OR IS LESS THAN "nGrids"
    Gridclass grid[200];
    //camera for this project
    ofEasyCam cam;
    //this sets the base height of the ocean
    int baseY;
    //controls wireframe vs solid display
    bool wires;
    //these are the stars
    //a million billion shinning stars
    ofSpherePrimitive orbs[1000];
   //this sets the color for the stars (spelled with a z because it looks cool
    ofColor starz;
    //these are a boat load of placer holder values for all the colors that the stars switch through.
    //This is a heirarchacle system where _Red is made of hred and lred and they are made of hred1 hred2 lred1 lred2, and so forth.
    //The actual color values are store in the sets that feature (h/l)Color(1/2)(1/2); example hred21;
    float _Red, _Green, _Blue, hred, hgreen, hblue, lred, lgreen, lblue, hred1, hgreen1, hblue1, hred2, hgreen2,hblue2, lred1, lgreen1, lblue1, lred2, lgreen2, lblue2, hred11, hgreen11, hblue11, hred21, hgreen21,hblue21, hred12, hgreen12, hblue12, hred22, hgreen22,hblue22,lred11, lgreen11, lblue11, lred21, lgreen21, lblue21, lred12, lgreen12, lblue12, lred22, lgreen22, lblue22;
    //this is the timer for the noise functions for the light colors. This causes the lights to slowly shift colors.
    float timer;
    //This controls how much we amplify the changes made on x-axis and the y-axis by the noise functions in the Grid class.
    //Bigger Y makes taller peaks and lower troughs
    //Bigger X makes the waves more aggressive and go farther forward. 
    float ampX, ampY;
    //This sets the X position of the camera to be the same as the moon so the moon is always centered.
    int camMoonX;
   
    

  
};
