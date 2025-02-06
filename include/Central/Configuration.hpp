#ifndef __CENTRAL_CONFIGURATION_HPP__
#define __CENTRAL_CONFIGURATION_HPP__

#include <string>

#include "Helpers.hpp"

namespace Configuration
{
    class Config
    {
    public:
        // <!----- DCCPlus Config ----->
        const Helpers::DCCPlus& getDCC() const
        {
            return _dccPlus;
        }

        void setDCC(const ::Helpers::DCCPlus& dccPlus)
        {
            _dccPlus = dccPlus;
            _dccPlus.enabled = true;            
        }

        bool isDCCEnabled()
        {
            return _dccPlus.enabled;
        }

        // <!----- RestApi Config ----->
        const Helpers::RestApi& getRestApi() const
        {
            return _restApi;
        }

        void setRestApi(const Helpers::RestApi& restApi)
        {
            _restApi = restApi;
            _restApi.enabled = true;            
        }

        bool isRestApiEnabled()
        {
            return _restApi.enabled;
        }
    
        // <!----- Logger Config ----->
        const Helpers::Logger& getLogger() const
        {
            return _logger;
        }

        void setLogger(const Helpers::Logger& logger)
        {
            _logger = logger;
            _logger.enabled = true;
        }

        bool isLoggerEnabled()
        {
            return _logger.enabled;
        }

        // <!----- Tracks Config ----->

        void setProgramingTrack(const Helpers::Track& programingTack)
        {
            _programingTrack = programingTack;
        }

        const Helpers::Track& getProgramingTrack()
        {
            return _programingTrack;
        }

        void setMainTrack(const Helpers::Track& mainTack)
        {
            _mainTrack = mainTack;
        }

        const Helpers::Track& getMainTrack()
        {
            return _mainTrack;
        }
        
        friend std::ostream& operator<<(std::ostream& os, const Configuration::Config& config);

    private:
        Helpers::DCCPlus _dccPlus;
        Helpers::RestApi _restApi;
        Helpers::Logger _logger;
        Helpers::Track  _mainTrack;
        Helpers::Track  _programingTrack;
    };
} // namespace Configuration

#endif
