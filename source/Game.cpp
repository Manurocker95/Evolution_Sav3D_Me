#include "Game.h"

/* This file is part of Evolution Sav3D Me!

	 Copyright (C) 2016 Manuel Rodríguez Matesanz
>    This program is free software: you can redistribute it and/or modify
>    it under the terms of the GNU General Public License as published by
>    the Free Software Foundation, either version 3 of the License, or
>    (at your option) any later version.
>
>    This program is distributed in the hope that it will be useful,
>    but WITHOUT ANY WARRANTY; without even the implied warranty of
>    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
>    GNU General Public License for more details.
>
>    You should have received a copy of the GNU General Public License
>    along with this program.  If not, see <http://www.gnu.org/licenses/>.
>    See LICENSE for information.
*/

// #================================================================#
// #		Clase Juego - El core del juego se lleva aquí			#
// #				Hecho por Manurocker95							#
// #					25/01/2017									#
// #================================================================#

// Constructor
Game::Game()
{	
	m_playingMusicTitle = false;
	m_playingMusicGame = false;
	m_sfxSplash = false;
	ndspChnWaveBufClear(1);
	ndspChnWaveBufClear(2);
	m_screen = SPLASH;
	m_state = NONE;
	fnt = new BmpFont(FONT_BFF);
	font = sftd_load_font_mem(pixelated_ttf, pixelated_ttf_size);
	fnt->setTabWidth(80);
	m_splashScreen = sfil_load_PNG_file(IMG_SPLASHSCREEN, SF2D_PLACE_RAM);
	m_backgroundImageBot = sfil_load_PNG_file(IMG_SPLASHSCREENBOTTOM, SF2D_PLACE_RAM);
	m_DebugMode = DEBUGMODE;
	m_splashOpeningState = 0;
	m_scTimer = 0;
	m_activeBananas = 0;
	m_rayCounter = 0;
	m_deltaRay = 0;
	m_timeToSpawn = TIME_TO_SPAWN_RAYS;
}

void Game::OpeningAnimation()
{


}

