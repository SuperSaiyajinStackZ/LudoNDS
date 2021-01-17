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

#ifndef _LUDONDS_GUI_HPP
#define _LUDONDS_GUI_HPP

#include "font.hpp"
#include "graphics.hpp"
#include "image.hpp"
#include "lang.hpp"
#include "sprite.hpp"
#include <string>

#define CLEAR			0x0
#define WHITE			0x1
#define LIGHT_GRAY		0x2
#define GRAY			0x3
#define DARKISH_GRAY	0x4
#define DARK_GRAY		0x5
#define DARKER_GRAY		0x6
#define DARKERER_GRAY	0x7

namespace Gui {
	extern Font font;
	extern Image Homes[4], MainField, Dices[6], BottomBG, TopBG, Button, GameSettings[5], Arrows[2], TitleBar, StackZ, MsgBox, DieIcon;
	extern Sprite Chips[16], ChipSelector, Selector[3], Selected, ButtonChip[2], LangButtons[2], LangSelector;

	void Init();
	void DrawField(uint8_t xOffs = 13, uint8_t yOffs = 13, bool onTop = false);
	void OverloadSelectorChip(uint8_t p);
};

#endif