#ifndef __CENTRAL_ACCESSORY_MANAGER_HPP__
#define __CENTRAL_ACCESSORY_MANAGER_HPP__

#include <mutex>
#include <DccExParser/TrackInterface.hpp>

namespace Central
{
    class TrackManager : public DccExParser::TrackInterface
    {
        public:
            TrackManager(std::mutex& main_track_mutex,std::mutex& programming_track_mutex);

            virtual bool isTrackEnabled(TackType eTrack) override;
            virtual bool isTrackOn(TackType eTrack) override;
            virtual void turnOnTrack(TackType eTrack) override;
            virtual void turnOffTrack(TackType eTrack) override;

            bool IsMainOn();
            bool IsProgrammingOn();

            bool HasMain();
            bool HasProgramming();

        private:
            // mutex to access to the progarming staff
            std::mutex& programming_track_mutex;
            // mutex to access to the main staff
            std::mutex& main_track_mutex;

            bool has_Main = false;
            bool bool has_Programming = false;

            bool enable_Main = true;
            bool bool enable_Programming = true;

            bool bool is_Main_On = false;
            bool bool is_Programming_On = false;
    };
}

#endif
