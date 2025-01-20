#include <catch2/catch_test_macros.hpp>

#include "DccExCommadConverter.hpp"
#include "CommandManager.hpp"

TEST_CASE("Test DCC implemented commands")
{
    using namespace Common;
    using namespace DccExParser;

    // general data to test
    static int max_locos;

    class CommandManagerTester: public CommandManager
    {
        public:
            
            std::pair<bool, Loco> lookupLocos(int locoId, bool autoCreate = false)
            {
                return {true, {} };
            }
            void setThrottle(int cab, int tspeed, int direction)
            {}
            
            bool setFunction(int cab, int functionNumber, bool on)
            {
                return true;
            }
            
            int getMaxLocos()
            {
                return max_locos;
            }
    };

    std::string logger;
    DccExParser::string_function loggerFunction = [&logger](const std::string& logger_parser)
    {
        logger = logger_parser;
    };

    std::string commandResult;
    DccExParser::string_function commandFunction = [&commandResult](const std::string& command_result)
    {
        commandResult = command_result;
    };

    CommandManagerTester commandTester;
    DccExCommandParser dccParser(commandTester, commandFunction, loggerFunction);
    DCCBasicParser dccBasicParser(dccParser);

    SECTION("Test # case")
    {
        max_locos = 20;
        dccBasicParser.read_stream("<#>\n");
        CHECK(commandResult == "<# " + std::to_string(max_locos) +">\n");
    }

    SECTION("Test empty case")
    {

    }
}