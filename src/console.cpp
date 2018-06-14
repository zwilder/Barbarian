#include "../include/console.hpp"

namespace wsl
{

Console::Console(int width, int height) : width_(width), height_(height)
{
    screen_.assign(width_ * height_, Glyph(' '));
}

Glyph Console::get(int x, int y)
{
    return screen_[x + (y * width_)];
}

void Console::put(int x, int y, Glyph glyph)
{
    screen_[x + (y * width_)] = glyph;
}

void Console::clear(int x, int y)
{
    screen_[x + (y * width_)] = Glyph(' ');
}

void Console::flush()
{
    for(int i = 0; i < screen_.size(); ++i)
    {
        screen_[i] = Glyph(' ');
    }
}
} // namespace wsl
