#pragma once

#include "property_grid.h"
#include "studio_app.h"

namespace Aetherion {

struct SignalEditor : StudioApp::IPlugin, PropertyGrid::IPlugin {
};

SignalEditor* createSignalEditor(StudioApp& app);

}
