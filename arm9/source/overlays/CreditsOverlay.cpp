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

void Overlays::CreditsOverlay() {
	bool doOut = false;

	Gui::TopBG.draw(0, 0, true, 3, true);
	Gui::StackZ.draw(68, 54, true, 3, true);
	Gui::font.clear();
	Gui::font.print(Lang::get("CREDITS"), 0, 2, true, 2, Alignment::center);
	Gui::font.print(Lang::get("DEV_BY"), 0, 18, true, 2, Alignment::center);
	Gui::font.print(Lang::get("CURRENT_VERSION") + "v0.1.0", 0, 175, true, 2, Alignment::center);

	Gui::TopBG.draw(0, 0, false, 3, true);
	Gui::font.print("devkitPro", 0, 20, false, 2, Alignment::center);
	Gui::font.print(Lang::get("DEVKITPRO"), 0, 35, false, 2, Alignment::center);

	Gui::font.print("Universal-Team", 0, 65, false, 2, Alignment::center);
	Gui::font.print(Lang::get("UNIVERSAL_CORE"), 0, 80, false, 2, Alignment::center);

	Gui::font.print("SuperSaiyajinStackZ", 0, 110, false, 2, Alignment::center);
	Gui::font.print(Lang::get("DEVELOPING_APP"), 0, 125, false, 2, Alignment::center);
	Gui::font.update();

	while(!doOut) {
		scanKeys();
		if (keysDown()) doOut = true;
		swiWaitForVBlank();
	};
}