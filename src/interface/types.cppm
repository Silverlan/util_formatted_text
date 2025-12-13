// SPDX-FileCopyrightText: (c) 2019 Silverlan <opensource@pragma-engine.com>
// SPDX-License-Identifier: MIT

module;

export module pragma.string.formatted_text:types;

export import pragma.string.unicode;
export import std.compat;

export namespace pragma {
	namespace string {
		using TextLength = size_t;
		using TextOffset = size_t;

		using LineIndex = uint32_t;
		using CharOffset = uint32_t;

		using ShiftOffset = int32_t;

		constexpr LineIndex LAST_LINE = std::numeric_limits<LineIndex>::max();
		constexpr LineIndex INVALID_LINE_INDEX = LAST_LINE;
		constexpr CharOffset LAST_CHAR = std::numeric_limits<CharOffset>::max();
		constexpr TextLength UNTIL_THE_END = std::numeric_limits<TextLength>::max();
		constexpr TextOffset END_OF_TEXT = std::numeric_limits<TextOffset>::max();

		class AnchorPoint;

		class FormattedTextLine;
		using PFormattedTextLine = std::shared_ptr<FormattedTextLine>;
	};
};
