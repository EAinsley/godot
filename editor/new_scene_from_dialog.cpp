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

	// Root Name Text Edit
	root_name_edit = memnew(LineEdit);
	root_name_edit->set_h_size_flags(Control::SIZE_EXPAND_FILL);
	register_text_enter(root_name_edit);
	gc->add_child(memnew(Label(TTR("Root Name:"))));
	gc->add_child(root_name_edit);

	// Inheritance Dropdown
	ancestor_options = memnew(OptionButton);
	ancestor_options->set_auto_translate_mode(AUTO_TRANSLATE_MODE_DISABLED);
	ancestor_options->set_h_size_flags(Control::SIZE_EXPAND_FILL);
	gc->add_child(memnew(Label(TTR("Inherits:"))));
	gc->add_child(ancestor_options);

	// File Path Edit and Button
	HBoxContainer *hb = memnew(HBoxContainer);
	file_path_edit = memnew(LineEdit);
	file_path_edit->set_h_size_flags(Control::SIZE_EXPAND_FILL);
	path_button = memnew(Button);
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
	set_title(TTR("Create New Scene From..."));
}

void NewSceneFromDialog::config(Node *p_selected_node) {
	// Set Root Name
	root_name_edit->set_text(p_selected_node->get_name());

	// Set Path Name
	String existing;
	if (extensions.size()) {
		String root_name(p_selected_node->get_name());
		root_name = EditorNode::adjust_scene_name_casing(root_name);
		existing = root_name + "." + extensions.begin()->to_lower();
	}
	// TODO - The correct default_path
	file_path_edit->set_text(p_selected_node->get_scene_file_path());

	//ANCHOR - set optionbuttons
	//NOTE - Need testing
	ancestor_options->clear();
	ancestor_options->add_item(p_selected_node->get_class_name(), 0);
	int item_count = 1;
	if (p_selected_node->get_scene_instance_state().is_valid()) {
		Vector<Node *> instances;
		Ref<SceneState> scene_state = p_selected_node->get_scene_instance_state();
		while (scene_state.is_valid()) {
			Ref<PackedScene> pack_data = ResourceLoader::load(scene_state->get_path());
			if (!pack_data.is_valid()) {
				break;
			}
			// QUESTION - GEN_EDIT_STATE_INSTANCE?
			Node *current_node = pack_data->instantiate(PackedScene::GEN_EDIT_STATE_INSTANCE);
			String name = current_node->get_name();
			String path_name = current_node->get_scene_file_path();
			String class_name = current_node->get_class_name();
			instances.push_back(current_node);
			ancestor_options->add_item(name, item_count);
			ancestor_options->set_item_tooltip(item_count, path_name);
			ancestor_options->set_item_metadata(item_count, scene_state);

			scene_state = current_node->get_scene_inherited_state();
			item_count++;
		};
		for (Node *instance : instances) {
			memdelete(instance);
		}
	}
	ancestor_options->select(0);
}

Ref<SceneState> NewSceneFromDialog::get_selected_scene_state() const {
	return ancestor_options->get_selected_metadata();
}

String NewSceneFromDialog::get_new_node_name() const {
	return root_name_edit->get_text();
}

void NewSceneFromDialog::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_THEME_CHANGED: {
			// FIXME - doesn't work why?
			path_button->set_button_icon(get_editor_theme_icon(SNAME("Folder")));
		} break;
	}
}
