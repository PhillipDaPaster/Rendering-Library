#include "imgui.h"
#include <string>
#include <vector>

namespace Renderer {
	inline void Rectangle(ImDrawList* drawlist, ImVec2 pos, ImVec2 size, ImColor color, float rounding = 0.f, float thickness = 1.f) {
		drawlist->AddRect(pos, ImVec2(pos.x + size.x, pos.y + size.y), color, rounding, 0, thickness);
	};

	inline void FilledRectangle(ImDrawList* drawlist, ImVec2 pos, ImVec2 size, ImColor color, float rounding = 0.f) {
		drawlist->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + size.y), color, rounding);
	};

	inline void Gradient(ImDrawList* drawlist, ImVec2 pos, ImVec2 size, ImColor col_upr_left, ImColor col_upr_right, ImColor col_bot_right, ImColor col_bot_left) {
		drawlist->AddRectFilledMultiColor(pos, ImVec2(pos.x + size.x, pos.y + size.y), col_upr_left, col_upr_right, col_bot_right, col_bot_left);
	}

	inline void GradientRect(ImDrawList* drawlist, int x, int y, int w, int h, ImColor TopLeftColor, ImColor TopRightColor, ImColor BottomLeftColor, ImColor BottomRightColor, float Thickness) {
		drawlist->AddRectFilledMultiColor(ImVec2(x, y), ImVec2(x + w, y + Thickness), TopLeftColor, TopRightColor, TopRightColor, TopLeftColor);// top line
		drawlist->AddRectFilledMultiColor(ImVec2(x + w - Thickness, y + Thickness), ImVec2(x + w, y + h - Thickness), TopRightColor, TopRightColor, BottomRightColor, BottomRightColor);// right line
		drawlist->AddRectFilledMultiColor(ImVec2(x, y + Thickness), ImVec2(x + Thickness, y + h - Thickness), TopLeftColor, TopLeftColor, BottomLeftColor, BottomLeftColor); // left line
		drawlist->AddRectFilledMultiColor(ImVec2(x, y + h - Thickness), ImVec2(x + w, y + h), BottomLeftColor, BottomRightColor, BottomRightColor, BottomLeftColor); // bottom line
	}


	inline void CornerRect(ImDrawList* drawlist, float x, float y, float w, float h, float corner_size, ImColor Color, ImColor Outline = ImColor(0, 0, 0, 255)) {
		float h_corner = (w * corner_size) / 99.5f;
		float v_corner = (h * corner_size) / 99.5f;

		if (corner_size == 0)
			return;

		// Outline
		drawlist->AddRectFilled(ImVec2(x, y), ImVec2(x + h_corner, y + 3), Outline);
		drawlist->AddRectFilled(ImVec2(x, y), ImVec2(x + 3, y + v_corner), Outline);
		drawlist->AddRectFilled(ImVec2(x + w - h_corner, y), ImVec2(x + w, y + 3), Outline);
		drawlist->AddRectFilled(ImVec2(x + w - 3, y), ImVec2(x + w, y + v_corner), Outline);
		drawlist->AddRectFilled(ImVec2(x, y + h - 3), ImVec2(x + h_corner, y + h), Outline);
		drawlist->AddRectFilled(ImVec2(x, y + h - v_corner), ImVec2(x + 3, y + h), Outline);
		drawlist->AddRectFilled(ImVec2(x + w - h_corner, y + h - 3), ImVec2(x + w, y + h), Outline);
		drawlist->AddRectFilled(ImVec2(x + w - 3, y + h - v_corner), ImVec2(x + w, y + h), Outline);

		// Main Box Corners
		drawlist->AddRectFilled(ImVec2(x + 1, y + 1), ImVec2(x + h_corner - 1, y + 2), Color);
		drawlist->AddRectFilled(ImVec2(x + 1, y + 1), ImVec2(x + 2, y + v_corner - 1), Color);
		drawlist->AddRectFilled(ImVec2(x + w - h_corner + 1, y + 1), ImVec2(x + w - 1, y + 2), Color);
		drawlist->AddRectFilled(ImVec2(x + w - 2, y + 1), ImVec2(x + w - 1, y + v_corner - 1), Color);
		drawlist->AddRectFilled(ImVec2(x + 1, y + h - 2), ImVec2(x + h_corner - 1, y + h - 1), Color);
		drawlist->AddRectFilled(ImVec2(x + 1, y + h - v_corner + 1), ImVec2(x + 2, y + h - 1), Color);
		drawlist->AddRectFilled(ImVec2(x + w - h_corner + 1, y + h - 2), ImVec2(x + w - 1, y + h - 1), Color);
		drawlist->AddRectFilled(ImVec2(x + w - 2, y + h - v_corner + 1), ImVec2(x + w - 1, y + h - 1), Color);
	}

	inline void Text(ImDrawList* drawlist, ImVec2 pos, std::string text, ImColor color, ImColor outline, ImFont* font = NULL, float size = 0.0f, float wrap_width = 0.0f, const ImVec4* cpu_fine_clip_rect = NULL) {
		if (outline.operator ImU32() != IM_COL32(0, 0, 0, 0)) { // 8 outlines are superior stroke text 
			drawlist->AddText(font, size, ImVec2(pos.x + 1, pos.y + 1), outline, text.c_str(), NULL, wrap_width, cpu_fine_clip_rect);
			drawlist->AddText(font, size, ImVec2(pos.x - 1, pos.y - 1), outline, text.c_str(), NULL, wrap_width, cpu_fine_clip_rect);
			drawlist->AddText(font, size, ImVec2(pos.x - 1, pos.y), outline, text.c_str(), NULL, wrap_width, cpu_fine_clip_rect);
			drawlist->AddText(font, size, ImVec2(pos.x, pos.y - 1), outline, text.c_str(), NULL, wrap_width, cpu_fine_clip_rect);
			drawlist->AddText(font, size, ImVec2(pos.x + 1, pos.y), outline, text.c_str(), NULL, wrap_width, cpu_fine_clip_rect);
			drawlist->AddText(font, size, ImVec2(pos.x, pos.y + 1), outline, text.c_str(), NULL, wrap_width, cpu_fine_clip_rect);
			drawlist->AddText(font, size, ImVec2(pos.x - 1, pos.y + 1), outline, text.c_str(), NULL, wrap_width, cpu_fine_clip_rect);
			drawlist->AddText(font, size, ImVec2(pos.x + 1, pos.y - 1), outline, text.c_str(), NULL, wrap_width, cpu_fine_clip_rect);
		}

		drawlist->AddText(font, size, pos, color, text.c_str(), NULL, wrap_width, cpu_fine_clip_rect);
	}

	inline void Circle(ImDrawList* drawlist, ImVec2 pos, float radius, ImColor color, float thickness = 1.f, int segments = 0) {
		drawlist->AddCircle(pos, radius, color, segments, thickness);
	}

	inline void CircleFilled(ImDrawList* drawlist, ImVec2 pos, float radius, ImColor color, int segments) {
		drawlist->AddCircleFilled(pos, radius, color, segments);
	}

	inline void Line(ImDrawList* drawlist, ImVec2 start, ImVec2 end, ImColor color, float thickness = 1.f) {
		drawlist->AddLine(start, end, color, thickness);
	}

	inline void Triangle(ImDrawList* drawlist, ImVec2 p1, ImVec2 p2, ImVec2 p3, ImColor color, float thickness = 1.f) {
		drawlist->AddTriangle(p1, p2, p3, color, thickness);
	}

	inline void TriangleFilled(ImDrawList* drawlist, ImVec2 p1, ImVec2 p2, ImVec2 p3, ImColor color) {
		drawlist->AddTriangleFilled(p1, p2, p3, color);
	}

	inline void Polyline(ImDrawList* drawlist, const std::vector<ImVec2>& points, ImColor color, bool closed = false, float thickness = 1.f) {
		drawlist->AddPolyline(points.data(), points.size(), color, closed, thickness);
	}

	inline void Polygon(ImDrawList* drawlist, const std::vector<ImVec2>& points, ImColor color) {
		drawlist->AddConvexPolyFilled(points.data(), points.size(), color);
	}

	inline void DashedLine(ImDrawList* drawlist, ImVec2 start, ImVec2 end, ImColor color, float thickness = 1.f, float dash_length = 5.f, float gap_length = 3.f) {
		ImVec2 direction = ImVec2(end.x - start.x, end.y - start.y);
		float length = sqrtf(direction.x * direction.x + direction.y * direction.y);
		direction.x /= length;
		direction.y /= length;

		float drawn_length = 0.f;
		while (drawn_length < length) {
			ImVec2 segment_start = ImVec2(start.x + direction.x * drawn_length, start.y + direction.y * drawn_length);
			drawn_length += dash_length;
			ImVec2 segment_end = ImVec2(start.x + direction.x * fminf(drawn_length, length), start.y + direction.y * fminf(drawn_length, length));
			drawlist->AddLine(segment_start, segment_end, color, thickness);
			drawn_length += gap_length;
		}
	}

	inline void Arrow(ImDrawList* drawlist, ImVec2 start, ImVec2 end, ImColor color, float thickness = 1.f, float arrow_size = 10.f) {
		drawlist->AddLine(start, end, color, thickness);

		ImVec2 direction = ImVec2(end.x - start.x, end.y - start.y);
		float length = sqrtf(direction.x * direction.x + direction.y * direction.y);
		direction.x /= length;
		direction.y /= length;

		ImVec2 perp_dir = ImVec2(-direction.y, direction.x);
		ImVec2 p1 = ImVec2(end.x - direction.x * arrow_size + perp_dir.x * (arrow_size / 2), end.y - direction.y * arrow_size + perp_dir.y * (arrow_size / 2));
		ImVec2 p2 = ImVec2(end.x - direction.x * arrow_size - perp_dir.x * (arrow_size / 2), end.y - direction.y * arrow_size - perp_dir.y * (arrow_size / 2));

		drawlist->AddTriangleFilled(end, p1, p2, color);
	}


};
