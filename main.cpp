#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

#define PI 3.14159265f

int main()
{
    // Crear la ventana
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Makibot");
    window.setFramerateLimit(60);

    // Coordenadas de la vista isométrica
    sf::Transform isoTransform;
    isoTransform.translate(300.f, 150.f);
    isoTransform.scale(1.f, 0.5f);
    isoTransform.rotate(45.f);

    // Cargar la textura del piso
    sf::Texture tileTexturePiso;
    if (!tileTexturePiso.loadFromFile("images/loza_verde.png"))
    {
        return -1;
    }
    // Cargar la textura del bloque
    sf::Texture tileTextureBloque;
    if (!tileTextureBloque.loadFromFile("images/loza_naranja.png"))
    {
        return -1;
    }
    // Crear el sprite del piso
    const int gridSize = 8;
    const float tileSize = 50.f;
    sf::Sprite tiles[gridSize][gridSize];
    for (int i = 0; i < gridSize; ++i)
    {
        for (int j = 0; j < gridSize; ++j)
        {
            tiles[i][j].setTexture(tileTexturePiso);
            tiles[i][j].setPosition(i * tileSize, j * tileSize);
        }
    }

    // Matrix para la cantidad de bloques
    int matrix[8][8] = {
        {0, 2, 2, 0, 0, 0, 0, 0},
        {0, 0, 2, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 3, 0, 0},
        {0, 0, 0, 2, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 2}
    };

    // Vector de sprites para los bloques
    std::vector<sf::Sprite> bloques;

    // Inicializar los sprites del piso y los bloques
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (matrix[i][j] != 0) {
                for (int k = 1; k <= matrix[i][j]; ++k) {
                    sf::Sprite bloque(tileTextureBloque);
                    bloque.setPosition(i * tileSize - (8.0f * k), j * tileSize - (8.0f * k));
                    bloques.push_back(bloque);
                }
            }
        }
    }

    // Cargar la textura que contiene todos los sprites
    sf::Texture spriteSheet;
    if (!spriteSheet.loadFromFile("images/derecha.png"))
    {
        return -1;
    }

    // Crear el sprite de la animación
    sf::Sprite animatedSprite;
    animatedSprite.setTexture(spriteSheet);

    // Definir los rectángulos para cada fotograma de la animación
    const int frameWidth = 25;
    const int frameHeight = 50;
    std::vector<sf::IntRect> frames;
    frames.push_back(sf::IntRect(0, 0, frameWidth, frameHeight));
    frames.push_back(sf::IntRect(frameWidth, 0, frameWidth, frameHeight));
    frames.push_back(sf::IntRect(2 * frameWidth, 0, frameWidth, frameHeight));

    // Ajustar la posición inicial del sprite para dibujarse desde la parte inferior
    animatedSprite.setOrigin(12.5f, 50.f);
    animatedSprite.setPosition(300.f, 150.f+(50.f/cos(45*PI/180.f))*0.25); // Posición inicial del sprite, el centro del primer cuadrado
    float des=((50.f/cos(45*PI/180.f))*0.25)/sin(30*PI/180.f);
    float desy=(50.f/cos(45*PI/180.f))*0.25;
    float desx=(50.f/cos(45*PI/180.f))*0.5;

    // Variables para la animación
    int currentFrame = 0;
    sf::Clock animationClock;
    float animationSpeed = 0.3f; // Aumentar la velocidad de la animación

    // Variables para controlar el movimiento
    bool moving = false;
    sf::Vector2f targetPosition = animatedSprite.getPosition();
    bool facingRight = true;

    // Bucle principal
    while (window.isOpen())
    {
        // Manejo de eventos
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && !moving)
            {
                if (event.key.code == sf::Keyboard::Left)
                {
                    targetPosition.x -= desx;
                    targetPosition.y += desy;
                    facingRight = false;
                    moving = true;
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    targetPosition.x += desx;
                    targetPosition.y -= desy;
                    facingRight = true;
                    moving = true;
                }
                else if (event.key.code == sf::Keyboard::Up)
                {
                    targetPosition.x -= desx;
                    targetPosition.y -= desy;
                    moving = true;
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    targetPosition.x += desx;
                    targetPosition.y += desy;
                    moving = true;
                }
            }
        }

        // Actualizar la animación del sprite
        if (moving)
        {
            // Verificar colisión con bloques
            sf::Vector2f newPosition = targetPosition;
            int gridX = (newPosition.x - (300.f+(tileSize/cos(45*PI/180.f))*0.5*((animatedSprite.getPosition().y-150.f-(tileSize/cos(45*PI/180.f))*0.25)/((tileSize/cos(45*PI/180.f))*0.5))) - (tileSize/cos(45*PI/180.f)) / 2) / (tileSize/cos(45*PI/180.f)) ;

            int gridY = (newPosition.y - (150.f+(tileSize/cos(45*PI/180.f))*0.25f*((animatedSprite.getPosition().x-300.f-(tileSize/cos(45*PI/180.f))*0.5)/((tileSize/cos(45*PI/180.f))))) - (tileSize/cos(45*PI/180.f))*0.25) / ((tileSize/cos(45*PI/180.f))*0.5);

            if (gridX >= 0 && gridX < gridSize && gridY >= 0 && gridY < gridSize && matrix[gridX][gridY] != 0)
            {
                moving = false; // Si hay un bloque en la nueva posición, cancelar el movimiento
                targetPosition = animatedSprite.getPosition(); // Mantener la posición actual
            }
            else
            {
                if (animationClock.getElapsedTime().asSeconds() > animationSpeed)
                {
                    currentFrame = (currentFrame + 1) % frames.size();
                    animatedSprite.setTextureRect(frames[currentFrame]);
                    animationClock.restart();
                }

                sf::Vector2f currentPosition = animatedSprite.getPosition();
                sf::Vector2f movement(0.f, 0.f);

                if (targetPosition.x > currentPosition.x)
                    movement.x = desx / 50.f;
                else if (targetPosition.x < currentPosition.x)
                    movement.x = -desx / 50.f;

                if (targetPosition.y > currentPosition.y)
                    movement.y = desy / 50.f;
                else if (targetPosition.y < currentPosition.y)
                    movement.y = -desy / 50.f;

                animatedSprite.move(movement);

                // Detener el movimiento al alcanzar el objetivo
                if (std::abs(targetPosition.x - currentPosition.x) < 1.f && std::abs(targetPosition.y - currentPosition.y) < 1.f)
                {
                    moving = false;
                    currentFrame = 0;
                    animatedSprite.setPosition(targetPosition);
                    animatedSprite.setTextureRect(frames[currentFrame]);
                }
            }
        }

        // Reflejar el sprite según la dirección
        if (facingRight)
            animatedSprite.setScale(1.f, 1.f);
        else
            animatedSprite.setScale(-1.f, 1.f);

        // Renderizar
        window.clear(sf::Color::White);

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

        // Dibujar el sprite animado sin la transformación isométrica
        window.draw(animatedSprite);

        window.display();
    }

    return 0;
}
