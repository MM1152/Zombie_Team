#include "stdafx.h"

int main()
{
    FRAMEWORK.Init(1920, 1080, "Pong!!");
    FRAMEWORK.Do();
    FRAMEWORK.Release();

    return 0;
}