// SPDX-FileCopyrightText: (c) 2019 Silverlan <opensource@pragma-engine.com>
// SPDX-License-Identifier: MIT

module;


export module pragma.string.formatted_text:anchor_point;

export import :types;
export import pragma.util;

export namespace util {
	namespace text {
		class FormattedTextLine;
		class LineStartAnchorPoint;
		class AnchorPoint {
		  public:
			template<class TAnchorPoint = AnchorPoint>
			static util::TSharedHandle<TAnchorPoint> Create(FormattedTextLine &line, bool allowOutOfBounds = false)
			{
				auto hAnchorPoint = util::TSharedHandle<TAnchorPoint> {new TAnchorPoint {allowOutOfBounds}};
				hAnchorPoint->m_handle = util::shared_handle_cast<TAnchorPoint, AnchorPoint>(hAnchorPoint);
				hAnchorPoint->SetLine(line);
				return hAnchorPoint;
			}
			virtual ~AnchorPoint() = default;
			LineIndex GetLineIndex() const;
			TextOffset GetTextCharOffset() const;
			FormattedTextLine &GetLine() const;
			bool IsValid() const;

			AnchorPoint &operator=(const AnchorPoint &) = delete;
			// TODO: Replace these with operator<=> once C++-20 is released
			bool operator==(const AnchorPoint &other) const;
			bool operator!=(const AnchorPoint &other) const;
			bool operator<(const AnchorPoint &other) const;
			bool operator>(const AnchorPoint &other) const;
			bool operator<=(const AnchorPoint &other) const;
			bool operator>=(const AnchorPoint &other) const;

			void SetLine(FormattedTextLine &line);
			LineStartAnchorPoint *GetParent();
			void SetParent(LineStartAnchorPoint &parent);
			void ClearParent();
			void ClearLine();
			bool IsAttachedToLine(FormattedTextLine &line) const;
			virtual bool IsLineStartAnchorPoint() const;
			bool IsInRange(TextOffset startOffset, TextLength len) const;
			bool ShouldAllowOutOfBounds() const;

			virtual void ShiftByOffset(ShiftOffset offset);
			void ShiftToOffset(TextOffset offset);
			void SetOffset(TextOffset offset);

			util::TSharedHandle<AnchorPoint> GetHandle();
		  protected:
			AnchorPoint(TextOffset charOffset = 0, bool allowOutOfBounds = false);
			AnchorPoint(const AnchorPoint &) = delete;
		  private:
			TextOffset m_charOffset = 0u;
			bool m_bAllowOutOfBounds = false;
			std::weak_ptr<FormattedTextLine> m_wpLine = {};
			util::TWeakSharedHandle<AnchorPoint> m_parent = {};

			util::TWeakSharedHandle<AnchorPoint> m_handle = {};
		};

		class LineStartAnchorPoint : public AnchorPoint {
		  public:
			void SetPreviousLineAnchorStartPoint(LineStartAnchorPoint &anchor);
			void ClearPreviousLineAnchorStartPoint();
			LineStartAnchorPoint *GetPreviousLineAnchorStartPoint();

			void SetNextLineAnchorStartPoint(LineStartAnchorPoint &anchor);
			void ClearNextLineAnchorStartPoint();
			LineStartAnchorPoint *GetNextLineAnchorStartPoint();

			virtual bool IsLineStartAnchorPoint() const override;
			virtual void ShiftByOffset(ShiftOffset offset) override;

			std::vector<util::TWeakSharedHandle<AnchorPoint>> &GetChildren();
			const std::vector<util::TWeakSharedHandle<AnchorPoint>> &GetChildren() const;
		  protected:
			void RemoveChild(const AnchorPoint &anchorPoint);
			std::vector<util::TWeakSharedHandle<AnchorPoint>> m_children = {};
			using AnchorPoint::AnchorPoint;
			using AnchorPoint::SetParent;
			friend AnchorPoint;
		  private:
			util::TWeakSharedHandle<AnchorPoint> m_prevLineAnchorStartPoint = {};
			util::TWeakSharedHandle<AnchorPoint> m_nextLineAnchorStartPoint = {};
		};
	};
};
