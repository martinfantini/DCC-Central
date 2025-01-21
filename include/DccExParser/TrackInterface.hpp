#ifndef __DCC_EX_TRACK_INTERFACE_HPP__
#define __DCC_EX_TRACK_INTERFACE_HPP__

#include <string>

namespace DccExParser
{
    class TrackInterface
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
    };
}

#endif