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
#include "common.hpp"
#include "coreHelper.hpp"
#include "gameHelper.hpp"
#include "gameScreen.hpp"

/* Platziere die Chips korrekt beim laden eines Spieles. */
void GameScreen::PlaceFigures() {
	/* Bereite die Figuren vor. */
	for(uint8_t i = 0; i < 4; i++) {
		if (i < this->currentGame->GetPlayerAmount()) {
			for (uint8_t i2 = 0; i2 < 4; i2++) {
				if (i2 < this->currentGame->GetFigurAmount()) {
					Gui::Chips[(i * 4) + i2].visibility(true);

					const std::pair<int, int> pos = this->GetPosition(i, i2, this->currentGame->GetPosition(i, i2));

					Gui::Chips[(i * 4) + i2].position(pos.first, pos.second);
					Gui::Chips[(i * 4) + i2].priority(1);

				} else {
					Gui::Chips[(i * 4) + i2].visibility(false); // Verstecke Chip, weil nicht genügend Figuren.
				}
			}

		} else {
			for (uint8_t i2 = 0; i2 < 4; i2++) {
				Gui::Chips[(i * 4) + i2].visibility(false); // Verstecke Chip, weil nicht genügend Spieler.
			}
		}
	}

	Gui::Chips[0].update(); // Aktualisiere Figuren.
}


/* Zeige oder Verstecke alle Figuren. */
void GameScreen::ToggleFigures(bool show) {
	if (!this->currentGame) return;

	for(uint8_t i = 0; i < 4; i++) {
		if (i < this->currentGame->GetPlayerAmount()) {
			for (uint8_t i2 = 0; i2 < 4; i2++) {
				if (i2 < this->currentGame->GetFigurAmount()) Gui::Chips[(i * 4) + i2].visibility(show);
			}
		}
	}

	if (this->awaitFigurSelect) Gui::ChipSelector.visibility(show);
	Gui::Chips[0].update(); // Aktualisiere Figuren.
}

/* Bereite ein neues Spiel vor. */
void GameScreen::PrepareGame() {
	const GameData dt = Overlays::PrepareGame();
	this->currentGame = std::make_unique<Game>(dt.PAmount, dt.FAmount, (dt.ThreeRolls ? 3 : 1));
	this->currentGame->SetAI(dt.UseAI);
	this->PlaceFigures();
	Gui::Chips[0].update(); // Aktualisiere Figuren.
	this->UpdateText();
}

/* Reinige und Aktualisiere den angezeigten Text. */
void GameScreen::UpdateText(void) {
	Gui::font.clear();
	Gui::font.print(Lang::get("CURRENT_PLAYER") + std::to_string(this->currentGame->GetCurrentPlayer() + 1), 0, 0, true, 2, Alignment::center);

	if (this->awaitFigurSelect) Gui::font.print(Lang::get("SELECT_FIGURE"), 0, 175, true, 2, Alignment::center);
	else Gui::font.print(Lang::get("ROLL_DICE"), 0, 175, true, 2, Alignment::center);

	Gui::font.update(); // Aktualisiere angezeigten Text.
}

