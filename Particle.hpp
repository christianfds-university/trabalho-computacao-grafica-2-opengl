#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <iostream>
#include <list>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "util.hpp"

using namespace std;

const float G = 6.67300;
// const float atrito = 1E-4;
const float atrito = 0;
const float max_speed = 15;

const int radius_delta = 3;

class Particle
{
private:
	void *id;

public:
	double pos_x;
	double pos_y;

	double speed_x = 0;
	double speed_y = 0;

	double radius = 5;

	double t_angle;
	double t_d;

	bool carga;
	bool is_mouse = false;

	int limit_x, limit_y;

	Particle(int limit_x, int limit_y);
	Particle(bool carga, int limit_x, int limit_y);
	Particle(double pos_x, double pos_y, int limit_x, int limit_y);
	Particle(double pos_x, double pos_y, bool carga, int limit_x, int limit_y);
	Particle(double pos_x, double pos_y, bool carga, double radius, int limit_x, int limit_y);

	void move(std::list<Particle *> l);
	void draw();

	void *get_id()
	{
		return this->id;
	}

	void difference(Particle *p, double *d, double *a);

	~Particle();
};

Particle::Particle(int limit_x, int limit_y){
	this->pos_x = util::randomNumberI() % limit_x;
	this->pos_y = util::randomNumberI() % limit_y;
	this->limit_x = limit_x;
	this->limit_y = limit_y;

	this->radius = 10 + (util::randomNumberI() % 2 ? 1 : -1) * util ::randomNumberI() % radius_delta;

	this->id = this;
	this->carga = util::randomNumberI() % 2;
}

Particle::Particle(bool carga, int limit_x, int limit_y){
	this->pos_x = util::randomNumberI() % limit_x;
	this->pos_y = util::randomNumberI() % limit_y;
	this->limit_x = limit_x;
	this->limit_y = limit_y;

	this->radius = 10 + (util::randomNumberI() % 2 ? 1 : -1) * util ::randomNumberI() % radius_delta;

	this->id = this;
	this->carga = carga;
}

Particle::Particle(double pos_x, double pos_y, int limit_x, int limit_y){
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	this->limit_x = limit_x;
	this->limit_y = limit_y;

	this->radius = 10 + (util::randomNumberI() % 2 ? 1 : -1) * util ::randomNumberI() % radius_delta;

	this->id = this;
	this->carga = util::randomNumberI() % 2;
}

Particle::Particle(double pos_x, double pos_y, bool carga, int limit_x, int limit_y){
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	this->limit_x = limit_x;
	this->limit_y = limit_y;

	this->radius = 10 + (util::randomNumberI() % 2 ? 1 : -1) * util ::randomNumberI() % radius_delta;

	this->id = this;
	this->carga = carga;
}

Particle::Particle(double pos_x, double pos_y, bool carga, double radius, int limit_x, int limit_y){
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	this->limit_x = limit_x;
	this->limit_y = limit_y;

	this->radius = radius;
	this->is_mouse = true;

	this->id = this;
	this->carga = carga;
}

