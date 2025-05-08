#include"Window.h"
#include <vector>

namespace eogl {

	class WindowManager{
		std::vector<Window*>windows;
		GLFWwindow* offscreen_context;
		uint localVao;

		public:
		WindowManager();
		~WindowManager();
		void addWindow(Window* window);
		void removeWindow(Window* window);
		int getMonitorCount();
		Monitor getIthMonitor(int i);
		Window* getWindow(GLFWwindow* window);
		inline GLFWwindow* getOffscreenContext() { return offscreen_context; }
		void setBackgroundContextActive();
		void setNoContext();
	};
	extern WindowManager* windowManager;
}