/* Der Haupt-Zeichnungs Teil. */
void GameScreen::Draw(void) const {
	if (!this->isSub) {
		Gui::TopBG.draw(0, 0, true, 3, true);
		Gui::BottomBG.draw(0, 0, false, 3, true);
		Gui::DrawField();
		if (this->awaitFigurSelect) Gui::Dices[this->currentGame->GetErgebnis() - 1].draw(88, 18 + 38, true, 3, true);
		Gui::DieIcon.draw(this->SubPos[5].x, this->SubPos[5].y, false, 3, true);
		return;
	}

	Gui::font.clear();
	Gui::TopBG.draw(0, 0, true, 3, true);

	Gui::font.print(Lang::get("GAME_PAUSED"), 0, 0, true, 2, Alignment::center);
	Gui::font.print(Lang::get("PLAYER_AMOUNT") + ": " + std::to_string(this->currentGame->GetPlayerAmount()), 0, 30, true, 2, Alignment::center);
	Gui::font.print(Lang::get("FIGURE_AMOUNT") + ": " + std::to_string(this->currentGame->GetFigurAmount()), 0, 50, true, 2, Alignment::center);
	Gui::font.print(Lang::get("CURRENT_PLAYER") + std::to_string(this->currentGame->GetCurrentPlayer() + 1), 0, 70, true, 2, Alignment::center);
	Gui::font.print(Lang::get("COMPUTER_ENABLED") + (this->currentGame->GetAI() ? Lang::get("YES") : Lang::get("NO")), 0, 90, true, 2, Alignment::center);
	Gui::font.print(Lang::get("DICE_ROLLS") + ": " + std::to_string(this->currentGame->GetDiceRolls()), 0, 110, true, 2, Alignment::center);
	Gui::font.print(Lang::get("DICE_ROLLS_ACTIVE") + std::to_string(this->currentGame->GetAVLDiceRolls()), 0, 130, true, 2, Alignment::center);
	Gui::font.print(Lang::get("SELECT_EXIT"), 0, 175, true, 2, Alignment::center);

	Gui::BottomBG.draw(0, 0, false, 3, true);

	for (uint8_t i = 0; i < 5; i++) {
		Gui::Button.draw(this->SubPos[i].x, this->SubPos[i].y, false, 3, true);
	}

	Gui::font.print(Lang::get("LOAD_GAME"), 0, 18, false, 2, Alignment::center);
	Gui::font.print(Lang::get("SAVE_GAME"), 0, 53, false, 2, Alignment::center);
	Gui::font.print(Lang::get("GAME_SETTINGS"), 0, 88, false, 2, Alignment::center);
	Gui::font.print(Lang::get("LANGUAGE"), 0, 123, false, 2, Alignment::center);
	Gui::font.print(Lang::get("CREDITS"), 0, 158, false, 2, Alignment::center);
	Gui::font.update();
}

/* Die Haupt-Logik. */
void GameScreen::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	/* Falls das Spiel vorbei ist. */
	if (this->gameOver) {
		if (!Msg::promptMsg(Lang::get("NEXT_GAME"), this->currentGame->GetCurrentPlayer())) exiting = true;
		else {
			this->awaitFigurSelect = false;
			this->PrepareGame();
			Screen::doDraw();
			this->UpdateText();
			this->gameOver = false;
		}
	}

	/* Nur wenn das Spiel noch nicht vorbei ist. */
	if (!this->gameOver) {
		if (!this->isSub) {
			if (!this->awaitFigurSelect) this->RoundLogic(hDown, hHeld, touch);
			else this->FigureSelection(hDown, hHeld, touch);

			if (hDown & KEY_START) {
				this->isSub = true;
				Gui::OverloadSelectorChip(this->currentGame->GetCurrentPlayer());
				this->ToggleFigures(false);

				for (uint8_t i = 0; i < 2; i++) Gui::ButtonChip[i].visibility(true);
				this->UpdateSub();
				Screen::doDraw();
			}

		} else {
			this->SubLogic(hDown, hHeld, touch);
		}
	}
}

