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
/// EventManager.cpp - Header for the event manager class.
/// Jun 7, 2021
/// https://discordcoreapi.com
/// \file EventManager.cpp

#include <discordcoreapi/CoRoutine.hpp>
#include <discordcoreapi/CommandController.hpp>
#include <discordcoreapi/DiscordCoreClient.hpp>
#include <discordcoreapi/EventManager.hpp>

namespace Jsonifier {

	template<> struct Core<DiscordCoreAPI::AutoModerationActionExecutionEventData> {
		using ValueType					 = DiscordCoreAPI::AutoModerationActionExecutionEventData;
		static constexpr auto parseValue = object("alert_system_message_id", &ValueType::alertSystemMessageId, "rule_trigger_type", &ValueType::ruleTriggerType, "matched_keyword",
			&ValueType::matchedKeyword, "matched_content", &ValueType::matchedContent, "content", &ValueType::content, "channel_id", &ValueType::channelId, "message_id",
			&ValueType::messageId, "action", &ValueType::action, "guild_id", &ValueType::guildId, "rule_id", &ValueType::ruleId, "user_id", &ValueType::userId);
	};

	template<> struct Core<DiscordCoreAPI::VoiceStateData> {
		using ValueType2 = DiscordCoreAPI::VoiceStateData;
		static constexpr auto parseValue =
			object("request_to_speak_timestamp", &ValueType2::requestToSpeakTimestamp, "session_id", &ValueType2::sessionId, "self_stream", &ValueType2::selfStream, "self_video",
				&ValueType2::selfVideo, "self_deaf", &ValueType2::selfDeaf, "self_mute", &ValueType2::selfMute, "suppress", &ValueType2::suppress, "deaf", &ValueType2::deaf,
				"mute", &ValueType2::mute, "user_id", &ValueType2::userId, "channel_id", &ValueType2::channelId, "guild_id", &ValueType2::guildId);
	};

	template<> struct Core<DiscordCoreAPI::GuildEmojisUpdateEventData> {
		using ValueType					 = DiscordCoreAPI::GuildEmojisUpdateEventData;
		static constexpr auto parseValue = object("emojis", &ValueType::emojis, "guild_id", &ValueType::guildId);
	};

	template<> struct Core<DiscordCoreAPI::ChannelPinsUpdateEventData> {
		using ValueType					 = DiscordCoreAPI::ChannelPinsUpdateEventData;
		static constexpr auto parseValue = object("last_pin_timestamp", &ValueType::lastPinTimeStamp, "channel_id", &ValueType::channelId, "guild_id", &ValueType::guildId);
	};

	template<> struct Core<DiscordCoreAPI::TypingStartData> {
		using ValueType					 = DiscordCoreAPI::TypingStartData;
		static constexpr auto parseValue = object("member", &ValueType::member, "channel_id", &ValueType::channelId, "guild_id", &ValueType::guildId, "timestamp",
			&ValueType::timeStamp, "user_id", &ValueType::userId);
	};

	template<> struct Core<DiscordCoreAPI::ReactionRemoveData> {
		using ValueType					 = DiscordCoreAPI::ReactionRemoveData;
		static constexpr auto parseValue = object("channel_id", &ValueType::channelId, "message_id", &ValueType::messageId, "guild_id", &ValueType::guildId, "user_id",
			&ValueType::userId, "emoji", &ValueType::emoji);
	};

	template<> struct Core<DiscordCoreAPI::GuildStickersUpdateEventData> {
		using ValueType					 = DiscordCoreAPI::GuildStickersUpdateEventData;
		static constexpr auto parseValue = object("stickers", &ValueType::stickers, "guild_id", &ValueType::guildId);
	};

	template<> struct Core<DiscordCoreAPI::VoiceServerUpdateData> {
		using ValueType					 = DiscordCoreAPI::VoiceServerUpdateData;
		static constexpr auto parseValue = object("endpoint", &ValueType::endpoint, "guild_id", &ValueType::guildId, "token", &ValueType::token);
	};

	template<> struct Core<DiscordCoreAPI::GuildMembersChunkEventData> {
		using ValueType					 = DiscordCoreAPI::GuildMembersChunkEventData;
		static constexpr auto parseValue = object("presences", &ValueType::presences, "members", &ValueType::members, "not_found", &ValueType::notFound, "chunk_index",
			&ValueType::chunkIndex, "chunk_count", &ValueType::chunkCount, "guild_id", &ValueType::guildId, "nonce", &ValueType::nonce);
	};

	template<> struct Core<DiscordCoreAPI::GuildMemberRemoveData> {
		using ValueType					 = DiscordCoreAPI::GuildMemberRemoveData;
		static constexpr auto parseValue = object("guild_id", &ValueType::guildId, "user", &ValueType::user);
	};

	template<> struct Core<DiscordCoreAPI::GuildBanAddData> {
		using ValueType					 = DiscordCoreAPI::GuildBanAddData;
		static constexpr auto parseValue = object("guild_id", &ValueType::guildId, "user", &ValueType::user);
	};

	template<> struct Core<DiscordCoreAPI::GuildBanRemoveData> {
		using ValueType					 = DiscordCoreAPI::GuildBanRemoveData;
		static constexpr auto parseValue = object("guild_id", &ValueType::guildId, "user", &ValueType::user);
	};

	template<> struct Core<DiscordCoreAPI::RoleCreationData> {
		using ValueType					 = DiscordCoreAPI::RoleCreationData;
		static constexpr auto parseValue = object("guild_id", &ValueType::guildId, "role", &ValueType::role);
	};

	template<> struct Core<DiscordCoreAPI::RoleUpdateData> {
		using ValueType					 = DiscordCoreAPI::RoleUpdateData;
		static constexpr auto parseValue = object("guild_id", &ValueType::guildId, "role", &ValueType::role);
	};

	template<> struct Core<DiscordCoreAPI::RoleDeletionData> {
		using ValueType					 = DiscordCoreAPI::RoleDeletionData;
		static constexpr auto parseValue = object("guild_id", &ValueType::guildId, "role", &ValueType::role);
	};

