#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>
#define PI 3.14159265f

using namespace std;
using namespace sf;

const float lado = 50.f;
const int gridSize = 8;
const float xIso=sqrt(2*lado*lado);
const float yIso=xIso/2.f;
const float ladoIso=sqrt(xIso*xIso/4.f+yIso*yIso/4.f);
const float angXY=atan2f(xIso,yIso);
const float angYX=atan2f(yIso,xIso);
const Vector2f pos_origin(300.f,150.f); 

Vector2i calculateGridIndices(const Vector2f& position, const Vector2f& gridOrigin)
{
    Vector2f relativePosition = position - gridOrigin;
    cout<<"posicionxy: "<<position.x<<"  "<<position.y<<endl;
    float ang_c1 = angXY - atan2f(abs(relativePosition.x),relativePosition.y);
    float ang_c2 = 2.f*angXY-ang_c1;
    float distX, distY;
    cout<<ang_c1*180.f/PI<<endl;
    float hipo = sqrt(relativePosition.x*relativePosition.x + relativePosition.y*relativePosition.y);

    if (relativePosition.x<=0)
    {   
        distX= (hipo/sin(PI-2.f*angXY))*sin(ang_c1);
        distY= (hipo/sin(PI-2.f*angXY))*sin(ang_c2);
    }else
    {
        distY= (hipo/sin(PI-2.f*angXY))*sin(ang_c1);
        distX= (hipo/sin(PI-2.f*angXY))*sin(ang_c2);
        
    }
    cout<<"distancia xy isometricas"<<distX<<" "<<distY<<endl;
    Vector2f transformedPosition(
        distX / ladoIso,
        distY / ladoIso
    );

    int posXIso = floor(transformedPosition.x);
    int posYISo = floor(transformedPosition.y);
    
    return Vector2i(posXIso, posYISo);
}