/* Die UnterMenü Logik. */
void GameScreen::SubLogic(uint32_t hDown, uint32_t hHeld, touchPosition touch) {
	if (hDown & KEY_B) {
		this->isSub = false;
		for (uint8_t i = 0; i < 2; i++) Gui::ButtonChip[i].visibility(false);
		this->ToggleFigures(true);
		Screen::doDraw();
		this->UpdateText();
	}

	if (hDown & KEY_SELECT) {
		if (Msg::promptMsg(Lang::get("EXIT_GAME"), this->currentGame->GetCurrentPlayer())) exiting = true;
		else {
			for (uint8_t i = 0; i < 2; i++) Gui::ButtonChip[i].visibility(true);
			this->UpdateSub();
			Screen::doDraw();
		}
	}

	if (hDown & KEY_DOWN) {
		if (this->subSel < 4) {
			this->subSel++;
			this->UpdateSub();
		}
	}

	if (hDown & KEY_UP) {
		if (this->subSel > 0) {
			this->subSel--;
			this->UpdateSub();
		}
	}

	if (hDown & KEY_A) {
		switch(this->subSel) {
			case 0:
				/* Lade Spieldaten. */
				if (!Msg::promptMsg(Lang::get("LOAD_FROM_FILE_PROMPT"), this->currentGame->GetCurrentPlayer())) {
					for (uint8_t i = 0; i < 2; i++) Gui::ButtonChip[i].visibility(true);
					this->UpdateSub();
					Screen::doDraw();
					return;
				}

				this->currentGame->LoadGameFromFile();
				if (this->currentGame->validLoaded()) {
					this->currentGame->convertDataToGame();
					this->awaitFigurSelect = false;
					this->isSub = false;

					this->PlaceFigures();
					Screen::doDraw();
					this->UpdateText();

				} else {
					Msg::WaitMsg(Lang::get("NOT_VALID_GAME"));
					for (uint8_t i = 0; i < 2; i++) Gui::ButtonChip[i].visibility(true);
					Screen::doDraw();
				}
				break;

			case 1:
				/* Speichere Spieldaten. */
				if (!Msg::promptMsg(Lang::get("SAVE_TO_FILE_PROMPT"), this->currentGame->GetCurrentPlayer())) {
					for (uint8_t i = 0; i < 2; i++) Gui::ButtonChip[i].visibility(true);
					this->UpdateSub();
					Screen::doDraw();
					return;
				}

				this->currentGame->SaveToFile(true);
				Msg::WaitMsg(Lang::get("SAVED_TO_FILE"));
				this->isSub = false;

				this->ToggleFigures(true);
				Screen::doDraw();
				this->UpdateText();
				break;

			case 2: {
					/* Spiel Einstellungen. */
					if (!Msg::promptMsg(Lang::get("GAME_SETTINGS_PROMPT"), this->currentGame->GetCurrentPlayer())) {
						for (uint8_t i = 0; i < 2; i++) Gui::ButtonChip[i].visibility(true);
						this->UpdateSub();
						Screen::doDraw();
						return;
					}

					const GameData dt = Overlays::PrepareGame(true);

					if (dt.FAmount == -1) {
						for (uint8_t i = 0; i < 2; i++) Gui::ButtonChip[i].visibility(true);
						Screen::doDraw();
						Gui::ButtonChip[0].update();
						return; // -1 == Abgebrochen.
					}

					this->currentGame->InitNewGame(dt.PAmount, dt.FAmount, (dt.ThreeRolls ? 3 : 1));
					this->currentGame->SetAI(dt.UseAI);
					this->awaitFigurSelect = false;
					this->isSub = false;

					this->PlaceFigures();
					Screen::doDraw();
					this->UpdateText();
				}
				break;

			case 3:
				/* Sprache Ändern. */
				for (uint8_t i = 0; i < 2; i++) Gui::ButtonChip[i].visibility(false);
				Gui::ButtonChip[0].update();
				Overlays::LanguageOverlay();
				for (uint8_t i = 0; i < 2; i++) Gui::ButtonChip[i].visibility(true);
				Screen::doDraw();
				Gui::ButtonChip[0].update();
				break;

			case 4:
				/* Credits Anzeigen. */
				for (uint8_t i = 0; i < 2; i++) Gui::ButtonChip[i].visibility(false);
				Gui::ButtonChip[0].update();
				Overlays::CreditsOverlay();
				for (uint8_t i = 0; i < 2; i++) Gui::ButtonChip[i].visibility(true);
				Screen::doDraw();
				Gui::ButtonChip[0].update();
				break;
		}
	}


	if (hDown & KEY_TOUCH) {
		if (touching(touch, this->SubPos[0])) {
			/* Lade Spieldaten. */
			if (!Msg::promptMsg(Lang::get("LOAD_FROM_FILE_PROMPT"), this->currentGame->GetCurrentPlayer())) {
				for (uint8_t i = 0; i < 2; i++) Gui::ButtonChip[i].visibility(true);
				this->UpdateSub();
				Screen::doDraw();
				return;
			}

			this->currentGame->LoadGameFromFile();
			if (this->currentGame->validLoaded()) {
				this->currentGame->convertDataToGame();
				this->awaitFigurSelect = false;
				this->isSub = false;

				this->PlaceFigures();
				Screen::doDraw();
				this->UpdateText();

			} else {
				Msg::WaitMsg(Lang::get("NOT_VALID_GAME"));
				for (uint8_t i = 0; i < 2; i++) Gui::ButtonChip[i].visibility(true);
				this->UpdateSub();
				Screen::doDraw();
			}

		} else if (touching(touch, this->SubPos[1])) {
			/* Speichere Spieldaten. */
			if (!Msg::promptMsg(Lang::get("SAVE_TO_FILE_PROMPT"), this->currentGame->GetCurrentPlayer())) {
				for (uint8_t i = 0; i < 2; i++) Gui::ButtonChip[i].visibility(true);
				this->UpdateSub();
				Screen::doDraw();
				return;
			}

			this->currentGame->SaveToFile(true);
			Msg::WaitMsg(Lang::get("SAVED_TO_FILE"));
			this->isSub = false;

			this->ToggleFigures(true);
			Screen::doDraw();
			this->UpdateText();

		} else if (touching(touch, this->SubPos[2])) {
			/* Spiel Einstellungen. */
			if (!Msg::promptMsg(Lang::get("GAME_SETTINGS_PROMPT"), this->currentGame->GetCurrentPlayer())) {
				for (uint8_t i = 0; i < 2; i++) Gui::ButtonChip[i].visibility(true);
				this->UpdateSub();
				Screen::doDraw();
				return;
			}

			const GameData dt = Overlays::PrepareGame(true);

			if (dt.FAmount == -1) {
				for (uint8_t i = 0; i < 2; i++) Gui::ButtonChip[i].visibility(true);
				Screen::doDraw();
				Gui::ButtonChip[0].update();
				return; // -1 == Abgebrochen.
			}

			this->currentGame->InitNewGame(dt.PAmount, dt.FAmount, (dt.ThreeRolls ? 3 : 1));
			this->currentGame->SetAI(dt.UseAI);
			this->awaitFigurSelect = false;
			this->isSub = false;

			this->PlaceFigures();
			Screen::doDraw();
			this->UpdateText();

		} else if (touching(touch, this->SubPos[3])) {
			/* Sprache Ändern. */
			for (uint8_t i = 0; i < 2; i++) Gui::ButtonChip[i].visibility(false);
			Gui::ButtonChip[0].update();
			Overlays::LanguageOverlay();
			for (uint8_t i = 0; i < 2; i++) Gui::ButtonChip[i].visibility(true);
			Screen::doDraw();
			Gui::ButtonChip[0].update();

		} else if (touching(touch, this->SubPos[4])) {
			/* Credits Anzeigen. */
			for (uint8_t i = 0; i < 2; i++) Gui::ButtonChip[i].visibility(false);
			Gui::ButtonChip[0].update();
			Overlays::CreditsOverlay();
			for (uint8_t i = 0; i < 2; i++) Gui::ButtonChip[i].visibility(true);
			Screen::doDraw();
			Gui::ButtonChip[0].update();
		}
	}
}

