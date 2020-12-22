//
//  Grid.cpp
//  Sea_of_Emotion
//
//  Created by Tam Nguyen on 2/13/20.
//

#include "Grid.hpp"
//_z controls the z placement of each vertex
void Gridclass::setup(int __z){
    
    
   //index is set to -1 so that the first vertex indexed is 0
       index=-1;
    
    //sets the lineWidth of the mesh
       glLineWidth(3);
    
    //This creates an array of points to create the triangle strip.
    //i controls the x-axis placement of the vertices
       for(int i=0; i<300; i++){
           
           grid.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
           
           //This set of commands creates 2 vertices starting with one below and then one above before moving along the x axis and repeating.
           //After each individual vertex is added the Index is increased and an index is added for that Vertex.
           
           grid.addVertex(glm::vec3(i*20, 0, __z*20));
           grid.addColor(oceanColor);
           index++;
           grid.addIndex(index);
         grid.addVertex(glm::vec3(i*20, 0, (__z+1)*20));
           index++;
               grid.addColor(oceanColor);
           grid.addIndex(index);
       }
    
}

//_z controls the z placement of the vertices
//_baseY controls the base Y-level of the ocean
//_ampX and _ampY control the amplification of the changes made to their respective axis
void Gridclass::update(int _z, int _baseY, float _ampX, float _ampY, float _waveSpeed){
    //chugs the timer along
    noiseTime+=0.01+_waveSpeed;
    
            //sets the U(pdate)Index to 0
             UIndex = 0;
    

            for(int j =0; j < 300; j++){
                
                //this is the noise function that controls the waves
                float myNoise = 20.0*ofSignedNoise(_z/40.0+noiseTime/6, j/40.0-noiseTime/3, noiseTime/3);
                
              
            
          
                //sets the oceanColor
                   if(myNoise >=0){
                                 oceanColor.set(ofMap(myNoise, 0,0, 40, 20),ofMap(myNoise, 0,20, 60, 255),ofMap(myNoise, 0,20, 120, 255));
                   }else{
                       oceanColor.set(ofMap(myNoise, -20,0, 40, 40),ofMap(myNoise, -20,0, 21, 60),ofMap(myNoise, -20,0, 60, 120));
                   }
               

                
                //Sets the vertex based upon the U(pdate)Index value and the brightness of the pixel color previously generated
                    grid.setVertex(UIndex, glm::vec3(j * 20+(myNoise*_ampX), _baseY+(myNoise*_ampY), _z*20+(myNoise*2)));
                
                
                //sets the color of the ocean
                  grid.setColor(UIndex,oceanColor);


            
                
                UIndex++;
                
                //this gets the pixel color for the next vertex in the index
               myNoise = 20.0*ofSignedNoise((_z+1)/40.0+noiseTime/6, j/40.0-noiseTime/3, noiseTime/3);
              
                
                //sets the ocean color
             if(myNoise >=0){
                                                       oceanColor.set(ofMap(myNoise, 0,0, 40, 20),ofMap(myNoise, 0,20, 60, 255),ofMap(myNoise, 0,20, 120, 255));
                                         }else{
                                    oceanColor.set(ofMap(myNoise, -20,0, 40, 40),ofMap(myNoise, -20,0, 21, 60),ofMap(myNoise, -20,0, 60, 120));
                                         }
           
                //sets the vertex and the color of the next vertex in the index
                 grid.setVertex((UIndex), glm::vec3(j * 20+(myNoise*_ampX), _baseY+(myNoise*_ampY), (_z+1)*20+(myNoise*2)));
                 grid.setColor(UIndex,oceanColor);

                
                UIndex++;
                      
                

         
    }
      
}
void Gridclass::draw(bool _meshState){
    
    
 //draws the wireframe or the solid mesh
    grid.drawWireframe();
    if(_meshState==false){
    grid.draw();
    }

    
}

