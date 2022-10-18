#ifndef WIRESPUZZLE_H
#define WIRESPUZZLE_H

#include "room.h"
#include "roomArrow.h"
#include "cursor.h"
#include "gameMenu.h"
#include "gameItem.h"

// first room puzzle
class WiressPuzzle: public Room {
    private:
        RenderWindow* store;
        RoomArrow* buttons;
        GameItem* options;
        bool mainWall;
        int nOptions;
    public:
        // constructor
        WiressPuzzle(RenderWindow* win) {
            // initialises room settings
            setRoom(480,270);
            active = false;
            store = win;
            //mainWall = true;

            // defines the number of arrows and defines each one
            buttons = new RoomArrow[2];
            buttons[0].setPosition(win,1500,0);
            buttons[1].setPosition(win,100,0);
            buttons[1].flipButton();
        
            // creates the clickable buttons
            options = new GameItem(13,13,6);

            
            
        }

        // draws the room and items
        void draw(RenderWindow* win) {
            if (active) {
                win->draw(*background);
                if (mainWall) {
                    buttons[0].draw(win);
                    options->draw(win);
                } else if (!mainWall) {
                    buttons[1].draw(win);
                }
            }
        }
        
        // handles button presses
        void buttonPress(Mouse_Cursor* cursor, Event e) {
            if (buttons[0].highlightSprite(cursor->getSprite(),200,0) && active && mainWall) {
                if (e.type == Event::MouseButtonPressed) {
                    // moves to new screen
                    if (e.mouseButton.button == Mouse::Left) {
                        setRoom(160,90);
                        mainWall = false;
                    }   
                }
            } else if (buttons[1].highlightSprite(cursor->getSprite(),200,0) && active && !mainWall) {
                if (e.type == Event::MouseButtonPressed) {
                    // moves back to original
                    if (e.mouseButton.button == Mouse::Left) {
                        setRoom(160,0);
                        mainWall = true;
                    }
                } 
            } else if (options->highlightSprite(cursor->getSprite(),0,40) && active && mainWall) {
                if (e.type == Event::MouseButtonPressed) {
                    // correct answer
                    if (e.mouseButton.button == Mouse::Left) {
                        active = false;
                    }
                }
            } /* else if (options[1].highlightSprite(cursor->getSprite(),13,40) && active && mainWall) {
                // does nothing
            } else if (options[2].highlightSprite(cursor->getSprite(),26,40) && active && mainWall) {
                // does nothing
            }*/
        }
        
        // returns the state of the room
        bool getStatus() {
            return active;
        }

        ~ChessPuzzle() {}
};

#endif