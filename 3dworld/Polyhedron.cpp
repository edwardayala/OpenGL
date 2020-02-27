// Edward Ayala
#include <GL/glut.h>  // (or others, depending on the system in use)

#include "Polyhedron.h"


Polyhedron::Polyhedron(string _fname, Vector3d _c, double _rotY, Vector3d _clr) : ObjLoader(_fname) {
  //cout << "Polyhedron constructor. " << endl;
  center = _c;
  rotY = _rotY;
  color = _clr;
}

Polyhedron::Polyhedron(const Polyhedron& other) {
  //cout << "Polyhedron copy constructor. " << endl;
  center = other.center;
  rotY = other.rotY;
  color = other.color;
  filename = other.filename;
  //////////////////////////////////////////////////////////
  //other data from obj loader

  verts = other.verts;
  vts = other.vts;
  vns = other.vns;
  faces = other.faces;
}

void Polyhedron::Recenter() {
  //TODO 
  double centerX, centerY, centerZ;

  for (int i = 0; i < faces.size(); i++)
  {
    for (int j = 0; j < faces[i].ids.size(); j++)
    {
      centerX = verts[faces[0].ids[0] - 1].GetX() / 2;
      centerY = verts[faces[1].ids[1] - 1].GetY() / 2;
      centerZ = verts[faces[2].ids[2] - 1].GetZ() / 2;
      cout << "v" << j << " = " << verts[faces[i].ids[j]-1] << endl;
      cout << "center: " << centerX << "," << centerY << "," << centerZ << endl << endl;
    } 
  }
  

}

void Polyhedron::RecenterXZ() {
  //TODO 
}

void Polyhedron::Draw() {
  //TODO 
  // cout << "Polyhedron::Draw color = " << color << endl;
  glBegin(GL_TRIANGLES);
  for (int i = 0; i < faces.size(); i++)
  {
    // faces[i].Print();
    for (int j = 0; j < faces[i].ids.size(); j++)
    {
      // cout << "v" << j << " = " << verts[faces[i].ids[j]-1] << endl;
      glVertex3d(verts[faces[i].ids[j] - 1].GetX(),
                 verts[faces[i].ids[j] - 1].GetY(),
                 verts[faces[i].ids[j] - 1].GetZ());
    }
  }
  glEnd();
}
