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
#include "coreHelper.hpp"

#define _DICE_DELAY 10 // Die Würfel-Verzögerung.
#define _AI_ROLL_DL 60 // AI Würfel-Verzögerung.

/* Zeige das Würfel-Overlay und wiedergebe ein Würfel-Ergebnis als einen uint8_t. */
uint8_t Overlays::RollDiceOverlay(bool AIRoll) {
	uint8_t diceRes = CoreHelper::RollDice(), diceDl = _DICE_DELAY, dl = _AI_ROLL_DL;
	bool doOut = false, draw = true;

	Gui::TopBG.draw(0, 0, true, 3, true);
	Gui::font.clear();
	if (!AIRoll) Gui::font.print(Lang::get("STOP_DICE"), 0, 175, true, 2, Alignment::center);
	Gui::font.update();

	while(!doOut) {
		swiWaitForVBlank();

		if (draw) {
			draw = false;
			Gui::Dices[diceRes - 1].draw(88, 18 + 38, true, 3, true);
		}

		if (!AIRoll) {
			scanKeys();
			if ((keysDown() & KEY_A) || (keysDown() & KEY_TOUCH)) doOut = true;

			/* Würfel-Teil. */
			if (diceDl > 0) {
				diceDl--;

				if (diceDl == 0) {
					diceDl = _DICE_DELAY;
					draw = true;

					if (diceRes < 6) diceRes++;
					else diceRes = 1;
				}
			}

		} else {
			scanKeys();
			if ((keysDown() & KEY_A) || (keysDown() & KEY_TOUCH)) doOut = true; // Lasse die Animation mit A überspringen.

			/* Würfel-Teil. */
			if (diceDl > 0) {
				diceDl--;
				dl--;

				if (diceDl == 0) {
					diceDl = _DICE_DELAY;
					draw = true;

					if (diceRes < 6) diceRes++;
					else diceRes = 1;
				}

				if (dl == 0) doOut = true;
			}
		}
	}

	return CoreHelper::RollDice(); // Am Ende wiedergebe einfach eine zufalls Zahl zwischen 1 und 6.
}