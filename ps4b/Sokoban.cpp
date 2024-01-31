// Copyright 2023
// By Jake Shick
// main.cpp for PS4b
#include "Sokoban.hpp"
Sokoban::Sokoban() {
    size_y = 0;
    size_x = 0;
    texture_ground.loadFromFile("ground_01.png");
    texture_player.loadFromFile("player_05.png");
    texture_wall.loadFromFile("block_06.png");
    texture_crate.loadFromFile("crate_03.png");
    texture_push_block.loadFromFile("ground_04.png");
    texture_filled.loadFromFile("ground_04.png");
}

std::istream &operator >>(std::istream &cin, Sokoban &s1) {
    cin >> s1.size_y >> s1.size_x;
    s1.texture_ground.loadFromFile("ground_01.png");
    s1.texture_player.loadFromFile("player_05.png");
    s1.texture_wall.loadFromFile("block_06.png");
    s1.texture_crate.loadFromFile("crate_03.png");
    s1.texture_push_block.loadFromFile("ground_04.png");
    s1.texture_filled.loadFromFile("ground_04.png");
    for (int i = 0; i < s1.size_y; i++) {
        std::vector <char> v1;
        for (int j = 0; j < s1.size_x; j++) {
            char c;
            cin >> c;
            v1.push_back(c);
            if (c == '@') {
                s1.track_player = {j, i};
            } else if (c == '#') {
                s1.track_wall.push_back({j, i});
            } else if (c == 'A') {
                s1.track_crate.push_back({j, i});
            } else if (c == 'a') {
                s1.track_filled_ground.push_back({j, i});
            }
        }
        s1.two_d_array.push_back(v1);
    }
    return cin;
}

void Sokoban::movePlayer(Direction player) {
    track_player = getNextPos(player, track_player);
    if (!(isNoWall(track_player.x, track_player.y))) {
        track_player = getPreviousPos(player, track_player);
    }
    size_t size_crate = track_crate.size();
    for (size_t i = 0; i < size_crate; i++) {
        if (track_player == track_crate.at(i)) {
            track_crate.at(i) = getNextPos(player, track_player);
        }
        // Checks to see if box is hitting a wall (Box going through wall fix)
        if (!(isNoWall(track_crate.at(i).x, track_crate.at(i).y))) {
            track_player = getNextPos(player, track_player);
            track_crate.at(i) = getPreviousPos(player, track_player);
            track_player = getPreviousPos(player, track_player);
        }
        // (Player goes through box fix)
        if (track_player.x == track_crate.at(i).x && track_player.y == track_crate.at(i).y) {
            track_player = getPreviousPos(player, track_player);
        }
        // (Boxes go through each other fix)
        sf::Vector2i first_crate_pos = track_crate.at(i);
        for (size_t j = 0; j < size_crate; j++) {
            if (i != j && first_crate_pos == track_crate.at(j)) {
                track_crate.at(i) = getPreviousPos(player, track_crate.at(i));
                track_player = getPreviousPos(player, track_player);
            }
        }
        // (Player can't go off map)
        if (track_player.x == size_x || track_player.y == size_y || track_player.x == -1
        || track_player.y == -1) {
            track_player = getPreviousPos(player, track_player);
        }
        // (Boxes can't go off map and adjusts player position)
        for (size_t j = 0; j < size_crate; j++) {
            if ((first_crate_pos.x == size_x || first_crate_pos.y == size_y
            || first_crate_pos.x == -1 || first_crate_pos.y == -1) && i != j) {
                first_crate_pos = track_crate.at(i);
                first_crate_pos = getPreviousPos(player, first_crate_pos);
                track_crate.at(i) = first_crate_pos;
                track_player = getPreviousPos(player, track_player);
            }
        }
    }
}


sf::Vector2i Sokoban:: getNextPos(Direction player, sf::Vector2i pos) {
    switch (player) {
        case Up:
            texture_player.loadFromFile("player_08.png");
            pos.y--;
            break;

        case Down:
            texture_player.loadFromFile("player_05.png");
            pos.y++;
            break;

        case Right:
            texture_player.loadFromFile("player_17.png");
            pos.x++;
            break;

        case Left:
            texture_player.loadFromFile("player_20.png");
            pos.x--;
            break;
    }
    return pos;
}

sf::Vector2i Sokoban::getPreviousPos(Direction player, sf::Vector2i pos) {
    switch (player) {
        case Up:
            texture_player.loadFromFile("player_08.png");
            pos.y++;
            break;

        case Down:
            texture_player.loadFromFile("player_05.png");
            pos.y--;
            break;

        case Right:
            texture_player.loadFromFile("player_17.png");
            pos.x--;
            break;

        case Left:
            texture_player.loadFromFile("player_20.png");
            pos.x++;
            break;
    }
    return pos;
}
bool Sokoban::isNoWall(int x, int y) {
    for (auto w : track_wall) {
        if (w.x == x && w.y == y) {
            return false;
        }
    }
    return true;
}

bool Sokoban::isWon() const {
    size_t size = track_filled_ground.size();
    for (size_t i = 0; i < size; i++) {
        sf::Vector2i temp = track_filled_ground.at(i);
        for (size_t j = 0; j < size; j++) {
            sf::Vector2i temp2 = track_crate.at(j);
            if (temp != temp2 && i == j) {
                return false;
            }
        }
    }
    return true;
}

void Sokoban::setOriginal() {
    for (int i = 0; i < size_y; i++) {
        for (int j = 0; j < size_x; j++) {
            char c;
            c = two_d_array[i][j];
            if (c == '#') {
                track_wall.pop_back();
            } else if (c == 'A') {
                track_crate.pop_back();
            } else if (c == 'a') {
                track_filled_ground.pop_back();
            }
        }
    }
    for (int i = 0; i < size_y; i++) {
        std::vector <char> v1;
        for (int j = 0; j < size_x; j++) {
            char c;
            c = two_d_array[i][j];
            if (c == '@') {
                track_player = {j, i};
            } else if (c == '#') {
                track_wall.push_back({j, i});
            } else if (c == 'A') {
                track_crate.push_back({j, i});
            } else if (c == 'a') {
                track_filled_ground.push_back({j, i});
            }
        }
        two_d_array.push_back(v1);
    }
}
int Sokoban::height() {
    return size_y;
}
int Sokoban::width() {
    return size_x;
}
void Sokoban::draw(sf::RenderTarget &window, sf::RenderStates states) const {
    sf::Sprite s;
    for (int i = 0; i < size_y; i++) {
        for (int j = 0; j < size_x; j++) {
            char c = two_d_array[i][j];
            if (c == '.') {
                s.setTexture(texture_ground);
            } else if (c == '@') {
                s.setTexture(texture_ground);
            } else if (c == '#') {
                s.setTexture(texture_wall);
            } else if (c == 'A') {
                s.setTexture(texture_ground);
            } else if (c == 'a') {
                s.setTexture(texture_push_block);
            } else if (c == '1') {
                s.setTexture(texture_filled);
            }
            s.setPosition(j * GRID_SIZE, i * GRID_SIZE);
            window.draw(s);
        }
    }
    s.setTexture(texture_player);
    s.setPosition((track_player.x * GRID_SIZE), (track_player.y * GRID_SIZE));
    window.draw(s);

    for (auto i : track_crate) {
        s.setTexture(texture_crate);
        s.setPosition((i.x * GRID_SIZE), (i.y * GRID_SIZE));
        window.draw(s);
    }
}