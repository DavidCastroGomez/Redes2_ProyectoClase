#pragma once
#include <list>
#include <mutex>

#include "Button.h"

class Window
{
public:
	/// <summary>
	/// Constructor creates window
	/// Dont touch window from other thread
	/// </summary>
	Window(unsigned int width = 800, unsigned int height = 600, std::string title = "Window");

	void AddButton(Button* bt);
	//Create system for update window at its normal update time, like android dispatcher.main, pass a lambda function
	void RunWindowsLoop();

private:

	std::mutex _mutex;
	sf::RenderWindow _window;

	Button* _lastClickedDownBt;
	std::list<Button*> _buttons;
	std::list<sf::Drawable*> _objectsToDraw;

};

