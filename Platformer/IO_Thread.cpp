#include <iostream>

#include "IO_Thread.h"

std::mutex mtxIO;

sf::Vector2i LmbStartPos, RmbStartPos;				//mouse positions for firing
sf::Vector2i LmbReleasedPos, RmbReleasedPos;		//and creating walls

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

	//Player player(sf::Vector2f(960, 540), 0);
	sf::Event evt;

	while (true) {
		while (window.pollEvent(evt)) {
			CheckEvent(&evt, bm, time.count());
			if (evt.type == sf::Event::Closed) {
				window.close();
			}	else if (evt.type == sf::Event::MouseButtonPressed) {
				if (evt.mouseButton.button == sf::Mouse::Right) {
					RmbStartPos = sf::Mouse::getPosition();											//save coordinates of LMB pressed
				}							
			} else if (evt.type == sf::Event::MouseButtonReleased) {
				if (evt.mouseButton.button == sf::Mouse::Left) {
					LmbReleasedPos = sf::Mouse::getPosition();
					sf::Vector2f direction = (sf::Vector2f)LmbReleasedPos - bm->GetPlayer()->GetPosition();
					bm->Fire(bm->GetPlayer()->GetPosition(), direction, 10, 10);								//firing when LMB released
				} else if (evt.mouseButton.button == sf::Mouse::Right) {
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

		window.draw(bm->GetPlayer()->GetBody());

		ui.setString("bullest:  " + std::to_string(bm->GetBullets()->size())	//bullets quantity
					+ "\nwalls:     " + std::to_string(bm->GetWalls()->size())	//walls quantity
					+ "\nfps:         " + std::to_string(1 / time.count())		//GUI FPS
					+ "\npFps:       " + std::to_string(1 / t->count()));		//physics FPS

		bm->SetProcessed(true);
		bm->GetCv()->notify_one();

		window.draw(ui);
		window.display();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			
		}

		time = std::chrono::high_resolution_clock::now() - clock;
		clock = std::chrono::high_resolution_clock::now();
	}
}

void CheckEvent(sf::Event* event, BulletManager* bm, float t){
	switch (event->type){
	case sf::Event::Closed:
		break;
	case sf::Event::KeyPressed:
		KeyboardCheck(event, bm, t);
		break;
	case sf::Event::KeyReleased:
		bm->GetPlayer()->SetDir(STP);
		break;
	case sf::Event::MouseButtonPressed:
		break;
	case sf::Event::MouseButtonReleased:
		break;
	case sf::Event::MouseMoved:
		bm->GetPlayer()->Rotate(sf::Vector2f(sf::Mouse::getPosition()));
		break;
	default:
		break;
	}
}

void MouseCheck(){

}

void KeyboardCheck(sf::Event* event, BulletManager* bm, float t){
	switch (event->key.code) {
	case sf::Keyboard::W:
		bm->GetPlayer()->SetDir(FWD);
		break;
	case sf::Keyboard::S:
		bm->GetPlayer()->SetDir(BWD);
		break;
	case sf::Keyboard::D:
		bm->GetPlayer()->SetDir(RGH);
		break;
	case sf::Keyboard::A:
		bm->GetPlayer()->SetDir(LFT);
		break;
	}
}/*

VisualThread::VisualThread(BulletManager* b, std::chrono::duration<float>* t, bool* gOver)
	:	bm(b), pTime(t), gameOver(gOver), window(sf::VideoMode(WIDTH, HEIGHT), "BulletManager", sf::Style::Fullscreen) {
	font.loadFromFile("OpenSans-Bold.ttf");
	//uiText.SetString("");
	uiText.setFont(font);
	uiText.setCharacterSize(16);
	uiText.setPosition(5, 5);
	uiText.setFillColor(sf::Color::Red);
}

VisualThread::~VisualThread(){
	*gameOver = false;
}

void VisualThread::Render() {
	window.clear();

	bm->SetProcessed(false);

	for (auto iter = bm->GetWalls()->begin(); iter != bm->GetWalls()->end(); ++iter) {
		window.draw(*iter->GetBody());
	}
	for (auto iter = bm->GetBullets()->begin(); iter != bm->GetBullets()->end(); ++iter) {
		window.draw(*iter->GetBody());
	}

	window.draw(bm->GetPlayer()->GetBody());

	uiText.setString("bullest:  " + std::to_string(bm->GetBullets()->size())	//bullets quantity
					+ "\nwalls:     " + std::to_string(bm->GetWalls()->size())	//walls quantity
					+ "\nfps:         " + std::to_string(1 / time.count())		//GUI FPS
					+ "\npFps:       " + std::to_string(1 / pTime->count()));	//physics FPS

	bm->SetProcessed(true);
	bm->GetCv()->notify_one();

	window.draw(uiText);
	window.display();
}

void VisualThread::Update() {
	auto clock = std::chrono::high_resolution_clock::now();
	while (!*gameOver) {
		Render();

		time = std::chrono::high_resolution_clock::now() - clock;
		clock = std::chrono::high_resolution_clock::now();
	}
}

void VisualThread::CheckEvent(){
	switch (evt.type) {
	case sf::Event::Closed:
		break;
	case sf::Event::KeyPressed:
		KeyboardCheck();
		break;
	case sf::Event::KeyReleased:
		bm->GetPlayer()->SetDir(STP);
		break;
	case sf::Event::MouseButtonPressed:
		break;
	case sf::Event::MouseButtonReleased:
		break;
	case sf::Event::MouseMoved:
		bm->GetPlayer()->Rotate(sf::Vector2f(sf::Mouse::getPosition()));
		break;
	default:
		break;
	}
}

void VisualThread::MouseCheck(){

}

void VisualThread::KeyboardCheck(){
	switch (evt.key.code) {
	case sf::Keyboard::W:
		bm->GetPlayer()->SetDir(FWD);
		break;
	case sf::Keyboard::S:
		bm->GetPlayer()->SetDir(BWD);
		break;
	case sf::Keyboard::D:
		bm->GetPlayer()->SetDir(RGH);
		break;
	case sf::Keyboard::A:
		bm->GetPlayer()->SetDir(LFT);
		break;
	}
}
*/