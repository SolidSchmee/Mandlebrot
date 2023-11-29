//Mandelbrot Set by Josh Adams and Ryan Campfield

#include "ComplexPlane.h"

int main()
{
    // Get desktop resolution and create a smaller window
    VideoMode desktopMode = VideoMode::getDesktopMode();
    //unsigned int windowWidth = desktopMode.width;
    //unsigned int windowHeight = desktopMode.height;

    float windowWidth = desktopMode.width/2;
    float windowHeight = desktopMode.height/2;

    // Construct the RenderWindow
    RenderWindow window(VideoMode(windowWidth, windowHeight), "Mandelbrot Set");

    // Construct the ComplexPlane
    ComplexPlane complexPlane(window.getSize().x, window.getSize().y);

    // Construct the Font and Text objects
    Font font;
    if (!font.loadFromFile("zeldadxt.ttf")) {
        // Handle font loading error
        return EXIT_FAILURE;
    }

    Text text("", font, 18);
    text.setPosition(10.0f, 10.0f);
    text.setFillColor(Color::Red);

    // Begin the main loop
    while (window.isOpen())
    {
        // Handle Input segment
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            // Handle MouseButtonPressed
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Right)
                {
                    // Right click to zoomOut and setCenter
                    complexPlane.zoomOut();
                    complexPlane.setCenter(Mouse::getPosition(window));
                    complexPlane.updateRender();
                    complexPlane.loadText(text);
                }
                else if (event.mouseButton.button == Mouse::Left)
                {
                    // Left click to zoomIn and setCenter
                    complexPlane.zoomIn();
                    complexPlane.setCenter(Mouse::getPosition(window));
                    complexPlane.updateRender();
                    complexPlane.loadText(text);
                }
                //State::CALCULATING;
            }

            // Handle MouseMoved
            if (event.type == Event::MouseMoved)
            {
                // Call setMouseLocation on the ComplexPlane object
                complexPlane.setMouseLocation(Mouse::getPosition(window));
            }

            // Check if Escape key is pressed to close the window
            if (Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();
        }

        // Update Scene segment
        complexPlane.updateRender();
        complexPlane.loadText(text);

        // Draw Scene segment
        window.clear();
        window.draw(complexPlane);
        window.draw(text);
        window.display();
    }

    return EXIT_SUCCESS;
}

