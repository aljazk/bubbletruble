#include "Menu.hpp"

#define MATH_PI (3.14159265359)

Menu::Menu(){
	//background
	back.loadFromFile("images/back.jpg");
	backSize = back.getSize();
	// create the window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	windowX = 1000, windowY = 1000;
    window.create(sf::VideoMode(windowX,windowY), "My window", sf::Style::Default, settings);
	window.setPosition(sf::Vector2i(500, 0));
	window.setKeyRepeatEnabled(false);

	// create font
	font.loadFromFile("arial.ttf");

	// create text
	text.setFont(font);

	// define eclipsed time
	eclipsed = 1;
	// mouse click cooldown
	mouseDown = false;
	
	//start the game
	mainMenu();
}

void Menu::mainMenu(){
	int action;
	// start loop
    while (window.isOpen()){
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)){
			inter.enterText(event);
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
		}
		
		// clear window
        window.clear(sf::Color::Black);
		// draw background
		sf::VertexArray backVert(sf::Quads);
		VertQuad backQuad;
		sf::Vector2u size = window.getSize();
		backQuad.set(sf::Vector2f(0,0), sf::Vector2f(backSize.x,backSize.y), sf::Vector2f(0,0), sf::Vector2f(size.x, size.y));
		backQuad.setCenter(sf::Vector2f(size.x, 0));
		backQuad.add(backVert);
		window.draw(backVert, &back);
		
		action = inter.check(window);
		if (action != 0){
			break;
		}
		inter.draw(window);
		
		// end the current frame
		eclipsed = clock.restart().asSeconds();
		// display fps
		std::ostringstream s;
		s << 1.f/eclipsed << endl;
		text.setString(s.str());
		text.setCharacterSize(10);
		text.setColor(sf::Color::White);
		text.setPosition(10,10);
		window.draw(text);


		// draw stuff on window
        window.display();
        //wait();
    }
	if(action == 1){
		gameMenu(1);
	} else if (action == 2){
		gameMenu(2);
	}
}

sf::Packet& operator <<(sf::Packet& packet, const sf::Vector3f& vect){
	return packet << vect.x << vect.y << vect.z;
}

sf::Packet& operator >>(sf::Packet& packet, sf::Vector3f& vect){
	return packet >> vect.x >> vect.y >> vect.z;
}

void Menu::gameMenu(int mode){
	//create bubble array
	Bubble bubbles;
	//bubbles.pop(0);
	
	//create players
	Player player;
	Player player1(1);
	
	Host server;
	Client client(inter.getName(0));
	if (mode == 1){
		server.create();
		std::cout << "Waiting for client" << std::endl;
		//server.acceptClient();
	} else {
		client.connect();
	}
	
	int data = 0;
	float dataTime = 0;
	float sendTime = 0;
	
	// start loop
    while (window.isOpen()){
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)){
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
		}
		
		// clear window
        window.clear(sf::Color::Black);
		
		// draw background
		sf::VertexArray backVert(sf::Quads);
		VertQuad backQuad;
		sf::Vector2u size = window.getSize();
		backQuad.set(sf::Vector2f(0,0), sf::Vector2f(backSize.x,backSize.y), sf::Vector2f(0,0), sf::Vector2f(size.x, size.y));
		backQuad.setCenter(sf::Vector2f(size.x, 0));
		backQuad.add(backVert);
		window.draw(backVert, &back);
		
		if (mode == 1){
			bool change = false;
			//create new bubble with mouse
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				if(!mouseDown){
					sf::Vector2i mouse;
					mouse = sf::Mouse::getPosition(window);
					if (window.hasFocus()){
						bubbles.create(sf::Vector2f(mouse.x,mouse.y), sf::Vector2f(50,0), 5);
						change = true;
					}
				}
				mouseDown = true;
			} else {
				mouseDown = false;
			}
			if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
				bubbles.remove();
				change = true;
			}
			//receive data from client
			sf::Packet packet = server.receive();
			
			//size of recived data
			data += packet.getDataSize();
			if (dataTime >= 1){
				std::cout << data << "b/s" << std::endl;
				data = 0;
				dataTime = 0;
			}
			
			if (packet.getDataSize() > 0){
				while (true){
					if (packet.endOfPacket()){
						break;
					} else {
						std::string type;
						packet >> type;
						if (type == "pp"){
							player1.set(packet);
						}
					}
				}
			}
			packet.clear();
			
			if (sendTime >= 0.1){
				player.getPos(packet);
				sendTime = 0;
			}
			
			//pop bubbles and return id that poped it;
			vector<sf::Vector2i> id = bubbles.popAll();
			bool stop = false;
			unsigned int size = id.size();
			if (size > 0){
				packet << "pop" << size;
				for (unsigned int i=0; i<id.size(); i++){
					change = true;
					packet << id[i].y;
					if (id[i].x == 0){
						player.stopVine();
					}
					if (id[i].x == 1){
						stop = true;
						player1.stopVine();
					}
				}
			}
			if (stop)
				packet << "stop";
			
			if (change)
				bubbles.getBubbles(packet);
			
			server.send(packet);
			
			player.move(eclipsed);
			player.draw(window);
			player1.draw(window);
			player1.move1(eclipsed);
			
			//do game stuff;
			bubbles.move(eclipsed);
			bubbles.draw(window);
			
			bubbles.addPops(player.getPops());
			bubbles.addPops(player1.getPops());
		} else {
			//receive data from host
			sf::Packet packet = client.receive();
			data += packet.getDataSize();			
			
			if (packet.getDataSize() > 0){
				while (true){
					if (packet.endOfPacket()){
						break;
					} else {
						std::string type;
						packet >> type;
						if (type == "pp"){
							player1.set(packet);
						}
						if (type == "pop"){
							unsigned int size;
							packet >> size;
							for (unsigned int i=0; i < size; i++){
								int c;
								packet >> c;
							}
						}
						if (type == "bub"){
							bubbles.set(packet);
						}
						if (type == "stop"){
							player.stopVine();
						}
					}
				}
			}
			
			packet.clear();
			//sent data to host
			if (dataTime >= 1){
				std::cout << data << "b/s" << std::endl;
				data = 0;
				dataTime = 0;
			}
			
			if (sendTime >= 0.1){
				player.getPos(packet);
				sendTime = 0;
			}
			client.send(packet);
			
			player.move(eclipsed);
			player.draw(window);
			player1.draw(window);
			player1.move1(eclipsed);
			
			bubbles.move(eclipsed);
			bubbles.draw(window);
			
		}

		
		// end the current frame
		eclipsed = clock.restart().asSeconds();
		dataTime += eclipsed;
		sendTime += eclipsed;
		// display fps
		std::ostringstream s;
		s << 1.f/eclipsed << endl;
		text.setString(s.str());
		text.setCharacterSize(10);
		text.setColor(sf::Color::White);
		text.setPosition(10,10);
		window.draw(text);


		// draw stuff on window
        window.display();
        //wait();
    }
}

void Menu::pauseMenu(){
	
}