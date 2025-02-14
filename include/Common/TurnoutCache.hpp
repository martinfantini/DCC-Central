#ifndef __COMMON_TURNOUT_CACHE_HPP__
#define __COMMON_TURNOUT_CACHE_HPP__

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>

#include "Turnout.hpp"
#include "IndexHelper.hpp"

namespace Common
{
    typedef 
        boost::multi_index_container<
            Turnout, //The data type stored
                boost::multi_index::indexed_by<
                    boost::multi_index::hashed_unique<
                        boost::multi_index::tag<IndexByPin>,
                        boost::multi_index::member<Turnout, int, &Turnout::Pin>
                    >,
                    boost::multi_index::hashed_unique<
                        boost::multi_index::tag<IndexById>,
                        boost::multi_index::member<Turnout, int, &Turnout::Id>
                    >,
                    boost::multi_index::hashed_unique<
                        boost::multi_index::tag<IndexByAddress>,
                        boost::multi_index::member<Turnout, int, &Turnout::Address>
                    >
            >
        > TurnoutMap;

    class TurnoutCache
    {
        private:
            TurnoutMap m_TurnoutCache;

        public:
            TurnoutCache() {}
            ~TurnoutCache() {}

            bool IsEmpty() const
            {
                return m_TurnoutCache.empty();
            }

            Turnout* GetTurnoutById(int Id) const
            {
                auto& indexById = m_TurnoutCache.get<IndexById>();
                auto iter = indexById.find(Id);
                if (iter != indexById.end()) return &iter.get_node()->value();

                return nullptr;
            }

            Turnout* GetTurnoutByAddress(int Address) const
            {
                auto& indexByAddress = m_TurnoutCache.get<IndexByAddress>();
                auto iter = indexByAddress.find(Address);
                if (iter != indexByAddress.end()) return &iter.get_node()->value();

                return nullptr;
            }

            Turnout* GetTurnoutByPin(const int pin) const
            {
                auto& indexById = m_TurnoutCache.get<IndexByPin>();
                auto iter = indexById.find(pin);
                if (iter != indexById.end()) return &iter.get_node()->value();

                return nullptr;
            }

            void Insert(Turnout turnout)
            {
                m_TurnoutCache.insert(turnout);
            }
    };
}

#endif
