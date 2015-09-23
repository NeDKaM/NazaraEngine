// Copyright (C) 2015 Jérôme Leclercq
// This file is part of the "Nazara Engine - Core module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_CALLONEXIT_HPP
#define NAZARA_CALLONEXIT_HPP

#include <Nazara/Prerequesites.hpp>
#include <functional>

class NzCallOnExit
{
	using Func = std::function<void()>;

	public:
		NzCallOnExit(Func func = nullptr);
        NzCallOnExit(const NzCallOnExit&) = delete;
        NzCallOnExit(NzCallOnExit&&) = delete;
		~NzCallOnExit();

		void CallAndReset(Func func = nullptr);
		void Reset(Func func = nullptr);

        NzCallOnExit& operator=(const NzCallOnExit&) = delete;
        NzCallOnExit& operator=(NzCallOnExit&&) = default;

	private:
		Func m_func;
};

#include <Nazara/Core/CallOnExit.inl>

#endif // NAZARA_CALLONEXIT_HPP
