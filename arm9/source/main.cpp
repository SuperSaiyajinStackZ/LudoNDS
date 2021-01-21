/*
	Diese Datei ist Teil von LudoNDS.
	Copyright (C) 2021 bei SuperSaiyajinStackZ.

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

	Additional Terms 7.b and 7.c of GPLv3 apply to this file:
		* Requiring preservation of specified reasonable legal notices or
		  author attributions in that material or in the Appropriate Legal
		  Notices displayed by works containing it.
		* Prohibiting misrepresentation of the origin of that material,
		  or requiring that modified versions of such material be marked in
		  reasonable ways as different from the original version.
*/

#include "common.hpp"
#include "gameScreen.hpp"
#include "nitrofs.h"
#include <dirent.h>
#include <fat.h>
#include <nds.h>

bool isTesting = false; // Setze zu true für No$GBA.

/*
	Falls eine bestimmte position berührt wird.. mache etwas.

	touchPosition touch: Die touchPosition variable. In der regel als "touch" angegeben.
	Structs::ButtonPos pos: Der strukt.
*/
bool touching(touchPosition touch, Structs::ButtonPos pos) {
	if (touch.px >= pos.x && touch.px <= (pos.x + pos.w) && touch.py >= pos.y && touch.py <= (pos.y + pos.h)) return true;
	return false;
}

int main(int argc, char **argv) {
	Graphics::init();
	keysSetRepeat(25, 5);
	defaultExceptionHandler();

	Graphics::drawRectangle(0, 0, 256, 192, DARKERER_GRAY, DARKER_GRAY, true, false);
	Graphics::drawRectangle(0, 0, 256, 192, DARKERER_GRAY, DARKER_GRAY, false, false);

	if (!isTesting) {
		/* Initialisiere Datei-System. */
		if (!fatInitDefault()) {
			consoleDemoInit();
			printf("fatInitDefault() failed...");
			printf("\nPress START to exit.");

			while(1) {
				scanKeys();
				if (keysDown() & KEY_START) return 0;
				swiWaitForVBlank();
			}
		}
	}

	/* Erstelle Ordner, falls nicht existierend. */
	if (!isTesting) {
		mkdir("/_nds", 0777);
		mkdir("/_nds/LudoNDS", 0777);
	}

	/* Versuche NitroFS von den bereitgestellten Argumenten zu initialisieren. */
	if (!nitroFSInit(argv[0])) {
		/* Falls das fehlschlägt, versuche NitroFS an 'LudoNDS.nds' anzuwenden. */
		if (!nitroFSInit("LudoNDS.nds")) {
			/* Falls das fehlschlägt, versuche '/_nds/LudoNDS/LudoNDS.nds'. */
			if (!nitroFSInit("/_nds/LudoNDS/LudoNDS.nds")) {
				consoleDemoInit();
				printf("nitroFSInit() failed...");
				printf("\nPress START to exit.");

				while(1) {
					scanKeys();
					if (keysDown() & KEY_START) return 0;
					swiWaitForVBlank();
				}
			}
		}
	}

	konfiguration = std::make_unique<Settings>();
	Lang::load(konfiguration->Language());
	Gui::Init();
	Overlays::SplashOverlay();
	Screen::set(std::make_unique<GameScreen>());
	Screen::doDraw();
	CoreHelper::GenerateSeed();

	while(!exiting) {
		touchPosition touch;
		scanKeys();
		uint32_t hDown = keysDown();
		uint32_t hHeld = keysHeld();
		touchRead(&touch);

		Screen::doLogic(hDown, hHeld, touch);
		swiWaitForVBlank();
	};

	konfiguration->Save();

	return 0;
}