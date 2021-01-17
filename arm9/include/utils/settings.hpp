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

#ifndef _LUDONDS_SETTINGS_HPP
#define _LUDONDS_SETTINGS_HPP

#include "json.hpp"
#include <nds.h>
#include <string>

class Settings {
public:
	Settings();
	void Save();
	void Initialize();

	/* Wiedergebe und Setze die Sprache. */
	uint8_t Language() const { return this->v_language; };
	void Language(uint8_t v) { this->v_language = v; if (!this->changesMade) this->changesMade = true; };

	/* Wiedergebe und Setze ob die Regeln angezeigt werden sollen. */
	uint8_t Rules() const { return this->v_rules; };
	void Rules(uint8_t v) { this->v_rules = v; if (!this->changesMade) this->changesMade = true; };

	/* Wiedergebe und Setze ob die Figur bewegt werden soll oder nicht. */
	uint8_t Animate() const { return this->v_animate; };
	void Animate(uint8_t v) { this->v_animate = v; if (!this->changesMade) this->changesMade = true; };
private:
	int GetInt(const std::string &key) const;
	void SetInt(const std::string &key, int v);

	nlohmann::json config; // Die Konfigurations Variable.
	bool changesMade = false;

	/* Variablen für die Konfiguration. */
	uint8_t v_language, v_rules, v_animate;
};

#endif