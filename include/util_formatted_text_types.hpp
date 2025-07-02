// SPDX-FileCopyrightText: (c) 2019 Silverlan <opensource@pragma-engine.com>
// SPDX-License-Identifier: MIT

#ifndef __UTIL_FORMATTED_TEXT_TYPES_HPP__
#define __UTIL_FORMATTED_TEXT_TYPES_HPP__

#include <cinttypes>
#include <limits>
#include <memory>

#ifdef _MSC_VER
namespace pragma::string {
	class Utf8String;
};
#else
import pragma.string.unicode;
#endif

namespace util {
	namespace text {
		using TextLength = size_t;
		using TextOffset = size_t;

		using LineIndex = uint32_t;
		using CharOffset = uint32_t;

		using ShiftOffset = int32_t;

		static const LineIndex LAST_LINE = std::numeric_limits<LineIndex>::max();
		static const LineIndex INVALID_LINE_INDEX = LAST_LINE;
		static const CharOffset LAST_CHAR = std::numeric_limits<CharOffset>::max();
		static const TextLength UNTIL_THE_END = std::numeric_limits<TextLength>::max();
		static const TextOffset END_OF_TEXT = std::numeric_limits<TextOffset>::max();

		class AnchorPoint;

		class FormattedTextLine;
		using PFormattedTextLine = std::shared_ptr<FormattedTextLine>;
	};
};

#endif
