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
#include "sprite.hpp"

const std::vector<Structs::ButtonPos> InitPos = {
	{ 89, 164 + 7, 14, 14 },
	{ 29, 89 + 7, 14, 14 },
	{ 89, 44 + 7, 14, 14 },
	{ 119, 89 + 7, 14, 14 }
};

void Overlays::SplashOverlay() {
	Sprite SplashChips[4];
	Image sD = Image("nitro:/graphics/dice/splashDie.gfx");

	/* Initialisiere Sprites. */
	for (uint8_t i = 0; i < 4; i++) {
		SplashChips[i] = Sprite(true, SpriteSize_32x32, SpriteColorFormat_Bmp);
		SplashChips[i].drawImage(0, 0, Image("nitro:/graphics/chips/chip_" + std::to_string(i + 1) + ".gfx"));
		SplashChips[i].position(InitPos[i].x, InitPos[i].y);
		SplashChips[i].visibility(true);
	}

	bool DoOut = false, DoDraw = true;
	uint8_t ToMove = 15 * 4; // 15 -> FeldGröße; 4 -> Felder Anzahl.

	while(!DoOut) {
		if (DoDraw) {
			DoDraw = false;

			Gui::BottomBG.draw(0, 0, true, 3, true);
			Gui::TitleBar.drawSpecial(0, 0, true, 3, 1, 1, 10, true);
			Gui::BottomBG.draw(0, 0, false, 3, true);
			Gui::MainField.draw(13, 20, true, 3, true);

			/* Häuser. */
			Gui::Homes[0].draw(13, 106 + 20, true, 3, true);
			Gui::Homes[1].draw(13, 20, true, 3, true);
			Gui::Homes[2].draw(106 + 13, 20, true, 3, true);
			Gui::Homes[3].draw(106 + 13, 106 + 20, true, 3, true);

			sD.draw(179 + 12, 20 + 59, true, 3, true);

			Gui::font.clear();
			Gui::font.print("LudoNDS", 0, 3, true, 2, Alignment::center);
			Gui::font.update();

			SplashChips[0].update();
		}

		if (ToMove > 0) {
			for (uint8_t i = 0; i < 3; i++) swiWaitForVBlank();
			SplashChips[0].position(SplashChips[0].x(), SplashChips[0].y() - 1);
			SplashChips[0].update();
			ToMove--;

			if (ToMove == 0) DoOut = true;
		}
	};

	/* Verstecke Sprites. */
	for (uint8_t i = 0; i < 4; i++) SplashChips[i].visibility(false);
	SplashChips[0].update();
}