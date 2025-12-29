#include "jsonstorage.h"

using json = nlohmann::json;

json storage::load(void) const
{
    
}

bool storage::exists(void) const
{
    return std::filesystem::exists(p_filepath);
}