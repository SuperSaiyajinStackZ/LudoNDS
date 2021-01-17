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

#include "gui.hpp"
#include "tonccpy.h"

Font Gui::font;
Image Gui::Homes[4], Gui::MainField, Gui::Dices[6], Gui::BottomBG, Gui::TopBG, Gui::Button,
	  Gui::GameSettings[5], Gui::Arrows[2], Gui::TitleBar, Gui::StackZ, Gui::MsgBox, Gui::DieIcon;
Sprite Gui::Chips[16], Gui::ChipSelector, Gui::Selector[3], Gui::Selected, Gui::ButtonChip[2],
	   Gui::LangButtons[2], Gui::LangSelector;

static const uint16_t defaultPalette[] = {
	0x0000, 0xFBDE, 0xE739, 0xA5B1, 0xBDEF, 0x98C6, 0x94A5, 0x8842, 0x8000
};

/* Initialisiert das GUI und lädt die Assets. */
void Gui::Init() {
	Gui::font = Font("nitro:/graphics/font/font.nftr"); // Lade Schriftart.

	/* Lade die Häuser. */
	for (uint8_t i = 0; i < 4; i++) {
		Gui::Homes[i] = Image("nitro:/graphics/houses/house_" + std::to_string(i + 1) + ".gfx");
	}

	/* Initialisiere die Figuren Chips. */
	for (uint8_t i = 0; i < 16; i++) {
		Gui::Chips[i] = Sprite(false, SpriteSize_16x16, SpriteColorFormat_Bmp);
		Gui::Chips[i].drawImage(0, 0, Image("nitro:/graphics/chips/chip_" + std::to_string((i / 4) + 1) + ".gfx"));
		Gui::Chips[i].visibility(false);
		Gui::Chips[i].priority(1);
	}

	/* Die Würfel. */
	for (uint8_t i = 0; i < 6; i++) {
		Gui::Dices[i] = Image("nitro:/graphics/dice/die_" + std::to_string(i + 1) + ".gfx");
	}

	Gui::MainField = Image("nitro:/graphics/others/mainfield.gfx");
	Gui::BottomBG = Image("nitro:/graphics/bgs/bottom_bg.gfx");
	Gui::TopBG = Image("nitro:/graphics/bgs/top_bg.gfx");
	Gui::Button = Image("nitro:/graphics/others/button.gfx");
	Gui::StackZ = Image("nitro:/graphics/others/stackZ.gfx");
	Gui::TitleBar = Image("nitro:/graphics/bgs/titlebar.gfx");
	Gui::MsgBox = Image("nitro:/graphics/others/msgBox.gfx");
	Gui::DieIcon = Image("nitro:/graphics/dice/dieIcon.gfx");

	Gui::ChipSelector = Sprite(false, SpriteSize_16x16, SpriteColorFormat_Bmp);
	Gui::ChipSelector.drawImage(0, 0, Image("nitro:/graphics/chips/chip_selector.gfx"));
	Gui::ChipSelector.visibility(false);
	Gui::ChipSelector.priority(0);

	/* Spiel-Einstellungs Selektor. */
	for (uint8_t i = 0; i < 3; i++) {
		Gui::Selector[i] = Sprite(false, SpriteSize_32x32, SpriteColorFormat_Bmp);
		Gui::Selector[i].drawImage(0, 0, Image("nitro:/graphics/settings/selector.gfx"));
		Gui::Selector[i].visibility(false);
		Gui::Selector[i].priority(0);
	}

	/* Der Ausgewählte Seiten-Streifen. */
	Gui::Selected = Sprite(false, SpriteSize_16x16, SpriteColorFormat_Bmp);
	Gui::Selected.drawImage(0, 0, Image("nitro:/graphics/settings/selected.gfx"));
	Gui::Selected.visibility(false);
	Gui::Selected.priority(0);

	/* Die Schaltflächen Chips. */
	for (uint8_t i = 0; i < 2; i++) {
		Gui::ButtonChip[i] = Sprite(false, SpriteSize_16x16, SpriteColorFormat_Bmp);
		Gui::ButtonChip[i].drawImage(0, 0, Image("nitro:/graphics/chips/chip_1.gfx"));
		Gui::ButtonChip[i].visibility(false);
		Gui::ButtonChip[i].priority(0);
	}

	const std::string GSettings[7] = { "figure_Amount.gfx", "player_Amount.gfx", "use_ai.gfx", "dice_rolls.gfx", "use_ai.gfx", "prev.gfx", "next.gfx" };

	for (int i = 0; i < 5; i++) {
		Gui::GameSettings[i] = Image("nitro:/graphics/settings/" + GSettings[i]);
	}

	for (int i = 0; i < 2; i++) {
		Gui::Arrows[i] = Image("nitro:/graphics/settings/" + GSettings[5 + i]);
	}

	/* Sprach-Auswahl Zeug. */
	for (uint8_t i = 0; i < 2; i++) {
		Gui::LangButtons[i] = Sprite(false, SpriteSize_16x16, SpriteColorFormat_Bmp);
		Gui::LangButtons[i].drawImage(0, 0, Image("nitro:/graphics/chips/chip_" + std::to_string((i % 4) + 1) + ".gfx"));
		Gui::LangButtons[i].visibility(false);
		Gui::LangButtons[i].priority(1);
	}

	Gui::LangSelector = Sprite(false, SpriteSize_16x16, SpriteColorFormat_Bmp);
	Gui::LangSelector.drawImage(0, 0, Image("nitro:/graphics/chips/chip_selector.gfx"));
	Gui::LangSelector.visibility(false);
	Gui::LangSelector.priority(0);

	/* Kopiere Farb-Palette in den VRAM. */
	uint16_t palette[sizeof(defaultPalette) / sizeof(defaultPalette[0])];
	tonccpy(palette, defaultPalette, sizeof(palette));
	tonccpy(BG_PALETTE, palette, sizeof(palette));
	tonccpy(BG_PALETTE_SUB, palette, sizeof(palette));

	Gui::Chips[0].update(); // Aktualisiere Sprites.
}

/*
	Zeichne das Spielfeld.

	uint8_t xOffs: Der X Offset (13 als standard).
	uint8_t xOffs: Der Y Offset (13 als standard).
	bool onTop: Ob auf den oberen (true) oder unteren (false) Screen gezeichnet werden soll (Unteren Screen als standard).
*/
void Gui::DrawField(uint8_t xOffs, uint8_t yOffs, bool onTop) {
	Gui::MainField.draw(xOffs, yOffs, onTop, 3, true); // Hauptfeld.

	/* Häuser. */
	Gui::Homes[0].draw(xOffs, 106 + yOffs, onTop, 3, true);
	Gui::Homes[1].draw(xOffs, yOffs, onTop, 3, true);
	Gui::Homes[2].draw(106 + xOffs, yOffs, onTop, 3, true);
	Gui::Homes[3].draw(106 + xOffs, 106 + yOffs, onTop, 3, true);
}

/*
	Überlade die Selektoren chips für die Schaltflächen.

	uint8_t p: Die Chip farbe / der Spieler.
*/
void Gui::OverloadSelectorChip(uint8_t p) {
	for (uint8_t i = 0; i < 2; i++) {
		Gui::ButtonChip[i].clear();
		Gui::ButtonChip[i].drawImage(0, 0, Image("nitro:/graphics/chips/chip_" + std::to_string(p + 1) + ".gfx"));
	}
}