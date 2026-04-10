#include <SFML/Graphics.hpp>
#include <matplot/matplot.h>
#include <vector>

int main() {
    using namespace matplot;

    // --- STEP 1: Generate & Save the Waveform ---
    auto t = linspace(0, 2 * pi, 500);
    auto y = transform(t, [](double x) { return sin(x); });
    
    auto p = plot(t, y);
    title("Carrier Waveform Test");
    save("assets/plot.png"); // Matplot++ tells Gnuplot to render this to a file

    // --- STEP 2: Display in SFML ---
    sf::RenderWindow window(sf::VideoMode(800, 600), "Analog Communication Tool");
    
    sf::Texture texture;
    if (!texture.loadFromFile("assets/plot.png")) {
        return -1; // Error if image wasn't created
    }
    sf::Sprite sprite(texture);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        window.clear(sf::Color::White);
        window.draw(sprite);
        window.display();
    }

    return 0;
}