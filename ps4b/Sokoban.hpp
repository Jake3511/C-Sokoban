// Copyright 2023
// By Jake Shick
// main.cpp for PS4b
#include <vector>
#include <iterator>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <SFML/Graphics.hpp>

const int GRID_SIZE = 64;
enum Direction {
  Up,
  Right,
  Left,
  Down
};

class Sokoban : public sf::Drawable {
 public:
  Sokoban();
  Sokoban(int h, int w, std::ifstream &file);
  friend std::istream &operator >>(std::istream &cin, Sokoban &s1);
  void movePlayer(Direction player);
  bool isWon() const;
  sf::Texture getText(int i, int j);
  sf::Vector2i getNextPos(Direction player, sf::Vector2i pos);
  sf::Vector2i getPreviousPos(Direction player, sf::Vector2i pos);
  bool isNoWall(int x, int y);
  void setOriginal();
  int height();
  int width();

 private:
  int size_x;
  int size_y;
  sf::Texture texture_ground;
  sf::Texture texture_player;
  sf::Texture texture_wall;
  sf::Texture texture_crate;
  sf::Texture texture_push_block;
  sf::Texture texture_filled;
  sf::Vector2i track_player;
  std::vector <sf::Vector2i> track_wall;
  std::vector <sf::Vector2i> track_crate;
  std::vector <sf::Vector2i> track_filled_ground;
  void virtual draw(sf::RenderTarget &window, sf::RenderStates states) const;
  std::vector <std::vector<char> > two_d_array;
};
