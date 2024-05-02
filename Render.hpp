#pragma once
#include "vector.hpp" // vector is on my github page or via this link Github - https://github.com/PhillipThePaster/Vector-Library/blob/main/Vector.hpp
#include <imgui.h> // need to change this to your code 
//----------------------------------------------------\
// [Render] : Main                                    |
//----------------------------------------------------|
// - Line                                             |
// - Line Glow                                        |
// - Rect                                             |
// - Rect Gradient                                    |
// - Rect Filled                                      |
// - Rect Filled Gradient                             |
// - Circle                                           |
// - Circle Filled                                    |
// - Circle Gradient                                  |
// - Arc Display                                      |
//----------------------------------------------------|
//----------------------------------------------------/

namespace Render {
    void line(ImDrawList* drawList, Vec2 From, Vec2 To, ImColor Color, float Thickness, bool Outline) {
        if (Outline)
            drawList->AddLine(From.ToImVec2(), To.ToImVec2(), ImColor(0, 0, 0), Thickness + 1.f);
        drawList->AddLine(From.ToImVec2(), To.ToImVec2(), Color, Thickness);
    }
    
    // dont use please
    void line_glow(ImDrawList* drawList, Vec2 From, Vec2 To, ImColor Color, float Thickness) {
        line(drawList, From, To, ImColor(Color.Value.x, Color.Value.y, Color.Value.z, Color.Value.w), Thickness + 1.f, false);
        line(drawList, From, To, ImColor(Color.Value.x, Color.Value.y, Color.Value.z, Color.Value.w * 0.4f), Thickness + 3.f, false);
        line(drawList, From, To, ImColor(Color.Value.x, Color.Value.y, Color.Value.z, Color.Value.w * 0.2f), Thickness + 5.f, false);
        line(drawList, From, To, ImColor(Color.Value.x, Color.Value.y, Color.Value.z, Color.Value.w * 0.09f), Thickness + 8.f, false);
        line(drawList, From, To, ImColor(Color.Value.x, Color.Value.y, Color.Value.z, Color.Value.w * 0.02f), Thickness + 11.f, false);
        line(drawList, From, To, ImColor(Color.Value.x, Color.Value.y, Color.Value.z, Color.Value.w * 0.004f), Thickness + 14.f, false);
    }

    void rect(ImDrawList* drawList, Vec2 Pos, Vec2 Size, ImColor Color, float Thickness, float Rounding, bool Outline) {
        if (Outline)
             drawList->AddRect(Pos.ToImVec2(), { Pos.x + Size.x, Pos.y + Size.y }, ImColor(0, 0, 0), Rounding, 0, Thickness + 1.f);
        drawList->AddRect(Pos.ToImVec2(), { Pos.x + Size.x, Pos.y + Size.y }, Color, Rounding, 0, Thickness);
    }

    void rect_gradient(ImDrawList* drawList, Vec2 Pos, Vec2 Size, ImColor TopColor, ImColor BottomColor, float Thickness) {
        ImVec2 TopLeft = Pos.ToImVec2();
        ImVec2 BottomRight = { Pos.x + Size.x, Pos.y + Size.y };

        drawList->AddRectFilled(TopLeft, ImVec2(BottomRight.x, TopLeft.y + Thickness), TopColor); // top 
        drawList->AddRectFilledMultiColor(ImVec2(BottomRight.x - Thickness, TopLeft.y + Thickness), ImVec2(BottomRight.x, BottomRight.y - Thickness), TopColor, TopColor, BottomColor, BottomColor); // right side
        drawList->AddRectFilledMultiColor(ImVec2(TopLeft.x, TopLeft.y + Thickness), ImVec2(TopLeft.x + Thickness, BottomRight.y - Thickness), TopColor, TopColor, BottomColor, BottomColor); // left side
        drawList->AddRectFilled(ImVec2(TopLeft.x, BottomRight.y - Thickness), BottomRight, BottomColor); // bottom
    }

    void rect_filled(ImDrawList* drawList, Vec2 Pos, Vec2 Size, ImColor Color, float Rounding) {
        drawList->AddRectFilled(Pos.ToImVec2(), { Pos.x + Size.x, Pos.y + Size.y }, Color, Rounding, 0);
    }


    void rect_filled_gradient(ImDrawList* drawList, Vec2 Pos, Vec2 Size, ImColor BgColor, ImColor TopColor, ImColor BotColor, float Rounding, int Nums)
    {
        ImDrawList* DrawList = drawList;
        ImDrawCornerFlags rounding_corners = ImDrawCornerFlags_All;
        ImVec2 a = Pos.ToImVec2();
        ImVec2 b = { Pos.x + Size.x,Pos.y + Size.y };

        Rounding = ImMin<float>(Rounding, fabsf(Size.x) * (((rounding_corners & ImDrawCornerFlags_Top) == ImDrawCornerFlags_Top) || ((rounding_corners & ImDrawCornerFlags_Bot) == ImDrawCornerFlags_Bot) ? 0.5f : 1.0f) - 1.0f);
        Rounding = ImMin<float>(Rounding, fabsf(Size.y) * (((rounding_corners & ImDrawCornerFlags_Left) == ImDrawCornerFlags_Left) || ((rounding_corners & ImDrawCornerFlags_Right) == ImDrawCornerFlags_Right) ? 0.5f : 1.0f) - 1.0f);

        //DrawList->AddRectFilledMultiColorRounded(a, b, BgColor, TopColor, TopColor, BotColor, BotColor, Rounding, rounding_corners);// something i was working not in the code
    }

