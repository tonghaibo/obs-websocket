/*
obs-websocket
Copyright (C) 2016	Stéphane Lepin <stephane.lepin@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program. If not, see <https://www.gnu.org/licenses/>
*/

#ifndef CONFIG_H
#define CONFIG_H

#include <obs-module.h>
#include <mbedtls/entropy.h>
#include <mbedtls/ctr_drbg.h>

class Config {
	public:
		Config();
		~Config();
		void SetPassword(const char *password);
		bool CheckAuth(const char *userChallenge);
		static const char* GenerateSalt(mbedtls_ctr_drbg_context *rng);
		static const char* GenerateChallenge(const char *password, const char *salt);
		static void OBSSaveCallback(obs_data_t *save_data, bool saving, void *);

		bool AuthRequired;
		const char *Challenge;
		const char *Salt;
		bool SettingsLoaded;
		
		static Config* Current();

	private:
		static Config *_instance;
		mbedtls_entropy_context entropy;
		mbedtls_ctr_drbg_context rng;
};

#endif // CONFIG_H