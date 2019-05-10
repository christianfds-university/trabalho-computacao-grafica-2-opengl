#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <list>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "Particle.hpp"

#define ESCAPE '\033'

GLint Width = 600, Height = 600;

list<Particle *> O_List;

void Display(void)
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    for (auto const &i : O_List)
    {
        i->move(O_List);
        i->draw();
    }

    glutSwapBuffers();
    glutPostRedisplay();
}

void Reshape(GLint w, GLint h)
{
    Width = w;
    Height = h;
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    for (auto const &i : O_List)
    {
        i->limit_x = w;
        i->limit_y = h;
    }
}

void Keyboard(unsigned char key, int x, int y)
{
    if (key == ESCAPE)
    {
        for (auto const &i : O_List)
        {
            delete i;
        }

        exit(0);
    }
}

void MouseMove(int x, int y)
{
    O_List.front()->pos_x = x;
    O_List.front()->pos_y = Width - y;
}

void MouseActivity(int button, int state, int x, int y)
{
    // Mouse Down
    if (button == 0 && state == 0)
    {
        O_List.front()->carga = !O_List.front()->carga;
    }
    // Scroll Up
    if (button == 3)
    {
        O_List.front()->radius++;
    }
    // Scroll Down
    if (button == 4)
    {
        O_List.front()->radius--;
        if (O_List.front()->radius == 0)
            O_List.front()->radius = 1;
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(Width, Height);
    glutCreateWindow("Trabson2 CG");

    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);
    glutMouseFunc(MouseActivity);
    glutPassiveMotionFunc(MouseMove);

    Particle *x;

    for (int i = 0; i < 50; i++)
    {
        x = new Particle(Width, Height);
        O_List.push_back(x);
    }

    x = new Particle(Width / 2, Height / 2, true, 100, Width, Height);
    O_List.push_front(x);

    glutMainLoop();
}