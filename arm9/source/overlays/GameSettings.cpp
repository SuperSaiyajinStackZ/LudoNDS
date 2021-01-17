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

const std::vector<Structs::ButtonPos> Positions = {
	/* Figuren. */
	{ 110, 35, 30, 30 },
	{ 144, 35, 30, 30 },
	{ 178, 35, 30, 30 },
	{ 212, 35, 30, 30 },

	/* Spieler. */
	{ 144, 85, 30, 30 },
	{ 178, 85, 30, 30 },
	{ 212, 85, 30, 30 },

	/* Computer. */
	{ 178, 135, 30, 30 },
	{ 212, 135, 30, 30 },

	/* Würfel Rolls. */
	{ 178, 35, 30, 30 },
	{ 212, 35, 30, 30 },

	/* Figur Animation. */
	{ 178, 85, 30, 30 },
	{ 212, 85, 30, 30 },

	/* Abbrechen und Weiter. */
	{ 4, 168, 20, 20 },
	{ 232, 168, 20, 20 }
};

static void Draw(const uint8_t selectedPlayer, const uint8_t selectedFigur, const bool useAI, const uint8_t sel, const bool threeRolls, const bool first) {
	if (first) {
		Gui::Selector[0].visibility(true);
		Gui::Selector[0].position(Positions[selectedFigur - 1].x, Positions[selectedFigur - 1].y);

		Gui::Selector[1].visibility(true);
		Gui::Selector[1].position(Positions[4 + selectedPlayer - 2].x, Positions[4 + selectedPlayer - 2].y);

		Gui::Selector[2].visibility(true);
		Gui::Selector[2].position(Positions[(useAI ? 8 : 7)].x, Positions[(useAI ? 8 : 7)].y);

	} else {
		Gui::Selector[0].visibility(true);
		Gui::Selector[0].position(Positions[(threeRolls ? 10 : 9)].x, Positions[(threeRolls ? 10 : 9)].y);

		Gui::Selector[1].visibility(true);
		Gui::Selector[1].position(Positions[(konfiguration->Animate() ? 12 : 11)].x, Positions[(konfiguration->Animate() ? 12 : 11)].y);

		Gui::Selector[2].visibility(false);
	}

	Gui::Selected.visibility(true);
	Gui::Selected.position(6, 47 + (sel * 50));

	Gui::Selector[0].update();
}

static void DrawPage(const bool first, const bool allowCancel) {
	/* Haupt-Teile. */
	Gui::BottomBG.draw(0, 0, false, 3, true);
	Gui::TitleBar.draw(0, 0, false, 3, true);
	if (allowCancel) Gui::Arrows[0].draw(4, 168, false, 3, true);
	Gui::Arrows[1].draw(232, 168, false, 3, true);
	Gui::font.clear();

	Gui::font.print(Lang::get("GAME_SETTINGS"), 0, 2, true, 2, Alignment::center);

	/* Text. */
	if (first) {
		Gui::font.print(Lang::get("GENERAL_SETTINGS"), 0, 2, false, 2, Alignment::center);
		Gui::font.print(Lang::get("FIGURE_AMOUNT") + ": ", 12, 45, false, 2, Alignment::left);
		Gui::font.print(Lang::get("PLAYER_AMOUNT") + ": ", 12, 95, false, 2, Alignment::left);
		Gui::font.print(Lang::get("ENABLE_COMPUTER") + ": ", 12, 145, false, 2, Alignment::left);

		/* Schaltflächen. */
		Gui::GameSettings[0].draw(Positions[0].x, Positions[0].y, false, 3, true);
		Gui::GameSettings[1].draw(Positions[4].x, Positions[4].y, false, 3, true);
		Gui::GameSettings[2].draw(Positions[7].x, Positions[7].y, false, 3, true);

	} else {
		Gui::font.print(Lang::get("OPTIONAL_SETTINGS"), 0, 2, false, 2, Alignment::center);
		Gui::font.print(Lang::get("DICE_ROLLS") + ": ", 12, 45, false, 2, Alignment::left);
		Gui::font.print(Lang::get("ANIMATE_FIGURE") + ": ", 12, 95, false, 2, Alignment::left);

		Gui::GameSettings[3].draw(Positions[9].x, Positions[9].y, false, 3, true);
		Gui::GameSettings[4].draw(Positions[11].x, Positions[11].y, false, 3, true);
	}

	Gui::font.update();
}

