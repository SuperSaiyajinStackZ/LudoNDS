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
#include <vector>

static const std::vector<Structs::ButtonPos> LangPos = {
	{ 14, 40, 14, 14 },
	{ 14, 70, 14, 14 }
};

const std::vector<std::string> Languages = { "Deutsch", "English" };

void Overlays::LanguageOverlay() {
	uint8_t lang = konfiguration->Language();
	bool doOut = false;

	Gui::TopBG.draw(0, 0, true, 3, true);
	Gui::font.clear();
	Gui::font.print(Lang::get("SELECT_LANG"), 0, 2, true, 2, Alignment::center);

	Gui::BottomBG.draw(0, 0, false, 3, true);
	for (uint8_t i = 0; i < 2; i++) {
		Gui::LangButtons[i].visibility(true);
		Gui::LangButtons[i].position(LangPos[i].x, LangPos[i].y);
		Gui::font.print(Languages[i], LangPos[i].x + 20, LangPos[i].y, false, 2, Alignment::left);
	}

	Gui::LangSelector.visibility(true);
	Gui::LangSelector.position(LangPos[lang].x, LangPos[lang].y);

	Gui::font.update();
	Gui::LangSelector.update();

	while(!doOut) {
		touchPosition touch;
		scanKeys();
		uint32_t hDown = keysDown();
		touchRead(&touch);

		if (hDown & KEY_DOWN) {
			if (lang < 1) {
				lang++;
				Gui::LangSelector.position(LangPos[lang].x, LangPos[lang].y);
				Gui::LangSelector.update();
			}
		}

		if (hDown & KEY_UP) {
			if (lang > 0) {
				lang--;
				Gui::LangSelector.position(LangPos[lang].x, LangPos[lang].y);
				Gui::LangSelector.update();
			}
		}

		if (hDown & KEY_TOUCH) {
			for (uint8_t i = 0; i < 2; i++) {
				if (touching(touch, LangPos[i])) {
					konfiguration->Language(i);
					Lang::load(konfiguration->Language());
					doOut = true;
				}
			}
		}

		if (hDown & KEY_A) {
			konfiguration->Language(lang);
			Lang::load(konfiguration->Language());
			doOut = true;
		}

		if (hDown & KEY_B) doOut = true;

		swiWaitForVBlank();
	};

	for (uint8_t i = 0; i < 2; i++) Gui::LangButtons[i].visibility(false);
	Gui::LangSelector.visibility(false);
	Gui::LangSelector.update();
}