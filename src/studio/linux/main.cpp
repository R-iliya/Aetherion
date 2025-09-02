#include "editor/studio_app.h"
#include "core/os.h"

int main(int argc, char* argv[])
{
	Aetherion::os::setCommandLine(argc, argv);
	auto* app = Aetherion::StudioApp::create();
	app->run();
	int exit_code = app->getExitCode();
	Aetherion::StudioApp::destroy(*app);
	return exit_code;
}
