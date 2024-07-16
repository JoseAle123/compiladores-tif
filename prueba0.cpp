#include <SFML/Graphics.hpp>
#include <iostream>

// Escalar las imágenes de los botones al pasar el ratón sobre ellas
void scaleOnHover(sf::Sprite& sprite, sf::RenderWindow& window) {
    if (sprite.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        sprite.setScale(0.9f, 0.9f);
    } else {
        sprite.setScale(0.8f, 0.8f);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Contador con SFML");

    // Cargar texturas
    sf::Texture textures[6];
    for (int i = 0; i < 6; ++i) {
        if (!textures[i].loadFromFile("images/" + std::to_string(i) + ".png")) {
            std::cerr << "Error cargando la imagen " << i << ".png" << std::endl;
            return -1;
        }
    }

    sf::Texture incrementTexture;
    if (!incrementTexture.loadFromFile("images/imageincrement.png")) {
        std::cerr << "Error cargando la imagen imageincrement.png" << std::endl;
        return -1;
    }

    sf::Texture decrementTexture;
    if (!decrementTexture.loadFromFile("images/imagendecrement.png")) {
        std::cerr << "Error cargando la imagen imagendecrement.png" << std::endl;
        return -1;
    }

    // Crear sprites
    int conty = 200;
    int counter = 0;
    sf::Sprite numberSprite(textures[counter]);
    numberSprite.setPosition(350, conty);

    sf::Sprite incrementButton(incrementTexture);
    incrementButton.setPosition(350, conty-20); // Encima del contador

    sf::Sprite decrementButton(decrementTexture);
    decrementButton.setPosition(350, conty+43); // Debajo del contador


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (incrementButton.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
                    if (counter < 5) {
                        counter++;
                        numberSprite.setTexture(textures[counter]);
                    }
                }

                if (decrementButton.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
                    if (counter > 0) {
                        counter--;
                        numberSprite.setTexture(textures[counter]);
                    }
                }
            }
        }

        // Escalar botones cuando el ratón pase sobre ellos
        scaleOnHover(incrementButton, window);
        scaleOnHover(decrementButton, window);

        window.clear();
        window.draw(numberSprite);
        window.draw(incrementButton);
        window.draw(decrementButton);
        window.display();
    }

    return 0;
}
