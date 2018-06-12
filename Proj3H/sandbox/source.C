
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
    char msg[128];
    sprintf(msg, "%s: start executing", SourceName());
    Logger::LogEvent(msg);
    Execute();
    sprintf(msg, "%s: finished executing", SourceName());
    Logger::LogEvent(msg);
}