// Draw - Se pintan los gráficos
void Game::Draw()
{
	switch(m_screen)
	{
	case SPLASH:

		if (m_splashOpeningState == 0)
		{
			sf2d_start_frame(GFX_TOP, GFX_LEFT);
			sf2d_draw_texture_blend(m_splashScreen, 0, 0, RGBA8(255, 255, 255, m_splashOpacity));
			sf2d_end_frame();

			sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
			sf2d_draw_texture_blend(m_backgroundImageBot, 0, 0, RGBA8(255, 255, 255, m_splashOpacity));

			if (m_DebugMode)
				fnt->drawStr("FPS:" + std::to_string(sf2d_get_fps()), 5, 5, RGBA8(0x00, 0x00, 0x00, 0xFF));

			sf2d_end_frame();

			m_splashOpacity += 3;

			if (m_splashOpacity >= 255)
			{
				m_splashOpacity = 255;
				m_splashOpeningState = 1;

				if (!m_sfxSplash)
				{
					m_sfxSplash = true;
					m_sfx = new sound (SND_SFX_SPLASH, 2, false, false);
					m_sfx->play();
				}
			}
		}
		else if (m_splashOpeningState == 1)
		{
			m_scTimer += 5;

			sf2d_start_frame(GFX_TOP, GFX_LEFT);
			sf2d_draw_texture_blend(m_splashScreen, 0, 0, RGBA8(255, 255, 255, m_splashOpacity));
			sf2d_end_frame();

			sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
			sf2d_draw_texture_blend(m_backgroundImageBot, 0, 0, RGBA8(255, 255, 255, m_splashOpacity));
			if (m_DebugMode)
				fnt->drawStr("FPS:" + std::to_string(sf2d_get_fps()), 5, 5, RGBA8(0x00, 0x00, 0x00, 0xFF));
			sf2d_end_frame();

			if (m_scTimer >= 300)
			{
				m_splashOpeningState = 2;
			}
		}
		else 
		{
			sf2d_start_frame(GFX_TOP, GFX_LEFT);
			sf2d_draw_texture_blend(m_splashScreen, 0, 0, RGBA8(255, 255, 255, m_splashOpacity));
			sf2d_end_frame();

			sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
			sf2d_draw_texture_blend(m_backgroundImageBot, 0, 0, RGBA8(255, 255, 255, m_splashOpacity));
			if (m_DebugMode)
				fnt->drawStr("FPS:" + std::to_string(sf2d_get_fps()), 5, 5, RGBA8(0x00, 0x00, 0x00, 0xFF));
			sf2d_end_frame();

			m_splashOpacity -= 3;

			if (m_splashOpacity <= 0)
			{
				m_screen = TITLESCREEN;
				sf2d_free_texture(m_splashScreen);
				m_backgroundImageTop = sfil_load_PNG_file(IMG_BG_TITLE_TOP, SF2D_PLACE_RAM);
				m_backgroundImageBot = sfil_load_PNG_file(IMG_BG_TITLE_BOT, SF2D_PLACE_RAM);
				m_buttonPlay = sfil_load_PNG_file(IMG_BT_PLAY, SF2D_PLACE_RAM);
				m_buttonBestScore = sfil_load_PNG_file(IMG_BT_BESTSCORE, SF2D_PLACE_RAM);
			}
		}
		break;
	case TITLESCREEN:
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
		//sf2d_draw_texture_part(pkmIconsGBC, x, y, 16 * (frame + (icon % PKM_PER_ROW) * 2), 16 * (icon / PKM_PER_ROW), 16, 16);
		sf2d_draw_texture(m_backgroundImageTop, 0, 0);
		sf2d_end_frame();

		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		sf2d_draw_texture(m_backgroundImageBot, 0, 0);
		sf2d_draw_texture(m_buttonPlay, 100, 65);
		sf2d_draw_texture(m_buttonBestScore, 90, 145);
		
		sftd_draw_text(font, 125, 150, C_BLUE, 20, "Best:");
		sftd_draw_text(font, 185, 150, C_BLUE, 20, std::to_string(m_maxScore).c_str());

		if (m_DebugMode)
			fnt->drawStr("FPS:" + std::to_string(sf2d_get_fps()), 5, 5, RGBA8(0x00, 0x00, 0x00, 0xFF));


		sftd_draw_text(font, 50, HEIGHT-20, C_WHITE, 12, "(C) Manurocker95 2017");
		sftd_draw_text(font, 230, HEIGHT - 20, C_WHITE, 12, "VERSION:");
		sftd_draw_text(font, 280, HEIGHT - 20, C_WHITE, 12, VERSION);
		sf2d_end_frame();

		break;
	case GAME:
		//sf2d_draw_texture_part(pMenu->gamemenu_get_sprite(), 90 - render_offset_3d * 2, 70, 0, 0, 213, 130);
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
		sf2d_draw_texture(m_backgroundImageTop, 0, 0);
		
		m_bananas[0]->Draw();
		m_bananas[1]->Draw();
		m_bananas[2]->Draw();
		
		m_fire->Draw();
		m_player->Draw();
		
		if (m_rayCounter > 0)
			m_rays[0]->Draw();
			
		sf2d_draw_texture(m_buttonBestScore, 120, 0);
		sftd_draw_text(font, 145, 5, C_BLUE, 20, "Score:");
		sftd_draw_text(font, 225, 5, C_BLUE, 20, std::to_string(m_score).c_str());

		if (m_state == PAUSE)
		{
			sf2d_draw_texture(m_splashScreen, 0, 0);
			sftd_draw_text(font, 40, 160, C_BLUE, 15, "Tap the bottom screen or Press A/Start to resume.");
		}

		sf2d_end_frame();

		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		sf2d_draw_texture(m_backgroundImageBot, 0, 0);
		sf2d_draw_texture(m_buttonPlay, 100, 65);
		sf2d_draw_texture(m_buttonBestScore, 90, 145);
		sftd_draw_text(font,125,150,C_BLUE,20, "Best:");
		sftd_draw_text(font, 185, 150, C_BLUE, 20, std::to_string(m_maxScore).c_str());

		if (m_state == PAUSE)
		{
			sf2d_draw_texture(m_splashScreen, -40, 0);
		}

		if (m_DebugMode)
		{
			fnt->drawStr("FPS:" + std::to_string(sf2d_get_fps()), 5, 5, RGBA8(0x00, 0x00, 0x00, 0xFF));
			fnt->drawStr("RayCounter:" + std::to_string(m_rayCounter), 5, 15, RGBA8(0x00, 0x00, 0x00, 0xFF));
			fnt->drawStr("RayTimer:" + std::to_string(m_deltaRay), 5, 25, RGBA8(0x00, 0x00, 0x00, 0xFF));
			fnt->drawStr("Invincible:" + std::to_string(m_player->getInvincible()), 5, 35, RGBA8(0x00, 0x00, 0x00, 0xFF));
			if (m_rayCounter > 0)
				fnt->drawStr("Invincible:" + std::to_string(m_rays[0]->getCounter()), 5, 45, RGBA8(0x00, 0x00, 0x00, 0xFF));
			
		}
		sf2d_end_frame();
	
		break;
	case ENDSCREEN:
	
		//sf2d_draw_texture_part(pMenu->gamemenu_get_sprite(), 90 - render_offset_3d * 2, 70, 0, 0, 213, 130);
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
		sf2d_draw_texture(m_backgroundImageTop, 0, 0);
		sf2d_end_frame();

		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		sf2d_draw_texture(m_backgroundImageBot, 0, 0);
		sftd_draw_text(font, 70, 130, C_WHITE, 20, "Tap the bottom screen.");
		if (m_DebugMode)
			fnt->drawStr("FPS:" + std::to_string(sf2d_get_fps()), 5, 5, RGBA8(0x00, 0x00, 0x00, 0xFF));
		sf2d_end_frame();

		break;
	}

	// Swap Buffers
	sf2d_swapbuffers();
}

