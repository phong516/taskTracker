#pragma once
#include "storage/jsonstorage.h"
class taskManager
{
    private:
        
    public:
        taskManager(void) {}
        bool load(json inputJson);
        bool save(json outputJson);