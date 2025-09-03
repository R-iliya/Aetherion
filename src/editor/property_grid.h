#pragma once

#include "core/array.h"

#include "editor/studio_app.h"
#include "editor/action.h"
#include "editor/text_filter.h"


namespace Aetherion {


struct AETHERION_EDITOR_API PropertyGrid : StudioApp::GUIPlugin {
	friend struct GridUIVisitor;
	struct IPlugin {
		virtual ~IPlugin() {}
		virtual void update() {}
		virtual void onGUI(PropertyGrid& grid, Span<const EntityRef> entities, ComponentType cmp_type, const TextFilter& filter, WorldEditor& editor) = 0;
		virtual void blobGUI(PropertyGrid& grid, Span<const EntityRef> entities, ComponentType cmp_type, u32 array_index, const TextFilter& filter, WorldEditor& editor) {}
		virtual bool onPathDropped(const struct PathInfo&) { return false; }
	};

	explicit PropertyGrid(StudioApp& app);

	void addPlugin(IPlugin& plugin) { m_plugins.push(&plugin); }
	void removePlugin(IPlugin& plugin) { m_plugins.eraseItem(&plugin); }
	bool entityInput(const char* name, EntityPtr* entity);

private:
	void onGUI() override;
	const char* getName() const override { return "property_grid"; }
	void showComponentProperties(Span<const EntityRef> entities, ComponentType cmp_type, WorldEditor& editor);
	void showCoreProperties(Span<const EntityRef> entities, WorldEditor& editor) const;
	void toggleUI() { m_is_open = !m_is_open; }
	bool isOpen() const { return m_is_open; }
	void onPathDropped(const char* path);

	StudioApp& m_app;
	Array<IPlugin*> m_plugins;
	EntityPtr m_deferred_select;
	
	bool m_is_open = false;
	bool m_focus_filter_request = false;
	TextFilter m_component_filter;
	TextFilter m_property_filter;
	Action m_toggle_ui{"Inspector", "Inspector", "Toggle UI", "inspector_toggle_ui", "", Action::WINDOW};
	Action m_focus_filter_action{"Inspector", "Focus filter", "Focus filter", "inspector_focus_filter", ""};
};


} // namespace Aetherion