/* Aktualisiere den Schaltflächen Chip für die Unter Menü Selektion. */
void GameScreen::UpdateSub() {
	Gui::ButtonChip[0].position(47, this->SubPos[this->subSel].y + 8);
	Gui::ButtonChip[1].position(195, this->SubPos[this->subSel].y + 8);
	Gui::ButtonChip[0].update();
}

/*
	Wiedergebe die X & Y Position für die Selektoren usw.

	uint8_t player: Der Spieler.
	uint8_t figur: Die Figur.
	uint8_t position: Die Position.
*/
std::pair<int, int> GameScreen::GetPosition(uint8_t player, uint8_t figur, uint8_t position) {
	/* 0 --> Startfeld. */
	if (position == 0) {
		return { this->PlayerField[(player * 4) + figur].x, this->PlayerField[(player * 4) + figur].y };

	} else if (position > 0 && position < 41) {
		return { this->MainField[GameHelper::PositionConvert(player, position) - 1].x, this->MainField[GameHelper::PositionConvert(player, position) - 1].y };


	/* Falls wir in den Eingangs-Bereich kommen. */
	} else if (position > 40) {
		return { this->EingangField[(player * 4) + (position - 41)].x, this->EingangField[(player * 4) + (position - 41)].y };
	}

	return { -1, -1 };
}

/*
	Der Runden-Teil. Rolle den Würfel.
*/
void GameScreen::RoundLogic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (this->currentGame->GetAI() && this->currentGame->GetCurrentPlayer() != 0) {
		this->AIHandle();

	} else {
		if ((hDown & KEY_X) || (hDown & KEY_TOUCH && touching(touch, this->SubPos[5]))) {
			this->currentGame->SetErgebnis(Overlays::RollDiceOverlay()); // Würfeln!

			bool confirmation = false;
			Gui::TopBG.draw(0, 0, true, 3, true);
			Gui::Dices[this->currentGame->GetErgebnis() - 1].draw(88, 18 + 38, true, 3, true);
			Gui::font.clear();
			Gui::font.print(Lang::get("CURRENT_PLAYER") + std::to_string(this->currentGame->GetCurrentPlayer() + 1), 0, 0, true, 2, Alignment::center);
			Gui::font.print(Lang::get("A_CONTINUE"), 0, 175, true, 2, Alignment::center);
			Gui::font.update();

			while(!confirmation) {
				scanKeys();
				uint32_t hDown = keysDown();
				if ((hDown & KEY_A) || (hDown & KEY_TOUCH)) confirmation = true;
				swiWaitForVBlank();
			};

			Gui::font.clear();

			for (uint8_t figur = 0; figur < this->currentGame->GetFigurAmount(); figur++) {
				if (GameHelper::CanMove(this->currentGame, this->currentGame->GetCurrentPlayer(), figur, this->currentGame->GetErgebnis())) {
					Gui::ChipSelector.visibility(true);
					this->GetFirstAvlFigur();
					this->awaitFigurSelect = true;
					this->UpdateText();
					return;
				}
			}

			GameHelper::SetContinue(this->currentGame, this->currentGame->GetCurrentPlayer());
			this->NextPHandle();
			Gui::TopBG.draw(0, 0, true, 3, true);
			this->UpdateText();
		}
	}
}

