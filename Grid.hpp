//
//  Grid.hpp
//  Sea_of_Emotion
//
//  Created by Tam Nguyen on 2/13/20.
//

#ifndef Grid_hpp
#define Grid_hpp

#include <stdio.h>
#include <ofMain.h>

//this class creates a single triangle strip mesh

class Gridclass{
public:
    
    //__z controls the z value of the vertices
    void setup(int __z);
    //_z controls the z placement of the vertices
    //baseY sets the base Y-value for the ocean
    //_ampx and _ampY controls the amplification of the changes made to their respective axises
    //_wavespeed increases the speed of the ocean
    void update(int _z, int baseY, float _ampX, float _ampY, float _waveSpeed);
    //_meshState controls whether a wireframe or a solid mesh is displayed
    void draw(bool _meshState);
    //creates the mesh
    ofMesh grid;
    
    //index is the counter I use to set the index of each Vertex and UIndex is the index counter I use in the UPDATE section of the code.
    int index, UIndex;
    //sets the Ocean Color
    ofColor oceanColor;
    //timer for the noise system that creates the waves
    float noiseTime;


};


#endif /* Grid_hpp */
