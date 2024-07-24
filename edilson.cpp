#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <string>

#include "converttxt.h"
#include "analizador.h"


using namespace std;


const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 600;
const float BUTTON_SCALE = 1.06f;

void escribirInstruccion(int numero, std::ofstream& archivo) {
    switch (numero) {
        case 1:
            archivo << "avanzar;" << std::endl;
            break;
        case 2:
            archivo << "girarDerecho;" << std::endl;
            break;
        case 3:
            archivo << "girarIzquierda;" << std::endl;
            break;
        case 4:
            archivo << "encender;" << std::endl;
            break;
        default:
            std::cerr << "Número inválido en el array: " << numero << std::endl;
            break;
    }
}

void guardarInstrucciones(int* array, int tamaño,int* array2, int tamaño2,int* array3, int tamaño3, const std::string& nombreArchivo, int iter) {
    std::ofstream archivo(nombreArchivo, std::ios::out);
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo para escribir." << std::endl;
        return;
    }
    archivo << "iniciar()" << std::endl;
    for (int i = 0; i < tamaño; ++i) {
        escribirInstruccion(array[i], archivo);
        if(array[i] == 5){
            for (int j = 0; j < tamaño2; ++j) {
                escribirInstruccion(array2[j], archivo);
            }
        }
        if(array[i] == 6){
            for(int g = 0; g < iter; ++g){
                for (int k = 0; k < tamaño3; ++k) {
                    escribirInstruccion(array3[k], archivo);
                    if(array3[k] == 5){
                        for (int m = 0; m < tamaño2; ++m) {
                            escribirInstruccion(array2[m], archivo);
                        }
                    }
                }
            }
        }
    }
    archivo << "." << std::endl;

    archivo.close();
}

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