void Game::InitializeGame()
{
	m_bgm->stop();
	m_sfxBanana = new sound(SND_SFX_BANANA, 2, false, false);
	m_player = new Monkey(200, 120, sfil_load_PNG_file(IMG_MONKEY_SPRITE, SF2D_PLACE_RAM), true, 4, 32);
	
	for (int i = 0; i < MAX_BANANAS; i++)
	{
		m_bananas[i] = new Object(Object::BANANA, sfil_load_PNG_file(IMG_BANANA_SPRITE, SF2D_PLACE_RAM),-CELL_SIZE, -CELL_SIZE, 4, 32, true);
	}
	
	m_fire = new Object(Object::FIRE, sfil_load_PNG_file(IMG_FIRE_SPRITE, SF2D_PLACE_RAM), -CELL_SIZE, -CELL_SIZE, 4, 32, true);

	m_score = 0;
	m_state = PLAYING;
	m_screen = GAME;
	m_playingMusicTitle = false;
	m_splashScreen = sfil_load_PNG_file(IMG_BG_PAUSE, SF2D_PLACE_RAM);
	m_backgroundImageTop = sfil_load_PNG_file(IMG_BG_GAME_TOP, SF2D_PLACE_RAM);
	m_buttonPlay = sfil_load_PNG_file(IMG_BT_PAUSE, SF2D_PLACE_RAM);
	m_timeToSpawn = TIME_TO_SPAWN_RAYS;
	m_bananaTimer = 0;
	m_fireTimer = 0;
	m_activeBananas = 0;
	m_rayCounter = 0;
	m_deltaRay = 0;
	m_invincibleTimer = 0;
}

