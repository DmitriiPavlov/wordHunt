#include "globals.h"
#include "raylib.h"
#include "solver.h"
#include <string>
#ifndef boardVisuals_h
#define boardVisuals_h

class Board{
public:
    char array [BOARD_WIDTH][BOARD_HEIGHT];
    
    int x,y,w,h;
    
    void drawBoard(){
        for (int i = 0; i<= BOARD_WIDTH; i++){
            DrawLine(x + i*w/BOARD_WIDTH, y, x + i*w/BOARD_WIDTH, y+h, BLACK);
        }
        
        for (int j = 0; j<= BOARD_HEIGHT; j++){
            DrawLine(x, y + j*h/BOARD_HEIGHT, x+w, y + j*h/BOARD_HEIGHT, BLACK);
        }
        
        for (int i = 0; i < BOARD_WIDTH; i++){
            for (int j = 0; j < BOARD_HEIGHT; j++){
                //i know this sucks, and don't know a better way to do this
                std::string text;
                text.push_back(array[i][j]);
                DrawText(text.c_str(), x + i*w/BOARD_WIDTH + h/(6*BOARD_HEIGHT), y + j*h/BOARD_HEIGHT + h/(6*BOARD_HEIGHT), h/BOARD_HEIGHT  , BLACK);
            }
        }
    }
    
    //should be called before hand
    //we just make the square that it starts on yellow or sum
    //and then we just draw a line
    
    void drawPath(std::vector<Pos> path){
        int squareHeight = h/BOARD_HEIGHT;
        int squareWidth = w/BOARD_WIDTH;
    
        DrawRectangle(x + path[0].x * squareWidth, y + path[0].y * squareHeight, squareWidth, squareHeight, YELLOW);
        
        for( int i = 1; i< path.size(); i++){
            Vector2 firstVec;
            firstVec.x = x + path[i-1].x*squareWidth + squareWidth/2;
            firstVec.y = y + path[i-1].y*squareHeight +squareHeight/2;
            
            Vector2 secondVec;
            secondVec.x = x + path[i].x*squareWidth + squareWidth/2;
            secondVec.y = y + path[i].y*squareHeight +squareHeight/2;
            DrawLineEx(firstVec, secondVec, 10.0, RED);
        }
    }
//
    Pos clickedOnSquare(int mousex, int mousey){
        int squareHeight = h/BOARD_HEIGHT;
        int squareWidth = w/BOARD_WIDTH;
        
        return Pos( (mousex - x)/squareWidth , (mousey - y)/squareHeight );
    }
    

    bool isClickedOn(int mousex, int mousey){
        return x<mousex && mousex < x+w &&  y<mousey && mousey < y+h;
    }
    
};


#endif
