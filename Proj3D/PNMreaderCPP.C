#include <PNMreaderCPP.h>

//#include <iostream>
//using namespace std;

PNMreaderCPP::PNMreaderCPP()
{
    fileName = new char[strlen("noName" + 1)];
    strcpy(fileName, "noName");
}

PNMreaderCPP::PNMreaderCPP(char *aFileName)
{
    //allocating memory for the fileName
    fileName = new char[strlen(aFileName + 1)];
    
    //copying aFileName into fileName
    strcpy(fileName, aFileName);
}

PNMreaderCPP::~PNMreaderCPP()
{
    if(strcmp(fileName, "noName") != 0)
    {
        delete[] fileName;
        fileName = new char[strlen("noName" + 1)];
        strcpy(fileName, "noName");
    }
}

void PNMreaderCPP::Execute()
{
    ifstream inFile;
    char magicNum[128];
    int width, height, maxval;
    Pixel *aBuffer;
        
    inFile.open(fileName, ios::binary | ios::in);
    
    if(!inFile)
    {
        cout << "Input file could not open." << endl;
        return;
    }
    
    //Reading the header of the file
    inFile >> magicNum >> width >> height >> maxval;
    inFile.ignore(256, '\n');
    
    if (strcmp(magicNum, "P6") != 0)
    {
        fprintf(stderr, "Input file %s is not a PNM file of type P6\n", fileName);
        return;
    }
    
    aBuffer = new Pixel[width*height];
    
    img.setHeight(height);
    img.setWidth(width);
    
    //Reading the buffer
    
    for(int i = 0; i < height*width; i++)
    {
        inFile.read(reinterpret_cast<char*>(&aBuffer[i]), sizeof(Pixel));
    }
    
    img.setBuffer(aBuffer);
    
    inFile.close();
    
}


