#include "ofApp.h"

//SEE APP.H FIRST

//--------------------------------------------------------------

void ofApp::setup(){
    
       //these variables set for the range of the eye, adapting to what shocked and angry looks like on each person
    minEye=-0.2;
    maxEye=0.5;
    midEye=(minEye+maxEye)/2;
    
    // load the first model
    skull.loadModel("Skull.obj", 20);
    // model info
    curFileInfo = ".obj";
    shadow.loadModel("Skull.obj", 20);
    curFileInfo = ".obj";
    
    skullColor.set(0, 255,255);
    
    
    // Setup grabber
       grabber.setup(1280,720);
              
    // Setup tracker
    tracker.setup();
    
    //This is setting the base amplitudes for the X and Y vertices of the waves
    ampX=4;
    ampY=5;
    
    //this sets the base ocean level on the Y-axis
       baseY=100;
    
    //this is generating random colors for the stars.
    hred11=ofRandom(255);
    hgreen11=ofRandom(255);
    hblue11=ofRandom(255);
    hred21=ofRandom(255);
    hgreen21=ofRandom(255);
    hblue21=ofRandom(255);
    lred12=ofRandom(255);
    lgreen12=ofRandom(255);
    lblue12=ofRandom(255);
    lred22=ofRandom(255);
    lgreen22=ofRandom(255);
    lblue22=ofRandom(255);
    
    //this starts the timer at 0 for the noise functions for the stars
    timer=0;
   
    //sets the camera to the middle of the ocean
    camMoonX=2500;
  cam.setPosition(camMoonX, 300, 4200);
    
//this makes it so that the ocean is shown as a wireframe rather than a texture
   wires=true;
    
    
//Grid SETUP
    //i controls the z position of the vertices

    for(int i=1; i<nGrids; i++){
             grid[i].setup(i);
         }
        
 
    //This creates 1000 stars
  for(int x = 0; x< 10; x++){
            for(int y = 0; y< 10; y++){
                for(int z = 0; z< 10; z++){
                    //calculate the index for the orb
                    int currOrb = ((x*10)+y)*10+z;
                   
                    //This sets the position of each star
                    //Only generates stars within 6000 of camMoonX
                    orbs[currOrb].setPosition(ofRandom(camMoonX-6000,camMoonX+6000), ofRandom(0, 4000), ofRandom(-2200, -2500)); //position the orb
                    
                    
                    orbs[currOrb].setRadius(10); //set the size of the orbs
                }
            }
        }
    }


