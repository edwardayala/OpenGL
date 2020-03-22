// Edward Ayala
#define GL_SILENCE_DEPRECATION
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
  //Recenter() - adjust the coordinates of the model to be centered about (0,0,0). 
  //To do this you should first compute the center of the model and then subtract the center from each vertex stored in the model.
 

  Vector3d com(0,0,0);  // Initialize com (center of mass)
  // Fill Vector3d with values from file
  for (auto &i : verts){
    com += i;
  }
  com /= verts.size();  // reduce vector by the size of the shape?
  cout << "-----------------------" << endl;
  cout << "COM:" << com << endl;
  cout << "-----------------------" << endl;
  // recenter each vector
  for (auto &i : verts){
    i -= com;
  }
}

void Polyhedron::RecenterXZ() {
  //TODO 
  // RecenterXZ() - adjust the coordinates of the model to be centered about (0, Y, 0) where Y is 
  // the original Y center of the model. You can think of this as just adjusting 2D center in the XZ plane.
  Vector3d com(0,0,0);  // Initialize com (center of mass)
  // Fill Vector3d with values from file
  for (auto &i : verts){
    com += i;
  }
  com /= verts.size();  // reduce vector by the size of the shape?
  cout << "-----------------------" << endl;
  cout << "COM:" << com << endl;
  cout << "-----------------------" << endl;
  // recenter X and Z
  for (auto &i : verts){
    i.SetX(i.GetX() - com.GetX());
    i.SetZ(i.GetZ() - com.GetZ());
  }
}

Vector3d Polyhedron::computeNormal(Face f) {
  Vector3d p1 = verts[f.ids[0]-1];
  Vector3d p2 = verts[f.ids[1]-1];
  Vector3d p3 = verts[f.ids[2]-1];

  Vector3d U = p2 - p1;
  Vector3d V = p3 - p1;

  double nx = U.GetY() * V.GetZ() - U.GetZ() * V.GetY();
  double ny = U.GetZ() * V.GetX() - U.GetX() * V.GetZ();
  double nz = U.GetX() * V.GetY() - U.GetY() * V.GetX();

  Vector3d Normal(nx,ny,nz);

  return Normal;
}

void Polyhedron::Draw() {
  //TODO 
  /*
  Draw - write the draw function in the Polyhedron class to draw each of the faces 
  (you can assume they are loaded as triangles). This should be a simple loop that 
  iterates through each of the faces and draws a triangle given three vertices that
  define the triangle. Be careful with indexing the vertices as OBJ definition start indexing at 1.
  */
  // cout << "Polyhedron::Draw color = " << color << endl;
  glPushMatrix();

  glTranslated(center.GetX(),center.GetY(),center.GetZ());
  glColor3d(color.GetX(),color.GetY(),color.GetZ());
  glRotated(rotY,0,1,0);

  glBegin(GL_TRIANGLES);
  for (int i = 0; i < faces.size(); i++)
  {
    Face& f = faces[i];
    Vector3d n = computeNormal(f);
    for (int j = 0; j < faces[i].ids.size(); j++)
    {
      // cout << "v" << j << " = " << verts[faces[i].ids[j]-1] << endl;
      glNormal3d(n.GetX(),n.GetY(),n.GetZ());
      glVertex3d(verts[faces[i].ids[j] - 1].GetX(),
                 verts[faces[i].ids[j] - 1].GetY(),
                 verts[faces[i].ids[j] - 1].GetZ());
    }
  }
  glEnd();
  glPopMatrix();
}
