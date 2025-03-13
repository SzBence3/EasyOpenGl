#include"Window.h"
#include <vector>

namespace eogl {

	class WindowManager{
		std::vector<Window*>windows;
	public:
		WindowManager();
		~WindowManager();
		void addWindow(Window* window);
		void removeWindow(Window* window);
		int getMonitorCount();
		Monitor getIthMonitor(int i);
		Window* getWindow(GLFWwindow* window);
	};
	extern WindowManager* windowManager;
}