/* Gehe zur nächsten Figur, falls verfügbar. */
void GameScreen::NextFigur() {
	if (this->currentGame->GetSelectedFigur() == this->currentGame->GetFigurAmount() - 1) return; // Bereits an der letzten Figur.

	for (uint8_t cFigur = this->currentGame->GetSelectedFigur() + 1; cFigur < this->currentGame->GetFigurAmount(); cFigur++) {
		if (this->currentGame->GetDone(this->currentGame->GetCurrentPlayer(), cFigur)) continue;

		if (GameHelper::CanMove(this->currentGame, this->currentGame->GetCurrentPlayer(), cFigur, this->currentGame->GetErgebnis())) {
			this->currentGame->SetSelectedFigur(cFigur);

			const std::pair<int, int> pos = this->GetPosition(this->currentGame->GetCurrentPlayer(), this->currentGame->GetSelectedFigur(), this->currentGame->GetPosition(this->currentGame->GetCurrentPlayer(), this->currentGame->GetSelectedFigur()));
			if (pos.first != -1) {
				Gui::ChipSelector.position(pos.first, pos.second);
				Gui::ChipSelector.update();
			}
			break;
		}
	}
}

/* Gehe zur vorherigen Figur, falls verfügbar. */
void GameScreen::PreviousFigur() {
	if (this->currentGame->GetSelectedFigur() <= 0) return; // Es gibt kein -1.

	for (int8_t cFigur = this->currentGame->GetSelectedFigur() - 1; cFigur >= 0; cFigur--) {
		if (this->currentGame->GetDone(this->currentGame->GetCurrentPlayer(), cFigur)) continue;

		if (GameHelper::CanMove(this->currentGame, this->currentGame->GetCurrentPlayer(), cFigur, this->currentGame->GetErgebnis())) {
			this->currentGame->SetSelectedFigur(cFigur);

			const std::pair<int, int> pos = this->GetPosition(this->currentGame->GetCurrentPlayer(), this->currentGame->GetSelectedFigur(), this->currentGame->GetPosition(this->currentGame->GetCurrentPlayer(), this->currentGame->GetSelectedFigur()));
			if (pos.first != -1) {
				Gui::ChipSelector.position(pos.first, pos.second);
				Gui::ChipSelector.update();
			}
			break;
		}
	}
}

/* Gehe zur ersten verfügbaren Figur-Selektion. */
void GameScreen::GetFirstAvlFigur() {
	for (uint8_t cFigur = 0; cFigur < this->currentGame->GetFigurAmount(); cFigur++) {
		if (this->currentGame->GetDone(this->currentGame->GetCurrentPlayer(), cFigur)) continue;

		if (GameHelper::CanMove(this->currentGame, this->currentGame->GetCurrentPlayer(), cFigur, this->currentGame->GetErgebnis())) {
			this->currentGame->SetSelectedFigur(cFigur);

			const std::pair<int, int> pos = this->GetPosition(this->currentGame->GetCurrentPlayer(), this->currentGame->GetSelectedFigur(), this->currentGame->GetPosition(this->currentGame->GetCurrentPlayer(), this->currentGame->GetSelectedFigur()));
			if (pos.first != -1) {
				Gui::ChipSelector.position(pos.first, pos.second);
				Gui::ChipSelector.update();
			}
			break;
		}
	}
}

/* Touch Handling für die Figuren. */
Structs::ButtonPos GameScreen::GetFigurTouchIndex(uint8_t player, uint8_t figur) const {
	const uint8_t position = this->currentGame->GetPosition(player, figur);

	/* 0 und 41+ haben eine spezielle handlung für die Touch Position. */
	if (position == 0) return this->PlayerField[(player * 4) + figur];

	/* Feld Handling. */
	if (position > 0 && position < 41) return this->MainField[GameHelper::PositionConvert(player, position) - 1];

	if (position > 40) return this->EingangField[(player * 4) + (position - 41)];

	return { 0,  0,  0,  0 };
}

