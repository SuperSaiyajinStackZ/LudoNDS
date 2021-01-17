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

#ifndef _LUDONDS_GAME_SCREEN_HPP
#define _LUDONDS_GAME_SCREEN_HPP

#include "game.hpp"
#include "screen.hpp"
#include "structs.hpp"
#include <vector>

class GameScreen : public Screen {
public:
	GameScreen() { this->PrepareGame(); };
	void Draw(void) const override;
	void Logic(u32 hDown, u32 hHeld, touchPosition touch) override;
private:
	/* Helfer Funktionen. */
	void PrepareGame();
	std::pair<int, int> GetPosition(uint8_t player, uint8_t figur, uint8_t position);
	Structs::ButtonPos GetFigurTouchIndex(uint8_t player, uint8_t figur) const;
	void UpdateText(void);
	void ToggleFigures(bool show);
	void PlaceFigures();
	void UpdateSub();
	void FigurMovement(uint8_t player, uint8_t figur, uint8_t movement);

	/* Spiel Funktionen. */
	bool Play();
	void NextFigur();
	void PreviousFigur();
	void GetFirstAvlFigur();
	void NextPHandle();

	/* Logiken. */
	void RoundLogic(u32 hDown, u32 hHeld, touchPosition touch);
	void FigureSelection(u32 hDown, u32 hHeld, touchPosition touch);
	void SubLogic(uint32_t hDown, uint32_t hHeld, touchPosition touch);
	void AIHandle();

	/* Variablen. */
	std::unique_ptr<Game> currentGame = nullptr;
	bool gameOver = false, awaitFigurSelect = false, isSub = false;
	uint8_t subSel = 0;

	/*
		Haupt-Feld Positionen für die Figuren.

		Beinhaltet nur die Äußeren Felder.
	*/
	const std::vector<Structs::ButtonPos> MainField = {
		{ 74, 164, 14, 14 },
		{ 74, 149, 14, 14 },
		{ 74, 134, 14, 14 },
		{ 74, 119, 14, 14 },
		{ 74, 104, 14, 14 },

		{ 59, 104, 14, 14 },
		{ 44, 104, 14, 14 },
		{ 29, 104, 14, 14 },
		{ 14, 104, 14, 14 },

		{ 14, 89, 14, 14 },
		{ 14, 74, 14, 14 },

		{ 29, 74, 14, 14 },
		{ 44, 74, 14, 14 },
		{ 59, 74, 14, 14 },
		{ 74, 74, 14, 14 },

		{ 74, 59, 14, 14 },
		{ 74, 44, 14, 14 },
		{ 74, 29, 14, 14 },
		{ 74, 14, 14, 14 },

		{ 89, 14, 14, 14 },
		{ 104, 14, 14, 14 },

		{ 104, 29, 14, 14 },
		{ 104, 44, 14, 14 },
		{ 104, 59, 14, 14 },
		{ 104, 74, 14, 14 },

		{ 119, 74, 14, 14 },
		{ 134, 74, 14, 14 },
		{ 149, 74, 14, 14 },
		{ 164, 74, 14, 14 },

		{ 164, 89, 14, 14 },
		{ 164, 104, 14, 14 },

		{ 149, 104, 14, 14 },
		{ 134, 104, 14, 14 },
		{ 119, 104, 14, 14 },
		{ 104, 104, 14, 14 },

		{ 104, 119, 14, 14 },
		{ 104, 134, 14, 14 },
		{ 104, 149, 14, 14 },
		{ 104, 164, 14, 14 },

		{ 89, 164, 14, 14 }
	};

	/*
		Haus-Felder der Figuren.

		Spieler * 4.. von 0 - 3.
	*/
	const std::vector<Structs::ButtonPos> PlayerField = {
		{ 26, 132, 14, 14 },
		{ 46, 132, 14, 14 },
		{ 26, 152, 14, 14 },
		{ 46, 152, 14, 14 },

		{ 26, 26, 14, 14 },
		{ 46, 26, 14, 14 },
		{ 26, 46, 14, 14 },
		{ 46, 46, 14, 14 },

		{ 132, 26, 14, 14 },
		{ 152, 26, 14, 14 },
		{ 132, 46, 14, 14 },
		{ 152, 46, 14, 14 },

		{ 132, 132, 14, 14 },
		{ 152, 132, 14, 14 },
		{ 132, 152, 14, 14 },
		{ 152, 152, 14, 14 }
	};

	/*
		Die Eingangs-Felder Positionen für die Figuren.

		Spieler * 4.. von 0 - 3.
	*/
	const std::vector<Structs::ButtonPos> EingangField = {
		{ 89, 149, 14, 14 },
		{ 89, 134, 14, 14 },
		{ 89, 119, 14, 14 },
		{ 89, 104, 14, 14 },

		{ 29, 89, 14, 14 },
		{ 44, 89, 14, 14 },
		{ 59, 89, 14, 14 },
		{ 74, 89, 14, 14 },

		{ 89, 29, 14, 14 },
		{ 89, 44, 14, 14 },
		{ 89, 59, 14, 14 },
		{ 89, 74, 14, 14 },

		{ 149, 89, 14, 14 },
		{ 134, 89, 14, 14 },
		{ 119, 89, 14, 14 },
		{ 104, 89, 14, 14 }
	};

	const std::vector<Structs::ButtonPos> SubPos = {
		{ 68, 11, 120, 30 },
		{ 68, 46, 120, 30 },
		{ 68, 81, 120, 30 },
		{ 68, 116, 120, 30 },
		{ 68, 151, 120, 30 },
		{ 199, 16, 32, 32 } // Würfel Icon.
	};
};

#endif