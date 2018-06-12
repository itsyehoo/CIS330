
#include <source.h>

source::source()
{
    img.setSource(this);
}

Image * source::GetOutput()
{
    return &img;
}

void source::Update()
{
    Execute();
}
