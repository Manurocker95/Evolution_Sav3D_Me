#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "Libraries.h"
#include "Monkey.h"
#include "Object.h"
#include "Ray.h"
#include "filepaths.h"
#include "pixelated_ttf.h"

#define MAX_BANANAS 3
#define BANANATIMER 150
#define FIRETIMER 400
#define POWERUPTIME 250
#define SCORE_TO_ADD 1
#define TIME_TO_SPAWN_RAYS 200
#define DYINGTIME 200

/* This file is part of Evolution Sav3D Me!

Copyright (C) 2016 Manuel Rodr�guez Matesanz
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

class Game
{

public:
	enum States { PLAYING, PAUSE, DYING, DEAD, OUT, NONE};    // Enumeraci�n de estados: Si est� vivo y juegando/en pausa o muerto
	enum Screens { SPLASH, TITLESCREEN, GAME, ENDSCREEN };// 0=Pantalla de t�tulo, 1=Pantalla de juego, 2=Pantalla de muerte
	Game();									// Constructor
	void CheckInputs();						// M�todo que comprueba los inputs del jugador para mover al personaje o pausar el juego
	void Update();							// M�todo que se llama cada frame
	void Draw();							// M�todo que dibuja los gr�ficos		
	void InitializeGame();					// M�todo que inicializa el juego
	States getState();						// M�todo que devuelve el estado actual del juego
	void setMaxScore(int value);			// M�todo que establece la m�xima puntuaci�n
	void saveScoreAndExit();				// M�todo que llama a guardar la puntuaci�n y se va al Endscreen
	void setDebug(bool value);				// M�todo que establece el modo debug (Activado/Desactivado)
	bool getDebug();						// M�todo que devuelve el valor de si es� o no activado el modo debug
	void OpeningAnimation();				// M�todo que muestra una animaci�n de entrada (Se abre el escenario)
	void addScore(int value);				// M�todo que establece la puntuaci�n a�adiendola
	int getScore() const;					// M�todo que devuelve la puntuaci�n
	bool isOut();							// M�todo para saber si se sale del programa
	void UpdateGame();
	void End();
	void ShowMessage(std::string msg, int x, int y, int size, u32 color, gfxScreen_t screen, gfx3dSide_t side, bool sftdlib);// M�todo que meustra un mensaje
private:
	States m_state;							// Estado actual de juego
	Screens m_screen;						// 0=Pantalla de t�tulo, 1=Pantalla de juego, 2=Pantalla de muerte
	int m_score;							// Puntuaci�n actual
	int m_maxScore;							// M�xima puntuaci�n conseguida
	int m_splashOpacity;
	int m_splashOpeningState;
	int	m_scTimer;
	int m_activeBananas;
	int m_bananaTimer;
	int m_fireTimer;
	int m_invincibleTimer;
	int m_dyingTimer;
	int m_timeToSpawn;
	bool m_DebugMode;						// Si el debug mode est� activado o no					
	Monkey* m_player;
	Object* m_bananas [MAX_BANANAS];
	Object* m_fire;
	Ray* m_rays [32]; //8x4
	int m_rayCounter;
	int m_deltaRay;
	sf2d_texture* m_backgroundImageTop;			//
	sf2d_texture* m_backgroundImageBot;
	sf2d_texture* m_buttonPlay;
	sf2d_texture* m_buttonBestScore;
	sf2d_texture* m_splashScreen;
	std::string fps;
	u32 held;
	touchPosition touch;
	BmpFont* fnt;
	sftd_font* font;

	//Audio
	ndspWaveBuf waveBuf;
	bool m_playingMusicTitle;
	sound* m_bgm;
	sound* m_bgm2;
	sound* m_bgmInvencible;
	bool m_playingMusicGame;
	sound* m_sfx;
	sound* m_sfxBanana;
	sound* m_sfxFire;
	bool m_sfxSplash;
	u8* data = NULL;
};

#endif

