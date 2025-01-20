#include "DccExCommadConverter.hpp"

namespace DccExParser
{
    DccExCommandConverter::DccExCommandConverter(Common::CommandManager& manager):
        _manager(manager)
    {}

    void DccExCommandConverter::parsed_values(const std::vector<std::string>& parsed_values)
    {

    }
}
