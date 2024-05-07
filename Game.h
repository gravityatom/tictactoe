#ifndef GAME_H
#define GAME_H


#include "Rectangle.h"
#include <iostream>

class Game {
    Rectangle **r;

    void AIMove() {
        if (!playerX) { // playerX = false
            bool moveMade = 0;
            for (int i = 0; i < count; i++) {
                for (int j = 0; j < count; j++){
                    if (r[i][j].isEmpty()) {
                        std::cout << "playing ij" << i << " " << j << std::endl;
                        r[i][j].playO();
                        moveMade = 1;
                        break;
                    }
                }
                if (moveMade){
                    break;
                }
            }
            playerX = !playerX; // set playerX to true
        }
        if (checkWinner()){
            std::cout << "winner" << std::endl;
        }
    }


public:
   // TODO: Create setter and getter functions for these variables and put them back to private
    bool playerX;
    bool AI;
    int count;
    int numGrid = 3;
    int clickedSquares = 0;

    void init(){
        playerX = true;
        r = new Rectangle*[count];
        for (int i = 0; i < count; i++){
            r[i] = new Rectangle[count];
        }

        float x = -0.9;
        float y = 0.9;

        float w = 1.8 / count;
        float h = 1.5 / count;

        // Initialize your state variables
        for (int i = 0; i < count; i++){
            x = -0.9;
            for (int j = 0; j < count; j++){
                r[i][j] = Rectangle(x, y, w, h);
                x += w;
            }
            y -= h;
        }
        start();
    }

    Game() {
        count = 3;
        init();
    }

    bool checkWinner(){
        std::cout << "Checking for winner" << std::endl;
	//check if there are horizontal win i.e if there is any row that has same value
    // playO means PLAYER_O, playX means PLAYER_X, isEmpty means EMPTY
        for(int i = 0; i <= 2; i++){ 
            for(int j = 1; j <= 2; j++){
                if(r[i][0].state != EMPTY && r[i][0].state == r[i][j].state){
                    if(j == 2){
                        return true;
                    }     
                }
                else{
                    break;
                }      
            }
        }
    
    //check if there are vertical win i.e if there is any column that has same value
        for(int i = 0; i <= 2; i++){
            for(int j = 1; j <= 2; j++){
                if(r[0][i].state != EMPTY && r[0][i].state == r[j][i].state){
                    if(j == 2){
                        return true;
                    }       
                }
                else{
                    break;
                }     
            }
        }

    //check if there is any diagonal win i.e. if there is any diagonals that has same value
        for(int i = 1; i <= 2; i++){
            if(r[0][0].state != EMPTY && r[0][0].state == r[i][i].state){
                if(i == 2){
                    return true;
                }		
            }
            else{
                break;
            }   
        }
        for(int i = 1; i <= 2; i++){
            if(r[2][0].state != EMPTY && r[2][0].state == r[2 - i][i].state){
                if(i == 2){
                    return true;
                }		
            }
            else{
                break;
            }    
        }
        return false;
    }


    void AIOn() {
        AI = true;
        AIMove();
    }

    void AIOff() {
        AI = false;
    }

    void playerXFirst() {
        playerX = true;
    }

    void playerOFirst() {
        playerX = false;
    }

    void start() {
        if (AI) {
            AIMove();
        }
    }



    void handleMouseClick(float x, float y) {
        std::cout << "Clicking on board" << std::endl;
        for (int i = 0; i < count; i++) {
            for (int j = 0; j < count; j++){
                if (r[i][j].contains(x,  y)) {
                    if (r[i][j].isEmpty()) {
                        if (playerX) {
                            r[i][j].playX();
                            clickedSquares++;
                            std::cout << "x move:" << clickedSquares << std::endl;
                        }
                        else {
                            r[i][j].playO();
                            clickedSquares++;
                            std::cout << "o move:" << clickedSquares << std::endl;
                        }
                    } 
                    playerX = !playerX;
                    break;
                }
            }
        }

        if (AI) {
            std::cout << "Ai's move" << std::endl;
            AIMove();
            clickedSquares++;
            std::cout << "ai move:" << clickedSquares << std::endl;
        }

        if (checkWinner()){
            std::cout << "winner" << std::endl;
        }

        if (clickedSquares == numGrid){
            std::cout << "max moves reached" << clickedSquares << std::endl;
        }
    }

    void draw() {
        for (int i = 0; i < count; i++){
            for(int j = 0; j < count; j++){
                r[i][j].draw();
            }
        } 
    }
};

#endif