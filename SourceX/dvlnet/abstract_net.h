#pragma once

#include <vector>
#include <memory>

#include "devilution.h"

namespace dvlnet {
	typedef std::vector<unsigned char> buffer_t;
	typedef void(__stdcall *snet_event_func)(struct _SNETEVENT*);
	typedef unsigned long provider_t;
	class dvlnet_exception : public std::exception {};

	class abstract_net {
	public:
		virtual int create(std::string addrstr, std::string passwd) = 0;
		virtual int join(std::string addrstr, std::string passwd) = 0;
		virtual bool SNetReceiveMessage(int* sender, char** data,
		                                int* size) = 0;
		virtual bool SNetSendMessage(int dest, void* data,
		                             unsigned int size) = 0;
		virtual bool SNetReceiveTurns(char** data, unsigned int* size,
		                              DWORD* status) = 0;
		virtual bool SNetSendTurn(char* data, unsigned int size) = 0;
		virtual int SNetGetProviderCaps(struct _SNETCAPS* caps) = 0;
		virtual void* SNetRegisterEventHandler(event_type evtype,
		                                       snet_event_func func) = 0;
		virtual void* SNetUnregisterEventHandler(event_type evtype,
		                                         snet_event_func func) = 0;
		virtual bool SNetLeaveGame(int type) = 0;
		virtual void setup_gameinfo(buffer_t info) = 0;
		virtual ~abstract_net();

		static std::unique_ptr<abstract_net> make_net(provider_t provider);
	};
}
