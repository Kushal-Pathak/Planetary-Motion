#include <SFML/Graphics.hpp>
#include <Windows.h>
#define height 900
#define width 1200
class Sun {
public:
	float mass = 100000, radius = 50;
	sf::Vector2f pos;
	sf::Color color;
	sf::CircleShape body;
	Sun() {
		mass = 100; radius = 40;
		pos = sf::Vector2f(width / 2, height / 2);
		color = sf::Color::Yellow;
		body.setRadius(radius);
		body.setPosition(pos);
		body.setOrigin(body.getRadius(), body.getRadius());
		body.setFillColor(color);
	}
	Sun(float m, float r, sf::Vector2f p, sf::Color c) {
		mass = m; radius = r; pos = p; color = c;
		body.setRadius(radius);
		body.setPosition(pos);
		body.setOrigin(body.getRadius(), body.getRadius());
		body.setFillColor(color);
	}
};
class Earth {
public:
	float radius = 20;
	float g_am = 0; // gravitaional acceleration magnitude
	float R = 10, G = 1000;
	sf::Vector2f g_acceleration;
	sf::Vector2f o_velocity;
	sf::Vector2f pos;
	sf::Color color;
	sf::CircleShape body;
	sf::Vertex trail[2];
	Earth() {
		radius = 20;
		pos = sf::Vector2f(width / 2, height / 2 - 350);
		color = sf::Color::Blue;
		body.setRadius(radius);
		body.setPosition(pos);
		body.setOrigin(body.getRadius(), body.getRadius());
		body.setFillColor(color);
		o_velocity.x = 15.f;
	}
	Earth(float r, sf::Vector2f p, sf::Color c) {
		radius = r; pos = p; color = c;
		body.setRadius(radius);
		body.setPosition(pos);
		body.setOrigin(body.getRadius(), body.getRadius());
		body.setFillColor(color);
		o_velocity.x = 10;
		o_velocity.y = 0;
	}
	void update(Sun sun) {
		trail[0] = pos;
		g_acceleration = sun.pos - pos;
		g_acceleration = normalize(g_acceleration);
		g_am = (G * sun.mass) / (R * R);
		g_acceleration *= g_am;
		o_velocity += g_acceleration;
		pos += o_velocity;
		trail[1] = pos;
		body.setPosition(pos);
	}
	sf::Vector2f normalize(sf::Vector2f vec) {
		float mag = sqrt(vec.x * vec.x + vec.y * vec.y);
		R = mag;
		vec.x /= mag;
		vec.y /= mag;
		return vec;
	}
};
int main() {
	sf::RenderWindow window(sf::VideoMode(width, height), "My Window");
	Sun sun;
	Earth earth;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		Sleep(100);
		window.clear(sf::Color::Black);
		window.draw(sun.body);
		window.draw(earth.body);
		window.draw(earth.trail, 2, sf::Lines);
		window.display();
		earth.update(sun);
	}
}