/* Der Selektion Teil für die Figur. */
void GameScreen::FigureSelection(u32 hDown, u32 hHeld, touchPosition touch) {
	if ((hDown & KEY_RIGHT) || (hDown & KEY_R)) this->NextFigur();

	if ((hDown & KEY_LEFT) || (hDown & KEY_L)) this->PreviousFigur();

	if (hDown & KEY_TOUCH) {
		for (uint8_t i = 0; i < this->currentGame->GetFigurAmount(); i++) {
			if (touching(touch, this->GetFigurTouchIndex(this->currentGame->GetCurrentPlayer(), i))) {
				if (this->currentGame->GetDone(this->currentGame->GetCurrentPlayer(), i)) return;
				if (!GameHelper::CanMove(this->currentGame, this->currentGame->GetCurrentPlayer(), i, this->currentGame->GetErgebnis())) return;

				this->currentGame->SetSelectedFigur(i);

				const std::pair<int, int> pos = this->GetPosition(this->currentGame->GetCurrentPlayer(), this->currentGame->GetSelectedFigur(), this->currentGame->GetPosition(this->currentGame->GetCurrentPlayer(), this->currentGame->GetSelectedFigur()));
				if (pos.first != -1) {
					Gui::ChipSelector.position(pos.first, pos.second);
					Gui::ChipSelector.update();
				}

				const bool canCont = this->Play();
				if (canCont) this->awaitFigurSelect = false; // Weil wir spielen konnten, erwarten wir keine Figur Selektion.

				if (canCont) {
					/* Führe die Kick Aktion aus. */
					const std::pair<int8_t, int8_t> temp = GameHelper::KickAction(this->currentGame, this->currentGame->GetCurrentPlayer(), this->currentGame->GetSelectedFigur());

					if (temp.first != -1) {
						const std::pair<int, int> pos = this->GetPosition(temp.first, temp.second, this->currentGame->GetPosition(temp.first, temp.second));
						Gui::Chips[(temp.first * 4) + temp.second].position(pos.first, pos.second);
						Gui::Chips[0].update();
					}
				}

				if (GameHelper::HasFinished(this->currentGame, this->currentGame->GetCurrentPlayer())) {
					this->ToggleFigures(false);
					Gui::Chips[0].update();

					char tmp[256];
					snprintf(tmp, sizeof(tmp), Lang::get("PLAYER_WON").c_str(), this->currentGame->GetCurrentPlayer() + 1);
					Msg::WaitMsg(tmp);

					this->gameOver = true;
					return;
				}

				if (!this->awaitFigurSelect) this->NextPHandle();
				Gui::TopBG.draw(0, 0, true, 3, true);
				this->UpdateText();
				return;
			}
		}
	}

	if (hDown & KEY_A) {
		const bool canCont = this->Play();
		this->awaitFigurSelect = !canCont;

		if (canCont) {
			/* Führe die Kick Aktion aus. */
			const std::pair<int8_t, int8_t> temp = GameHelper::KickAction(this->currentGame, this->currentGame->GetCurrentPlayer(), this->currentGame->GetSelectedFigur());

			if (temp.first != -1) {
				const std::pair<int, int> pos = this->GetPosition(temp.first, temp.second, this->currentGame->GetPosition(temp.first, temp.second));
				Gui::Chips[(temp.first * 4) + temp.second].position(pos.first, pos.second);
				Gui::Chips[0].update();
			}
		}

		if (GameHelper::HasFinished(this->currentGame, this->currentGame->GetCurrentPlayer())) {
			this->ToggleFigures(false);
			Gui::Chips[0].update();

			char tmp[256];
			snprintf(tmp, sizeof(tmp), Lang::get("PLAYER_WON").c_str(), this->currentGame->GetCurrentPlayer() + 1);
			Msg::WaitMsg(tmp);

			this->gameOver = true;
			return;
		}

		if (!this->awaitFigurSelect) this->NextPHandle();
		Gui::TopBG.draw(0, 0, true, 3, true);
		this->UpdateText();
	}
}