//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();

       // Update tracker when there are new frames
       if(grabber.isFrameNew()){
           tracker.update(grabber);
       }
    
    //starts a for loop for each face
    for (auto face : tracker.getInstances()){
        
       //gets landmarks for faces
        ofxFaceTracker2Landmarks markers = face.getLandmarks();
        
        
        //gets the positions of the mouth parts
         lMouthCorner = markers.getImagePoint(48);
         rMouthCorner = markers.getImagePoint(64);
         MouthCenter = markers.getImagePoint(66);
        lCMouth = markers.getImagePoint(50);
        rCMouth = markers.getImagePoint(52);
        mouthTop = markers.getImagePoint(62);
        mouthBottom = markers.getImagePoint(66);
        
        //this finds out how open the mouth is
        distMouthOpen = ofDist(mouthTop.x, mouthTop.y, mouthBottom.x, mouthBottom.y);
        
       //this finds out the distance between the two corners of the mouth
    distLeftMouthRight=ofDist(lMouthCorner.x,lMouthCorner.y, rMouthCorner.x,rMouthCorner.y);
        
        //This finds the distance between the two peaks on the upper lip to give a point of relativity
        distCenterMouth=ofDist(lCMouth.x, lCMouth.y, rCMouth.x, rCMouth.y);
        
        //this finds the ratio between the distance between the corners of the mouth to the distance between the two peaks of the upper lip
        MouthRatio+= ((distLeftMouthRight/distCenterMouth)-MouthRatio)*0.03;
        
       //this finds the ratio between how open the mouth is and the two peaks of the upper lip.
        MouthOpenRatio+=((distMouthOpen/distCenterMouth)-MouthOpenRatio)*0.03;
        
        
      if(MouthOpenRatio>0.4 and MouthOpenRatio<0.65){
      
      }
        if(MouthOpenRatio>=0.65){
                  
        }
        std::cout<<"Dist:"<<distLeftMouthRight<<endl;
        std::cout<<"Ratio:"<<MouthRatio<<endl;
        std::cout<<"OpenRatio:"<<MouthOpenRatio<<endl;
        
        
       
        //Gets the position of the (left/right)(Eye/Brow)(Center/edge)
    lEyeC = markers.getImagePoint(39);
    lEyeE = markers.getImagePoint(36);
        
    rEyeC = markers.getImagePoint(42);
    rEyeE = markers.getImagePoint(45);
        
    lBrowC = markers.getImagePoint(21);
    lBrowE = markers.getImagePoint(17);
    rBrowC = markers.getImagePoint(22);
    rBrowE = markers.getImagePoint(26);
        
  
        //Gets the distance between the corresponding brow and eye points
        lDistE = ofDist(lEyeE.x, lEyeE.y, lBrowE.x, lBrowE.y);
        lDistC = ofDist(lEyeC.x, lEyeC.y, lBrowC.x, lBrowC.y);
        
        rDistE = ofDist(rEyeE.x, rEyeE.y, rBrowE.x, rBrowE.y);
        rDistC = ofDist(rEyeC.x, rEyeC.y, rBrowC.x, rBrowC.y);
        
        //This finds how high the center of the brow is relative to the edge of the brow and then sets the value for 'level' at 0
        lRatio += ((lDistC/lDistE)-1-lRatio)*0.05;
        rRatio += ((rDistC/rDistE)-1-rRatio)*0.05;
        
     
        
//This is the smoothing equation for the average eyebrow height
        averageBrowtoEye += (((lRatio+rRatio)/2)-averageBrowtoEye) *0.05;
        
        
        //this redefines the mininum distance from rest that the eyebrows need to be in order to be considered worried or angry
        midEye=(maxEye-((maxEye-minEye)/2));
        
        //this adjusts the max brow to Eye ratio so that it remains fairly reactive
        
        if(averageBrowtoEye>maxEye ){
            maxEye+=((averageBrowtoEye-maxEye)*0.005);
            averageBrowtoEye=maxEye;
        }
        
        if(averageBrowtoEye<maxEye-0.4){
            maxEye+=(((averageBrowtoEye+0.35)-maxEye)*0.003);
        }
        std::cout<<"MaxEye:"<<maxEye<<endl;
        
        
        //this adjusts the min brow to eye ratio so that it remains fairly reactive
        if(averageBrowtoEye<minEye ){
        minEye+=((averageBrowtoEye-minEye)*0.005);
            averageBrowtoEye=minEye;
        }
        
        if(averageBrowtoEye>minEye+0.4){
            minEye+=(((averageBrowtoEye+0.35)-minEye)*0.001);
        }
        std::cout<<"MinEye:"<<minEye<<endl;
        
    }

    //this is the section for a shocked expression (eyebrows raised)
    if(averageBrowtoEye>=(midEye*0.57)){
       
        //this increases the wavespeed based on how shocked the eyebrows are
        waveSpeed+=((ofMap(averageBrowtoEye, (midEye*0.57), maxEye, 0, 0.03)-waveSpeed)*0.01);
       
        //this increases the wave height based on the eyebrows
        waveHeight=ofMap(averageBrowtoEye, (midEye*0.57), maxEye, 0, 4);
       
       //this changes the color of the skull to a lime yellow from blue based on eyebrows
        skullColor.set(ofMap(averageBrowtoEye, (midEye*0.57), maxEye, 0, 244), ofMap(averageBrowtoEye, (midEye*0.57), maxEye, 255, 255), ofMap(averageBrowtoEye, (midEye*0.57), maxEye, 255, 0));
        
    }
    
    //this section does the control for an angry expression (eyebrows furrowed)
    if(averageBrowtoEye<=(midEye*0.29)){
       
        //wavespeed controls
        waveSpeed += ((ofMap(averageBrowtoEye, (midEye*0.29), minEye, 0, 0.03))-waveSpeed)*0.01;
        
        //waveheight controls
        waveHeight = ofMap(averageBrowtoEye, (midEye*0.29), minEye, 0, 4);
       
        //increases the reach of the waves
        waveReach = ofMap(averageBrowtoEye, (midEye*0.29), minEye, 0, 4);
       
        //sets the color of the skull to switch from blue to red
        skullColor.set(ofMap(averageBrowtoEye, (midEye*0.29), minEye, 0, 209), ofMap(averageBrowtoEye, (midEye*0.29), minEye, 255, 0), ofMap(averageBrowtoEye, (midEye*0.29), minEye, 255, 29));
    }
    
    
    //this is vertical and horizontal height of the waves
    ampY+=((5+waveHeight)-ampY)*0.05;
    ampX=((4+waveReach)-ampX)*0.05;
    
    //this chugs the timer along
       timer+=0.03;
    
    
    
    
   
  //i controls the Z-Value of the vertices
    //baseY sets the base-level of the ocean
    //ampX and ampY control the amplification of changes made on their respective axis.
 
    for(int i=1; i<nGrids; i++){
             grid[i].update(i, baseY, ampX, ampY, waveSpeed);
         }

}
  

