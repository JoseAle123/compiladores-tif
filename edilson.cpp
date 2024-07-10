#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
using namespace std;


const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 600;
const float BUTTON_SCALE = 1.06f;

void imprimirArray(int array[], int size) {
    std::cout << "Contenido del array: ";
    for (int i = 0; i < size; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

void Inicializar(int arr[], int size) {

    for (int i = 0; i < size; ++i) {
        arr[i] = 0;
    }
}
// Función para dibujar las imágenes en base al array
void dibujarImagenes(sf::RenderWindow& window, const std::vector<sf::Texture>& texturas, int array[], int tamano, int xx, int yy, sf::Event event , bool &estado ) {
    // Tamaño de cada imagen (asumimos que todas tienen el mismo tamaño)
    sf::Vector2u imageSize = texturas[0].getSize();
    int imageWidth = imageSize.x;
    int imageHeight = imageSize.y;

    int offsetX = xx; // Desplazamiento en x
    int offsetY = yy; // Desplazamiento en y

    for (int i = 0; i < tamano; ++i) {
        if (array[i] >= 0 && array[i] < texturas.size()) {
            sf::Sprite sprite(texturas[array[i]]);
            sprite.setPosition(offsetX + (i % 4) * imageWidth, offsetY + (i / 4) * imageHeight);
            window.draw(sprite);
        } else {
            std::cerr << "Valor de índice fuera de rango: " << array[i] << std::endl;
        }
    }
    sf::RectangleShape button(sf::Vector2f(30, 30));
    sf::RectangleShape button2(sf::Vector2f(30, 30));
    button.setPosition((offsetX + (0 % 4) * imageWidth) - 40, offsetY + (0 / 4) * imageHeight);
    button2.setPosition((offsetX + (0 % 4) * imageWidth) - 40, (offsetY + (0 / 4) * imageHeight) + 40);
    button.setFillColor(sf::Color::Red);
    button2.setFillColor(sf::Color::Green);
    
    if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                if (button.getGlobalBounds().contains(mousePosF)) {
                    if (button.getFillColor() == sf::Color::Red) {
                        button.setFillColor(sf::Color::Green);
                        Inicializar(array,tamano);
                        estado = false;
                    } else {
                        button.setFillColor(sf::Color::Red);
                    }
                }
                if (button2.getGlobalBounds().contains(mousePosF)) {
                    if (button2.getFillColor() == sf::Color::Green) {
                        button2.setFillColor(sf::Color::Yellow);
                        estado = true;
                    } else {
                        button2.setFillColor(sf::Color::Green);
                    }
                }
                
            }

    window.draw(button);
    window.draw(button2);
    
}

struct Button {
    sf::Sprite sprite;
    int id;
    bool isHovered = false;
};

void InsertarInstru(int array[], int size, int valor) {
    bool encontrado = false;
    for (int i = 0; i < size; ++i) {
        if (array[i] == 0) {
            array[i] = valor;
            break;
        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Botones con Imagen Central");


    // Cargar texturas
    std::vector<sf::Texture> buttonTexture(5);

    if (!buttonTexture[0].loadFromFile("images/vacio.png") ||
        !buttonTexture[4].loadFromFile("images/f1.png") ||
        !buttonTexture[1].loadFromFile("images/giroleft.png") ||
        !buttonTexture[2].loadFromFile("images/giroright.png") ||
        !buttonTexture[3].loadFromFile("images/avanzar.png")
        ) {
        return -1;
    }

    std::vector<Button> buttons(4);
    buttons[0] = {sf::Sprite(buttonTexture[4]), 4};
    buttons[1] = {sf::Sprite(buttonTexture[1]), 1};
    buttons[2] = {sf::Sprite(buttonTexture[2]), 2};
    buttons[3] = {sf::Sprite(buttonTexture[3]), 3};
    

    for (size_t i = 0; i < buttons.size(); ++i) {
        buttons[i].sprite.setPosition(WINDOW_WIDTH - buttons[i].sprite.getGlobalBounds().width * (i + 1) - 10 * i, 10);
    }

    sf::Sprite centralSprite;
    centralSprite.setTexture(buttonTexture[0]);
    centralSprite.setPosition(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);
    centralSprite.setOrigin(buttonTexture[0].getSize().x / 2.f, buttonTexture[0].getSize().y / 2.f);

    std::vector<int> pressedButtons;
    int mainbot[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
    int f1bot[4] = {0,0,0,0};
    bool boolmain = false; bool boolf1 = false;
    bool clicDerechoPresionado = false; 

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Procesar interacción del ratón
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        for (auto& button : buttons) {
            sf::FloatRect bounds = button.sprite.getGlobalBounds();
            if (bounds.contains(static_cast<sf::Vector2f>(mousePos))) {
                if (!button.isHovered) {
                    button.sprite.setScale(BUTTON_SCALE, BUTTON_SCALE);
                    button.isHovered = true;
                }


                else if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        clicDerechoPresionado = true;
                        centralSprite.setTexture(*button.sprite.getTexture());
                    }
                } else if (event.type == sf::Event::MouseButtonReleased) {
                    if (event.mouseButton.button == sf::Mouse::Left && clicDerechoPresionado == true ) {
                        if(boolmain){
                            InsertarInstru(mainbot,12,button.id );
                            imprimirArray(mainbot,12);
                        }
                        if(boolf1){
                            InsertarInstru(f1bot,4,button.id );
                            imprimirArray(f1bot,4);
                        }
                        clicDerechoPresionado = false;
                    }
                }
                

            } else {
                if (button.isHovered) {
                    button.sprite.setScale(1.f, 1.f);
                    button.isHovered = false;
                }
            }
        }

        window.clear();
        for (const auto& button : buttons) {
            window.draw(button.sprite);
        }
        dibujarImagenes(window, buttonTexture, mainbot, sizeof(mainbot) / sizeof(mainbot[0]), 720, 100,event, boolmain);
        dibujarImagenes(window, buttonTexture, f1bot, sizeof(f1bot) / sizeof(f1bot[0]), 720, 320,event, boolf1);
        window.draw(centralSprite);
        
        window.display();
    }

    return 0;
}