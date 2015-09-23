// Copyright (C) 2015 Jérôme Leclercq
// This file is part of the "Nazara Engine - Renderer module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_RENDERBUFFER_HPP
#define NAZARA_RENDERBUFFER_HPP

#include <Nazara/Prerequesites.hpp>
#include <Nazara/Core/ObjectLibrary.hpp>
#include <Nazara/Core/ObjectRef.hpp>
#include <Nazara/Core/RefCounted.hpp>
#include <Nazara/Core/Signal.hpp>
#include <Nazara/Renderer/Config.hpp>
#include <Nazara/Utility/Enums.hpp>

class NzRenderBuffer;

using NzRenderBufferConstRef = NzObjectRef<const NzRenderBuffer>;
using NzRenderBufferLibrary = NzObjectLibrary<NzRenderBuffer>;
using NzRenderBufferRef = NzObjectRef<NzRenderBuffer>;

class NAZARA_RENDERER_API NzRenderBuffer : public NzRefCounted
{
	friend NzRenderBufferLibrary;
	friend class NzRenderer;

	public:
		NzRenderBuffer();
        NzRenderBuffer(const NzRenderBuffer&) = delete;
        NzRenderBuffer(NzRenderBuffer&&) = delete;
		~NzRenderBuffer();

		bool Create(nzPixelFormat format, unsigned int width, unsigned int height);
		void Destroy();

		unsigned int GetHeight() const;
		nzPixelFormat GetFormat() const;
		unsigned int GetWidth() const;

		// Fonctions OpenGL
		unsigned int GetOpenGLID() const;

		bool IsValid() const;

        NzRenderBuffer& operator=(const NzRenderBuffer&) = delete;
        NzRenderBuffer& operator=(NzRenderBuffer&&) = delete;

		static bool IsSupported();
		template<typename... Args> static NzRenderBufferRef New(Args&&... args);

		// Signals:
		NazaraSignal(OnRenderBufferDestroy, const NzRenderBuffer* /*renderBuffer*/);
		NazaraSignal(OnRenderBufferRelease, const NzRenderBuffer* /*renderBuffer*/);

	private:
		static bool Initialize();
		static void Uninitialize();

		nzPixelFormat m_pixelFormat;
		unsigned int m_height;
		unsigned int m_id;
		unsigned int m_width;

		static NzRenderBufferLibrary::LibraryMap s_library;
};

#include <Nazara/Renderer/RenderBuffer.inl>

#endif // NAZARA_RENDERBUFFER_HPP