// Cada frame comprobamos los inputs
void Game::CheckInputs()
{
	hidScanInput();

	//Salimos pulsando Select
	if ((hidKeysDown() & KEY_SELECT))
	{
		m_state = OUT;
		End();
	}

	if ((hidKeysDown() & KEY_R) && (hidKeysDown() & KEY_L))
	{
		m_DebugMode = !m_DebugMode;
	}

	if ((hidKeysDown() & KEY_SELECT) && (hidKeysDown() & KEY_R))
	{
		saveScoreAndExit();
	}

	switch (m_screen)
	{
	case SPLASH:
		if ((m_DebugMode) && (hidKeysDown() & KEY_TOUCH))
		{
			m_screen = TITLESCREEN;
			sf2d_free_texture(m_splashScreen);
			m_backgroundImageTop = sfil_load_PNG_file(IMG_BG_TITLE_TOP, SF2D_PLACE_RAM);
			m_backgroundImageBot = sfil_load_PNG_file(IMG_BG_TITLE_BOT, SF2D_PLACE_RAM);
			m_buttonPlay = sfil_load_PNG_file(IMG_BT_PLAY, SF2D_PLACE_RAM);
			m_buttonBestScore = sfil_load_PNG_file(IMG_BT_BESTSCORE, SF2D_PLACE_RAM);
		}
		break;
	case TITLESCREEN:

		if (hidKeysDown() & KEY_TOUCH)
		{
			hidTouchRead(&touch);
			if ((touch.px > 100 && touch.px < 260) && (touch.py > 65 && touch.py < 120))
			{
				//Inicializamos el juego
				InitializeGame();
			}
		}

		// Si en la pantalla de título pulsamos A
		if (hidKeysDown() & KEY_A)
		{
			//Inicializamos el juego
			InitializeGame();
		}

		break;
	case GAME:
		
		held = hidKeysHeld();

		if (m_state == PAUSE)
		{
			if ((hidKeysDown() & KEY_TOUCH) || (hidKeysDown() & KEY_A) || (hidKeysDown() & KEY_START))
			{
				m_state = PLAYING;
				return;
			}
		}
		else
		{
			if ((hidKeysDown() & KEY_LEFT))
			{
				m_player->move(-CELL_SIZE, true);
			}

			if (hidKeysDown() & KEY_RIGHT)
			{
				m_player->move(CELL_SIZE, true);
			}

			if (hidKeysDown() & KEY_UP)
			{
				m_player->move(-CELL_SIZE, false);
			}

			if (hidKeysDown() & KEY_DOWN)
			{
				m_player->move(CELL_SIZE, false);
			}

			m_player->Update();

			m_bananas[0]->Update();
			m_bananas[1]->Update();
			m_bananas[2]->Update();

			m_fire->Update();

			if (m_rayCounter > 0)
				m_rays[0]->Update();

			if (hidKeysDown() & KEY_TOUCH)
			{
				hidTouchRead(&touch);
				if ((touch.px > 100 && touch.px < 260) && (touch.py > 65 && touch.py < 120))
				{
					m_state = PAUSE;	
				}
			}

			if ((hidKeysDown() & KEY_START))
			{
				m_state = PAUSE;
			}
		}
		break;
	case ENDSCREEN:
		if ((hidKeysDown() & KEY_TOUCH) || (hidKeysDown() & KEY_A))
		{
			m_bgm2->stop();
			m_playingMusicGame = false;
			m_screen = TITLESCREEN;
			m_backgroundImageTop = sfil_load_PNG_file(IMG_BG_TITLE_TOP, SF2D_PLACE_RAM);
			m_backgroundImageBot = sfil_load_PNG_file(IMG_BG_TITLE_BOT, SF2D_PLACE_RAM);
			m_buttonPlay = sfil_load_PNG_file(IMG_BT_PLAY, SF2D_PLACE_RAM);
			m_buttonBestScore = sfil_load_PNG_file(IMG_BT_BESTSCORE, SF2D_PLACE_RAM);
		}
		break;
	}
}