	template<> struct Core<DiscordCoreAPI::GuildScheduledEventUserAddData> {
		using ValueType					 = DiscordCoreAPI::GuildScheduledEventUserAddData;
		static constexpr auto parseValue = object("guild_scheduled_event_id", &ValueType::guildScheduledEventId, "guild_id", &ValueType::guildId, "user_id", &ValueType::userId);
	};

	template<> struct Core<DiscordCoreAPI::GuildScheduledEventUserRemoveData> {
		using ValueType					 = DiscordCoreAPI::GuildScheduledEventUserRemoveData;
		static constexpr auto parseValue = object("guild_scheduled_event_id", &ValueType::guildScheduledEventId, "guild_id", &ValueType::guildId, "user_id", &ValueType::userId);
	};

	template<> struct Core<DiscordCoreAPI::IntegrationCreationData> {
		using ValueType					 = DiscordCoreAPI::IntegrationCreationData;
		static constexpr auto parseValue = object("integration_data", &ValueType::integrationData, "guild_id", &ValueType::guildId);
	};

	template<> struct Core<DiscordCoreAPI::IntegrationUpdateData> {
		using ValueType					 = DiscordCoreAPI::IntegrationUpdateData;
		static constexpr auto parseValue = object("integration_data", &ValueType::integrationData, "guild_id", &ValueType::guildId);
	};

	template<> struct Core<DiscordCoreAPI::IntegrationDeletionData> {
		using ValueType					 = DiscordCoreAPI::IntegrationDeletionData;
		static constexpr auto parseValue = object("application_id", &ValueType::applicationId, "guild_id", &ValueType::guildId, "id", &ValueType::id);
	};

	template<> struct Core<DiscordCoreAPI::InviteDeletionData> {
		using ValueType					 = DiscordCoreAPI::InviteDeletionData;
		static constexpr auto parseValue = object("channel_id", &ValueType::channelId, "guild_id", &ValueType::guildId, "code", &ValueType::code);
	};

	template<> struct Core<DiscordCoreAPI::MessageDeletionData> {
		using ValueType					 = DiscordCoreAPI::MessageDeletionData;
		static constexpr auto parseValue = object("message_id", &ValueType::messageId, "channel_id", &ValueType::channelId, "guild_id", &ValueType::guildId);
	};

	template<> struct Core<DiscordCoreAPI::MessageDeletionBulkData> {
		using ValueType					 = DiscordCoreAPI::MessageDeletionBulkData;
		static constexpr auto parseValue = object("ids", &ValueType::ids, "channel_id", &ValueType::channelId, "guild_id", &ValueType::guildId);
	};

	template<> struct Core<DiscordCoreAPI::ReactionRemoveAllData> {
		using ValueType					 = DiscordCoreAPI::ReactionRemoveAllData;
		static constexpr auto parseValue = object("channel_id", &ValueType::channelId, "message_id", &ValueType::messageId, "guild_id", &ValueType::guildId);
	};

	template<> struct Core<DiscordCoreAPI::ReactionRemoveEmojiData> {
		using ValueType = DiscordCoreAPI::ReactionRemoveEmojiData;
		static constexpr auto parseValue =
			object("message_id", &ValueType::messageId, "channel_id", &ValueType::channelId, "guild_id", &ValueType::guildId, "emoji", &ValueType::emoji);
	};

	template<> struct Core<DiscordCoreAPI::WebHookUpdateData> {
		using ValueType					 = DiscordCoreAPI::WebHookUpdateData;
		static constexpr auto parseValue = object("channel_id", &ValueType::channelId, "guild_id", &ValueType::guildId);
	};

}// namespace Jsonifier

namespace DiscordCoreAPI {

	template<> UnorderedMap<std::string, UnboundedMessageBlock<MessageData>*> ObjectCollector<MessageData>::objectsBuffersMap;

	template<> UnorderedMap<std::string, UnboundedMessageBlock<ReactionData>*> ObjectCollector<ReactionData>::objectsBuffersMap;

