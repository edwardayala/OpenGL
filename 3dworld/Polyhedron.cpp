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
  // double centerX, centerY, centerZ;

  // for (int i = 0; i < faces.size(); i++)
  // {
  //   for (int j = 0; j < faces[i].ids.size(); j++)
  //   {
  //     centerX = verts[faces[0].ids[0] - 1].GetX() / 2;
  //     centerY = verts[faces[1].ids[1] - 1].GetY() / 2;
  //     centerZ = verts[faces[2].ids[2] - 1].GetZ() / 2;
  //     cout << "v" << j << " = " << verts[faces[i].ids[j]-1] << endl;
  //     cout << "center: " << centerX << "," << centerY << "," << centerZ << endl << endl;
  //   } 
  // }

  Vector3d com(0,0,0);
  for (auto &i : verts){
    com += i;
  }
  com /= verts.size();
  cout << "-----------------------" << endl;
  cout << "COM:" << com << endl;
  cout << "-----------------------" << endl;

  for (auto &i : verts){
    i -= com;
  }
}

void Polyhedron::RecenterXZ() {
  //TODO 
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
