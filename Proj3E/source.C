#include <source.h>

source::source()
{
    img.setSource(this); //setting source. could be reader/shrinker/blender/etc....
}

source::~source()
{
    
}

Image * source::GetOutput()
{
    return &img;
}

//Source has an Update (virtual)
//Filter and PNMreader inherit Source, so they need an Update implementation
//Implement custom one for Filter and custom one for PNMreader
void source::Update()
{
    //For filter:
    //First, call Update on each of the non-null input images
    //Each source has the two input image variables from Sink
    //After these finish and return, call Execute on the filter
    
    this->Execute(); // execute source. could be reader/shrinker/blender/etc....
}
