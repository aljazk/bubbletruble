#include "bubble.hpp"

Bubble::Bubble(){
	seed = time(NULL);
	create(sf::Vector2f(450,300), sf::Vector2f(-50,0), 5);
    texture.loadFromFile("images/bubble.png");
	texture.setSmooth(true);
}

Bubble::Bubble(const sf::Vector2f newPos, const sf::Vector2f newVel,const int newSize){
	seed = time(NULL);
	create(newPos, newVel, newSize);
    texture.loadFromFile("images/bubble.png");
	texture.setSmooth(true);
}

int random(){
	return rand() % 255 + 100;
}

void Bubble::draw(sf::RenderWindow &window){
	sf::VertexArray circles;
	circles.setPrimitiveType(sf::Quads);
	VertQuad quad;
	for (unsigned int i=0; i<size.size(); i++){
		int s = size[i]*SIZE*2;
		quad.set(sf::Vector2f(0,0), sf::Vector2f(100,100), pos[i], sf::Vector2f(s,s));
		srand (seed+s);
		quad.setColor(sf::Color(random(), random(), random(), 255));
		quad.add(circles);
	}
	window.draw(circles, &texture);
}

void Bubble::draw(sf::RenderWindow &window, vector<sf::Vector3f> bubbles){
	sf::VertexArray circles;
	circles.setPrimitiveType(sf::Quads);
	VertQuad quad;
	for (unsigned int i=0; i<bubbles.size(); i++){
		int s = bubbles[i].z*SIZE*2;
		quad.set(sf::Vector2f(0,0), sf::Vector2f(100,100), sf::Vector2f(bubbles[i].x, bubbles[i].y), sf::Vector2f(s,s));
		srand (seed+s);
		quad.setColor(sf::Color(random(), random(), random(), 255));
		quad.add(circles);
	}
	window.draw(circles);
}


void Bubble::draw(sf::RenderWindow &window, sf::Packet &packet){
	sf::VertexArray circles;
	circles.setPrimitiveType(sf::Quads);
	VertQuad quad;
	unsigned int setsize;
	packet >> setsize;
	for (unsigned int i=0; i<setsize; i++){
		sf::Vector2f ppos;
		int ssize;
		packet >> ppos.x >> ppos.y >> ssize;
		int s = ssize*SIZE*2;
		quad.set(sf::Vector2f(0,0), sf::Vector2f(100,100), ppos, sf::Vector2f(s,s));
		srand (seed+s);
		quad.setColor(sf::Color(random(), random(), random(), 255));
		quad.add(circles);
	}
	window.draw(circles, &texture);
}

void Bubble::set(sf::Packet &packet){
	unsigned int setsize;
	packet >> setsize;
	size.resize(setsize);
	pos.resize(setsize);
	vel.resize(setsize);
	for (unsigned int i=0; i<setsize; i++){
		packet >> pos[i].x >> pos[i].y >> size[i];
		packet >> vel[i].x >> vel[i].y;
	}
}

void Bubble::move(const float eclipsed){
	for(unsigned int i=0; i<size.size(); i++){
		vel[i].y += 90*eclipsed;
		pos[i].x += vel[i].x * eclipsed;
		pos[i].y += vel[i].y * eclipsed;
		if(pos[i].y > 1000-size[i]*SIZE){
			pos[i].y = 1000-size[i]*SIZE;
			vel[i].y = -vel[i].y;
		}
		if(pos[i].x > 1000-size[i]*SIZE){
			pos[i].x = 1000-size[i]*SIZE;
			vel[i].x = -vel[i].x;
		}
		if(pos[i].x < 0+size[i]*SIZE){
			pos[i].x = 0+size[i]*SIZE;
			vel[i].x = -vel[i].x;
		}
	}
}

void Bubble::create(const sf::Vector2f newPos, const sf::Vector2f newVel,const int newSize){
	if (newSize >= 1){
		pos.push_back(newPos);
		vel.push_back(newVel);
		size.push_back(newSize);
	}
}

void Bubble::remove(){
	for(unsigned int i=0; i<size.size(); i++){
		remove(i);
	}
}

void Bubble::remove(const unsigned int id){
	pos.erase(pos.begin()+id);
	vel.erase(vel.begin()+id);
	size.erase(size.begin()+id);
}

void Bubble::pop(const unsigned int id){
	int nvel = -110;
	if(size[id]-1 == 1){
		nvel = -150;
	}
	create(pos[id], sf::Vector2f(vel[id].x, nvel), size[id]-1);
	create(pos[id], sf::Vector2f(-vel[id].x, nvel), size[id]-1);
	remove(id);
}

vector<sf::Vector2i> Bubble::popAll(){
	vector<sf::Vector2i> ids;
 	for(unsigned int i=0; i<size.size(); i++){
		if(pos[i].y < 0+size[i]*SIZE){
			pop(i);
		} else {
			for(unsigned int p=0; p<pops.size(); p++){
				float dist = sqrt( pow(pos[i].x-pops[p].x, 2) + pow(pos[i].y-pops[p].y, 2) );
				if(dist < SIZE*size[i]){
					ids.push_back(sf::Vector2i(pops[p].z, i));
					pop(i);
				}
			}
		}
	}
	pops.clear();
	return ids;
}

void Bubble::addPop(const sf::Vector3f newPop){
	pops.push_back(newPop);
}


void Bubble::addPops(vector<sf::Vector3f> newPop){
	for(unsigned int i=0; i<newPop.size(); i++){
		pops.push_back(newPop[i]);
	}
}

void Bubble::addPops(sf::Packet &packet){
	float x,y;
	unsigned int newsize;
	packet >> newsize;//another pocket with value 0 appers from unknown reason o.O just ignore it..
	packet >> newsize;
	for(unsigned int i=0; i<newsize; i++){
		packet >> x >> y;
		pops.push_back(sf::Vector3f(x,y,1));
	}
}

vector<sf::Vector3f> Bubble::getBubbles(){
	vector<sf::Vector3f> bubbles;
	for(unsigned int i=0; i<size.size(); i++){
		bubbles.push_back(sf::Vector3f(pos[i].x, pos[i].y, size[i]));
	}
	return bubbles;
}

void Bubble::getBubbles(sf::Packet &packet){
	unsigned int setsize = size.size();
	packet << "bub" << setsize;
	for(unsigned int i=0; i<setsize; i++){
		packet << pos[i].x << pos[i].y << size[i];
		packet << vel[i].x << vel[i].y;
	}
}
