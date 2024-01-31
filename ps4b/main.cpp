// Copyright 2023
// By Jake Shick
// main.cpp for PS4b
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Sokoban.hpp"

int main(int argc, char* argv[]) {
    std::ifstream file;
    file.open(argv[1]);
    Sokoban t;
    file >> t;
    int h = t.height();
    int w = t.width();
    sf::Music happy_wheels;
    if (!happy_wheels.openFromFile("victory_sJDDywi.wav")) {
        std::cout << "Music File could not be opened!" << std::endl;
        return EXIT_FAILURE;
    }
    sf::RenderWindow window(sf::VideoMode(w * GRID_SIZE, h * GRID_SIZE), "Sokoban!");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            Direction player;
            if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
                    player = Up;
                    t.movePlayer(player);
                }

                if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
                    player = Down;
                    t.movePlayer(player);
                }

                if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) {
                    player = Left;
                    t.movePlayer(player);
                }

                if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) {
                    player = Right;
                    t.movePlayer(player);
                }

                if (event.key.code == sf::Keyboard::R) {
                    t.setOriginal();
                }
                if (t.isWon()) {
                    happy_wheels.play();
                    std::cout << "CONGRATS!" << std::endl;
                }
            }
        }
        window.clear();
        window.draw(t);
        window.display();
    }
    return 0;
}