    void rect_filled_gradient(ImDrawList* drawList, Vec2 Pos, Vec2 Size, ImColor color, ImColor colorb, float rounding = 0.f, bool Horizontal = false) {
        if (Horizontal) {
            drawList->AddRectFilledMultiColor(ImVec2(Pos.x, Pos.y), ImVec2(Size.x, Size.y), colorb, color, color, colorb);
        }
        else {
            drawList->AddRectFilledMultiColor(ImVec2(Pos.x , Pos.y), ImVec2(Size.x, Size.y), color, color, colorb, colorb);
        }
    }

    void rect_corners(ImDrawList* drawList, float cornerLength, const ImVec2& pos, const ImVec2& size, ImColor Color) {
        ImVec2 topLeft = pos;
        ImVec2 topRight = { pos.x + size.x, pos.y };
        ImVec2 bottomLeft = { pos.x, pos.y + size.y };
        ImVec2 bottomRight = { pos.x + size.x, pos.y + size.y };


        drawList->AddLine({ topLeft.x, topLeft.y }, { topLeft.x + cornerLength, topLeft.y }, Color, 1.f);
        drawList->AddLine({ topLeft.x, topLeft.y }, { topLeft.x, topLeft.y + cornerLength }, Color, 1.f);
        drawList->AddLine({ topRight.x - cornerLength, topRight.y }, { topRight.x, topRight.y }, Color, 1.f);
        drawList->AddLine({ topRight.x, topRight.y }, { topRight.x, topRight.y + cornerLength }, Color, 1.f);
        drawList->AddLine({ bottomLeft.x, bottomLeft.y - cornerLength }, { bottomLeft.x, bottomLeft.y }, Color, 1.f);
        drawList->AddLine({ bottomLeft.x, bottomLeft.y }, { bottomLeft.x + cornerLength, bottomLeft.y }, Color, 1.f);
        drawList->AddLine({ bottomRight.x - cornerLength, bottomRight.y }, { bottomRight.x, bottomRight.y }, Color, 1.f);
        drawList->AddLine({ bottomRight.x, bottomRight.y - cornerLength }, { bottomRight.x, bottomRight.y }, Color, 1.f);
    }


    void circle(ImDrawList* drawList, Vec2 Center, float Radius, ImColor Color, float Thickness, int Num, bool Outline) {
        if (Outline)
            drawList->AddCircle(Center.ToImVec2(), Radius, ImColor(0, 0, 0), Num, Thickness + 1);
        drawList->AddCircle(Center.ToImVec2(), Radius, Color, Num, Thickness);
    }

    void circle_filled(ImDrawList* drawList, Vec2 Center, float Radius, ImColor Color, int Num) {
        drawList->AddCircleFilled(Center.ToImVec2(), Radius, Color, Num);
    }

    void circle_gradient(ImDrawList* drawList, const Vec2 center, float radius, ImColor col_in, ImColor col_out) {
        if (((col_in | col_out) & IM_COL32_A_MASK) == 0 || radius < 0.5f)
            return;

        drawList->_PathArcToFastEx(ImVec2(center.x, center.y), radius, 0, IM_DRAWLIST_ARCFAST_SAMPLE_MAX, 0);
        const int count = drawList->_Path.Size - 1;

        unsigned int vtx_base = drawList->_VtxCurrentIdx;
        drawList->PrimReserve(count * 3, count + 1);

        const ImVec2 uv = drawList->_Data->TexUvWhitePixel;
        drawList->PrimWriteVtx(ImVec2(center.x, center.y), uv, col_in);
        for (int n = 0; n < count; n++)
            drawList->PrimWriteVtx(drawList->_Path[n], uv, col_out);

        for (int n = 0; n < count; n++) {
            drawList->PrimWriteIdx((ImDrawIdx)(vtx_base));
            drawList->PrimWriteIdx((ImDrawIdx)(vtx_base + 1 + n));
            drawList->PrimWriteIdx((ImDrawIdx)(vtx_base + 1 + ((n + 1) % count)));
        }
        drawList->_Path.Size = 0;
    }

    void arc_display(ImDrawList* drawList, ImVec2 Center, float Radius, ImColor Color, float Thickness, float Angle_begin, float Angle_end, float Nums) {
        ImDrawList* DrawList = drawList;
        float angle = (Angle_end - Angle_begin) / Nums;
        for (int i = 0; i < Nums; i++) {
            float angle_ = i * angle + Angle_begin - IM_PI / 2;
            DrawList->PathLineTo({ Center.x - Radius * cos(angle_), Center.y - Radius * sin(angle_) });
        }
        DrawList->PathStroke(Color, false, Thickness);
    }
}
