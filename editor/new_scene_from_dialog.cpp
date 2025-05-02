/**************************************************************************/
/*  new_scene_from_dialog.cpp                                             */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#include "editor/new_scene_from_dialog.h"

#include "editor/editor_node.h"
#include "scene/gui/grid_container.h"
#include "scene/gui/item_list.h"
#include "scene/resources/packed_scene.h"

NewSceneFromDialog::NewSceneFromDialog() {
	// set_file_mode(EditorFileDialog::FILE_MODE_SAVE_FILE);

	// Ref<PackedScene> sd = memnew(PackedScene);
	// ResourceSaver::get_recognized_extensions(sd, &extensions);
	// for (const String &extension : extensions) {
	// 	add_filter("*." + extension, extension.to_upper());
	// }
	// set_title(TTR("Save New Scene As..."));

	// Configure self
	set_ok_button_text(TTR("Create"));
	// Main Container
	VBoxContainer *vb = memnew(VBoxContainer);
	GridContainer *gc = memnew(GridContainer);
	gc->set_columns(2);
	vb->add_child(gc);
	add_child(vb);

	// TODO: Add Root Name
	root_name_edit = memnew(LineEdit);
	root_name_edit->set_h_size_flags(Control::SIZE_EXPAND_FILL);
	register_text_enter(root_name_edit);
	gc->add_child(memnew(Label(TTR("Root Name:"))));
	gc->add_child(root_name_edit);

	// TODO: Add Inherited dropdown
	ancestor_options = memnew(OptionButton);
	ancestor_options->set_auto_translate_mode(AUTO_TRANSLATE_MODE_DISABLED);
	ancestor_options->set_h_size_flags(Control::SIZE_EXPAND_FILL);
	gc->add_child(memnew(Label(TTR("Inherits:"))));
	gc->add_child(ancestor_options);

	// TODO: Add File Path
	HBoxContainer *hb = memnew(HBoxContainer);
	file_path_edit = memnew(LineEdit);
	file_path_edit->set_h_size_flags(Control::SIZE_EXPAND_FILL);
	Button *path_button = memnew(Button);
	register_text_enter(file_path_edit);

	// TODO: connect pressed signal here to pop file browser
	hb->add_child(file_path_edit);
	hb->add_child(path_button);
	gc->add_child(memnew(Label(TTR("Path:"))));
	gc->add_child(hb);

	// TODO: Add reset options
	GridContainer *checkbox_gc = memnew(GridContainer);
	checkbox_gc->set_columns(2);
	checkbox_gc->add_child(memnew(CheckBox(TTR("Reset Position"))));
	checkbox_gc->add_child(memnew(CheckBox(TTR("Reset Rotation"))));
	checkbox_gc->add_child(memnew(CheckBox(TTR("Reset Scale"))));
	checkbox_gc->add_child(memnew(CheckBox(TTR("Remove Script"))));
	gc->add_child(memnew(Label(TTR("Configs:"))));
	gc->add_child(checkbox_gc);
	// add_option(TTR("Reset Position"), Vector<String>(), true);
	// add_option(TTR("Reset Rotation"), Vector<String>(), false);
	// add_option(TTR("Reset Scale"), Vector<String>(), false);
	// add_option(TTR("Auto Rename"), Vector<String>(), true);
	// sidemenu = memnew(VBoxContainer);
	// sidemenu->set_alignment(BoxContainer::AlignmentMode::ALIGNMENT_END);
	// sidemenu->set_custom_minimum_size(Size2(150, 300));

	// ancestor_list = memnew(ItemList);
	// ancestor_list->set_select_mode(ItemList::SelectMode::SELECT_SINGLE);

	// ancestor_sidemenu = memnew(VBoxContainer);
	// ancestor_sidemenu->add_margin_child(TTR("Inherit from..."), ancestor_list, true);

	// HBoxContainer *rename_box = memnew(HBoxContainer);
	// NOTE: I don't know the difference of TTR and ETR. Check this later
	// Label *l = memnew(Label(TTR("Name:")));
	// l->set_theme_type_variation("HeaderSmall");
	// rename_box->add_child(l);

	// root_name_edit = memnew(LineEdit);
	// root_name_edit->set_structured_text_bidi_override(TextServer::STRUCTURED_TEXT_FILE);
	// root_name_edit->set_stretch_ratio(4);
	// root_name_edit->set_h_size_flags(Control::SIZE_EXPAND_FILL);
	// rename_box->add_child(root_name_edit);

	// add_side_menu(sidemenu);
	// sidemenu->add_child(ancestor_sidemenu);
	// sidemenu->add_child(rename_box);
	// add_side_menu(ancestor_sidemenu);
	set_title(TTR("Create New Scene From..."));
}

void NewSceneFromDialog::config(Node *p_selected_node) {
	String existing;
	if (extensions.size()) {
		String root_name(p_selected_node->get_name());
		root_name = EditorNode::adjust_scene_name_casing(root_name);
		// existing = root_name + "." + extensions.front()->get().to_lower();
	}
	// set_current_path(existing);
	// setup the list
	// ancestor_list->clear();
	// int item_count = 0;
	// if (p_selected_node->get_scene_instance_state().is_valid()) {
	// 	Vector<Node *> instances;
	// 	Ref<SceneState> scene_state = p_selected_node->get_scene_instance_state();
	// 	while (scene_state.is_valid()) {
	// 		Ref<PackedScene> pack_data = ResourceLoader::load(scene_state->get_path());
	// 		if (!pack_data.is_valid()) {
	// 			break;
	// 		}
	// 		// QUESTION - GEN_EDIT_STATE_INSTANCE?
	// 		Node *current_node = pack_data->instantiate(PackedScene::GEN_EDIT_STATE_INSTANCE);
	// 		String name = current_node->get_name();
	// 		String path_name = current_node->get_scene_file_path();
	// 		String class_name = current_node->get_class_name();
	// 		instances.push_back(current_node);
	// 		ancestor_list->add_item(name, EditorNode::get_singleton()->get_class_icon(class_name));
	// 		ancestor_list->set_item_tooltip(item_count, path_name);
	// 		ancestor_list->set_item_metadata(item_count, scene_state);

	// 		scene_state = current_node->get_scene_inherited_state();
	// 		item_count++;
	// 	};
	// 	for (Node *instance : instances) {
	// 		memdelete(instance);
	// 	}
	// }
	// if (item_count > 0) {
	// 	ancestor_list->select(0);
	// ancestor_sidemenu->set_visible(true);
	// } else {
	// ancestor_sidemenu->set_visible(false);
	// }
	// root_name_edit->set_text(p_selected_node->get_name());
}

Ref<SceneState> NewSceneFromDialog::get_selected_scene_state() const {
	// PackedInt32Array items = ancestor_list->get_selected_items();
	// if (items.size() > 0) {
	// 	return ancestor_list->get_item_metadata(items[0]);
	// }
	return nullptr;
}

String NewSceneFromDialog::get_new_node_name() const {
	return root_name_edit->get_text();
}
