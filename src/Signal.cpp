/*
 * Signal.cpp
 */

#include "StdAfx.h"

namespace fbi
{
	Signal::Signal()
	{
	}

	Signal::~Signal()
	{
	}

	void _OnSignal(int s)
	{
		switch(s)
		{
		case SIGHUP:
			break;
		case SIGINT:
		case SIGTERM:
		case SIGABRT:
			// majd aminek le kell futnia
			main_shutdown_manager.shutdown();
			break;
		}

		signal(s, _OnSignal);
	}

	void segfault_handler(int c)
	{
		Log.Warning("Crash", "Segfault handler elindult...");

		// majd ami lefut

		Log.Notice("Crash", "Program leáll...");
		abort();
	}

	void _HookSignals()
	{
		Log.Notice("Signal", "Hooking signals...");
		signal(SIGINT,  _OnSignal);
		signal(SIGTERM, _OnSignal);
		signal(SIGABRT, _OnSignal);
		signal(SIGHUP,  _OnSignal);
		signal(SIGUSR1, _OnSignal);

		// crash handler
		signal(SIGSEGV, segfault_handler);
		signal(SIGFPE,  segfault_handler);
		signal(SIGILL,  segfault_handler);
		signal(SIGBUS,  segfault_handler);
	}

	void _UnhookSignals()
	{
		Log.Notice("Signal", "Unhooking signals...");
		signal(SIGINT,  0);
		signal(SIGTERM, 0);
		signal(SIGABRT, 0);
		signal(SIGHUP,  0);
	}

	void Signal::HookSignals()
	{
		_HookSignals();
	}

	void Signal::UnhookSignals()
	{
		_UnhookSignals();
	}
}
