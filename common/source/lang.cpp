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

#include "lang.hpp"
#include <stdio.h>

static nlohmann::json appJson;
#define LANG_PATH "nitro:/lang/"

/*
	Wiedergebe den String von der app.json datei.

	const std::string &key: Welcher "index" abgerufen werden soll.
*/
std::string Lang::get(const std::string &key) {
	if (!appJson.contains(key)) return "";

	return appJson.at(key).get_ref<const std::string &>();
}

static std::string langs[] = { "de", "en" };

/*
	Lädt eine app.json datei.

	uint8_t lang: Der Sprachen-Index, welcher oben als string array angegeben ist.
*/
void Lang::load(uint8_t lang) {
	FILE *values = fopen((LANG_PATH + langs[lang] + "/app.json").c_str(), "rt");
	if (values) appJson = nlohmann::json::parse(values, nullptr, false);
	fclose(values);
}