/*
BStone: Unofficial source port of Blake Stone: Aliens of Gold and Blake Stone: Planet Strike
Copyright (c) 2013-2024 Boris I. Bendovsky (bibendovsky@hotmail.com) and Contributors
SPDX-License-Identifier: MIT
*/

#include "bstone_game_timer.h"

#include <algorithm>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

#include "bstone_exception.h"

namespace bstone {

void GameTimer::operator=(GameTimerTicks ticks)
{
	set_ticks(ticks);
}

GameTimer::GameTimer() = default;

GameTimer::~GameTimer()
{
	stop();
}

bool GameTimer::is_started() const noexcept
{
#ifdef __EMSCRIPTEN__
	return is_started_;
#else
	return thread_.joinable();
#endif
}

void GameTimer::start(int frequency)
try {
	stop();

	if (frequency < 10 || frequency > 100)
	{
		BSTONE_THROW_STATIC_SOURCE("Frequency out of range.");
	}

	mt_is_cancellation_requested_ = false;
	set_ticks_internal(0);
#ifdef __EMSCRIPTEN__
	frequency_ = frequency;
	start_time_ms_ = emscripten_get_now();
	is_started_ = true;
#else
	thread_ = Thread{&GameTimer::thread_main, this, frequency};
#endif
}
catch (...)
{
	stop();
	StaticSourceException::fail_nested(BSTONE_MAKE_SOURCE_LOCATION());
}

void GameTimer::stop() noexcept
{
	if (!is_started())
	{
		return;
	}

#ifdef __EMSCRIPTEN__
	is_started_ = false;
#else
	mt_is_cancellation_requested_ = true;
	thread_.join();
#endif
}

GameTimerTicks GameTimer::get_ticks() const
{
	ensure_is_started();
#ifdef __EMSCRIPTEN__
	const auto now_ms = emscripten_get_now();
	const auto elapsed_ms = now_ms - start_time_ms_;
	const auto elapsed_ticks = static_cast<GameTimerTicks>(
		(elapsed_ms * frequency_) / 1000.0);
	return mt_ticks_.load(std::memory_order_relaxed) + elapsed_ticks;
#else
	return mt_ticks_.load(std::memory_order_acquire);
#endif
}

void GameTimer::set_ticks(GameTimerTicks ticks)
{
	ensure_is_started();
	set_ticks_internal(ticks);
#ifdef __EMSCRIPTEN__
	start_time_ms_ = emscripten_get_now();
#endif
}

void GameTimer::subtract_ticks(GameTimerTicks ticks)
{
	ensure_is_started();
	mt_ticks_.fetch_sub(ticks, std::memory_order_relaxed);
}

GameTimer::operator GameTimerTicks() const
{
	return get_ticks();
}

void GameTimer::ensure_is_started() const
{
	if (!is_started())
	{
		BSTONE_THROW_STATIC_SOURCE("Not started.");
	}
}

void GameTimer::set_ticks_internal(GameTimerTicks ticks)
{
	mt_ticks_.store(ticks, std::memory_order_relaxed);
}

void GameTimer::increase_ticks() noexcept
{
	mt_ticks_.fetch_add(1, std::memory_order_relaxed);
}

void GameTimer::thread_main(int frequency) noexcept
{
#ifndef __EMSCRIPTEN__
	const auto base_interval = ClockTicks{1000} / frequency;
	const auto double_base_interval = base_interval * 2;
	auto interval_counter = ClockTicks{frequency};

	increase_ticks();
	auto last_time_point = Clock::now();
	std::this_thread::sleep_for(Milliseconds{base_interval});

	while (!mt_is_cancellation_requested_)
	{
		increase_ticks();

		interval_counter += frequency;
		const auto extra_interval = interval_counter / 1000;
		interval_counter %= 1000;

		const auto time_point = Clock::now();
		const auto time_diff = time_point - last_time_point;
		last_time_point = time_point;
		const auto last_interval = std::chrono::duration_cast<Milliseconds>(time_diff).count();
		const auto new_interval = double_base_interval - last_interval + extra_interval;
		const auto new_adjusted_interval = std::max(new_interval, ClockTicks{0});
		std::this_thread::sleep_for(Milliseconds{new_adjusted_interval});
	}
#else
	static_cast<void>(frequency);
#endif
}

// ==========================================================================

void operator-=(GameTimer& a, GameTimerTicks b)
{
	a.subtract_ticks(b);
}

} // namespace bstone
