/*
BStone: A Source port of
Blake Stone: Aliens of Gold and Blake Stone: Planet Strike

Copyright (c) 1992-2013 Apogee Entertainment, LLC
Copyright (c) 2013-2021 Boris I. Bendovsky (bibendovsky@hotmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the
Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/


#include "bstone_atomic_flag.h"


namespace bstone
{


AtomicFlag::AtomicFlag() noexcept = default;

AtomicFlag::AtomicFlag(
	bool value) noexcept
	:
	flag_{value}
{
}

AtomicFlag::AtomicFlag(
	const AtomicFlag& rhs)
	:
	flag_{rhs}
{
}

void AtomicFlag::operator=(
	bool value) noexcept
{
	set(value);
}

bool AtomicFlag::is_set() const noexcept
{
	return flag_.load(std::memory_order_acquire);
}

void AtomicFlag::set(
	bool value) noexcept
{
	flag_.store(value, std::memory_order_release);
}

AtomicFlag::operator bool() const noexcept
{
	return is_set();
}


} // bstone
