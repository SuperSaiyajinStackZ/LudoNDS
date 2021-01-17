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

extern bool touching(touchPosition touch, Structs::ButtonPos pos);

void Msg::DisplayMsg(const std::string &msg) {
	Gui::TopBG.draw(0, 0, true, 3, true);
	Gui::MsgBox.draw(10, 18 + 8, true, 3, true);
	Gui::font.clear();
	Gui::font.print(msg, 10 + 8, 18 + 8 + 4, true, 2, Alignment::left);
	Gui::BottomBG.draw(0, 0, false, 3, true);
	Gui::font.update();
}

void Msg::WaitMsg(const std::string &msg) {
	Gui::TopBG.draw(0, 0, true, 3, true);
	Gui::MsgBox.draw(10, 18 + 8, true, 3, true);
	Gui::font.clear();
	Gui::font.print(msg, 10 + 8, 18 + 8 + 4, true, 2, Alignment::left);
	Gui::font.print(Lang::get("A_CONTINUE"), 0, 175, true, 2, Alignment::center);
	Gui::BottomBG.draw(0, 0, false, 3, true);
	Gui::font.update();

	bool doOut = false;
	while(!doOut) {
		swiWaitForVBlank();
		scanKeys();
		if ((keysDown() & KEY_A) || (keysDown() & KEY_TOUCH)) doOut = true;
	};
}

const std::vector<Structs::ButtonPos> pos = {
	{ 68, 106, 120, 30 }, // Nein.
	{ 68, 71, 120, 30 } // Ja.
};

bool Msg::promptMsg(const std::string &msg, const uint8_t p) {
	bool res = true;

	Gui::TopBG.draw(0, 0, true, 3, true);
	Gui::MsgBox.draw(10, 18 + 8, true, 3, true);
	Gui::font.clear();
	Gui::font.print(msg, 10 + 8, 18 + 8 + 4, true, 2, Alignment::left);
	Gui::BottomBG.draw(0, 0, false, 3, true);
	for (uint8_t i = 0; i < 2; i++) Gui::Button.draw(pos[i].x, pos[i].y, false, 3, true);
	Gui::font.print(Lang::get("YES"), 0, 78, false, 2, Alignment::center);
	Gui::font.print(Lang::get("NO"), 0, 113, false, 2, Alignment::center);

	Gui::font.update();

	Gui::OverloadSelectorChip(p);
	for (uint8_t i = 0; i < 2; i++) Gui::ButtonChip[i].visibility(true);
	Gui::ButtonChip[0].position(47, pos[1].y + 8);
	Gui::ButtonChip[1].position(195, pos[1].y + 8);
	Gui::ButtonChip[0].update();

	while(1) {
		touchPosition t;
		scanKeys();
		uint32_t hDown = keysDown();
		touchRead(&t);

		if (hDown & KEY_DOWN) {
			res = false;
			Gui::ButtonChip[0].position(47, pos[0].y + 8);
			Gui::ButtonChip[1].position(195, pos[0].y + 8);
			Gui::ButtonChip[0].update();
		}

		if (hDown & KEY_UP) {
			res = true;
			Gui::ButtonChip[0].position(47, pos[1].y + 8);
			Gui::ButtonChip[1].position(195, pos[1].y + 8);
			Gui::ButtonChip[0].update();
		}

		if (hDown & KEY_A) break;

		if (hDown & KEY_TOUCH) {
			bool didTouch = false;

			for (uint8_t i = 0; i < 2; i++) {
				if (touching(t, pos[i])) {
					res = i;
					didTouch = true;
					break;
				}
			}

			if (didTouch) break;
		}
		swiWaitForVBlank();
	};

	for (uint8_t i = 0; i < 2; i++) Gui::ButtonChip[i].visibility(false);
	Gui::ButtonChip[0].update();

	return res;
}