void FIFOdelete(int array[], int& tamano) {
    for (int i = tamano - 1; i >= 0; --i) {
        if (array[i] != 0) {
            array[i] = 0;
            break; 
        }
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
    static int esc = 30;
    static int esc2 = 30;
    
    sf::RectangleShape button(sf::Vector2f(esc, esc));
    sf::RectangleShape button2(sf::Vector2f(esc2, esc2));
    button.setPosition((offsetX + (0 % 4) * imageWidth) - 40, offsetY + (0 / 4) * imageHeight);
    button2.setPosition((offsetX + (0 % 4) * imageWidth) - 40, (offsetY + (0 / 4) * imageHeight) + 40);
    button.setFillColor(!estado ? sf::Color::Red : sf::Color::Red);
    button2.setFillColor(!estado ? sf::Color::Green : sf::Color::Yellow);

    static bool buttonPressed = false;
    static bool button2Pressed = false;
    
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        if (button.getGlobalBounds().contains(mousePosF) && !buttonPressed) {
            buttonPressed = true;
            FIFOdelete(array,tamano);
            button.setFillColor(sf::Color::White);
            esc = 28;
        }

        if (button2.getGlobalBounds().contains(mousePosF) && !button2Pressed) {
            button2Pressed = true;
            estado = !estado; // Cambia el estado
            esc2 = 28;
        }
    } else if (event.type == sf::Event::MouseButtonReleased) {
        if(buttonPressed){
            buttonPressed = false; // Reinicia el estado al soltar el botón
            esc = 30;
        }
        if(button2Pressed){
            button2Pressed = false; // Reinicia el estado al soltar el botón
            esc2 = 30;
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
    for (int i = 0; i < size; ++i) {
        if (array[i] == 0) {
            array[i] = valor;
            break;
        }
    }
}

void scaleOnHover(sf::Sprite& sprite, sf::RenderWindow& window) {
    if (sprite.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        sprite.setScale(0.9f, 0.9f);
    } else {
        sprite.setScale(0.8f, 0.8f);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "MakyBot");

    //contador
    sf::Texture textures[6];
    for (int i = 0; i < 6; ++i) {
        if (!textures[i].loadFromFile("images/" + std::to_string(i) + ".png")) {
            std::cerr << "Error cargando la imagen " << i << ".png" << std::endl;
            return -1;
        }
    }

    sf::Texture iniciarTexture;
    sf::Texture incrementTexture;
    sf::Texture decrementTexture;
    if (!iniciarTexture.loadFromFile("images/go.png" )|| !incrementTexture.loadFromFile("images/imageincrement.png" )|| !decrementTexture.loadFromFile("images/imagendecrement.png")) {
        std::cerr << "Error cargando la imagen imageincrement.png o decrement" << std::endl;
        return -1;
    }

    int clicks = 0;
    sf::Sprite iniciarButton(iniciarTexture);
    iniciarButton.setPosition(420, 480);
    string lenguajeintermedio;

    // imagenes del contador
    int conty = 485;
    int counter = 0; //importante
    sf::Sprite numberSprite(textures[counter]);
    numberSprite.setPosition(620, conty);

    sf::Sprite incrementButton(incrementTexture);
    incrementButton.setPosition(620, conty-20); // Encima del contador

    sf::Sprite decrementButton(decrementTexture);
    decrementButton.setPosition(620, conty+43);

    // Cargar texturas
    std::vector<sf::Texture> buttonTexture(7);

    if (!buttonTexture[0].loadFromFile("images/vacio.png") ||
        !buttonTexture[5].loadFromFile("images/f1.png") ||
        !buttonTexture[3].loadFromFile("images/giroleft.png") ||
        !buttonTexture[2].loadFromFile("images/giroright.png") ||
        !buttonTexture[1].loadFromFile("images/avanzar.png") ||
        !buttonTexture[6].loadFromFile("images/bucle.png") ||
        !buttonTexture[4].loadFromFile("images/foco.png") 

        ) {
        return -1;
    }

    std::vector<Button> buttons(6);
    buttons[0] = {sf::Sprite(buttonTexture[6]), 6};
    buttons[1] = {sf::Sprite(buttonTexture[5]), 5};
    buttons[2] = {sf::Sprite(buttonTexture[4]), 4};
    buttons[3] = {sf::Sprite(buttonTexture[3]), 3};
    buttons[4] = {sf::Sprite(buttonTexture[2]), 2};
    buttons[5] = {sf::Sprite(buttonTexture[1]), 1};
    
    

    for (size_t i = 0; i < buttons.size(); ++i) {
        buttons[i].sprite.setPosition(WINDOW_WIDTH - buttons[i].sprite.getGlobalBounds().width * (i + 1) - 10 * i, 10);
    }

    sf::Sprite centralSprite;
    centralSprite.setTexture(buttonTexture[0]);
    centralSprite.setPosition(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);
    centralSprite.setOrigin(buttonTexture[0].getSize().x / 2.f, buttonTexture[0].getSize().y / 2.f);

    std::vector<int> pressedButtons;
    int mainbot[12] = {0,0,0,0,0,0,0,0,0,0,0,0};//importante
    int f1bot[8] = {0,0,0,0,0,0,0,0};
    int buclebot[4] = {0,0,0,0};

    bool boolmain = false; bool boolf1 = false; bool boolbucle = false;
    bool clicDerechoPresionado = false; 

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (iniciarButton.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
                    counter++;
                    guardarInstrucciones(mainbot, 12,f1bot, 8,buclebot, 4, "instrucciones.txt", counter);
                    lenguajeintermedio = txtConvertstring("instrucciones.txt");
                    analizadorSyx(lenguajeintermedio);
                    cout << lenguajeintermedio << endl;
                    numberSprite.setTexture(textures[counter]);
                }
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
                            InsertarInstru(f1bot,8,button.id );
                            imprimirArray(f1bot,8);
                        }
                        if(boolbucle){
                            InsertarInstru(buclebot,4,button.id );
                            imprimirArray(buclebot,4);
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
        scaleOnHover(iniciarButton, window);
        
        scaleOnHover(incrementButton, window);
        scaleOnHover(decrementButton, window);

        window.clear();
        window.draw(iniciarButton);
        window.draw(numberSprite);
        window.draw(incrementButton);
        window.draw(decrementButton);
        for (const auto& button : buttons) {
            window.draw(button.sprite);
        }
        dibujarImagenes(window, buttonTexture, mainbot, sizeof(mainbot) / sizeof(mainbot[0]), 720, 100,event, boolmain);
        dibujarImagenes(window, buttonTexture, f1bot, sizeof(f1bot) / sizeof(f1bot[0]), 720, 320,event, boolf1);
        dibujarImagenes(window, buttonTexture, buclebot, sizeof(buclebot) / sizeof(buclebot[0]), 720, 470,event, boolbucle);
        window.draw(centralSprite);
        
        window.display();
    }

    return 0;
}