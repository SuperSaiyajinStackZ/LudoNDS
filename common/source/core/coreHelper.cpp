/*
	Diese Datei ist Teil von Ludo3DS & LudoNDS.
	Copyright (C) 2020-2021 bei SuperSaiyajinStackZ.

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

#include "coreHelper.hpp"
#include <ctime>

static bool hasSeeded = false;

/* Generiere den Seed für unseren Zufalls-Generator. */
void CoreHelper::GenerateSeed() {
	if (!hasSeeded) {
		hasSeeded = true;
		randomGenerator.seed(time(NULL));
	}
}

/* Lasse den Würfel rollen und wiedergebe das Ergebnis. */
uint8_t CoreHelper::RollDice() {
	if (!hasSeeded) return 0; // Da wir noch nicht geseeded haben, wiedergebe 0.

	return randomGenerator() % 6 + 1;
}