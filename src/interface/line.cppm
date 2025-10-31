// SPDX-FileCopyrightText: (c) 2019 Silverlan <opensource@pragma-engine.com>
// SPDX-License-Identifier: MIT

module;


export module pragma.string.formatted_text:line;

export import :text_line;
export import pragma.string.unicode;
export import pragma.util;

export namespace util {
	namespace text {
		class FormattedText;
		class TextTagComponent;
		class LineStartAnchorPoint;
		class AnchorPoint;
		class FormattedTextLine : public std::enable_shared_from_this<FormattedTextLine> {
		  public:
			static PFormattedTextLine Create(FormattedText &text, const std::string &line = "");
			FormattedTextLine(const FormattedTextLine &) = delete;
			FormattedTextLine &operator=(const FormattedTextLine &) = delete;
			~FormattedTextLine();
			const TextLine &GetFormattedLine() const;
			TextLine &GetFormattedLine();

			const TextLine &GetUnformattedLine() const;
			TextLine &GetUnformattedLine();

			CharOffset AppendString(const pragma::string::Utf8StringView &str);
			std::optional<CharOffset> InsertString(const pragma::string::Utf8StringView &str, CharOffset charOffset);
			pragma::string::Utf8StringView Substr(CharOffset offset, TextLength len = UNTIL_THE_END) const;
			std::optional<TextLength> Erase(CharOffset startOffset, TextLength len = UNTIL_THE_END, pragma::string::Utf8String *outErasedString = nullptr);
			bool Move(CharOffset startOffset, TextLength len, FormattedTextLine &moveTarget, CharOffset targetCharOffset = LAST_CHAR);

			std::vector<util::TSharedHandle<TextTagComponent>> &GetTagComponents();
			const std::vector<util::TSharedHandle<TextTagComponent>> &GetTagComponents() const;
			std::vector<util::TWeakSharedHandle<AnchorPoint>> &GetAnchorPoints();
			const std::vector<util::TWeakSharedHandle<AnchorPoint>> &GetAnchorPoints() const;
			const LineStartAnchorPoint &GetStartAnchorPoint() const;
			LineStartAnchorPoint &GetStartAnchorPoint();
			LineIndex GetIndex() const;

			bool IsEmpty() const;
			TextOffset GetStartOffset() const;
			TextOffset GetEndOffset() const;
			TextOffset GetFormattedStartOffset() const;
			// End-offset including the new-line character
			TextOffset GetAbsEndOffset() const;
			TextLength GetAbsLength() const;
			TextLength GetLength() const;
			TextLength GetAbsFormattedLength() const;
			TextLength GetFormattedLength() const;
			std::optional<CharOffset> GetRelativeOffset(TextOffset offset) const;
			bool IsInRange(TextOffset offset, TextLength len = 1) const;
			std::optional<char> GetChar(CharOffset offset) const;
			CharOffset GetFormattedCharOffset(CharOffset offset) const;
			CharOffset GetUnformattedCharOffset(CharOffset offset) const;
			util::TSharedHandle<AnchorPoint> CreateAnchorPoint(CharOffset charOffset, bool allowOutOfBounds = false);

			void AppendCharacter(int32_t c);
			TextLine &Format();
			FormattedText &GetTargetText() const;

#ifdef ENABLE_FORMATTED_TEXT_UNIT_TESTS
			bool Validate(std::stringstream &msg) const;
#endif
		  protected:
			FormattedTextLine(FormattedText &text, const std::string &line = "");
			void Initialize(LineIndex lineIndex);
			void SetIndex(LineIndex lineIndex);
			void DetachAnchorPoint(const AnchorPoint &anchorPoint);
			void AttachAnchorPoint(AnchorPoint &anchorPoint);

			// oldLineLen = original length of this line before the modification that caused the shift
			// was applied
			void ShiftAnchors(CharOffset startOffset, TextLength len, ShiftOffset shiftAmount, TextLength oldLineLen);
			std::vector<TSharedHandle<AnchorPoint>> DetachAnchorPoints(CharOffset startOffset, TextLength len = UNTIL_THE_END);
			void AttachAnchorPoints(std::vector<TSharedHandle<AnchorPoint>> &anchorPoints, ShiftOffset shiftOffset = 0);
			util::TSharedHandle<TextTagComponent> ParseTagComponent(CharOffset offset, const pragma::string::Utf8StringView &str);
			friend FormattedText;
			friend AnchorPoint;
		  private:
			FormattedText &m_text;
			util::TSharedHandle<LineStartAnchorPoint> m_startAnchorPoint = nullptr;
			TextOffset m_formattedStartOffset = 0;
			TextLine m_formattedLine;
			TextLine m_unformattedLine;
			std::vector<CharOffset> m_unformattedCharIndexToFormatted = {};
			std::vector<CharOffset> m_formattedCharIndexToUnformatted = {};
			LineIndex m_lineIndex = INVALID_LINE_INDEX;
			std::vector<util::TSharedHandle<TextTagComponent>> m_tagComponents = {};
			std::vector<util::TWeakSharedHandle<AnchorPoint>> m_anchorPoints = {};

			bool m_bDirty = false;
		};
	};
};
