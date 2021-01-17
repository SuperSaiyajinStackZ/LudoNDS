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

#include "animHelper.hpp"

/* Unten-Links. */
std::pair<int8_t, int8_t> AnimHelper::Player1Movement(uint8_t figur, uint8_t pos) {
	if (pos == 0) {
		/* Spezial Handling. */
		switch(figur) {
			case 0:
				return { 48, 32 };

			case 1:
				return { 28, 32 };

			case 2:
				return { 48, 12 };

			case 3:
				return { 28, 12 };
		}
	}

	/* 15 pro spielfeld. */
	if (pos > 0 && pos < 5) return { 0, -15 };
	if (pos > 4 && pos < 9) return { -15, 0 };
	if (pos > 8 && pos < 11) return { 0, -15 };
	if (pos > 10 && pos < 15) return { 15, 0 };
	if (pos > 14 && pos < 19) return { 0, -15 };
	if (pos > 18 && pos < 21) return { 15, 0 };
	if (pos > 20 && pos < 25) return { 0, 15 };
	if (pos > 24 && pos < 29) return { 15, 0 };
	if (pos > 28 && pos < 31) return { 0, 15 };
	if (pos > 30 && pos < 35) return { -15, 0 };
	if (pos > 34 && pos < 39) return { 0, 15 };
	if (pos > 38 && pos < 40) return { -15, 0 };
	if (pos > 39 && pos < 45) return { 0, -15 };

	return { 0, 0 };
}

/* Oben-Links. */
std::pair<int8_t, int8_t> AnimHelper::Player2Movement(uint8_t figur, uint8_t pos) {
	if (pos == 0) {
		/* Spezial Handling. */
		switch(figur) {
			case 0:
				return { -12, 48 };

			case 1:
				return { -32, 48 };

			case 2:
				return { -12, 28 };

			case 3:
				return { -32, 28 };
		}
	}

	/* 15 pro spielfeld. */
	if (pos > 0 && pos < 5) return { 15, 0 };
	if (pos > 4 && pos < 9) return { 0, -15 };
	if (pos > 8 && pos < 11) return { 15, 0 };
	if (pos > 10 && pos < 15) return { 0, 15 };
	if (pos > 14 && pos < 19) return { 15, 0 };
	if (pos > 18 && pos < 21) return { 0, 15 };
	if (pos > 20 && pos < 25) return { -15, 0 };
	if (pos > 24 && pos < 29) return { 0, 15 };
	if (pos > 28 && pos < 31) return { -15, 0 };
	if (pos > 30 && pos < 35) return { 0, -15 };
	if (pos > 34 && pos < 39) return { -15, 0 };
	if (pos > 38 && pos < 40) return { 0, -15 };
	if (pos > 39 && pos < 45) return { 15, 0 };

	return { 0, 0 };
}

/* Oben-Rechts. */
std::pair<int8_t, int8_t> AnimHelper::Player3Movement(uint8_t figur, uint8_t pos) {
	if (pos == 0) {
		/* Spezial Handling. */
		switch(figur) {
			case 0:
				return { -28, -12 };

			case 1:
				return { -48, -12 };

			case 2:
				return { -28, -32 };

			case 3:
				return { -48, -32 };
		}
	}

	/* 15 pro spielfeld. */
	if (pos > 0 && pos < 5) return { 0, 15 };
	if (pos > 4 && pos < 9) return { 15, 0 };
	if (pos > 8 && pos < 11) return { 0, 15 };
	if (pos > 10 && pos < 15) return { -15, 0 };
	if (pos > 14 && pos < 19) return { 0, 15 };
	if (pos > 18 && pos < 21) return { -15, 0 };
	if (pos > 20 && pos < 25) return { 0, -15 };
	if (pos > 24 && pos < 29) return { -15, 0 };
	if (pos > 28 && pos < 31) return { 0, -15 };
	if (pos > 30 && pos < 35) return { 15, 0 };
	if (pos > 34 && pos < 39) return { 0, -15 };
	if (pos > 38 && pos < 40) return { 15, 0 };
	if (pos > 39 && pos < 45) return { 0, 15 };

	return { 0, 0 };
}

/* Unten-Rechts. */
std::pair<int8_t, int8_t> AnimHelper::Player4Movement(uint8_t figur, uint8_t pos) {
	if (pos == 0) {
		/* Spezial Handling. */
		switch(figur) {
			case 0:
				return { 32, -28 };

			case 1:
				return { 12, -28 };

			case 2:
				return { 32, -48 };

			case 3:
				return { 12, -48 };
		}
	}

	/* 15 pro spielfeld. */
	if (pos > 0 && pos < 5) return { -15, 0 };
	if (pos > 4 && pos < 9) return { 0, 15 };
	if (pos > 8 && pos < 11) return { -15, 0 };
	if (pos > 10 && pos < 15) return { 0, -15 };
	if (pos > 14 && pos < 19) return { -15, 0 };
	if (pos > 18 && pos < 21) return { 0, -15 };
	if (pos > 20 && pos < 25) return { 15, 0 };
	if (pos > 24 && pos < 29) return { 0, -15 };
	if (pos > 28 && pos < 31) return { 15, 0 };
	if (pos > 30 && pos < 35) return { 0, 15 };
	if (pos > 34 && pos < 39) return { 15, 0 };
	if (pos > 38 && pos < 40) return { 0, 15 };
	if (pos > 39 && pos < 45) return { -15, 0 };

	return { 0, 0 };
}

/*
	Wiedergibt die X und Y Distanz für die Figur, damit sie animiert mit += gezeichnet werden kann.

	uint8_t player: Der Spieler.
	uint8_t figur: Die Figur.
	uint8_t pos: Die aktuelle Position.
*/
std::pair<int8_t, int8_t> AnimHelper::PlayerMovement(uint8_t player, uint8_t figur, uint8_t pos) {
	switch(player) {
		case 0:
			return AnimHelper::Player1Movement(figur, pos);

		case 1:
			return AnimHelper::Player2Movement(figur, pos);

		case 2:
			return AnimHelper::Player3Movement(figur, pos);

		case 3:
			return AnimHelper::Player4Movement(figur, pos);
	}

	return { 0, 0 };
}