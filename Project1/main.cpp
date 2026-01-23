#include"Application.h"

int main() {
	auto& app = Application::Instance(); //singleton instance of facade
	if (!app.Init()) {
		return -1;
	}

	app.Run();
	app.ShutDown();
	return 0;
}