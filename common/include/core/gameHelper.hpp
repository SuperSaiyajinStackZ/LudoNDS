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

#ifndef _LUDONDS_GAME_HELPER_HPP
#define _LUDONDS_GAME_HELPER_HPP

#include "coreHelper.hpp"
#include "game.hpp"

namespace GameHelper {
	uint8_t PositionConvert(uint8_t Player, uint8_t Position);

	bool HasFinished(std::unique_ptr<Game> &game, uint8_t player);
	bool DoesOwnFigurBlock(std::unique_ptr<Game> &game, uint8_t player, uint8_t figur, uint8_t ergebnis);
	bool AllFiguresInHouse(std::unique_ptr<Game> &game, uint8_t player);
	std::pair<int8_t, int8_t> KickAction(std::unique_ptr<Game> &game, uint8_t player, uint8_t figur);
	bool NeedsToHandleFromHouse(std::unique_ptr<Game> &game, uint8_t player);

	void MarkAsDone(std::unique_ptr<Game> &game, uint8_t player, uint8_t figur);
	bool CanMove(std::unique_ptr<Game> &game, uint8_t player, uint8_t figur, uint8_t ergebnis);
	void AdditionalDoneCheck(std::unique_ptr<Game> &game, uint8_t player, uint8_t figur);
	bool CanKick(std::unique_ptr<Game> &game, uint8_t player, uint8_t figur);

	void SetContinue(std::unique_ptr<Game> &game, uint8_t player);
};

#endif