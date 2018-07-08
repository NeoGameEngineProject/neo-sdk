#include "Game.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

#include <VFSFile.h>
#include <iostream>

using namespace Neo;

#ifndef ASSET_MODE
#define ASSET_MODE 0
#endif

#ifdef __EMSCRIPTEN__
void doIteration();
#endif

Game::Game(unsigned int width, unsigned int height, const char* title)
{
#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(doIteration, 60, 0);
	emscripten_pause_main_loop();
#endif
	
	m_window = m_platform.createWindow(width, height, title);
}

void Game::changeState(GameStateRef&& game, bool now)
{
	if(!now)
	{
		m_requestedGame = std::move(game);
		return;
	}
	
	if(m_currentGame != nullptr)
		m_currentGame->end();
	
	// TODO Render loading screen!
	m_currentGame = std::move(game);
	m_currentGame->setGame(this);
	m_currentGame->begin(m_platform, *m_window);
	
	m_lastFrameTime = m_platform.getTime() / 1000.0;
}

void Game::update()
{
	if(m_requestedGame.get())
	{
		changeState(std::move(m_requestedGame), true);
	}
	
	double t0 = (double) m_platform.getTime() / 1000.0;
	float delta = (t0 - m_lastFrameTime);
	m_lastFrameTime = t0;
	
	m_currentGame->update(m_platform, delta);
}

void Game::draw()
{
	m_currentGame->draw(*m_window->getRenderer());
}

#ifndef __EMSCRIPTEN__
int Game::run(int argc, char** argv)
{
	// Set loading mode
#if ASSET_MODE != 0
	const char* pkg = (ASSET_MODE == 1 ? argv[0] : "data.neo");
	if(!Neo::VFSOpenHook::mount(pkg, argv[0]))
	{
		std::cerr << "Could not open assets file!" << std::endl;
		return 1;
	}
#endif
	
	m_running = true;
	while(m_running && (m_currentGame || m_requestedGame))
	{
		update();
		draw();
	}

	return 0;
}
#else
static Neo::Game* game = nullptr;
const char* arg0 = nullptr;
void doIteration()
{
	game->update();
	game->draw();
}

int Game::run(int argc, char** argv)
{
	arg0 = argv[0];
	game = this;

	std::string fullpath = getenv("PWD");
	emscripten_async_wget((fullpath + "data.neo").c_str(), "data.neo",
		[](const char* s){
			std::cout << "Done downloading " << s << std::endl;
		
			if(!Neo::VFSOpenHook::mount("data.neo", arg0))
			{
				std::cerr << "Could not open assets file!" << std::endl;
				return;
			}

			emscripten_resume_main_loop();
		},

		[](const char* s){
			std::cerr << "Error: Could not download " << s << std::endl;
			exit(1);
		});
	
	return 0;
}
#endif
