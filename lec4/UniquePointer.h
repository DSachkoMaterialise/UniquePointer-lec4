#pragma once
#include <cstddef>

template <class T>
class UniquePointer
  {
	private:
		T* m_ptr = nullptr;
		void freePtr() 
			{
			if (m_ptr)
				delete m_ptr;
			}
	public:
		UniquePointer() noexcept = default;
		explicit UniquePointer(T* ptr) noexcept : m_ptr(ptr)
			{}
		~UniquePointer()
			{
			freePtr();
			}
		UniquePointer(const UniquePointer&) = delete;
		UniquePointer& operator=(const UniquePointer&) = delete;
		UniquePointer(UniquePointer&& pointer)  noexcept : m_ptr(pointer.m_ptr)
			{
			pointer.m_ptr = nullptr;
			}
		UniquePointer& operator=(UniquePointer&& pointer)
			{
			freePtr();
			m_ptr = pointer.m_ptr;
			pointer.m_ptr = nullptr;
			return *this;
			}
		void reset(T* ptr)
			{
			freePtr();
			m_ptr = ptr;
			}
		UniquePointer& operator=(nullptr_t)
			{
			freePtr();
			return *this;
			}
		bool operator==(const UniquePointer& pointer) const noexcept
			{
			return m_ptr == pointer.m_ptr;
			}
		bool operator==(nullptr_t) const noexcept
			{
			return m_ptr == nullptr;
			}
		T& operator*() noexcept
			{
			return *m_ptr;
			}
		const T& operator*() const noexcept
			{
			return *m_ptr;
			}
		T* operator->() noexcept
			{
			return m_ptr;
			}
		const T* operator->() const noexcept
			{
			return m_ptr;
			}
		const T* get() const noexcept
			{
			return m_ptr;
			}
		T* get() noexcept
			{
			return m_ptr;
			}
		T* release() noexcept
			{
			auto ptr = m_ptr;
			m_ptr = nullptr;
			return ptr;
			}
		operator bool() const noexcept
			{
			return m_ptr;
			}
	};