GameData Overlays::PrepareGame(bool allowCancel) {
	GameData dt = { 2, 1, false, false };
	uint8_t selection = 0;
	bool draw = true, firstPage = true;

	Gui::TopBG.draw(0, 0, true, 3, true);


	DrawPage(firstPage, allowCancel);
	while(1) {
		if (draw) {
			draw = false;
			Draw(dt.PAmount, dt.FAmount, dt.UseAI, selection, dt.ThreeRolls, firstPage);
		}

		scanKeys();
		touchPosition t;
		touchRead(&t);

		uint32_t hDown = keysDown();

		if (hDown & KEY_DOWN) {
			if (firstPage) {
				if (selection < 2) {
					selection++;
					draw = true;
				}

			} else {
				if (selection < 1) {
					selection++;
					draw = true;
				}
			}
		}

		if (hDown & KEY_UP) {
			if (selection > 0) {
				selection--;
				draw = true;
			}
		}

		if (hDown & KEY_RIGHT) {
			if (firstPage) {
				switch(selection) {
					case 0:
						/* Figuren Anzahl. */
						if (dt.FAmount < 4) dt.FAmount++;
						break;

					case 1:
						/* Spieler Anzahl. */
						if (dt.PAmount < 4) dt.PAmount++;
						break;

					case 2:
						/* Computer benutzt. */
						if (!dt.UseAI) dt.UseAI = true;
						break;
				}

			} else {
				switch(selection) {
					case 0:
						/* Würfel-Rolls. */
						if (!dt.ThreeRolls) dt.ThreeRolls = true;
						break;

					case 1:
						/* Animation. */
						if (!konfiguration->Animate()) konfiguration->Animate(true);
						break;
				}
			}

			draw = true;
		}

		if (hDown & KEY_LEFT) {
			if (firstPage) {
				switch(selection) {
					case 0:
						/* Figuren Anzahl. */
						if (dt.FAmount > 1) dt.FAmount--;
						break;

					case 1:
						/* Spieler Anzahl. */
						if (dt.PAmount > 2) dt.PAmount--;
						break;

					case 2:
						/* Computer benutzt. */
						if (dt.UseAI) dt.UseAI = false;
						break;
				}

			} else {
				switch(selection) {
					case 0:
						/* Würfel-Rolls. */
						if (dt.ThreeRolls) dt.ThreeRolls = false;
						break;

					case 1:
						/* Animation. */
						if (konfiguration->Animate()) konfiguration->Animate(false);
						break;
				}
			}

			draw = true;
		}

		if ((hDown & KEY_R) || (hDown & KEY_L)) {
			selection = 0;
			firstPage = !firstPage;
			DrawPage(firstPage, allowCancel);
			draw = true;
		}

		if (hDown & KEY_A) {
			if (firstPage) {
				switch(selection) {
					case 0:
						/* Figuren Anzahl. */
						if (dt.FAmount < 4) dt.FAmount++;
						else dt.FAmount = 1;
						break;

					case 1:
						/* Spieler Anzahl. */
						if (dt.PAmount < 4) dt.PAmount++;
						else dt.PAmount = 2;
						break;

					case 2:
						/* Computer benutzt. */
						dt.UseAI = !dt.UseAI;
						break;
				}

			} else {
				switch(selection) {
					case 0:
						/* Würfel Rolls. */
						dt.ThreeRolls = !dt.ThreeRolls;
						break;

					case 1:
						/* Animation. */
						konfiguration->Animate(!konfiguration->Animate());
						break;
				}
			}

			draw = true;
		}

		if (hDown & KEY_START) break;

		if (hDown & KEY_TOUCH) {
			if (allowCancel) {
				if (touching(t, Positions[13])) {
					dt = { -1, -1, false, false };
					break;
				}
			}

			if (touching(t, Positions[14])) break;

			bool didTouch = false;

			if (firstPage) {
				/* Figuren Anzahl. */
				for (uint8_t i = 0; i < 4; i++) {
					if (touching(t, Positions[i])) {
						dt.FAmount = i + 1;
						didTouch = true;
						break;
					}
				}


				if (!didTouch) {
					/* Spieler Anzahl. */
					for (uint8_t i = 0; i < 3; i++) {
						if (touching(t, Positions[4 + i])) {
							dt.PAmount = i + 2;
							didTouch = true;
							break;
						}
					}
				}

				if (!didTouch) {
					/* Computer. */
					for (uint8_t i = 0; i < 2; i++) {
						if (touching(t, Positions[7 + i])) {
							dt.UseAI = i;
							didTouch = true;
							break;
						}
					}
				}

			} else {
				/* Computer. */
				for (uint8_t i = 0; i < 2; i++) {
					if (touching(t, Positions[9 + i])) {
						dt.ThreeRolls = i;
						didTouch = true;
						break;
					}
				}

				if (!didTouch) {
					/* Animation. */
					for (uint8_t i = 0; i < 2; i++) {
						if (touching(t, Positions[11 + i])) {
							konfiguration->Animate(i);
							didTouch = true;
							break;
						}
					}
				}
			}

			draw = didTouch;
		}

		swiWaitForVBlank();
	}

	/* Verstecke alles. */
	for (int i = 0; i < 3; i++) {
		Gui::Selector[i].visibility(false);
	}

	Gui::Selected.visibility(false);
	Gui::font.clear();
	Gui::Selected.update();
	Gui::font.update();

	return dt;
}