void Particle::move(std::list<Particle *> l){
	if (!this->is_mouse)
	{

		double angle, distance, forca;
		double acc_x, acc_y;

		acc_x = acc_y = 0;

		// Calcula a aceleração pra cada particula
		for (auto const &i : l) {
			if (i->get_id() != this->id)
			{
				this->difference(i, &distance, &angle);
				if (distance != 0)
				{
					forca = (G * this->radius * i->radius * 1E-2) / (distance * distance);

					// Caso seja de carga igual, inverte o angulo
					if (this->carga == i->carga)
					{
						angle += -M_PI;
					}

					this->t_angle = angle;
					this->t_d = distance;

					acc_x += forca * cos(angle);
					acc_y += forca * sin(angle);
				}
			}
		}

		this->speed_x += acc_x;
		this->speed_y += acc_y;

		// Limita a velocidade
		if (abs(this->speed_x) > max_speed) {
			this->speed_x = max_speed * (this->speed_x > 0 ? 1 : -1);
		}
		if (abs(this->speed_y) > max_speed) {
			this->speed_y = max_speed * (this->speed_y > 0 ? 1 : -1);
		}

		// Aplica o atrito
		this->speed_x -= (this->speed_x > 0 ? 1 : -1) * atrito;
		this->speed_y -= (this->speed_y > 0 ? 1 : -1) * atrito;

		// Realiza a movimentação
		this->pos_x += this->speed_x;
		this->pos_y += this->speed_y;


	// Limite de raio de cada elipse
		/*
		for (auto const &i : l) {
			if (i->get_id() != this->id) {
				this->difference(i, &distance, &angle);

				double min_d = this->radius + i->radius;
				if (distance <= min_d) {
					double d_x, d_y;
					d_x = this->pos_x - i->pos_x;
					d_y = this->pos_y - i->pos_y;

					printf("d_y: %lf\n", d_y);
					printf("  d: %lf\n", distance);
					printf("m_d: %lf\n", min_d);

					printf("r_1: %lf\n", this->radius);
					printf("r_2: %lf\n", i->radius);

					printf("d_x: %lf\n", d_x);


					if(!this->is_mouse){
						if(d_x < min_d)
							this->pos_x = i->pos_x + min_d*cos(angle - M_PI);

						if(d_y < min_d)
							this->pos_y = i->pos_y + min_d*sin(angle - M_PI);
					}

					/*
					printf("n_d_x: %lf\n", this->pos_x - i->pos_x);
					printf("n_d_y: %lf\n", this->pos_y - i->pos_y);
				}
			}
		}
		*/
	}



	// Limites de tela
	if (this->pos_x > this->limit_x - (this->radius))
	{
		this->pos_x = this->limit_x - (this->radius);
		this->speed_x = 0;
	}
	if (this->pos_y > this->limit_y - (this->radius))
	{
		this->pos_y = this->limit_y - (this->radius);
		this->speed_y = 0;
	}
	if (this->pos_x < 0 + (this->radius))
	{
		this->pos_x = 0 + (this->radius);
		this->speed_x = 0;
	}
	if (this->pos_y < 0 + (this->radius))
	{
		this->pos_y = 0 + (this->radius);
		this->speed_y = 0;
	}
}	

void Particle::draw(){
	if (this->carga)
		glColor3ub(0, 0, 255);
	else
		glColor3ub(255, 0, 0);

	glBegin(GL_LINE_LOOP);

	for (int i = 0; i <= 360; i++)
	{
		float degInRad = i * util::DEG2RAD;
		glVertex2f(cos(degInRad) * this->radius + this->pos_x, sin(degInRad) * this->radius + this->pos_y);
	}

	glEnd();

	// if(this->is_mouse){
		glBegin(GL_LINE_LOOP);
		glVertex2f(this->pos_x, this->pos_y);
		glVertex2f(this->pos_x, this->pos_y+1);

		// glVertex2f(this->pos_x-1, this->pos_y-1);
		// glVertex2f(this->pos_x, this->pos_y-1);
		// glVertex2f(this->pos_x+1, this->pos_y-1);
		// glVertex2f(this->pos_x+1, this->pos_y);
		// glVertex2f(this->pos_x+1, this->pos_y+1);
		// glVertex2f(this->pos_x, this->pos_y+1);
		// glVertex2f(this->pos_x-1, this->pos_y+1);
		// glVertex2f(this->pos_x-1, this->pos_y+2);

		glEnd();
	// }

	// ANGULO DEBUG
	/*
	glPushMatrix();

	glColor3ub(255, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(this->pos_x, this->pos_y);
	glVertex2f(this->pos_x + cos(t_angle) * t_d, this->pos_y + sin(t_angle) * t_d);
	glEnd();

	glPopMatrix();
	*/
}

void Particle::difference(Particle *p, double *d, double *a){
	double dx = this->pos_x - p->pos_x;
	double dy = this->pos_y - p->pos_y;

	*d = sqrt((dx * dx) + (dy * dy));
	if (dx == 0)
		*a = atan(0);
	else
		*a = atan(dy / dx);
	// Por algum motivo quando o dx > 0 o angulo ta dando ruim '-'
	if (dx > 0)
	{
		*a += -M_PI;
	}
}

Particle::~Particle(){
}

#endif