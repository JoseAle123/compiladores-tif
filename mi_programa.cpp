#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>

#include "mapas.h"

#define PI 3.14159265f

using namespace std;
using namespace sf;

const float lado = 50.f;
const int gridSize = 8;
const float xIso = sqrt(2 * lado * lado);
const float yIso = xIso / 2.f;
const float ladoIso = sqrt(xIso * xIso / 4.f + yIso * yIso / 4.f);
const float angXY = atan2f(xIso, yIso);
const float angYX = atan2f(yIso, xIso);
const Vector2f pos_origin(300.f, 150.f);

Vector2i calculateGridIndices(const Vector2f &position, const Vector2f &gridOrigin)
{
    Vector2f relativePosition = position - gridOrigin;
    // cout<<"posicionxy: "<<position.x<<"  "<<position.y<<endl;
    float ang_c1 = angXY - atan2f(abs(relativePosition.x), relativePosition.y);
    float ang_c2 = 2.f * angXY - ang_c1;
    float distX, distY;
    // cout<<ang_c1*180.f/PI<<endl;
    float hipo = sqrt(relativePosition.x * relativePosition.x + relativePosition.y * relativePosition.y);

    if (relativePosition.x <= 0)
    {
        distX = (hipo / sin(PI - 2.f * angXY)) * sin(ang_c1);
        distY = (hipo / sin(PI - 2.f * angXY)) * sin(ang_c2);
    }
    else
    {
        distY = (hipo / sin(PI - 2.f * angXY)) * sin(ang_c1);
        distX = (hipo / sin(PI - 2.f * angXY)) * sin(ang_c2);
    }
    // cout<<"distancia xy isometricas"<<distX<<" "<<distY<<endl;
    Vector2f transformedPosition(
        distX / ladoIso,
        distY / ladoIso);

    int posXIso = floor(transformedPosition.x);
    int posYISo = floor(transformedPosition.y);

    return Vector2i(posXIso, posYISo);
}



void moveLeft(Vector2f &targetPosition, bool &moving, bool &miraNE, bool &miraNO, bool &miraSO, bool &miraSE, float xIso, float yIso) {
    targetPosition.x -= xIso / 2.f;
    targetPosition.y += yIso / 2.f;
    miraNE = false;
    miraNO = false;
    miraSO = true;
    miraSE = false;
    moving = true;
}

void moveRight(Vector2f &targetPosition, bool &moving, bool &miraNE, bool &miraNO, bool &miraSO, bool &miraSE, float xIso, float yIso) {
    targetPosition.x += xIso / 2.f;
    targetPosition.y -= yIso / 2.f;
    miraNE = true;
    miraNO = false;
    miraSO = false;
    miraSE = false;
    moving = true;
}

void moveUp(Vector2f &targetPosition, bool &moving, bool &miraNE, bool &miraNO, bool &miraSO, bool &miraSE, float xIso, float yIso) {
    targetPosition.x -= xIso / 2.f;
    targetPosition.y -= yIso / 2.f;
    miraNE = false;
    miraNO = true;
    miraSO = false;
    miraSE = false;
    moving = true;
}

void moveDown(Vector2f &targetPosition, bool &moving, bool &miraNE, bool &miraNO, bool &miraSO, bool &miraSE, float xIso, float yIso) {
    targetPosition.x += xIso / 2.f;
    targetPosition.y += yIso / 2.f;
    miraNE = false;
    miraNO = false;
    miraSO = false;
    miraSE = true;
    moving = true;
}


void crearSpritesPiso(Sprite tiles[][gridSize], const int matriz3D[][gridSize], Texture& texturaLozaAzul, Texture& texturaPiso) {
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (matriz3D[i][j] == -1) {
                tiles[i][j].setTexture(texturaLozaAzul);
            } else {
                tiles[i][j].setTexture(texturaPiso);
            }
            tiles[i][j].setPosition(i * lado, j * lado);
        }
    }
}

// Función para crear los sprites de los bloques
void crearSpritesBloques(vector<Sprite>& bloques, const int matriz3D[][gridSize], Texture& texturaBloque) {
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (matriz3D[i][j] != 0) {
                for (int k = 1; k <= matriz3D[i][j]; ++k) {
                    Sprite bloque(texturaBloque);
                    bloque.setPosition(i * lado - (8.0f * k), j * lado - (8.0f * k));
                    bloques.push_back(bloque);
                }
            }
        }
    }
}

