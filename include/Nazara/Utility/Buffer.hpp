// Copyright (C) 2015 Jérôme Leclercq
// This file is part of the "Nazara Engine - Utility module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_BUFFER_HPP
#define NAZARA_BUFFER_HPP

#include <Nazara/Prerequesites.hpp>
#include <Nazara/Core/ObjectRef.hpp>
#include <Nazara/Core/RefCounted.hpp>
#include <Nazara/Core/Signal.hpp>
#include <Nazara/Utility/Config.hpp>
#include <Nazara/Utility/Enums.hpp>

class NzBuffer;

using NzBufferConstRef = NzObjectRef<const NzBuffer>;
using NzBufferRef = NzObjectRef<NzBuffer>;

class NzAbstractBuffer;

class NAZARA_UTILITY_API NzBuffer : public NzRefCounted
{
	friend class NzUtility;

	public:
		using BufferFactory = NzAbstractBuffer* (*)(NzBuffer* parent, nzBufferType type);

		NzBuffer(nzBufferType type);
		NzBuffer(nzBufferType type, unsigned int size, nzUInt32 storage = nzDataStorage_Software, nzBufferUsage usage = nzBufferUsage_Static);
        NzBuffer(const NzBuffer&) = delete;
        NzBuffer(NzBuffer&&) = delete;
		~NzBuffer();

		bool CopyContent(const NzBuffer& buffer);

		bool Create(unsigned int size, nzUInt32 storage = nzDataStorage_Software, nzBufferUsage usage = nzBufferUsage_Static);
		void Destroy();

		bool Fill(const void* data, unsigned int offset, unsigned int size, bool forceDiscard = false);

		NzAbstractBuffer* GetImpl() const;
		unsigned int GetSize() const;
		nzUInt32 GetStorage() const;
		nzBufferType GetType() const;
		nzBufferUsage GetUsage() const;

		bool IsHardware() const;
		bool IsValid() const;

		void* Map(nzBufferAccess access, unsigned int offset = 0, unsigned int size = 0);
		void* Map(nzBufferAccess access, unsigned int offset = 0, unsigned int size = 0) const;

		bool SetStorage(nzUInt32 storage);

		void Unmap() const;

        NzBuffer& operator=(const NzBuffer&) = delete;
        NzBuffer& operator=(NzBuffer&&) = delete;

		static bool IsStorageSupported(nzUInt32 storage);
		template<typename... Args> static NzBufferRef New(Args&&... args);
		static void SetBufferFactory(nzUInt32 storage, BufferFactory func);

		// Signals:
		NazaraSignal(OnBufferDestroy, const NzBuffer* /*buffer*/);
		NazaraSignal(OnBufferRelease, const NzBuffer* /*buffer*/);

	private:
		static bool Initialize();
		static void Uninitialize();

		nzBufferType m_type;
		nzBufferUsage m_usage;
		nzUInt32 m_storage;
		NzAbstractBuffer* m_impl;
		unsigned int m_size;

		static BufferFactory s_bufferFactories[nzDataStorage_Max+1];
};

#include <Nazara/Utility/Buffer.inl>

#endif // NAZARA_BUFFER_HPP
