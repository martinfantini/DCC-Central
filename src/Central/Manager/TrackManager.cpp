#include "Mananger/TrackManager.hpp"

#include <glog/logging.h>

namespace Central
{
    TrackManager::TrackManager(std::mutex& main_track_mutex,std::mutex& programming_track_mutex)
        : main_track_mutex(main_track_mutex), programming_track_mutex(programming_track_mutex)
    {}

    bool TrackManager::isTrackEnabled(TackType eTrack)
    {

    }

    bool TrackManager::isTrackOn(TackType eTrack)
    {

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


            bool enable_Main = true;
            bool bool enable_Programming = true;


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



            bool has_Main = false;
            bool bool has_Programming = false;

            bool bool is_Main_On = false;
            bool bool is_Programming_On = false;

    class TrackManager : public DccExParser::TrackInterface
    {
        public:

            enum TackType
            {
                eMain = 0,
                eProg,
                eJoin,
            };

            virtual bool isTrackEnabled(TackType eTrack) = 0;
            virtual bool isTrackOn(TackType eTrack) = 0;
            virtual void turnOnTrack(TackType eTrack) = 0;
            virtual void turnOffTrack(TackType eTrack) = 0;
            
        private:
            // mutex to access to the progarming staff
            std::mutex& programming_track_mutex;
            // mutex to access to the main staff
            std::mutex& main_track_mutex;
    };
}

#endif


            bool TrackManager::isTrackEnabled(TackType eTrack) override;
            bool TrackManager::isTrackOn(TackType eTrack) override;
            void TrackManager::turnOnTrack(TackType eTrack) override;
            void TrackManager::turnOffTrack(TackType eTrack) override;
            bool TrackManager::IsMainOn();
            bool TrackManager::IsProgrammingOn();

            bool TrackManager::HasMain();
            bool TrackManager::HasProgramming();

        private:
            // mutex to access to the progarming staff
            std::mutex& programming_track_mutex;
            // mutex to access to the main staff
            std::mutex& main_track_mutex;




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
            bool has_Programming = false;

            bool is_Main_On = false;
            bool is_Programming_On = false;
