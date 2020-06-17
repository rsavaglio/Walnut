#pragma once

#include "Walnut/Core.h"


namespace Walnut {

	// Events in walnut are blocking
	// Future we might want to implement an event buffer

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WondowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory // For filtering events
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput       = BIT(1),
		EventCategoryKeyboard    = BIT(2),
		EventCategoryMouse       = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() {return EventType::##type;} \
								virtual EventType GetEventType() const override {return GetStaticType();} \
								virtual const char* GetName() const override {return #type;}

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category;}



	class WALNUT_API Event
	{
		friend class EventDispatcher;

	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); } // Debug only

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

		bool Handled = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	
	public:
		// Created with an event
		EventDispatcher(Event& event) 
			: m_Event(event) {} 

		// Takes in a function that is implement elsewhere
		template<typename T>
		bool Dispatch(EventFn<T> func) 
		{
			// If the functions event argument matches the saved event
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				// Call the function
				m_Event.Handled = func(*(T*)&m_Event);
				return true;
			}
			// If they don't match, do nothing
			return false;
		}
	private:
		Event& m_Event; 
	};

	inline std::ostream& operator <<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

}