int main()
{
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
    // Crear el sprite del piso
    
    Sprite tiles[gridSize][gridSize];
    for (int i = 0; i < gridSize; ++i)
    {
        for (int j = 0; j < gridSize; ++j)
        {
            tiles[i][j].setTexture(texturaPiso);
            tiles[i][j].setPosition(i * lado, j * lado);
        }
    }

    // matriz3D para la cantidad de bloques
    int matriz3D[8][8] = {
        {0, 2, 2, 0, 0, 0, 0, 0},
        {0, 0, 2, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 3, 0, 0},
        {0, 0, 0, 2, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 7, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 2}
    };

    // Vector de sprites para los bloques
    vector<Sprite> bloques;
    // Vector para los bloques q se sobreponen al makibot
    vector <Sprite> bloques2;
    // Inicializar los sprites del piso y los bloques
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
    // Figura del makibot en 2D
    CircleShape makibot2D;
    makibot2D.setRadius(5.f); 
    makibot2D.setFillColor(Color::White); 
    makibot2D.setOrigin(makibot2D.getRadius(), makibot2D.getRadius());
    makibot2D.setPosition(507.5f, 407.5f);

    // matriz2D para la cantidad de bloques

    int matriz2D[8][8] = {
        {0, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 1}
    };
    Sprite tiles2d[gridSize][gridSize];
    for (int i = 0; i < gridSize; ++i)
    {
        for (int j = 0; j < gridSize; ++j)
        {
            if(matriz2D[i][j] == 1)
                tiles2d[i][j].setTexture(texturaBloque2d);
            else
                tiles2d[i][j].setTexture(texturaPiso2d);

            tiles2d[i][j].setPosition(500 + i * 15,400 + j * 15);
        }
    }

    // Cargar la textura que contiene todos los sprites
    Texture spriteSheet;
    if (!spriteSheet.loadFromFile("images/derecha.png"))
    {
        return -1;
    }
    
    // Crear el sprite de la animación
    Sprite makibot;
    makibot.setTexture(spriteSheet);

    // Definir los rectángulos para cada fotograma de la animación
    const int frameWidth = 25;
    const int frameHeight = 50;
    vector<IntRect> frames;
    frames.push_back(IntRect(0, 0, frameWidth, frameHeight));
    frames.push_back(IntRect(frameWidth, 0, frameWidth, frameHeight));
    frames.push_back(IntRect(2 * frameWidth, 0, frameWidth, frameHeight));

    // Ajustar la posición inicial del sprite para dibujarse desde la parte inferior
    makibot.setOrigin(12.5f, 50.f);
    makibot.setPosition(300.f, 150.f + yIso/2.f); // Posición inicial del sprite, el centro del primer cuadrado
    // primera aparicion del makibot
    makibot.setTextureRect(frames[0]);
    // Variables para la animación
    int currentFrame = 0;
    Clock animationClock;
    float animationSpeed = 0.3f; // Aumentar la velocidad de la animación

    // Variables para controlar el movimiento
    bool moving = false;
    Vector2f targetPosition = makibot.getPosition();
    bool facingRight = true;

    
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
                    targetPosition.x -= xIso/2.f;
                    targetPosition.y += yIso/2.f;
                    facingRight = false;
                    moving = true;
                }
                else if (event.key.code == Keyboard::Right)
                {
                    targetPosition.x += xIso/2.f;
                    targetPosition.y -= yIso/2.f;
                    facingRight = true;
                    moving = true;
                }
                else if (event.key.code == Keyboard::Up)
                {
                    targetPosition.x -= xIso/2.f;
                    targetPosition.y -= yIso/2.f;
                    moving = true;
                }
                else if (event.key.code == Keyboard::Down)
                {
                    targetPosition.x += xIso/2.f;
                    targetPosition.y += yIso/2.f;
                    moving = true;
                }
            }
        }

        // Actualizar la animación del sprite
        if (moving)
        {
            // Verificar colisión con bloques
            Vector2f newPosition = targetPosition;
            int posXIso,posYISo;
            Vector2i indices = calculateGridIndices(newPosition, pos_origin);

            posXIso = indices.x;
            posYISo = indices.y;

            cout<<posXIso<<posYISo<<endl;
            if (!(posXIso >= 0 && posXIso < gridSize && posYISo >= 0 && posYISo < gridSize) || matriz3D[posXIso][posYISo] != 0)
            {
                moving = false; 
                targetPosition = makibot.getPosition(); 
            }
            else
            {
                if (animationClock.getElapsedTime().asSeconds() > animationSpeed)
                {
                    currentFrame = (currentFrame + 1) % frames.size();
                    makibot.setTextureRect(frames[currentFrame]);
                    animationClock.restart();
                }

                Vector2f currentPosition = makibot.getPosition();
                Vector2f movement(0.f, 0.f);

                if (targetPosition.x > currentPosition.x)
                    movement.x = xIso/2.f / 50.f;
                else if (targetPosition.x < currentPosition.x)
                    movement.x = -xIso/2.f / 50.f;

                if (targetPosition.y > currentPosition.y)
                    movement.y = yIso/2.f / 50.f;
                else if (targetPosition.y < currentPosition.y)
                    movement.y = -yIso/2.f / 50.f;

                makibot.move(movement);

                // Detener el movimiento al alcanzar el objetivo
                if (abs(targetPosition.x - currentPosition.x) < 1.f && abs(targetPosition.y - currentPosition.y) < 1.f)
                {
                    moving = false;
                    currentFrame = 0;
                    makibot.setPosition(targetPosition);
                    makibot.setTextureRect(frames[currentFrame]);
                }
                //posicion de makibot2D
                makibot2D.setPosition(507.5f + 15.f*posXIso ,407.4f + 15.f*posYISo);
                
                //mapa 2D , se verifica la posicion de los bloques y el makibot
                bloques2.clear();
                for (int i = 0; i < gridSize; ++i) {
                    for (int j = 0; j < gridSize; ++j) {
                        if (posXIso<i || posYISo<j) {
                            for (int k = 1; k <= matriz3D[i][j]; ++k) {
                                Sprite bloque(texturaBloque);
                                bloque.setPosition(i * lado - (8.0f * k), j * lado - (8.0f * k));
                                bloques2.push_back(bloque);
                            }
                        }
                    }
                }
            }
        }

        if (facingRight)
            makibot.setScale(1.f, 1.f);
        else
            makibot.setScale(-1.f, 1.f);

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
        for (auto& bloque : bloques)
        {
            window.draw(bloque, isoTransform);
        }

        window.draw(makibot);
        window.draw(makibot2D);

        for (auto& bloque : bloques2)
        {
            window.draw(bloque, isoTransform);
        }
        
        window.display();
    }

    return 0;
}
