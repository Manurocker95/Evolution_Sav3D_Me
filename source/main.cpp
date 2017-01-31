#if __INTELLISENSE__
typedef unsigned int __SIZE_TYPE__;
typedef unsigned long __PTRDIFF_TYPE__;
#define __attribute__(q)
#define __builtin_strcmp(a,b) 0
#define __builtin_strlen(a) 0
#define __builtin_memcpy(a,b) 0
#define __builtin_va_list void*
#define __builtin_va_start(a,b)
#define __extension__
#endif

#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

// #================================================================#
// #		Clase main - El bucle principal corre aquí				#
// #				Hecho por Manurocker95							#
// #					25/01/2017									#
// #================================================================#

#include "Libraries.h"
#include "Game.h"

void initializeFonts()
{

}

ndspWaveBuf waveBuf;

int main()
{

	// Set the random seed based on the time
	srand(time(NULL));

	// Inicializamos los servicios
	// Srv
	srvInit();

	// SF2D + SFIL (Imágenes + gpu)
	sf2d_init();
	sf2d_set_clear_color(RGBA8(0, 0, 0, 255));
	//sf2d_set_clear_color(RGBA8(255, 255, 255, 255));
	sf2d_set_3D(false);
	//sf2d_set_vblank_wait(0);

	//Sftd (Textos)
	sftd_init();

	// Romfs
	//romfsInit();

	// Sound
	
	ndspInit();

	//MAX SCORE DATA
	ifstream myReadFile(SCORE_FILE);
	int score;
	myReadFile >> score;

	if (score == NULL)
	{
		score = 0;
	}

	// Creamos el objeto juego
	Game* m_game = new Game();
	m_game->setMaxScore(score);

	while (aptMainLoop())
	{
		// Update: Check inputs + Draw
		m_game->Update();

		if (m_game->isOut())
		{
			break;
		}

		sf2d_swapbuffers();
	}

	delete (m_game);

	// Salimos de los servicios y eliminamos de memoria los obj. sobrantes
	//romfsExit();
	ndspExit();
	sf2d_fini();
	sftd_fini();

	return 0;
}