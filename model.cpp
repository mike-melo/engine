#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <string>

#include "model.hpp"

#include "assimp/Importer.hpp"      
#include "assimp/scene.h"           
#include "assimp/postprocess.h" 

#include "GL/glew.h"

using namespace std;

Model::Model(const std::string& modelFileName) {            
  this->load(modelFileName);
}

void Model::load(const std::string& modelFileName) {
  Assimp::Importer importer;
  const aiScene* scene = importer.ReadFile( modelFileName, 
        aiProcess_Triangulate );
        
  printf ("  %i animations\n", scene->mNumAnimations);
  printf ("  %i cameras\n", scene->mNumCameras);
  printf ("  %i lights\n", scene->mNumLights);
  printf ("  %i materials\n", scene->mNumMaterials);
  printf ("  %i meshes\n", scene->mNumMeshes);
  printf ("  %i textures\n", scene->mNumTextures);
  
  const aiMesh* mesh = scene->mMeshes[0];
  
  if(mesh->HasPositions()) {
   for(unsigned int i = 0; i<mesh->mNumVertices; i++) {
     const aiVector3D* vp = &(mesh->mVertices[i]);
     this->points.push_back(vp->x);
     this->points.push_back(vp->y);
     this->points.push_back(vp->z);              
   }                          
  }
}

void Model::prepare() {
  unsigned int vbo = 0;
  glGenBuffers (1, &vbo);
  glBindBuffer (GL_ARRAY_BUFFER, vbo);

  glBufferData (GL_ARRAY_BUFFER, this->points.size() * sizeof (float), &this->points.front(), GL_STATIC_DRAW); 

  glGenVertexArrays (1, &this->vao);
  glBindVertexArray (this->vao);
  glEnableVertexAttribArray (0);
  glBindBuffer (GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void Model::render() {
  glBindVertexArray (this->vao);
  glDrawArrays (GL_TRIANGLES, 0, this->points.size());     
}

Model::~Model() {
}   

