#include <array>
#include <SFML/Graphics.hpp>
#include "tagged.hpp"
#include "sequence.hpp"
#include "collide.hpp"
#include "world.hpp"

static void stop(const pkmn::composite &e) {
    if (pkmn::get<pkmn::movement>(e)) {
        pkmn::get<pkmn::movement>(e)->vector = sf::Vector2f(0.0f, 0.0f);
    }
}

int main(int argc, char *argv[]) {
    sf::RenderWindow window(sf::VideoMode(320, 240), "PKMNEngine");
    window.setFramerateLimit(60);
    
    sf::Texture texture;
    texture.loadFromFile("rsrc/player.png");
    
    sf::View view;
    view.reset(sf::FloatRect(0.0f, 0.0f, 320.0f, 240.f));
    
    std::array<sf::Sprite,4> downarray = {
        sf::Sprite(texture, sf::IntRect(32, 0, 32, 32)),
        sf::Sprite(texture, sf::IntRect(0, 0, 32, 32)),
        sf::Sprite(texture, sf::IntRect(64, 0, 32, 32)),
        sf::Sprite(texture, sf::IntRect(0, 0, 32, 32)),
    };
    auto down = pkmn::makeseq(downarray.begin(), downarray.end());
    
    std::array<sf::Sprite,4> leftarray = {
        sf::Sprite(texture, sf::IntRect(32, 32, 32, 32)),
        sf::Sprite(texture, sf::IntRect(0, 32, 32, 32)),
        sf::Sprite(texture, sf::IntRect(64, 32, 32, 32)),
        sf::Sprite(texture, sf::IntRect(0, 32, 32, 32)),
    };
    auto left = pkmn::makeseq(leftarray.begin(), leftarray.end());
    
    std::array<sf::Sprite,4> rightarray = {
        sf::Sprite(texture, sf::IntRect(32, 64, 32, 32)),
        sf::Sprite(texture, sf::IntRect(0, 64, 32, 32)),
        sf::Sprite(texture, sf::IntRect(64, 64, 32, 32)),
        sf::Sprite(texture, sf::IntRect(0, 64, 32, 32)),
    };
    auto right = pkmn::makeseq(rightarray.begin(), rightarray.end());
    
    std::array<sf::Sprite,4> uparray = {
        sf::Sprite(texture, sf::IntRect(32, 96, 32, 32)),
        sf::Sprite(texture, sf::IntRect(0, 96, 32, 32)),
        sf::Sprite(texture, sf::IntRect(64, 96, 32, 32)),
        sf::Sprite(texture, sf::IntRect(0, 96, 32, 32)),
    };
    auto up = pkmn::makeseq(uparray.begin(), uparray.end());
    
    pkmn::grid grid;
    pkmn::world world(grid, view.getSize());
    
    pkmn::composite player;
    
    pkmn::insert(player, pkmn::geometry(down.at(0)));
    pkmn::insert(player, pkmn::animation(*pkmn::get<pkmn::geometry>(player), down));
    pkmn::insert(player, pkmn::movement(sf::Vector2f(0.0f, 0.0f), 0.1f, [&](const sf::Vector2f &dm){pkmn::get<pkmn::geometry>(player)->move(dm);}));
    auto at = pkmn::insert(player, pkmn::timer(false, 160, std::ref(*pkmn::get<pkmn::animation>(player))));
    pkmn::insert(player, pkmn::timer(true, 0, std::ref(*pkmn::get<pkmn::movement>(player))));
    pkmn::insert(player, pkmn::sensor(sf::FloatRect(0.0f, 0.0f, 32.0f, 32.0f)));
    pkmn::insert(world, player);

    pkmn::composite obstacle;
    pkmn::insert(obstacle, pkmn::geometry(down.at(0)));
    pkmn::insert(obstacle, pkmn::sensor(sf::FloatRect(0.0f, 0.0f, 32.0f, 32.0f), stop));
    pkmn::insert(world, obstacle);
    
    pkmn::get<pkmn::geometry>(obstacle)->setPosition(96.0f, 96.0f);
    pkmn::get<pkmn::geometry>(player)->setPosition(64.0f, 64.0f);
    
    sf::Clock frameClock;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        
        sf::Time frameTime = frameClock.restart();
        
        if (pkmn::get<pkmn::movement>(player)->vector == sf::Vector2f(0.0f, 0.0f)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                pkmn::get<pkmn::animation>(player)->frames = &down;
                pkmn::get<pkmn::animation>(player)->reset();
                pkmn::get<pkmn::movement>(player)->vector = sf::Vector2f(0.0f, 32.0f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                pkmn::get<pkmn::animation>(player)->frames = &up;
                pkmn::get<pkmn::animation>(player)->reset();
                pkmn::get<pkmn::movement>(player)->vector = sf::Vector2f(0.0f, -32.0f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                pkmn::get<pkmn::animation>(player)->frames = &left;
                pkmn::get<pkmn::animation>(player)->reset();
                pkmn::get<pkmn::movement>(player)->vector = sf::Vector2f(-32.0f, 0.0f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                pkmn::get<pkmn::animation>(player)->frames = &right;
                pkmn::get<pkmn::animation>(player)->reset();
                pkmn::get<pkmn::movement>(player)->vector = sf::Vector2f(32.0f, 0.0f);
            }
        }
        
        if (pkmn::get<pkmn::movement>(player)->vector != sf::Vector2f(0.0f, 0.0f)) { 
            pkmn::unwrap<pkmn::timer>(at).enabled = true;
        } else {
            pkmn::unwrap<pkmn::timer>(at).enabled = false;
            pkmn::get<pkmn::animation>(player)->reset(true);
        }
        
        view.setCenter(pkmn::get<pkmn::geometry>(player)->getPosition() + sf::Vector2f(32.0f, 32.0f));
        window.setView(view);

        window.clear();
        
        pkmn::reseat(world, player);
        
        std::array<pkmn::grid::iterator,4> quadrants = {
            world.find(sf::Vector2i(view.getCenter().x - view.getSize().x / 2, 
                                    view.getCenter().y - view.getSize().y / 2)),
            world.find(sf::Vector2i(view.getCenter().x + view.getSize().x / 2,
                                    view.getCenter().y - view.getSize().y / 2)),
            world.find(sf::Vector2i(view.getCenter().x - view.getSize().x / 2,
                                    view.getCenter().y + view.getSize().y / 2)),
            world.find(sf::Vector2i(view.getCenter().x + view.getSize().x / 2,
                                    view.getCenter().y + view.getSize().y / 2))
        };
        
        std::sort(quadrants.begin(), quadrants.end(), [](const pkmn::grid::iterator &lhs, const pkmn::grid::iterator &rhs){return &(*lhs) < &(*rhs);});
        
        for (auto begin = quadrants.begin(), end = std::unique(quadrants.begin(), quadrants.end()); begin != end; ++begin) {
            if (*begin != grid.end()) {
                for (auto cursor1 = (*begin)->second.begin(), end = (*begin)->second.end(); cursor1 != end; ++cursor1) {
                    for (auto cursor2 = cursor1; cursor2 != end; ++cursor2) {
                        pkmn::collide(**cursor1, **cursor2);
                    }
                    for (auto range = pkmn::equal_range<pkmn::timer>(**cursor1); range.first != range.second; ++range.first) {
                        pkmn::unwrap<pkmn::timer>(range.first).update(frameTime.asMilliseconds());
                    }
                    window.draw(*pkmn::get<pkmn::geometry>(**cursor1));
                }
            }
        }

        window.display();
    }
    
    return 0;
}

