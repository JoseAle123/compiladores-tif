#include <SFML/Graphics.hpp>

int main()
{
    // Crear la ventana
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Vista Isometrica");
    
    // Coordenadas de la vista isométrica
    sf::Transform isoTransform;
    isoTransform.translate(300.f, 150.f);
    isoTransform.scale(1.f, .5f);
    isoTransform.rotate(45.f);

    // Crear el cubo
    sf::RectangleShape cube(sf::Vector2f(50.f, 50.f));
    cube.setFillColor(sf::Color::Blue);
    //cube.setOutlineColor(sf::Color::Blue);
    //cube.setOutlineThickness(2.f);
    cube.setPosition(0.f, 0.f); // Posición inicial del cubo

    // Cargar la textura del piso
    sf::Texture tileTexture;
    if (!tileTexture.loadFromFile("images/loza.png"))
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
            tiles[i][j].setTexture(tileTexture);
            tiles[i][j].setPosition(1*i * tileSize, j * tileSize);
        }
    }

    // Variables para controlar el movimiento
    bool moveLeft = false;
    bool moveRight = false;
    bool moveUp = false;
    bool moveDown = false;

    // Bucle principal
    while (window.isOpen())
    {
        // Manejo de eventos
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left)
                    moveLeft = true;
                else if (event.key.code == sf::Keyboard::Right)
                    moveRight = true;
                else if (event.key.code == sf::Keyboard::Up)
                    moveUp = true;
                else if (event.key.code == sf::Keyboard::Down)
                    moveDown = true;
            }
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Left)
                    moveLeft = false;
                else if (event.key.code == sf::Keyboard::Right)
                    moveRight = false;
                else if (event.key.code == sf::Keyboard::Up)
                    moveUp = false;
                else if (event.key.code == sf::Keyboard::Down)
                    moveDown = false;
            }
        }

        // Actualizar la posición del cubo
        if (moveLeft)
        {
            cube.move(-tileSize, 0.f);
            moveLeft = false;
        }
        else if (moveRight)
        {
            cube.move(tileSize, 0.f);
            moveRight = false;
        }
        else if (moveUp)
        {
            cube.move(0.f, -tileSize);
            moveUp = false;
        }
        else if (moveDown)
        {
            cube.move(0.f, tileSize);
            moveDown = false;
        }

        // Renderizar
        window.clear(sf::Color::White);
        
        // Dibujar el piso
        for (int i = 0; i < gridSize; ++i)
        {
            for (int j = 0; j < gridSize; ++j)
            {
                window.draw(tiles[i][j], isoTransform);
            }
        }

        // Dibujar el cubo
        window.draw(cube, isoTransform);
        
        window.display();
    }

    return 0;
}
