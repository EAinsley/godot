/**************************************************************************/
/*  test_animation_library.h                                              */
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

#ifndef TEST_ANIMATION_LIBRARY_H
#define TEST_ANIMATION_LIBRARY_H

#include "scene/resources/animation_library.h"

#include "tests/test_macros.h"

namespace TestAnimationLibrary {

TEST_CASE("[AnimationLibrary] Name Validation") {
	const String empty_name = "";

	const String bad_names[4] = {
		String("[stop]"),
		String("7,5"),
		String(":("),
		String("/home")
	};

	const String good_name = "A good name";

	for (int i = 0; i < 4; i++) {
		CHECK_FALSE(AnimationLibrary::is_valid_animation_name(bad_names[i]));
		CHECK_FALSE(AnimationLibrary::is_valid_library_name(bad_names[i]));
	}

	CHECK_FALSE(AnimationLibrary::is_valid_animation_name(empty_name));
	CHECK(AnimationLibrary::is_valid_library_name(empty_name));

	CHECK(AnimationLibrary::is_valid_animation_name(good_name));
	CHECK(AnimationLibrary::is_valid_library_name(good_name));
}

} //namespace TestAnimationLibrary

#endif // TEST_ANIMATION_LIBRARY_H
