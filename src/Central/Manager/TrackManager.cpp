#include <Manager/TrackManager.hpp>

#include <glog/logging.h>

#pragma message("TODO TrackManager" __FILE__)

namespace Central
{
    TrackManager::TrackManager(std::mutex& main_track_mutex,std::mutex& programming_track_mutex)
        : main_track_mutex(main_track_mutex), programming_track_mutex(programming_track_mutex)
    {}

    bool TrackManager::isTrackEnabled(TackType eTrack)
    {
        return true;
    }

    bool TrackManager::isTrackOn(TackType eTrack)
    {
        return true;
    }

    void TrackManager::turnOnTrack(TackType eTrack)
    {

    }

    void TrackManager::turnOffTrack(TackType eTrack)
    {


    }

    bool TrackManager::IsMainOn()
    {
        if (!has_Main)
            return false;

        {
            const std::lock_guard<std::mutex> lock_cache(main_track_mutex);
            return is_Main_On;
        }
    }

    bool TrackManager::IsProgrammingOn()
    {
        if (!has_Programming)
            return false;

        {
            const std::lock_guard<std::mutex> lock_cache(programming_track_mutex);
            if (!enable_Programming)
                return false;

            return is_Programming_On;
        }
    }

    bool TrackManager::HasMain()
    {
        return has_Main;
    }

    bool TrackManager::HasProgramming()
    {
        return has_Programming;
    }
}