/*
	Die Spiel-Logik.

	Wiedergibt (false), falls nicht spielbar.
*/
bool GameScreen::Play() {
	const uint8_t position = this->currentGame->GetPosition(this->currentGame->GetCurrentPlayer(), this->currentGame->GetSelectedFigur());

	/* 0 --> Auf Feld 1, falls das Ergebnis eine 6 war, ansonsten ungültig. */
	if (position == 0) {
		if (this->currentGame->GetErgebnis() == 6) {
			if (!GameHelper::DoesOwnFigurBlock(this->currentGame, this->currentGame->GetCurrentPlayer(), this->currentGame->GetSelectedFigur(), 1)) {
				this->FigurMovement(this->currentGame->GetCurrentPlayer(), this->currentGame->GetSelectedFigur(), 1);

				this->currentGame->SetPosition(this->currentGame->GetCurrentPlayer(), this->currentGame->GetSelectedFigur(), 1);

				if (!konfiguration->Animate()) {
					const std::pair<int, int> pos = this->GetPosition(this->currentGame->GetCurrentPlayer(), this->currentGame->GetSelectedFigur(), this->currentGame->GetPosition(this->currentGame->GetCurrentPlayer(), this->currentGame->GetSelectedFigur()));
					if (pos.first != -1) {
						Gui::Chips[(this->currentGame->GetCurrentPlayer() * 4) + this->currentGame->GetSelectedFigur()].position(pos.first, pos.second);
					}
				}

				Gui::ChipSelector.visibility(false);
				this->currentGame->SetCanContinue(true);
				Gui::Chips[0].update();
				return true;

			} else {
				return false; // Die Eigene Figur blockt.
			}

		} else {
			return false; // Position 0 und keine 6 -> Ungültig!
		}

		/* Falls die Position nicht 0 ist. */
	} else {
		if (position + this->currentGame->GetErgebnis() < 45) {
			if (!GameHelper::DoesOwnFigurBlock(this->currentGame, this->currentGame->GetCurrentPlayer(), this->currentGame->GetSelectedFigur(), this->currentGame->GetErgebnis())) {
				this->FigurMovement(this->currentGame->GetCurrentPlayer(), this->currentGame->GetSelectedFigur(), this->currentGame->GetErgebnis());

				this->currentGame->SetPosition(this->currentGame->GetCurrentPlayer(), this->currentGame->GetSelectedFigur(), position + this->currentGame->GetErgebnis());

				if (!konfiguration->Animate()) {
					const std::pair<int, int> pos = this->GetPosition(this->currentGame->GetCurrentPlayer(), this->currentGame->GetSelectedFigur(), this->currentGame->GetPosition(this->currentGame->GetCurrentPlayer(), this->currentGame->GetSelectedFigur()));
					if (pos.first != -1) {
						Gui::Chips[(this->currentGame->GetCurrentPlayer() * 4) + this->currentGame->GetSelectedFigur()].position(pos.first, pos.second);
					}
				}

				GameHelper::MarkAsDone(this->currentGame, this->currentGame->GetCurrentPlayer(), this->currentGame->GetSelectedFigur());

				for (uint8_t i = 0; i < this->currentGame->GetFigurAmount(); i++) {
					GameHelper::AdditionalDoneCheck(this->currentGame, this->currentGame->GetCurrentPlayer(), i);
				}

				Gui::ChipSelector.visibility(false);
				this->currentGame->SetCanContinue(this->currentGame->GetErgebnis() == 6);
				Gui::Chips[0].update();
				return true;

			} else {
				return false; // Die Eigene Figur blockt.
			}

		} else {
			return false; // Größer als 44.
		}
	}

	return false;
}

/* Nächster Spieler Handle. */
void GameScreen::NextPHandle() {
	/* Setze Werte zurück für den nächsten Zug. */
	this->currentGame->SetErgebnis(0);
	this->currentGame->SetSelectedFigur(0);

	if (this->currentGame->GetCanContinue()) {
		this->currentGame->SetCanContinue(false);
		return;
	}

	if (this->currentGame->GetCurrentPlayer() < this->currentGame->GetPlayerAmount() - 1) this->currentGame->SetCurrentPlayer(this->currentGame->GetCurrentPlayer() + 1);
	else this->currentGame->SetCurrentPlayer(0);

	this->currentGame->SetAVLDiceRolls(this->currentGame->GetDiceRolls()); // Setze standard Würfel-Rolls.
}

