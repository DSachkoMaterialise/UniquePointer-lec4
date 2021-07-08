#pragma once

template<class T>
class SharedPointer
  {
	private:
		class SharedData
			{
			private:
				T* m_data = nullptr;
				size_t m_counter = 1;
			public:
				SharedData() noexcept = default;
				explicit SharedData(T* data) noexcept : m_data(data)
					{}
				void inc() noexcept
					{
					++m_counter;
					}
				bool dec()
					{
					if (--m_counter == 0)
						{
						delete m_data;
						m_data = nullptr;
						}
					return m_counter;
					}
				T& get() const noexcept
					{
					return *m_data;
					}
				size_t getCounter() const noexcept
					{
					return m_counter;
					}
			} *m_ptr = nullptr;
		
		void inc()
			{
			if (m_ptr)
				m_ptr->inc();
			}
		void dec()
			{
			if (m_ptr && !m_ptr->dec())
				delete m_ptr;
			}
	public:
		SharedPointer() noexcept = default;
		~SharedPointer()
			{
			dec();
			}

		explicit SharedPointer(T* ptr) noexcept : m_ptr(new SharedData(ptr))
			{}

		SharedPointer(SharedPointer& sp) noexcept : m_ptr(sp.m_ptr)
			{
			inc();
			}

		SharedPointer(SharedPointer&& sp) noexcept : m_ptr(sp.m_ptr)
			{
			sp.m_ptr = nullptr;
			}

		SharedPointer& operator=(SharedPointer& sp) noexcept
			{
			dec();
			m_ptr = sp.m_ptr;
			return *this;
			}

		SharedPointer& operator=(SharedPointer&& sp) noexcept
			{
			m_ptr = sp.m_ptr;
			sp.m_ptr = nullptr;
			return *this;
			}

		SharedPointer& operator=(nullptr_t) noexcept
			{
			dec();
			m_ptr = nullptr;
			}

		T& operator*() const noexcept
			{
			return m_ptr->get();
			}

		T* operator->() const noexcept
			{
			return &m_ptr->get();
			}

		T* get() const noexcept
			{
			return &m_ptr->get();
			}

		operator bool() const noexcept
			{
			return m_ptr;
			}

		bool operator==(const SharedPointer& pointer) const noexcept
			{
			return m_ptr == pointer.m_ptr;
			}
		
		bool operator==(nullptr_t) const noexcept
			{
			return m_ptr == nullptr;
			}

		size_t use_count() const noexcept
			{
			return m_ptr ? m_ptr->getCounter() : 0;
			}
	};

