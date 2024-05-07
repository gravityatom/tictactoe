#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <iostream>
#include "AppController.h"
#include "Rectangle.h"
#include "Button.h"
#include "Game.h"

class Controller : public AppController {
    // State variables needed for you app
    Rectangle **r;
    Game game;
    
    Button startButton;
    Button exitButton;
    Button aiButton;
    Button playerButton;

    Button button3;
    Button button4;
    Button button5;

    Button gameOverButton;
    Button backButton;
    Button playAgainButton;
    Button winnerButton;

    bool gameEnabled = 0;
    int gameGrid = 4;
    bool gameMode = 0;
    int count = gameGrid;
    
public:
    Controller(){

        startButton     = Button("Start", -0.2, 0.5);
        exitButton      = Button("Exit", -0.2, -0.5);
        aiButton        = Button("vs. AI", -0.2, 0.3);
        playerButton    = Button("vs. Player", -0.2, 0.1);

        button3         = Button("3 x 3", -0.6, -0.2);
        button4         = Button("4 x 4", -0.2, -0.2);
        button5         = Button("5 x 5", 0.2, -0.2);

        backButton      = Button("Back to Start",0.2, -0.7);

        gameOverButton  = Button("GAME OVER", -0.2, 0.2);
        playAgainButton = Button("Play Again ? Click Back to start", -0.7, 0.0);
        winnerButton    = Button("Winner Detected", -0.5, 0.2);  
    }

    void leftMouseDown( float x, float y ){
        if (gameEnabled == 1){
            game.handleMouseClick(x, y);
            if (backButton.contains(x, y)){
                gameEnabled = 0;
                game.clickedSquares = 0;
            }
        }
       
        else{
            if (startButton.contains(x, y)){
                gameEnabled = 1;
                game.numGrid = game.count * game.count; 
                std::cout << "board size " << game.numGrid << std::endl;
                std::cout << "Game Starting" << std::endl;
                game.clickedSquares = 0;
                game.init();  
            }

            if (aiButton.contains(x, y)){
                std::cout << "Vs. AI" << std::endl;
                game.AIOn();
            }

            if (playerButton.contains(x, y)){
                std::cout << "Vs. Player" << std::endl;
                game.AIOff();
            }

            if (exitButton.contains(x, y)){
                exit(EXIT_SUCCESS);
            }

            if (button3.contains(x, y)){
                std::cout << "Will change to 3x3" << std::endl;
                game.handleMouseClick(x, y);
                game.count = 3;   
            }

            else if (button4.contains(x, y)){
                std::cout << "Will change to 4x4" << std::endl;
                game.handleMouseClick(x, y);
                game.count = 4; 
            }

            else if (button5.contains(x, y)){
                std::cout << "Will change to 5x5" << std::endl;
                game.handleMouseClick(x, y);
                game.count = 5;
            }
        }
    }

    void render() {
        // Render some graphics

        if(gameEnabled == 1){
            glClearDepth(1);
            game.draw();
            backButton.draw();
        }

        else{
            button3.draw();
            button4.draw();
            button5.draw();

            startButton.draw();
            exitButton.draw();
            aiButton.draw();
            playerButton.draw();
        }
        
        if (gameEnabled == 1 && game.clickedSquares >= game.numGrid){
            if(!game.checkWinner()){
                std::cout << "Display game over" << std::endl;
                // gameOverButton.draw();
                backButton.draw();
                playAgainButton.draw();
            }
        }

        if(gameEnabled == 1 && game.checkWinner()){
            std::cout << "Winner found" << std::endl;
            winnerButton.draw();
            backButton.draw();
            playAgainButton.draw();  
        }
    }
};

#endif