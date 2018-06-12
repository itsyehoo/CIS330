#include <sink.h>

sink::sink()
{
    imgPtr1 = NULL;
    imgPtr2 = NULL;
}

sink::~sink()
{

}

void sink::SetInput(Image *input1)
{
    imgPtr1 = input1;
}

void sink::SetInput2(Image *input2)
{
    imgPtr2 = input2;
}

Image sink::GetInput()
{
    return *imgPtr1;
}

Image sink::getInput2()
{
    return *imgPtr2;
}