void Game::UpdateGame()
{
	switch (m_screen)
	{
	case TITLESCREEN:
		if (!m_playingMusicTitle)
		{
			ndspChnWaveBufClear(1);
			m_bgm = new sound(SND_BGM_TITLE, 1, true, false);
			m_bgm->play();
			m_playingMusicTitle = true;
		}
		break;
	case GAME:
		
		if (!m_playingMusicGame)
		{
			ndspChnWaveBufClear(1);
			m_bgm2 = new sound(SND_BGM_GAME, 1, true);
			m_bgm2->play();
			m_playingMusicGame = true;
		}

		if (m_state == PLAYING)
		{
			if (m_bananaTimer >= BANANATIMER)
			{
				m_bananaTimer = 0;

				if (m_activeBananas < MAX_BANANAS)
				{
					int x = rand() % (8) + 1; //
					int y = rand() % (4) + 1;

					m_activeBananas++;
					m_bananas[m_activeBananas - 1]->setActive(true);
					m_bananas[m_activeBananas - 1]->setX(x*CELL_SIZE);
					m_bananas[m_activeBananas - 1]->setY(y*CELL_SIZE);
				}
				else
				{
					int bananaN = rand() % 3;

					int x = rand() % (8) + 1; //
					int y = rand() % (4) + 1;

					m_bananas[bananaN]->setActive(true);
					m_bananas[bananaN]->setX(x*CELL_SIZE);
					m_bananas[bananaN]->setY(y*CELL_SIZE);

				}
			}
			else
			{
				m_bananaTimer++;
			}

			if (m_bananas[0]->CheckCollision(m_player))
			{
				m_activeBananas--;
				m_bananas[0]->setActive(false);
				addScore(SCORE_TO_ADD);
				m_bananas[0]->moveToCoord(-CELL_SIZE, -CELL_SIZE);

				ndspChnWaveBufClear(2);
				m_sfxBanana->play();
			}
			if (m_bananas[1]->CheckCollision(m_player))
			{
				m_activeBananas--;
				m_bananas[1]->setActive(false);
				addScore(SCORE_TO_ADD);
				m_bananas[1]->moveToCoord(-CELL_SIZE, -CELL_SIZE);

				ndspChnWaveBufClear(2);
				m_sfxBanana->play();
			}
			if (m_bananas[2]->CheckCollision(m_player))
			{
				m_activeBananas--;
				m_bananas[2]->setActive(false);
				addScore(SCORE_TO_ADD);
				m_bananas[2]->moveToCoord(-CELL_SIZE, -CELL_SIZE);
				
				ndspChnWaveBufClear(2);
				m_sfxBanana->play();

			}

			if (m_player->getInvincible())
			{
				if (m_invincibleTimer >= POWERUPTIME)
				{
					m_fireTimer = 0;
					m_invincibleTimer = 0;
					m_player->setInvincible(false);
					m_player->setSprite(sfil_load_PNG_file(IMG_MONKEY_SPRITE, SF2D_PLACE_RAM));
					m_player->setFrameSize(32);
				}
				else
				{
					m_invincibleTimer++;
				}
			}
			else
			{
				if (m_fireTimer >= FIRETIMER)
				{
					m_fireTimer = 0;
					int x = CELL_SIZE;
					int y = CELL_SIZE;
					do
					{
						x = rand() % (8) + 1; //
						y = rand() % (4) + 1;
					
					} while ((x*CELL_SIZE == m_player->getX() && y*CELL_SIZE == m_player->getY()) || (x*CELL_SIZE == m_bananas[0]->getX() && y*CELL_SIZE == m_player->getY()) || (x*CELL_SIZE == m_bananas[1]->getX() && y*CELL_SIZE == m_player->getY()) || (x*CELL_SIZE == m_bananas[2]->getX() && y*CELL_SIZE == m_player->getY()));
					
					m_fire->setActive(true);
					m_fire->setX(x*CELL_SIZE);
					m_fire->setY(y*CELL_SIZE);
				}
				else
				{
					m_fireTimer++;
				}

				if (m_fire->isActive())
				{
					if (m_fire->CheckCollision(m_player))
					{
						m_fire->moveToCoord(-CELL_SIZE, -CELL_SIZE);
						m_fireTimer = 0;
						m_invincibleTimer = 0;
						m_player->setInvincible(true);
						m_player->setSprite(sfil_load_PNG_file(IMG_MONKEYFIRE_SPRITE, SF2D_PLACE_RAM));
						m_player->setFrameSize(40);
					}
				}
			}


			// RAYOS:
			
			if (m_rayCounter == 0)
			{
				m_deltaRay++;

				if (m_deltaRay >= m_timeToSpawn)
				{
					m_rayCounter++;
					m_rays[0] = new Ray();
					m_deltaRay = 0;
				}
			}
			else
			{
				m_deltaRay++;

				if (m_deltaRay >= m_timeToSpawn)
				{
					m_rays[0]->loadData();
					m_deltaRay = 0;
				}

				if (m_rays[0]->CheckCollision(m_player))
				{
					m_state = DYING;
					m_player->setState(Monkey::DYING);
					m_player->setSprite(sfil_load_PNG_file(IMG_MONKEY_SPRITE_DYING, SF2D_PLACE_RAM));
					m_player->setFrameSize(32);
					m_player->setNumFrames(8);
					m_rayCounter--;
					m_deltaRay = 0;
					delete(m_rays[0]);
				}
			}
			

		}
		else if (m_state == PAUSE)
		{
			Draw();
		}
		else if (m_state == DYING)
		{
			m_state = DEAD;
			m_player->setState(Monkey::DEAD);
			m_player->setSprite(sfil_load_PNG_file(IMG_MONKEY_SPRITE_DEAD, SF2D_PLACE_RAM));
			m_player->setFrameSize(32);
			m_player->setNumFrames(4);
			Draw();
		}
		else if (m_state == DEAD)
		{
			Draw();
			saveScoreAndExit();
		}

		break;
	case ENDSCREEN:
		break;
	}
}

