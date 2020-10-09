#include <mutex>

#include "IO_Thread.h"
#include "Player.h"

std::mutex mtxIO;

sf::Vector2i LmbStartPos, RmbStartPos;				//mouse positions for firing
sf::Vector2i LmbReleasedPos, RmbReleasedPos;		//and creating walls
sf::Vector2i lookAt(0,0);

void input(BulletManager* bm, std::chrono::duration<float>* t, bool* gameOver) {
	sf::Font font;									//text obj for UI
	font.loadFromFile("OpenSans-Bold.ttf");			//
	sf::Text ui("",font,16);						//
	ui.setPosition(5, 5);							//
	ui.setFillColor(sf::Color::Red);				//

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "BulletManager", sf::Style::Fullscreen);
	//window.setVerticalSyncEnabled(true);

	std::chrono::duration<float> time;
	auto clock = std::chrono::high_resolution_clock::now();

	Player player(sf::Vector2f(960, 540), 0);

	sf::Event event;

	while (true) {
		if (lookAt != sf::Mouse::getPosition()) {
			lookAt = sf::Mouse::getPosition();
			player.Rotate(sf::Vector2f(lookAt));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
			bm->WallTrancform();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			player.Move(FWD, time.count(), bm->GetWalls());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			player.Move(BWD, time.count(), bm->GetWalls());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			player.Move(RGH, time.count(), bm->GetWalls());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			player.Move(LFT, time.count(), bm->GetWalls());
		}

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			} else if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Right) {
					RmbStartPos = sf::Mouse::getPosition();											//save coordinates of LMB pressed
				}							
			} else if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					LmbReleasedPos = sf::Mouse::getPosition();
					sf::Vector2f direction = (sf::Vector2f)LmbReleasedPos - player.GetPosition();
					bm->Fire(player.GetPosition(), direction, 10, 10);								//firing when LMB released
				} else if (event.mouseButton.button == sf::Mouse::Right) {
					RmbReleasedPos = sf::Mouse::getPosition();
					bm->CreateWall(sf::Vector2f(RmbStartPos), sf::Vector2f(RmbReleasedPos), false);	//build a wall when RMB released
				}
			}
		}

		window.clear();

		bm->SetProcessed(false);

		for (auto iter = bm->GetWalls()->begin(); iter != bm->GetWalls()->end(); ++iter) {
			window.draw(*iter->GetBody());
		}
		for (auto iter = bm->GetBullets()->begin(); iter != bm->GetBullets()->end(); ++iter) {
			window.draw(*iter->GetBody());
		}

		window.draw(player.GetBody());

		ui.setString("bullest:  " + std::to_string(bm->GetBullets()->size())	//bullets quantity
					+ "\nwalls:     " + std::to_string(bm->GetWalls()->size())	//walls quantity
					+ "\nfps:         " + std::to_string(1 / time.count())		//GUI FPS
					+ "\npFps:       " + std::to_string(1 / t->count()));		//physics FPS

		bm->SetProcessed(true);
		bm->GetCv()->notify_one();

		window.draw(ui);
		window.display();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			*gameOver = true;
		}

		time = std::chrono::high_resolution_clock::now() - clock;
		clock = std::chrono::high_resolution_clock::now();
	}
}