/* Computer Handling. */
void GameScreen::AIHandle() {
	this->currentGame->SetErgebnis(Overlays::RollDiceOverlay(true)); // Würfel mit Verzögerung.

	bool confirmation = false;
	Gui::TopBG.draw(0, 0, true, 3, true);
	Gui::Dices[this->currentGame->GetErgebnis() - 1].draw(88, 18 + 38, true, 3, true);
	Gui::font.clear();
	Gui::font.print(Lang::get("CURRENT_PLAYER") + std::to_string(this->currentGame->GetCurrentPlayer() + 1), 0, 0, true, 2, Alignment::center);
	Gui::font.print(Lang::get("A_CONTINUE"), 0, 175, true, 2, Alignment::center);
	Gui::font.update();

	while(!confirmation) {
		scanKeys();
		uint32_t hDown = keysDown();
		if ((hDown & KEY_A) || (hDown & KEY_TOUCH)) confirmation = true;
		swiWaitForVBlank();
	};

	Gui::font.clear();
	bool canMove = false;
	int8_t res = -1; // int8_t.. damit wir -1 benutzen können.

	for (uint8_t figur = 0; figur < this->currentGame->GetFigurAmount(); figur++) {
		if (GameHelper::CanMove(this->currentGame, this->currentGame->GetCurrentPlayer(), figur, this->currentGame->GetErgebnis())) {
			/* Fokussiert aufs kicken. ;P */
			if (GameHelper::CanKick(this->currentGame, this->currentGame->GetCurrentPlayer(), figur)) {
				this->currentGame->SetSelectedFigur(figur);
				canMove = true;
				break;

			} else {
				res = figur;
			}
		}
	}

	if (!canMove) {
		if (res != -1) {
			this->GetFirstAvlFigur();
			canMove = true;
		}
	}

	if (canMove) {
		const bool canCont = this->Play();

		if (canCont) {
			/* Führe die Kick Aktion aus. */
			const std::pair<int8_t, int8_t> temp = GameHelper::KickAction(this->currentGame, this->currentGame->GetCurrentPlayer(), this->currentGame->GetSelectedFigur());

			if (temp.first != -1) {
				const std::pair<int, int> pos = this->GetPosition(temp.first, temp.second, this->currentGame->GetPosition(temp.first, temp.second));
				Gui::Chips[(temp.first * 4) + temp.second].position(pos.first, pos.second);
				Gui::Chips[0].update();
			}
		}

		if (GameHelper::HasFinished(this->currentGame, this->currentGame->GetCurrentPlayer())) {
			this->ToggleFigures(false);
			Gui::Chips[0].update();

			char tmp[256];
			snprintf(tmp, sizeof(tmp), Lang::get("PLAYER_WON").c_str(), this->currentGame->GetCurrentPlayer() + 1);
			Msg::WaitMsg(tmp);

			this->gameOver = true;
			return;
		}

		this->NextPHandle();
		Gui::TopBG.draw(0, 0, true, 3, true);
		this->UpdateText();

	} else {
		GameHelper::SetContinue(this->currentGame, this->currentGame->GetCurrentPlayer());
		this->NextPHandle();
		Gui::TopBG.draw(0, 0, true, 3, true);
		this->UpdateText();
	}
}

#define _ANIM_DELAY 10 // Animations-Verzögerung der Figur. TODO: Finde eine gute Verzögerung.

/*
	Bewegt eine Figur.

	uint8_t player: Der Spieler.
	uint8_t figur: Die Figur.
	uint8_t movement: Die Anzahl der Felder.
*/
void GameScreen::FigurMovement(uint8_t player, uint8_t figur, uint8_t movement) {
	if (!konfiguration->Animate()) return;

	uint8_t toMove = movement; // Die Anzahl der Bewegungen.

	const uint8_t pos = this->currentGame->GetPosition(player, figur);
	uint8_t MovedPositions = 0;
	Gui::TopBG.draw(0, 0, true, 3, true);

	while(toMove > 0) {
		const std::pair<int8_t, int8_t> PosMove = AnimHelper::PlayerMovement(player, figur, pos + MovedPositions);

		Gui::Dices[toMove - 1].draw(88, 18 + 38, true, 3, true);

		for (uint8_t i = 0; i < _ANIM_DELAY; i++) { swiWaitForVBlank(); };

		Gui::Chips[(player * 4) + figur].position(Gui::Chips[(player * 4) + figur].x() + PosMove.first, Gui::Chips[(player * 4) + figur].y() + PosMove.second);
		Gui::Chips[(player * 4) + figur].update();
		MovedPositions++;
		toMove--;
	};
}