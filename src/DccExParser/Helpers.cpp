#include "Helpers.hpp"

namespace DccExParser::Helpers
{
    std::string DccTrackStatus(DccExParser::TrackInterface& _trackInterface)
    {
        std::string result;
        std::string reason;
        bool main_on = _trackInterface.isTrackOn(TrackInterface::TackType::eMain);
        bool prog_on = _trackInterface.isTrackOn(TrackInterface::TackType::eProg);
        bool join_on = _trackInterface.isTrackOn(TrackInterface::TackType::eJoin);
        
        if (main_on && prog_on && join_on)
            result = "<p1 JOIN>";
        else if (main_on && prog_on)
            result = "<p1>";
        else if (main_on)
            result = "<p1 MAIN>";
        else if (prog_on)
            result = "<p1 PROG>";
        else
            result = "<p0>";
        return result;
    }

    void emergencyStop(DccExParser::TrackInterface& _trackInterface)
    {
        _trackInterface.turnOffTrack(TrackInterface::TackType::eMain);
        _trackInterface.turnOffTrack(TrackInterface::TackType::eProg);
        _trackInterface.turnOffTrack(TrackInterface::TackType::eJoin);
    }
}