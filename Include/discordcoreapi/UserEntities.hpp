/*
	MIT License

	DiscordCoreAPI, A bot library for Discord, written in C++, and featuring explicit multithreading through the usage of custom, asynchronous C++
   CoRoutines.

	Copyright 2022, 2023 Chris M. (RealTimeChris)

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/
/// UserEntities.hpp - Header for UserData related classes and structs.
/// May 13, 2021
/// https://discordcoreapi.com
/// \file UserEntities.hpp

#pragma once

#include <discordcoreapi/FoundationEntities.hpp>
#include <discordcoreapi/Utilities/HttpsClient.hpp>
#include <discordcoreapi/Utilities/WebSocketClient.hpp>

namespace DiscordCoreAPI {

	/**
	 * \addtogroup foundation_entities
	 * @{
	 */

	/// @brief For adding a user to a group DM.
	struct AddRecipientToGroupDMData {
		Snowflake channelId{};///< The ChannelData Snowflake of the DM.
		std::string token{};///< The user's access token.
		std::string nick{};///< The user's nickname.
		Snowflake userId{};///< The user's Snowflake.
	};

	/// @brief For removing a User from a group DM.
	struct RemoveRecipientFromGroupDMData {
		Snowflake channelId{};///< The ChannelData Snowflake of the DM.
		Snowflake userId{};///< The user's Snowflake.
	};

	/// @brief For updating the bot's current voice state.
	struct ModifyCurrentUserVoiceStateData {
		std::string requestToSpeakTimestamp{};///< ISO8601 timeStamp.
		Snowflake channelId{};///< The id of the ChannelData the user is currently in.
		Snowflake guildId{};///< The Guild within which to update the bot's voice state.
		bool suppress{};///< Toggles the user's suppress state.
	};

	/// @brief For modifying a User's voice state.
	struct ModifyUserVoiceStateData {
		Snowflake channelId{};///< The id of the ChannelData the user is currently in.
		Snowflake guildId{};///< The Guild within which you would like to modify their voice state.
		Snowflake userId{};///< The user for which you would like to modify the voice state of.
		bool suppress{};///< Toggles the user's suppress state.
	};

	/// @brief For getting UserData responseData from the library's cache or the Discord server.
	struct GetUserData {
		Snowflake userId{};///< The id of the desired UserData.
	};

	/// @brief For modifying the Bot's UserData responseData.
	struct ModifyCurrentUserData {
		std::string userName{};///< UserData's username, if changed may cause the user's discriminator to be randomized.
		std::string avatar{};///< If passed, modifies the user's avatar.
	};

	/**@}*/

	/**
	 * \addtogroup main_endpoints
	 * @{
	 */
	/// @brief An interface class for the UserData related Discord endpoints.
	class DiscordCoreAPI_Dll Users {
	  public:
		friend class DiscordCoreInternal::WebSocketClient;
		friend class DiscordCoreInternal::BaseSocketAgent;
		friend class DiscordCoreClient;
		friend class UserData;
		friend class Guild;

		static void initialize(DiscordCoreInternal::HttpsClient*, ConfigManager* configManagerNew);

		/// @brief Adds a chosen recipient to a group DM.
		/// @param dataPackage An AddRecipientToGroupDMData  structure.
		/// @return A CoRoutine containing void.
		static CoRoutine<void> addRecipientToGroupDMAsync(AddRecipientToGroupDMData dataPackage);

		/// @brief Removes a chosen recipient from a group DM.
		/// @param dataPackage A RemoveRecipientFromGroupDMData structure.
		/// @return A CoRoutine containing void.
		static CoRoutine<void> removeRecipientFromGroupDMAsync(RemoveRecipientFromGroupDMData dataPackage);

		/// @brief Sets the bot's current voice state.
		/// @param dataPackage A ModifyCurrentUserVoiceStateData structure.
		/// @return A CoRoutine containing void.
		static CoRoutine<void> modifyCurrentUserVoiceStateAsync(ModifyCurrentUserVoiceStateData dataPackage);

		/// @brief Sets another user's current voice state.
		/// @param dataPackage A ModifyUserVoiceStateData structure.
		/// @return A CoRoutine containing void.
		static CoRoutine<void> modifyUserVoiceStateAsync(ModifyUserVoiceStateData dataPackage);

		/// @brief Collects the Bot's current UserData responseData.
		/// @return A CoRoutine containing a User.
		static CoRoutine<UserData> getCurrentUserAsync();

		/// @brief Collects a given User from the library's cache.
		/// @param dataPackage A GetUserData structure.
		/// @return A CoRoutine containing a User.
		static UserCacheData getCachedUser(GetUserData dataPackage);

		/// @brief Collects a given User from the Discord servers.
		/// @param dataPackage A GetUserData structure.
		/// @return A CoRoutine containing a User.
		static CoRoutine<UserData> getUserAsync(GetUserData dataPackage);

		/// @brief Modifies the Bot's UserData responseData.
		/// @param dataPackage A ModifyCurrentUserData structure.
		/// @return A CoRoutine containing a User.
		static CoRoutine<UserData> modifyCurrentUserAsync(ModifyCurrentUserData dataPackage);

		/// @brief Collects the UserData's Connections.
		/// @return A CoRoutine containing a vector<ConnectionData>.
		static CoRoutine<Jsonifier::Vector<ConnectionData>> getUserConnectionsAsync();

		/// @brief Collects the Application responseData associated with the current Bot.
		/// @return A CoRoutine containing an ApplicationData.
		static CoRoutine<ApplicationData> getCurrentUserApplicationInfoAsync();

		/// @brief Collects the Authorization info associated with the current Bot.
		/// @return A CoRoutine containing an AuthorizationInfoData.
		static CoRoutine<AuthorizationInfoData> getCurrentUserAuthorizationInfoAsync();

		static void insertUser(UserCacheData&& user);

		inline static ObjectCache<UserCacheData>& getCache() {
			return cache;
		}

		static bool doWeCacheUsers();

	  protected:
		static DiscordCoreInternal::HttpsClient* httpsClient;
		static ObjectCache<UserCacheData> cache;
		static bool doWeCacheUsersBool;
	};
	/**@}*/

}// namespace DiscordCoreAPI