// Método que llama cada frame a los inputs y al dibujado 
void Game::Update()
{
	fps = "FPS: " + ((int)sf2d_get_fps());

	UpdateGame();
	CheckInputs();
	Draw();
}

void Game::ShowMessage(std::string msg, int x, int y, int size, u32 color, gfxScreen_t screen, gfx3dSide_t side)
{
	sf2d_start_frame(screen, side);
	fnt->drawStr(msg, x, y, color);
	sf2d_end_frame();
}

void Game::addScore(int value)
{
	m_score += value;
}

int Game::getScore() const
{
	return m_score;
}

Game::States Game::getState()
{
	return m_state;
}

void Game::setDebug(bool value)
{
	m_DebugMode = value;
}

bool Game::getDebug()
{
	return m_DebugMode;
}

bool Game::isOut()
{
	if (m_state == OUT)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Game::End()
{
	m_player->end();
	m_bananas[0]->End();
	m_bananas[1]->End();
	m_bananas[2]->End();
	m_fire->End();
	sf2d_free_texture(m_buttonPlay);
	sf2d_free_texture(m_splashScreen);
	sf2d_free_texture(m_backgroundImageTop);
	sf2d_free_texture(m_backgroundImageBot);
	sf2d_free_texture(m_buttonBestScore);
}

void Game::setMaxScore(int value)
{
	m_maxScore = value;
}

void Game::saveScoreAndExit()
{
	sf2d_free_texture(m_backgroundImageTop);
	sf2d_free_texture(m_backgroundImageBot);

	m_backgroundImageTop = sfil_load_PNG_file(IMG_BG_GAMEOVER_TOP, SF2D_PLACE_RAM);
	m_backgroundImageBot = sfil_load_PNG_file(IMG_BG_GAMEOVER_BOT, SF2D_PLACE_RAM);

	m_screen = ENDSCREEN;

	if (m_score > m_maxScore)
	{
		m_maxScore = m_score;
	}
	
	std::ofstream ofs;
	ofs.open(SCORE_FILE, std::ofstream::out | std::ofstream::trunc);
	ofs << m_score;
	ofs.close();
}