	OnInputEventCreationData::OnInputEventCreationData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	OnApplicationCommandPermissionsUpdateData::OnApplicationCommandPermissionsUpdateData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	OnAutoModerationRuleCreationData::OnAutoModerationRuleCreationData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	OnAutoModerationRuleUpdateData::OnAutoModerationRuleUpdateData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	OnAutoModerationRuleDeletionData::OnAutoModerationRuleDeletionData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	OnAutoModerationActionExecutionData::OnAutoModerationActionExecutionData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	OnChannelCreationData::OnChannelCreationData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
		if (Channels::doWeCacheChannels()) {
			if (Guilds::getCache().contains(value.guildId)) {
				Guilds::getCache()[value.guildId].channels.emplace(value.id);
			}
			Channels::insertChannel(static_cast<ChannelCacheData>(value));
		}
	}

	OnChannelUpdateData::OnChannelUpdateData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<UpdatedEventData*>(this), dataToParse);
		oldValue = Channels::getCachedChannel({ .channelId = value.id });
		if (Channels::doWeCacheChannels()) {
			Channels::insertChannel(static_cast<ChannelCacheData>(value));
		}
	}

	OnChannelDeletionData::OnChannelDeletionData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
		if (Channels::doWeCacheChannels()) {
			if (Guilds::getCache().contains(value.guildId)) {
				if (Guilds::getCache().operator[](value.guildId).channels.contains(value.id)) {
					Guilds::getCache().operator[](value.guildId).channels.erase(value.id);
				}
			}
			Channels::removeChannel(static_cast<ChannelCacheData>(value));
		}
	}

	OnChannelPinsUpdateData::OnChannelPinsUpdateData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	OnThreadCreationData::OnThreadCreationData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	OnThreadUpdateData::OnThreadUpdateData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	OnThreadDeletionData::OnThreadDeletionData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	OnThreadListSyncData::OnThreadListSyncData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	OnThreadMemberUpdateData::OnThreadMemberUpdateData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	OnThreadMembersUpdateData::OnThreadMembersUpdateData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	template<JsonifierInternal::TimeT TimeType> class StopWatchNew {
	  public:
		inline StopWatchNew() {
			resetTimer();
		}

		using HRClock = std::chrono::high_resolution_clock;

		inline StopWatchNew& operator=(StopWatchNew&& other) noexcept {
			maxNumberOfTimeUnits.store(other.maxNumberOfTimeUnits.load(std::memory_order_acquire), std::memory_order_release);
			startTime.store(other.startTime.load(std::memory_order_acquire), std::memory_order_release);
			return *this;
		}

		inline StopWatchNew(StopWatchNew&& other) noexcept {
			*this = std::move(other);
		}

		inline StopWatchNew& operator=(const StopWatchNew& other) noexcept {
			maxNumberOfTimeUnits.store(other.maxNumberOfTimeUnits.load(std::memory_order_acquire), std::memory_order_release);
			startTime.store(other.startTime.load(std::memory_order_acquire), std::memory_order_release);
			return *this;
		}

		inline StopWatchNew(const StopWatchNew& other) noexcept {
			*this = other;
		}

		inline StopWatchNew(uint64_t maxNumberOfTimeUnitsNew) {
			maxNumberOfTimeUnits.store(TimeType{ maxNumberOfTimeUnitsNew }, std::memory_order_release);
			resetTimer();
		}

		inline StopWatchNew(TimeType maxNumberOfTimeUnitsNew) {
			maxNumberOfTimeUnits.store(maxNumberOfTimeUnitsNew, std::memory_order_release);
			resetTimer();
		}

		inline TimeType totalTimePassed() const {
			return std::chrono::duration_cast<TimeType>(HRClock::now().time_since_epoch()) - startTime.load(std::memory_order_acquire);
		}

		inline TimeType getTotalWaitTime() const {
			return maxNumberOfTimeUnits.load(std::memory_order_acquire);
		}

		inline bool hasTimePassed() const {
			if (std::chrono::duration_cast<TimeType>(HRClock::now().time_since_epoch()) - startTime.load(std::memory_order_acquire) >=
				maxNumberOfTimeUnits.load(std::memory_order_acquire)) {
				return true;
			} else {
				return false;
			}
		}

		inline void resetTimer() {
			startTime.store(std::chrono::duration_cast<TimeType>(HRClock::now().time_since_epoch()), std::memory_order_release);
		}

	  protected:
		std::atomic<TimeType> maxNumberOfTimeUnits{ TimeType{ 0 } };
		std::atomic<TimeType> startTime{ TimeType{ 0 } };
	};

	inline StopWatchNew<Milliseconds> stopWatch{};

	OnGuildCreationData::OnGuildCreationData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse, DiscordCoreClient* client) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
		value.discordCoreClient = client;
		if (GuildMembers::doWeCacheGuildMembers() || Users::doWeCacheUsers()) {
			if (GuildMembers::doWeCacheGuildMembers()) {
				GuildMembers::getCache().reserve(GuildMembers::getCache().size() + value.members.size());
			}
			if (Users::doWeCacheUsers()) {
				Users::getCache().reserve(GuildMembers::getCache().size() + value.members.size());
			}
			for (auto& valueNew: value.members) {
				try {
					if (Users::doWeCacheUsers()) {
						Users::insertUser(static_cast<UserCacheData>(valueNew.user));
					}
					if (GuildMembers::doWeCacheGuildMembers()) {
						valueNew.guildId = value.id;
						GuildMembers::insertGuildMember(static_cast<GuildMemberCacheData>(valueNew));
					}					
				} catch (...) {
					MessagePrinter::printError<PrintMessageType::General>("OnGuildCreationData::OnGuildCreationData()");
				}
			}
			for (auto& valueNew: value.voiceStates) {
				try {
					valueNew.guildId = value.id;
					GuildMembers::insertVoiceState(static_cast<VoiceStateDataLight>(valueNew));
				} catch (...) {
					MessagePrinter::printError<PrintMessageType::General>("OnGuildCreationData::OnGuildCreationData()");
				}
			}
		}
		if (Channels::doWeCacheChannels()) {
			Channels::getCache().reserve(GuildMembers::getCache().size() + value.channels.size());
			for (auto& valueNew: value.channels) {
				try {
					valueNew.guildId = value.id;
					Channels::insertChannel(static_cast<ChannelCacheData>(valueNew));
				} catch (...) {
					MessagePrinter::printError<PrintMessageType::General>("OnGuildCreationData::OnGuildCreationData()");
				}
			}
		}
		if (Roles::doWeCacheRoles()) {
			Roles::getCache().reserve(GuildMembers::getCache().size() + value.roles.size());
			for (auto& valueNew: value.roles) {
				try {
					Roles::insertRole(static_cast<RoleCacheData>(valueNew));
				} catch (...) {
					MessagePrinter::printError<PrintMessageType::General>("OnGuildCreationData::OnGuildCreationData()");
				}
			}
		}
		if (Guilds::doWeCacheGuilds()) {
			value.discordCoreClient = client;
			if (Guilds::getCache().size() % 100 == 0) {
				std::cout << "GUILD COUNT: " << Guilds::getCache().size() << ", AFTER: " << stopWatch.totalTimePassed() << std::endl;
			}
			Guilds::insertGuild(static_cast<GuildCacheData>(value));
		}
	}

	OnGuildUpdateData::OnGuildUpdateData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse, DiscordCoreClient* clientNew) {
		parserNew.parseJson<true, true>(*static_cast<UpdatedEventData*>(this), dataToParse);
		value.discordCoreClient = clientNew;
		if (Guilds::doWeCacheGuilds()) {
			Guilds::insertGuild(static_cast<GuildCacheData>(value));
		}
	}

	OnGuildDeletionData::OnGuildDeletionData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
		for (auto& valueNew: value.members) {
			GuildMembers::removeGuildMember(valueNew);
		}
		for (auto& valueNew: value.channels) {
			Channels::removeChannel(valueNew);
		}
		for (auto& valueNew: value.roles) {
			Roles::removeRole(valueNew);
		}
		if (Guilds::doWeCacheGuilds()) {
			Guilds::removeGuild(value);
		}
	}

	OnGuildBanAddData::OnGuildBanAddData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
		if (Guilds::getCache().contains(value.guildId)) {
			if (Guilds::getCache().operator[](value.guildId).members.contains(value.user.id)) {
				Guilds::getCache().operator[](value.guildId).members.erase(value.user.id);
				--Guilds::getCache()[value.guildId].memberCount;
			}
		}
	}

	OnGuildBanRemoveData::OnGuildBanRemoveData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	OnGuildEmojisUpdateData::OnGuildEmojisUpdateData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
		if (Guilds::getCache().contains(value.guildId)) {
			Guilds::getCache()[value.guildId].emoji.clear();
			for (auto& valueNew: value.emojis) {
				Guilds::getCache()[value.guildId].emoji.emplace(valueNew.id);
			}
		}
	}

	OnGuildStickersUpdateData::OnGuildStickersUpdateData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	OnGuildIntegrationsUpdateData::OnGuildIntegrationsUpdateData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	OnGuildMemberAddData::OnGuildMemberAddData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
		if (GuildMembers::doWeCacheGuildMembers()) {
			GuildMembers::insertGuildMember(static_cast<GuildMemberCacheData>(value));
			if (Guilds::getCache().contains(value.guildId)) {
				++Guilds::getCache()[value.guildId].memberCount;
			}
		}
	}

	OnGuildMemberRemoveData::OnGuildMemberRemoveData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
		GuildMemberData guildMember = GuildMembers::getCachedGuildMember({ .guildMemberId = value.user.id, .guildId = value.guildId });
		if (GuildMembers::doWeCacheGuildMembers()) {
			if (Guilds::getCache().contains(value.guildId)) {
				if (Guilds::getCache().operator[](value.guildId).members.contains(value.user.id)) {
					Guilds::getCache().operator[](value.guildId).members.erase(value.user.id);
					--Guilds::getCache()[value.guildId].memberCount;
				}
			}
			GuildMembers::removeGuildMember(guildMember);
		}
	}

	OnGuildMemberUpdateData::OnGuildMemberUpdateData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<UpdatedEventData*>(this), dataToParse);
		oldValue = GuildMembers::getCachedGuildMember({ .guildMemberId = value.user.id, .guildId = value.guildId });
		if (GuildMembers::doWeCacheGuildMembers()) {
			GuildMembers::insertGuildMember(static_cast<GuildMemberCacheData>(value));
		}
	}

	OnGuildMembersChunkData::OnGuildMembersChunkData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	OnRoleCreationData::OnRoleCreationData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
		if (Roles::doWeCacheRoles()) {
			if (Guilds::getCache().contains(value.guildId)) {
				Roles::insertRole(static_cast<RoleCacheData>(value.role));
				Guilds::getCache()[value.guildId].roles.emplace(value.role.id);
			}
		}
	}

	OnRoleUpdateData::OnRoleUpdateData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<UpdatedEventData*>(this), dataToParse);
		oldValue = Roles::getCachedRole({ .guildId = value.guildId, .roleId = value.role.id });
		if (Roles::doWeCacheRoles()) {
			Roles::insertRole(static_cast<RoleCacheData>(value.role));
		}
	}

	OnRoleDeletionData::OnRoleDeletionData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
		if (Roles::doWeCacheRoles()) {
			if (Guilds::getCache().contains(value.guildId)) {
				if (Guilds::getCache().operator[](value.guildId).channels.contains(value.role.id)) {
					Guilds::getCache().operator[](value.guildId).channels.erase(value.role.id);
				}
			}
			Roles::removeRole(static_cast<RoleCacheData>(value.role));
		}
	}

	OnVoiceServerUpdateData::OnVoiceServerUpdateData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse, DiscordCoreInternal::WebSocketClient* sslShard) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
		if (sslShard->areWeCollectingData.load(std::memory_order_acquire) && !sslShard->serverUpdateCollected && !sslShard->stateUpdateCollected) {
			sslShard->voiceConnectionData		   = DiscordCoreInternal::VoiceConnectionData{};
			sslShard->voiceConnectionData.endPoint = value.endpoint;
			sslShard->voiceConnectionData.token	   = value.token;
			sslShard->serverUpdateCollected		   = true;
		} else if (sslShard->areWeCollectingData.load(std::memory_order_acquire) && !sslShard->serverUpdateCollected) {
			sslShard->voiceConnectionData.endPoint = value.endpoint;
			sslShard->voiceConnectionData.token	   = value.token;
			if (sslShard->voiceConnectionDataBufferMap.contains(value.guildId.operator const uint64_t&())) {
				sslShard->voiceConnectionDataBufferMap[value.guildId.operator const uint64_t&()]->send(sslShard->voiceConnectionData);
			}
			sslShard->areWeCollectingData.store(false, std::memory_order_release);
			sslShard->serverUpdateCollected = false;
			sslShard->stateUpdateCollected	= false;
		}
	};

	OnGuildScheduledEventCreationData::OnGuildScheduledEventCreationData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	OnGuildScheduledEventUpdateData::OnGuildScheduledEventUpdateData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	OnGuildScheduledEventDeletionData::OnGuildScheduledEventDeletionData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	OnGuildScheduledEventUserAddData::OnGuildScheduledEventUserAddData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	OnGuildScheduledEventUserRemoveData::OnGuildScheduledEventUserRemoveData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	OnIntegrationCreationData::OnIntegrationCreationData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	OnIntegrationUpdateData::OnIntegrationUpdateData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	OnIntegrationDeletionData::OnIntegrationDeletionData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	OnInteractionCreationData::OnInteractionCreationData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse, DiscordCoreClient* discordCoreClient) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
		UniquePtr<InputEventData> eventData{ makeUnique<InputEventData>(value) };
		switch (value.type) {
			case InteractionType::Application_Command: {
				eventData->responseType		= InputEventResponseType::Unset;
				*eventData->interactionData = value;
				UniquePtr<CommandData> commandData{ makeUnique<CommandData>(*eventData) };
				discordCoreClient->getCommandController().checkForAndRunCommand(*commandData);
				UniquePtr<OnInputEventCreationData> eventCreationData{ makeUnique<OnInputEventCreationData>(parser, dataToParse) };
				eventCreationData->value = *eventData;
				break;
			}
			case InteractionType::Message_Component: {
				switch (value.data.componentType) {
					case ComponentType::Action_Row:
					case ComponentType::Button: {
						eventData->responseType		= InputEventResponseType::Unset;
						*eventData->interactionData = value;
						if (ButtonCollector::buttonInteractionBuffersMap.contains(eventData->getChannelData().id + eventData->getMessageData().id)) {
							ButtonCollector::buttonInteractionBuffersMap[eventData->getChannelData().id + eventData->getMessageData().id]->send(value);
						}
						ButtonCollector::buttonInteractionEventsMap.operator()(*eventData->interactionData);
						break;
					}
					case ComponentType::Channel_Select:
					case ComponentType::Mentionable_Select:
					case ComponentType::Role_Select:
					case ComponentType::User_Select:
					case ComponentType::String_Select: {
						eventData->responseType		= InputEventResponseType::Unset;
						*eventData->interactionData = value;
						if (SelectMenuCollector::selectMenuInteractionBuffersMap.contains(eventData->getChannelData().id + eventData->getMessageData().id)) {
							SelectMenuCollector::selectMenuInteractionBuffersMap[eventData->getChannelData().id + eventData->getMessageData().id]->send(value);
						}
						SelectMenuCollector::selectMenuInteractionEventsMap.operator()(*eventData->interactionData);
						break;
					}
					case ComponentType::Text_Input: {
						break;
					}
				}
				break;
			}
			case InteractionType::Modal_Submit: {
				eventData->responseType		= InputEventResponseType::Unset;
				*eventData->interactionData = value;
				UniquePtr<OnInputEventCreationData> eventCreationData{ makeUnique<OnInputEventCreationData>(parser, dataToParse) };
				eventCreationData->value = *eventData;
				if (ModalCollector::modalInteractionBuffersMap.contains(eventData->getChannelData().id)) {
					ModalCollector::modalInteractionBuffersMap[eventData->getChannelData().id]->send(eventData->getInteractionData());
					ModalCollector::modalInteractionEventsMap.operator()(*eventData->interactionData);
				}
				break;
			}
			case InteractionType::Application_Command_Autocomplete: {
				eventData->responseType		= InputEventResponseType::Unset;
				*eventData->interactionData = value;
				UniquePtr<OnAutoCompleteEntryData> autocompleteEntryData{ makeUnique<OnAutoCompleteEntryData>(parser, dataToParse) };
				autocompleteEntryData->value = *eventData;
				discordCoreClient->getEventManager().onAutoCompleteEntryEvent(*autocompleteEntryData);
				break;
			}
			case InteractionType::Ping: {
				break;
			}
		}
	}

	OnInviteCreationData::OnInviteCreationData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	OnInviteDeletionData::OnInviteDeletionData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	OnMessageCreationData::OnMessageCreationData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
		for (auto& [key, valueNew]: MessageCollector::objectsBuffersMap) {
			valueNew->send(value);
		}
	}

	OnMessageUpdateData::OnMessageUpdateData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
		for (auto& [key, valueNew]: MessageCollector::objectsBuffersMap) {
			valueNew->send(value);
		}
	}

	OnMessageDeletionData::OnMessageDeletionData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	OnMessageDeleteBulkData::OnMessageDeleteBulkData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	OnReactionAddData::OnReactionAddData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
		for (auto& [key, valueNew]: ReactionCollector::objectsBuffersMap) {
			valueNew->send(value);
		}
	}

	OnReactionRemoveData::OnReactionRemoveData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	OnReactionRemoveAllData::OnReactionRemoveAllData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	OnReactionRemoveEmojiData::OnReactionRemoveEmojiData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	OnPresenceUpdateData::OnPresenceUpdateData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	OnStageInstanceCreationData::OnStageInstanceCreationData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	OnStageInstanceUpdateData::OnStageInstanceUpdateData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	OnStageInstanceDeletionData::OnStageInstanceDeletionData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	OnTypingStartData::OnTypingStartData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	OnUserUpdateData::OnUserUpdateData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<UpdatedEventData*>(this), dataToParse);
		oldValue = Users::getCachedUser({ value.id });
		if (Users::doWeCacheUsers()) {
			Users::insertUser(static_cast<UserCacheData>(value));
		}
	}

	OnVoiceStateUpdateData::OnVoiceStateUpdateData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse, DiscordCoreInternal::WebSocketClient* sslShard) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
		if (sslShard->areWeCollectingData.load(std::memory_order_acquire) && !sslShard->stateUpdateCollected && !sslShard->serverUpdateCollected &&
			value.userId == sslShard->userId) {
			sslShard->voiceConnectionData			= DiscordCoreInternal::VoiceConnectionData{};
			sslShard->voiceConnectionData.sessionId = value.sessionId;
			sslShard->stateUpdateCollected			= true;
		} else if (sslShard->areWeCollectingData.load(std::memory_order_acquire) && !sslShard->stateUpdateCollected && value.userId == sslShard->userId) {
			sslShard->voiceConnectionData.sessionId = value.sessionId;
			if (sslShard->voiceConnectionDataBufferMap.contains(value.guildId.operator const uint64_t&())) {
				sslShard->voiceConnectionDataBufferMap[value.guildId.operator const uint64_t&()]->send(std::move(sslShard->voiceConnectionData));
			}
			sslShard->areWeCollectingData.store(false, std::memory_order_release);
			sslShard->serverUpdateCollected = false;
			sslShard->stateUpdateCollected	= false;
		}
		VoiceStateDataLight voiceDataNew{};
		voiceDataNew.channelId = value.channelId;
		voiceDataNew.guildId   = value.guildId;
		voiceDataNew.userId	   = value.userId;
		GuildMembers::insertVoiceState(std::move(voiceDataNew));
	}

	OnWebhookUpdateData::OnWebhookUpdateData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	OnAutoCompleteEntryData::OnAutoCompleteEntryData(Jsonifier::JsonifierCore& parserNew, std::string_view dataToParse) {
		parserNew.parseJson<true, true>(*static_cast<EventData*>(this), dataToParse);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onApplicationCommandsPermissionsUpdate(
		DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnApplicationCommandPermissionsUpdateData> handler) {
		return onApplicationCommandPermissionsUpdateEvent.add(std::move(handler));
	}

	void EventManager::onApplicationCommandsPermissionsUpdate(DiscordCoreInternal::EventDelegateToken& token) {
		return onApplicationCommandPermissionsUpdateEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onAutoModerationRuleCreation(
		DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnAutoModerationRuleCreationData> handler) {
		return onAutoModerationRuleCreationEvent.add(std::move(handler));
	}

	void EventManager::onAutoModerationRuleCreation(DiscordCoreInternal::EventDelegateToken& token) {
		return onAutoModerationRuleCreationEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onAutoModerationRuleUpdate(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnAutoModerationRuleUpdateData> handler) {
		return onAutoModerationRuleUpdateEvent.add(std::move(handler));
	}

	void EventManager::onAutoModerationRuleUpdate(DiscordCoreInternal::EventDelegateToken& token) {
		return onAutoModerationRuleUpdateEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onAutoModerationRuleDeletion(
		DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnAutoModerationRuleDeletionData> handler) {
		return onAutoModerationRuleDeletionEvent.add(std::move(handler));
	}

	void EventManager::onAutoModerationRuleDeletion(DiscordCoreInternal::EventDelegateToken& token) {
		return onAutoModerationRuleDeletionEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onAutoModerationActionExecution(
		DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnAutoModerationActionExecutionData> handler) {
		return onAutoModerationActionExecutionEvent.add(std::move(handler));
	}

	void EventManager::onAutoModerationActionExecution(DiscordCoreInternal::EventDelegateToken& token) {
		return onAutoModerationActionExecutionEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onAutoCompleteEntry(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnAutoCompleteEntryData> handler) {
		return onAutoCompleteEntryEvent.add(std::move(handler));
	}

	void EventManager::onAutoCompleteEntry(DiscordCoreInternal::EventDelegateToken& token) {
		return onInputEventCreationEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onInputEventCreation(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnInputEventCreationData> handler) {
		return onInputEventCreationEvent.add(std::move(handler));
	}

	void EventManager::onInputEventCreation(DiscordCoreInternal::EventDelegateToken& token) {
		return onInputEventCreationEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onChannelCreation(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnChannelCreationData> handler) {
		return onChannelCreationEvent.add(std::move(handler));
	}

	void EventManager::onChannelCreation(DiscordCoreInternal::EventDelegateToken& token) {
		onChannelCreationEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onChannelUpdate(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnChannelUpdateData> handler) {
		return onChannelUpdateEvent.add(std::move(handler));
	}

	void EventManager::onChannelUpdate(DiscordCoreInternal::EventDelegateToken& token) {
		onChannelUpdateEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onChannelDeletion(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnChannelDeletionData> handler) {
		return onChannelDeletionEvent.add(std::move(handler));
	}

	void EventManager::onChannelDeletion(DiscordCoreInternal::EventDelegateToken& token) {
		onChannelDeletionEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onChannelPinsUpdate(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnChannelPinsUpdateData> handler) {
		return onChannelPinsUpdateEvent.add(std::move(handler));
	}

	void EventManager::onChannelPinsUpdate(DiscordCoreInternal::EventDelegateToken& token) {
		return onChannelPinsUpdateEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onThreadCreation(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnThreadCreationData> handler) {
		return onThreadCreationEvent.add(std::move(handler));
	}

	void EventManager::onThreadCreation(DiscordCoreInternal::EventDelegateToken& token) {
		return onThreadCreationEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onThreadUpdate(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnThreadUpdateData> handler) {
		return onThreadUpdateEvent.add(std::move(handler));
	}

	void EventManager::onThreadUpdate(DiscordCoreInternal::EventDelegateToken& token) {
		return onThreadUpdateEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onThreadDeletion(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnThreadDeletionData> handler) {
		return onThreadDeletionEvent.add(std::move(handler));
	}

	void EventManager::onThreadDeletion(DiscordCoreInternal::EventDelegateToken& token) {
		return onThreadDeletionEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onThreadListSync(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnThreadListSyncData> handler) {
		return onThreadListSyncEvent.add(std::move(handler));
	}

	void EventManager::onThreadListSync(DiscordCoreInternal::EventDelegateToken& token) {
		return onThreadListSyncEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onThreadMemberUpdate(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnThreadMemberUpdateData> handler) {
		return onThreadMemberUpdateEvent.add(std::move(handler));
	}

	void EventManager::onThreadMemberUpdate(DiscordCoreInternal::EventDelegateToken& token) {
		return onThreadMemberUpdateEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onThreadMembersUpdate(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnThreadMembersUpdateData> handler) {
		return onThreadMembersUpdateEvent.add(std::move(handler));
	}

	void EventManager::onThreadMembersUpdate(DiscordCoreInternal::EventDelegateToken& token) {
		return onThreadMembersUpdateEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onGuildCreation(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnGuildCreationData> handler) {
		return onGuildCreationEvent.add(std::move(handler));
	}

	void EventManager::onGuildCreation(DiscordCoreInternal::EventDelegateToken& token) {
		onGuildCreationEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onGuildUpdate(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnGuildUpdateData> handler) {
		return onGuildUpdateEvent.add(std::move(handler));
	}

	void EventManager::onGuildUpdate(DiscordCoreInternal::EventDelegateToken& token) {
		onGuildUpdateEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onGuildDeletion(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnGuildDeletionData> handler) {
		return onGuildDeletionEvent.add(std::move(handler));
	}

	void EventManager::onGuildDeletion(DiscordCoreInternal::EventDelegateToken& token) {
		onGuildDeletionEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onGuildBanAdd(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnGuildBanAddData> handler) {
		return onGuildBanAddEvent.add(std::move(handler));
	}

	void EventManager::onGuildBanAdd(DiscordCoreInternal::EventDelegateToken& token) {
		onGuildBanAddEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onGuildBanRemove(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnGuildBanRemoveData> handler) {
		return onGuildBanRemoveEvent.add(std::move(handler));
	}

	void EventManager::onGuildBanRemove(DiscordCoreInternal::EventDelegateToken& token) {
		onGuildBanRemoveEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onGuildEmojisUpdate(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnGuildEmojisUpdateData> handler) {
		return onGuildEmojisUpdateEvent.add(std::move(handler));
	}

	void EventManager::onGuildEmojisUpdate(DiscordCoreInternal::EventDelegateToken& token) {
		onGuildEmojisUpdateEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onGuildStickersUpdate(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnGuildStickersUpdateData> handler) {
		return onGuildStickersUpdateEvent.add(std::move(handler));
	}

	void EventManager::onGuildStickersUpdate(DiscordCoreInternal::EventDelegateToken& token) {
		onGuildStickersUpdateEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onGuildIntegrationsUpdate(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnGuildIntegrationsUpdateData> handler) {
		return onGuildIntegrationsUpdateEvent.add(std::move(handler));
	}

	void EventManager::onGuildIntegrationsUpdate(DiscordCoreInternal::EventDelegateToken& token) {
		onGuildIntegrationsUpdateEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onGuildMembersChunk(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnGuildMembersChunkData> handler) {
		return onGuildMembersChunkEvent.add(std::move(handler));
	}

	void EventManager::onGuildMembersChunk(DiscordCoreInternal::EventDelegateToken& token) {
		onGuildMembersChunkEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onGuildMemberAdd(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnGuildMemberAddData> handler) {
		return onGuildMemberAddEvent.add(std::move(handler));
	}

	void EventManager::onGuildMemberAdd(DiscordCoreInternal::EventDelegateToken& token) {
		onGuildMemberAddEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onGuildMemberRemove(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnGuildMemberRemoveData> handler) {
		return onGuildMemberRemoveEvent.add(std::move(handler));
	}

	void EventManager::onGuildMemberRemove(DiscordCoreInternal::EventDelegateToken& token) {
		onGuildMemberRemoveEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onGuildMemberUpdate(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnGuildMemberUpdateData> handler) {
		return onGuildMemberUpdateEvent.add(std::move(handler));
	}

	void EventManager::onGuildMemberUpdate(DiscordCoreInternal::EventDelegateToken& token) {
		onGuildMemberUpdateEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onRoleCreation(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnRoleCreationData> handler) {
		return onRoleCreationEvent.add(std::move(handler));
	}

	void EventManager::onRoleCreation(DiscordCoreInternal::EventDelegateToken& token) {
		onRoleCreationEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onRoleUpdate(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnRoleUpdateData> handler) {
		return onRoleUpdateEvent.add(std::move(handler));
	}

	void EventManager::onRoleUpdate(DiscordCoreInternal::EventDelegateToken& token) {
		onRoleUpdateEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onRoleDeletion(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnRoleDeletionData> handler) {
		return onRoleDeletionEvent.add(std::move(handler));
	}

	void EventManager::onRoleDeletion(DiscordCoreInternal::EventDelegateToken& token) {
		onRoleDeletionEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onGuildScheduledEventCreation(
		DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnGuildScheduledEventCreationData> handler) {
		return onGuildScheduledEventCreationEvent.add(std::move(handler));
	}

	void EventManager::onGuildScheduledEventCreation(DiscordCoreInternal::EventDelegateToken& token) {
		onGuildScheduledEventCreationEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onGuildScheduledEventUpdate(
		DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnGuildScheduledEventUpdateData> handler) {
		return onGuildScheduledEventUpdateEvent.add(std::move(handler));
	}

	void EventManager::onGuildScheduledEventUpdate(DiscordCoreInternal::EventDelegateToken& token) {
		onGuildScheduledEventUpdateEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onGuildScheduledEventDeletion(
		DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnGuildScheduledEventDeletionData> handler) {
		return onGuildScheduledEventDeletionEvent.add(std::move(handler));
	}

	void EventManager::onGuildScheduledEventDeletion(DiscordCoreInternal::EventDelegateToken& token) {
		onGuildScheduledEventDeletionEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onGuildScheduledEventUserAdd(
		DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnGuildScheduledEventUserAddData> handler) {
		return onGuildScheduledEventUserAddEvent.add(std::move(handler));
	}

	void EventManager::onGuildScheduledEventUserAdd(DiscordCoreInternal::EventDelegateToken& token) {
		onGuildScheduledEventUserAddEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onGuildScheduledEventUserRemove(
		DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnGuildScheduledEventUserRemoveData> handler) {
		return onGuildScheduledEventUserRemoveEvent.add(std::move(handler));
	}

	void EventManager::onGuildScheduledEventUserRemove(DiscordCoreInternal::EventDelegateToken& token) {
		onGuildScheduledEventUserRemoveEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onIntegrationCreation(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnIntegrationCreationData> handler) {
		return onIntegrationCreationEvent.add(std::move(handler));
	}

	void EventManager::onIntegrationCreation(DiscordCoreInternal::EventDelegateToken& token) {
		onIntegrationCreationEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onIntegrationUpdate(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnIntegrationUpdateData> handler) {
		return onIntegrationUpdateEvent.add(std::move(handler));
	}

	void EventManager::onIntegrationUpdate(DiscordCoreInternal::EventDelegateToken& token) {
		onIntegrationUpdateEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onIntegrationDeletion(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnIntegrationDeletionData> handler) {
		return onIntegrationDeletionEvent.add(std::move(handler));
	}

	void EventManager::onIntegrationDeletion(DiscordCoreInternal::EventDelegateToken& token) {
		onIntegrationDeletionEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onInteractionCreation(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnInteractionCreationData> handler) {
		return onInteractionCreationEvent.add(std::move(handler));
	}

	void EventManager::onInteractionCreation(DiscordCoreInternal::EventDelegateToken& token) {
		onInteractionCreationEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onInviteCreation(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnInviteCreationData> handler) {
		return onInviteCreationEvent.add(std::move(handler));
	}

	void EventManager::onInviteCreation(DiscordCoreInternal::EventDelegateToken& token) {
		onInviteCreationEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onInviteDeletion(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnInviteDeletionData> handler) {
		return onInviteDeletionEvent.add(std::move(handler));
	}

	void EventManager::onInviteDeletion(DiscordCoreInternal::EventDelegateToken& token) {
		onInviteDeletionEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onMessageCreation(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnMessageCreationData> handler) {
		return onMessageCreationEvent.add(std::move(handler));
	}

	void EventManager::onMessageCreation(DiscordCoreInternal::EventDelegateToken& token) {
		onMessageCreationEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onMessageUpdate(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnMessageUpdateData> handler) {
		return onMessageUpdateEvent.add(std::move(handler));
	}

	void EventManager::onMessageUpdate(DiscordCoreInternal::EventDelegateToken& token) {
		onMessageUpdateEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onMessageDeletion(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnMessageDeletionData> handler) {
		return onMessageDeletionEvent.add(std::move(handler));
	}

	void EventManager::onMessageDeletion(DiscordCoreInternal::EventDelegateToken& token) {
		onMessageDeletionEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onMessageDeleteBulk(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnMessageDeleteBulkData> handler) {
		return onMessageDeleteBulkEvent.add(std::move(handler));
	}

	void EventManager::onMessageDeleteBulk(DiscordCoreInternal::EventDelegateToken& token) {
		onMessageDeleteBulkEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onReactionAdd(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnReactionAddData> handler) {
		return onReactionAddEvent.add(std::move(handler));
	}

	void EventManager::onReactionAdd(DiscordCoreInternal::EventDelegateToken& token) {
		onReactionAddEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onReactionRemove(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnReactionRemoveData> handler) {
		return onReactionRemoveEvent.add(std::move(handler));
	}

	void EventManager::onReactionRemove(DiscordCoreInternal::EventDelegateToken& token) {
		onReactionRemoveEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onReactionRemoveAll(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnReactionRemoveAllData> handler) {
		return onReactionRemoveAllEvent.add(std::move(handler));
	}

	void EventManager::onReactionRemoveAll(DiscordCoreInternal::EventDelegateToken& token) {
		onReactionRemoveAllEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onReactionRemoveEmoji(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnReactionRemoveEmojiData> handler) {
		return onReactionRemoveEmojiEvent.add(std::move(handler));
	}

	void EventManager::onReactionRemoveEmoji(DiscordCoreInternal::EventDelegateToken& token) {
		onReactionRemoveEmojiEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onPresenceUpdate(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnPresenceUpdateData> handler) {
		return onPresenceUpdateEvent.add(std::move(handler));
	}

	void EventManager::onPresenceUpdate(DiscordCoreInternal::EventDelegateToken& token) {
		onPresenceUpdateEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onStageInstanceCreation(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnStageInstanceCreationData> handler) {
		return onStageInstanceCreationEvent.add(std::move(handler));
	}

	void EventManager::onStageInstanceCreation(DiscordCoreInternal::EventDelegateToken& token) {
		onStageInstanceCreationEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onStageInstanceUpdate(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnStageInstanceUpdateData> handler) {
		return onStageInstanceUpdateEvent.add(std::move(handler));
	}

	void EventManager::onStageInstanceUpdate(DiscordCoreInternal::EventDelegateToken& token) {
		onStageInstanceUpdateEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onStageInstanceDeletion(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnStageInstanceDeletionData> handler) {
		return onStageInstanceDeletionEvent.add(std::move(handler));
	}

	void EventManager::onStageInstanceDeletion(DiscordCoreInternal::EventDelegateToken& token) {
		onStageInstanceDeletionEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onTypingStart(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnTypingStartData> handler) {
		return onTypingStartEvent.add(std::move(handler));
	}

	void EventManager::onTypingStart(DiscordCoreInternal::EventDelegateToken& token) {
		onTypingStartEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onUserUpdate(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnUserUpdateData> handler) {
		return onUserUpdateEvent.add(std::move(handler));
	}

	void EventManager::onUserUpdate(DiscordCoreInternal::EventDelegateToken& token) {
		onUserUpdateEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onVoiceStateUpdate(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnVoiceStateUpdateData> handler) {
		return onVoiceStateUpdateEvent.add(std::move(handler));
	}

	void EventManager::onVoiceStateUpdate(DiscordCoreInternal::EventDelegateToken& token) {
		onVoiceStateUpdateEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onVoiceServerUpdate(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnVoiceServerUpdateData> handler) {
		return onVoiceServerUpdateEvent.add(std::move(handler));
	}

	void EventManager::onVoiceServerUpdate(DiscordCoreInternal::EventDelegateToken& token) {
		onVoiceServerUpdateEvent.erase(token);
	}

	DiscordCoreInternal::EventDelegateToken EventManager::onWebhookUpdate(DiscordCoreInternal::EventDelegate<CoRoutine<void>, OnWebhookUpdateData> handler) {
		return onWebhookUpdateEvent.add(std::move(handler));
	}

	void EventManager::onWebhookUpdate(DiscordCoreInternal::EventDelegateToken& token) {
		onWebhookUpdateEvent.erase(token);
	}


};// namespace DiscordCoreAPI