//--------------------------------------------------------------
void ofApp::draw(){

   //sets the background as black
    ofBackground(0);
    //draws things in front last
    ofEnableDepthTest();

    cam.begin();
    

 
//i selects the orb to have its color changed
    for(int i = 0; i<1000; i++){
        //these noise functions just cause the stars to twinkle by switching between 8 (i think) colors
        float Noisew = ofSignedNoise(i/30.0+timer/6, timer/3);
        float Noisex = ofSignedNoise(i/60.0+timer/6, timer/3);
        float Noisey = ofSignedNoise(i/40.0+timer/6, timer/3);
        
    
   
        //Sub-units of Color
        _Red=ofMap(Noisew, -1,1,hred, lred);
         _Green=ofMap(Noisew, -1,1,hgreen, lgreen);
         _Blue=ofMap(Noisew, -1,1,hblue, lblue);
        
        //sub units of _Color
        hred=ofMap(Noisex, -1,1, hred1, hred2);
        hgreen=ofMap(Noisex, -1,1, hgreen1, hgreen2);
        hblue=ofMap(Noisex, -1,1, hblue1, hblue2);
        
        lred=ofMap(Noisex, -1,1, lred1, lred2);
        lgreen=ofMap(Noisex, -1,1, lgreen1, lgreen2);
        lblue=ofMap(Noisex, -1,1, lblue1, lblue2);
        
        //Sub-units of (h/l)color
        hred1=ofMap(Noisey, -1,1, hred11, hred12);
        hgreen1=ofMap(Noisey, -1,1, hgreen11, hgreen12);
        hblue1=ofMap(Noisey, -1,1, hblue11, hblue12);
        
        lred1=ofMap(Noisey, -1,1, lred11, lred12);
        lgreen1=ofMap(Noisey, -1,1, lgreen11, lgreen12);
        lblue1=ofMap(Noisey, -1,1, lblue11, lblue12);
        
        hred2=ofMap(Noisey, -1,1, hred21, hred22);
        hgreen2=ofMap(Noisey, -1,1, hgreen21, hgreen22);
        hblue2=ofMap(Noisey, -1,1, hblue21, hblue22);
                     
        lred2=ofMap(Noisey, -1,1, lred21, lred22);
        lgreen2=ofMap(Noisey, -1,1, lgreen21, lgreen22);
        lblue2=ofMap(Noisey, -1,1, lblue21, lblue22);
       
        //Sets the actual color for the individual star
        starz.set(_Red, _Green, _Blue);
        ofSetColor(starz);
          
            
        
            
             orbs[i].draw();//draw all the orbs
         }
    
    //wires controls whether a wire frame is displayed or a solid mesh
     for(int i=1; i<nGrids; i++){
      grid[i].draw(wires);
      }
    
    cam.end();
    cam.draw();
    MOON=true;
 ofPushStyle();

   

       // Iterate over all faces
       for(auto face : tracker.getInstances()){
           MOON=false;
           // Apply the pose matrix
           ofPushView();
           face.loadPoseMatrix();

     

           ofPushMatrix();
           
           //these set up the skull model
               ofSetColor(skullColor);
               skull.drawWireframe();
               skull.setPosition(100, -50, 00);
               skull.setScale(ofMap(MouthOpenRatio, 0.1, 1.1, 0.2, 0.8),ofMap(MouthOpenRatio, 0.1, 1.1, 0.2, 0.8),ofMap(MouthOpenRatio, 0.1, 1.1, 0.2, 0.8));
               skull.setRotation(0, 90, 1, 0, 0);
           ofPopMatrix();

           ofPushMatrix();
           //these set up the shadow skull model
           ofSetColor(0, 0, 0);
           shadow.drawFaces();
           shadow.setPosition(100, -50, 0);
           shadow.setScale(ofMap(MouthOpenRatio, 0.1, 1.1, 0.2, 0.8)-0.0000001,ofMap(MouthOpenRatio, 0.1, 1.1, 0.2, 0.8)-0.0000001,ofMap(MouthOpenRatio, 0.1, 1.1, 0.2, 0.8)-0.0000001);
           shadow.setRotation(0, 90, 1, 0, 0);
           ofPopMatrix();

           ofPopView();
       }
       ofPopStyle();
    
    
    if(MOON==true){
        ofSetColor(209, 0, 28);
        ofDrawSphere(850, 150, 0, 100);
        
    }
 
   
    ofDisableDepthTest();
 
    
}

//--------------------------------------------------------------

void ofApp::keyPressed(int key){

    if (key == 'a'){
        wires=false;
    }
    if (key == 'd'){
           wires=true;
       }
}
