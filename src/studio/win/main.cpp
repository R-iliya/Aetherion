#include "core/os.h"
#include "core/debug.h"
#include "core/default_allocator.h"
#include "core/win/simple_win.h"
#include "editor/studio_app.h"

int main(int argc, char* argv[])
{
	SetProcessDPIAware();
	void* shcore = Aetherion::os::loadLibrary("shcore.dll");
	if (shcore) {
		auto setter = (decltype(&SetProcessDpiAwareness))Aetherion::os::getLibrarySymbol(shcore, "SetProcessDpiAwareness");
		if (setter) setter(PROCESS_PER_MONITOR_DPI_AWARE);
	}

	Aetherion::DefaultAllocator allocator;
	Aetherion::debug::Allocator debug_allocator(allocator);
	auto* app = Aetherion::StudioApp::create(debug_allocator);
	app->run();
	const int exit_code = app->getExitCode();
	Aetherion::StudioApp::destroy(*app);
	if(shcore) Aetherion::os::unloadLibrary(shcore);
	return exit_code;
}
