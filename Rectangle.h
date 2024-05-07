#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <GL/freeglut.h>
#include <GL/gl.h>
#include "Color.h"
#include "Shape.h"
#include <cmath>


enum RectangleState {EMPTY, PLAYER_X, PLAYER_O};

class Rectangle : public Shape{

    float w;
    float h;
    float size;
    Color color;
    bool solid;

public:
    RectangleState state;
    Rectangle() {
        x = 0.0f;
        y = 0.0f;
        w = 0.4f;
        h = 0.2f;
        selected = false;
        solid = true;
        state = EMPTY;
        size = 0.4f;
    }

    Rectangle(float x, float y, float w, float h, Color color) {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        this->color = color;
        this->size = 0.4f;
        selected = false;
        solid = true;
        state = EMPTY;
    }
    Rectangle(float x, float y, float w, float h) {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        selected = false;
        solid = false;
        this->size = 0.4f;
        state = EMPTY;
    }

    bool isEmpty(){
        return state == EMPTY;
    }

    void playX(){
        state = PLAYER_X;
    }

    void playO(){
        state = PLAYER_O;
    }

    void draw() {
        if (!solid){
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }

        glColor3f(color.getR(), color.getG(), color.getB());
        glBegin(GL_POLYGON);
            glVertex2f(x, y);
            glVertex2f(x + w, y);
            glVertex2f(x + w, y - h);
            glVertex2f(x, y - h);
        glEnd();

        
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        if (state == PLAYER_X) {
            glBegin(GL_LINES);
                glVertex2f(x + 0.1f, y - 0.1f);
                glVertex2f(x + size - 0.1f, y - size + 0.1f);

                glVertex2f(x + size - 0.1f, y - 0.1f);
                glVertex2f(x + 0.1f, y - size + 0.1f);
            glEnd();  
        }
         else if (state == PLAYER_O) {
            glBegin(GL_LINES);
                float inc = (2 * M_PI) / 60;
                for (float theta = 0; theta <= 2 * M_PI; theta += inc) {
                    glVertex2f((x + (size / 2)) + (size / 2 - 0.1f) * cos(theta), (y - (size / 2)) + (size / 2 - 0.1f) * sin(theta));
                    glVertex2f((x + (size / 2)) + (size / 2 - 0.1f) * cos(theta + inc), (y - (size / 2)) + (size / 2 - 0.1f) * sin(theta + inc));
                }
            glEnd();
        }
    }

    bool contains(float mx, float my) {
        if (mx >= x && mx <= x + w && my <= y && my >= y - h) {
            return true;
        } else {
            return false;
        }
    }
    
    void setColor(Color color){
        this->color = color;
    }

    void setW(float w){
        this->w = w;
    }

    void setH(float h){
        this->h = h;
    }

    float getW(){
        return w;
    }

    float getH(){
        return h;
    }

};

#endif