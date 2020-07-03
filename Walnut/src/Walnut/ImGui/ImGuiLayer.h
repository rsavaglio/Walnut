#pragma once

#include "Walnut/Layer.h"

#include "Walnut/Events/ApplicationEvent.h"
#include "Walnut/Events/KeyEvent.h"
#include "Walnut/Events/MouseEvent.h"


namespace Walnut {

	class WALNUT_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
		
	private:
		float m_Time = 0.0f;
	};
}