// Función para crear los sprites en una matriz 2D
void configurarSprites(sf::Sprite tiles2d[][gridSize], const int matriz2D[][gridSize], sf::Texture& texturaBloque2d, sf::Texture& texturaLozaAzul2D, sf::Texture& texturaPiso2d) {
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (matriz2D[i][j] == 1) {
                tiles2d[i][j].setTexture(texturaBloque2d);
            } else if (matriz2D[i][j] == -1) {
                tiles2d[i][j].setTexture(texturaLozaAzul2D);
            } else {
                tiles2d[i][j].setTexture(texturaPiso2d);
            }

            tiles2d[i][j].setPosition(500 + i * 15, 400 + j * 15);
        }
    }
}


void moveRobot(Sprite& makibot, const Vector2f& targetPosition, Vector2f& currentPosition, float xIso, float yIso)
{
    Vector2f movement(0.f, 0.f);

    if (targetPosition.x > currentPosition.x)
        movement.x = xIso / 2.f / 50.f;
    else if (targetPosition.x < currentPosition.x)
        movement.x = -xIso / 2.f / 50.f;

    if (targetPosition.y > currentPosition.y)
        movement.y = yIso / 2.f / 50.f;
    else if (targetPosition.y < currentPosition.y)
        movement.y = -yIso / 2.f / 50.f;

    makibot.move(movement);
    //currentPosition = makibot.getPosition();  // Actualiza la posición actual después de mover
}


void stopMovement(Sprite& makibot, const Vector2f& targetPosition, const Vector2f& currentPosition, int& currentFrame, bool miraNE, bool miraNO, bool miraSO, bool miraSE, bool& moving, const vector<IntRect>& framesB, const vector<IntRect>& framesF)
{
    if (abs(targetPosition.x - currentPosition.x) < 1.f && abs(targetPosition.y - currentPosition.y) < 1.f)
    {
        moving = false;
        currentFrame = 0;
        makibot.setPosition(targetPosition);
        if (miraNE || miraNO)
        {
            makibot.setTextureRect(framesB[currentFrame]);
            cout << "arriba" << endl;
        }
        else if (miraSE || miraSO)
        {
            makibot.setTextureRect(framesF[currentFrame]);
            cout << "abajo" << endl;
        }
    }
}


void updateBlocks(vector<Sprite>& bloques2, const int mapas[][gridSize], int gridSize, const Texture& texturaBloque, float lado, int posXIso, int posYISo)
{
    bloques2.clear();
    for (int i = 0; i < gridSize; ++i)
    {
        for (int j = 0; j < gridSize; ++j)
        {
            if (posXIso <= i && posYISo <= j)
            {
                for (int k = 1; k <= mapas[i][j]; ++k)
                {
                    Sprite bloque(texturaBloque);
                    bloque.setPosition(i * lado - (8.0f * k), j * lado - (8.0f * k));
                    bloques2.push_back(bloque);
                }
            }
        }
    }
}





