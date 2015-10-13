#include "player.hpp"

Player::Player(){
	if (!texture.loadFromFile("images/player.png")){
		std::cout << "Could not load player.png texture" << std::endl;
	}
	texture.setSmooth(true);
	if (!texture2.loadFromFile("images/player2.png")){
		std::cout << "Could not load player.png texture" << std::endl;
	}
	texture2.setSmooth(true);
	pos = sf::Vector2f(700,1000-40);
	vine = pos;
	vel = 0;
	id = 0;
}

Player::Player(int nid){
	if (!texture.loadFromFile("images/player.png")){
		std::cout << "Could not load player.png texture" << std::endl;
	}
	texture.setSmooth(true);
	if (!texture2.loadFromFile("images/player2.png")){
		std::cout << "Could not load player.png texture" << std::endl;
	}
	texture2.setSmooth(true);
	pos = sf::Vector2f(700,1000-40);
	vine = pos;
	vel = 0;
	id = nid;
}

void Player::draw(sf::RenderWindow &window){
	sf::VertexArray vert;
	//draw vine
	vert.setPrimitiveType(sf::Lines);
	vert.append(pos);
	vert.append(vine);
	window.draw(vert);
	
	//draw player
	vert.clear();
	VertQuad quad;
	if(vel == 0){
		quad.set(sf::Vector2f(0,0), sf::Vector2f(40,80), sf::Vector2f((int)pos.x, (int)pos.y), sf::Vector2f(40,80));
	} else {
		quad.set(sf::Vector2f(50,0), sf::Vector2f(40,80), sf::Vector2f((int)pos.x, (int)pos.y), sf::Vector2f(vel*40,80));
	}
	vert.setPrimitiveType(sf::Quads);
	quad.add(vert);
	if (id == 0){
		window.draw(vert, &texture);
	} else {
		window.draw(vert, &texture2);
	}
}

void Player::draw(sf::RenderWindow &window, sf::Vector3f play){
	sf::VertexArray vert;
	//draw player
	vert.clear();
	VertQuad quad;
	if(play.z == 0){
		quad.set(sf::Vector2f(0,0), sf::Vector2f(40,80), sf::Vector2f((int)play.x, (int)play.y), sf::Vector2f(40,80));
	} else {
		quad.set(sf::Vector2f(50,0), sf::Vector2f(40,80), sf::Vector2f((int)play.x, (int)play.y), sf::Vector2f(play.z*40,80));
	}
	vert.setPrimitiveType(sf::Quads);
	quad.add(vert);
	window.draw(vert, &texture2);
}

void Player::draw(sf::RenderWindow &window, sf::Packet &packet){
	sf::VertexArray vert;
	//draw vine
	vert.setPrimitiveType(sf::Lines);
	sf::Vector2f ppos;
	int pvel;
	packet >> ppos.x >> ppos.y >> pvel;
	vert.append(ppos);
	sf::Vector2f pvine;
	packet >> pvine.x >> pvine.y;
	vert.append(pvine);
	window.draw(vert);
	//draw player
	vert.clear();
	VertQuad quad;
	if(pvel == 0){
		quad.set(sf::Vector2f(0,0), sf::Vector2f(40,80), sf::Vector2f((int)ppos.x, (int)ppos.y), sf::Vector2f(40,80));
	} else {
		quad.set(sf::Vector2f(50,0), sf::Vector2f(40,80), sf::Vector2f((int)ppos.x, (int)ppos.y), sf::Vector2f(pvel*40,80));
	}
	vert.setPrimitiveType(sf::Quads);
	quad.add(vert);
	window.draw(vert, &texture2);
}

void Player::set(sf::Packet &packet){
	packet >> pos.x >> pos.y >> vel;
	packet >> vine.x >> vine.y;
	if (vine != pos){
		pops.push_back(sf::Vector3f(vine.x, vine.y, id));
	}
}

void Player::move(const float eclisped){
	vel = 0;
	if (vine == pos){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
			vel -= 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
			vel += 1;
		}
		pos.x += vel*100*eclisped;
		vine = pos;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
			vine.y -= 100*eclisped;
			pops.push_back(sf::Vector3f(pos.x, pos.y, id));
		}
	} else {
		vine.y -= 1000*eclisped;
		pops[0].x = vine.x;
		pops[0].y = vine.y;
		if (vine.y < 0){
			stopVine();
		}
	}
}

void Player::move1(const float eclisped){
	if (vine == pos){
		pos.x += vel*100*eclisped;
		vine = pos;
	} else {
		vine.y -= 1000*eclisped;
		pops[0].x = vine.x;
		pops[0].y = vine.y;
		if (vine.y < 0){
			stopVine();
		}
	}
}

void Player::stopVine(){
	vine = pos;
	pops.clear();
}

vector<sf::Vector3f> Player::getPops(){
	return pops;
}

void Player::getPops(sf::Packet &packet){
	packet << pops.size();
	for(unsigned int i=0; i<pops.size(); i++){
		packet << pops[i].x << pops[i].y;
	}
}

sf::Vector3f Player::getPos(){
	return sf::Vector3f(pos.x, pos.y, vel);
}

void Player::getPos(sf::Packet& packet){
	packet << "pp";
	packet << pos.x << pos.y << vel;
	packet << vine.x << vine.y;
}