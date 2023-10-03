#include<iostream>
#include <SFML/Graphics.hpp>
#include"Header.h"
using namespace std;
using namespace sf;
int main()
{
	
    srand(time(0)); int r, c;
    card_game A;
    A.play();

    return 0;

}





int main5()
{
    sf::RenderWindow window(sf::VideoMode(1200, 700), "SFML works!");
   
	sf::Texture cardTextures[52];
	sf::Sprite cardSprites[52];

	std::string suits[] = { "hearts", "diamonds", "clubs", "spades" };
	std::string ranks[] = { "ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "jack", "queen", "king" };

	for (int suitIndex = 0; suitIndex < 4; suitIndex++) {
		for (int rankIndex = 0; rankIndex < 13; rankIndex++) {
			std::string filename = ranks[rankIndex] + "_of_" + suits[suitIndex] + ".png";

			if (!cardTextures[suitIndex * 13 + rankIndex].loadFromFile(filename)) {
				// Handle loading error
				return 1;
			}

			cardSprites[suitIndex * 13 + rankIndex].setTexture(cardTextures[suitIndex * 13 + rankIndex]);
		}
	}

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear();
		for (int i = 0; i < 52; i++) {
			cardSprites[i].setPosition(i * 20.0f, 0.0f);
			window.draw(cardSprites[i]);
		}
		window.display();
	}
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		Position a=MouseClick(window);
		cout << a.ri << ' ' << a.ci<<endl;
    }

    return 0;
}