int main()
{
    int mapaActual = 0; // Índice del mapa actual

    // Crear la ventana
    RenderWindow window(VideoMode(1000, 600), "Makibot");
    window.setFramerateLimit(60);

    // Coordenadas de la vista isométrica
    Transform isoTransform;
    isoTransform.translate(300.f, 150.f);
    isoTransform.scale(1.f, 0.5f);
    isoTransform.rotate(45.f);

    // Cargar la textura del piso
    Texture texturaPiso;
    if (!texturaPiso.loadFromFile("images/loza_verde.png"))
    {
        return -1;
    }
    Texture texturaPiso2d;
    if (!texturaPiso2d.loadFromFile("images/loza_verde2d.png"))
    {
        return -1;
    }
    // Cargar la textura del bloque
    Texture texturaBloque;
    if (!texturaBloque.loadFromFile("images/loza_naranja.png"))
    {
        return -1;
    }
    Texture texturaBloque2d;
    if (!texturaBloque2d.loadFromFile("images/loza_naranja2d.png"))
    {
        return -1;
    }

    // Cargar la textura del punto final del mapa3D
    Texture texturaLozaAzul;
    if (!texturaLozaAzul.loadFromFile("images/loza_azul.png"))
    {
        return -1;
    }



    // Crear el sprite del piso

    Sprite tiles[gridSize][gridSize];
    
    crearSpritesPiso(tiles, mapas[mapaActual], texturaLozaAzul, texturaPiso);

    // Vector de sprites para los bloques
    vector<Sprite> bloques;
    // Vector para los bloques q se sobreponen al makibot
    vector<Sprite> bloques2;
    // Inicializar los sprites del piso y los bloques
    crearSpritesBloques(bloques, mapas[mapaActual], texturaBloque);


    // Figura del makibot en 2D
    CircleShape makibot2D;
    makibot2D.setRadius(5.f);
    makibot2D.setFillColor(Color::White);
    makibot2D.setOrigin(makibot2D.getRadius(), makibot2D.getRadius());
    makibot2D.setPosition(507.5f, 407.5f);


    // Cargar la textura del punto final del mapa2D
    Texture texturaLozaAzul2D;
    if (!texturaLozaAzul2D.loadFromFile("images/loza_azul2d.png"))
    {
        return -1;
    }



    //crear el minimapa en 2d
    Sprite tiles2d[gridSize][gridSize];
    configurarSprites(tiles2d, matrices2d[mapaActual], texturaBloque2d, texturaLozaAzul2D, texturaPiso2d);


    

    const int frameWidth = 25;
    const int frameHeight = 50;
    // SPRITES FRONTAL
    Texture spriteMaki;
    if (!spriteMaki.loadFromFile("images/sprite_makibot.png"))
    {
        return -1;
    }

    // Crear el sprite de la animación
    Sprite makibot;
    makibot.setTexture(spriteMaki);

    // Definir los rectángulos para cada fotograma de la animación

    vector<IntRect> framesF;
    framesF.push_back(IntRect(0, 0, frameWidth, frameHeight));
    framesF.push_back(IntRect(frameWidth, 0, frameWidth, frameHeight));
    framesF.push_back(IntRect(2 * frameWidth, 0, frameWidth, frameHeight));

    IntRect focoF = IntRect(3 * frameWidth, 0, frameWidth, frameHeight);

    vector<IntRect> framesB;
    framesB.push_back(IntRect(0, frameHeight, frameWidth, frameHeight));
    framesB.push_back(IntRect(frameWidth, frameHeight, frameWidth, frameHeight));
    framesB.push_back(IntRect(2 * frameWidth, frameHeight, frameWidth, frameHeight));

    IntRect focoB = IntRect(3 * frameWidth, frameHeight, frameWidth, frameHeight);

    // Ajustar la posición inicial del sprite para dibujarse desde la parte inferior
    makibot.setOrigin(12.5f, 50.f);
    makibot.setPosition(300.f, 150.f + yIso / 2.f);

    // primera aparicion del makibot
    makibot.setTextureRect(framesF[0]);

    // Variables para la animación
    int currentFrame = 0;
    Clock animationClock;
    float animationSpeed = 0.3f; 

    // Variables para controlar el movimiento
    bool moving = false;
    Vector2f targetPosition = makibot.getPosition();

    bool miraNE = false;
    bool miraNO = false;
    bool miraSO = false;
    bool miraSE = true;

    // Bucle principal
    while (window.isOpen())
    {

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed && !moving)
            {
                if (event.key.code == Keyboard::Left)
                {
                    moveLeft(targetPosition, moving, miraNE, miraNO, miraSO, miraSE, xIso, yIso);
                }
                else if (event.key.code == Keyboard::Right)
                {
                    moveRight(targetPosition, moving, miraNE, miraNO, miraSO, miraSE, xIso, yIso);
                }
                else if (event.key.code == Keyboard::Up)
                {
                    moveUp(targetPosition, moving, miraNE, miraNO, miraSO, miraSE, xIso, yIso);
                }
                else if (event.key.code == Keyboard::Down)
                {
                    moveDown(targetPosition, moving, miraNE, miraNO, miraSO, miraSE, xIso, yIso);
                }
            }
        }


        


        // Actualizar la animación del sprite
        if (moving)
        {
            // Verificar colisión con bloques
            Vector2f newPosition = targetPosition;
            int posXIso, posYISo;
            Vector2i indices = calculateGridIndices(newPosition, pos_origin);

            posXIso = indices.x;
            posYISo = indices.y;

            cout << posXIso << posYISo << endl;

            if (mapas[mapaActual][posXIso][posYISo] == -1) {
                bloques.clear();

                for (int i = 0; i < gridSize; ++i) {
                    for (int j = 0; j < gridSize; ++j) {
                        tiles[i][j] = Sprite(); // Reasignar un sprite por defecto
                    }
                }

                for (int i = 0; i < gridSize; ++i) {
                    for (int j = 0; j < gridSize; ++j) {
                        tiles2d[i][j] = Sprite(); // Reasignar un sprite por defecto
                    }
                }

                // Incrementar mapaActual y usar el operador módulo para reiniciar a 0 cuando se alcance el límite
                mapaActual = (mapaActual + 1) % 5;

                posXIso = 0;
                posYISo = 0;
                makibot.setOrigin(12.5f, 50.f);
                makibot.setPosition(300.f, 150.f + yIso / 2.f);

                // Actualizar targetPosition a la nueva posición inicial
                targetPosition = makibot.getPosition();

                crearSpritesPiso(tiles, mapas[mapaActual], texturaLozaAzul, texturaPiso);
                crearSpritesBloques(bloques, mapas[mapaActual], texturaBloque);
                configurarSprites(tiles2d, matrices2d[mapaActual], texturaBloque2d, texturaLozaAzul2D, texturaPiso2d);

                // Detener movimiento
                moving = false;
            }

            
            if (!(posXIso >= 0 && posXIso < gridSize && posYISo >= 0 && posYISo < gridSize) ||
                    (mapas[mapaActual][posXIso][posYISo] != 0 && mapas[mapaActual][posXIso][posYISo] != -1))
            {
                moving = false;
                targetPosition = makibot.getPosition();
            }

           

            else
            {
                if (animationClock.getElapsedTime().asSeconds() > animationSpeed)
                {
                    if (miraNE || miraNO)
                    {
                        currentFrame = (currentFrame + 1) % framesB.size();
                        makibot.setTextureRect(framesB[currentFrame]);
                        cout << "arriba" << endl;
                    }
                    else if (miraSO || miraSE)
                    {
                        currentFrame = (currentFrame + 1) % framesF.size();
                        makibot.setTextureRect(framesF[currentFrame]);
                    }

                    animationClock.restart();
                }

                // movimeinto del profesor
                Vector2f currentPosition = makibot.getPosition();
                moveRobot(makibot, targetPosition, currentPosition, xIso, yIso);

                // Detener el movimiento al alcanzar el objetivo

                stopMovement(makibot, targetPosition, makibot.getPosition(), currentFrame, miraNE, miraNO, miraSO, miraSE, moving, framesB, framesF);
                // posicion de makibot2D
                makibot2D.setPosition(507.5f + 15.f * posXIso, 407.4f + 15.f * posYISo);

                // mapa 2D , se verifica la posicion de los bloques y el makibot
                updateBlocks(bloques2, mapas[mapaActual], gridSize, texturaBloque, lado, posXIso, posYISo);
            }
        }

        if (miraNE)
            makibot.setScale(1.f, 1.f);
        else if (miraNO)
            makibot.setScale(-1.f, 1.f);
        else if (miraSO)
            makibot.setScale(-1.f, 1.f);
        else if (miraSE)
            makibot.setScale(1.f, 1.f);

        window.clear(Color::White);
        // dibujar piso 2d
        for (int i = 0; i < gridSize; ++i)
        {
            for (int j = 0; j < gridSize; ++j)
            {
                window.draw(tiles2d[i][j]);
            }
        }
        // Dibujar el piso y los bloques
        for (int i = 0; i < gridSize; ++i)
        {
            for (int j = 0; j < gridSize; ++j)
            {
                window.draw(tiles[i][j], isoTransform);
            }
        }
        for (auto &bloque : bloques)
        {
            window.draw(bloque, isoTransform);
        }

        window.draw(makibot);
        window.draw(makibot2D);

        for (auto &bloque : bloques2)
        {
            window.draw(bloque, isoTransform);
        }

        window.display();
    }

    return 0;
}