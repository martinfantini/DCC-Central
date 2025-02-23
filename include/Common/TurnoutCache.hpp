#ifndef __COMMON_TURNOUT_CACHE_HPP__
#define __COMMON_TURNOUT_CACHE_HPP__

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/composite_key.hpp>

#include "Turnout.hpp"
#include "IndexHelper.hpp"

namespace Common
{
    typedef 
        boost::multi_index_container<
            Turnout, //The data type stored
                boost::multi_index::indexed_by<
                    boost::multi_index::hashed_unique<
                        boost::multi_index::tag<IndexById>,
                        boost::multi_index::member<Turnout, int, &Turnout::Id>
                    >,
                    boost::multi_index::hashed_unique<
                        boost::multi_index::tag<IndexByAddressSubAddress>,
                        boost::multi_index::composite_key<
                            Turnout,
                            boost::multi_index::member<Turnout, int, &Turnout::Address>,
                            boost::multi_index::member<Turnout, int, &Turnout::SubAddress>
                        >
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

            Turnout* GetTurnoutByAddressSubAddress(int Address, int SubAddress = 0) const
            {
                auto& indexByAddress = m_TurnoutCache.get<IndexByAddressSubAddress>();
                auto iter = indexByAddress.find(std::make_tuple(Address, SubAddress));
                if (iter != indexByAddress.end()) return &iter.get_node()->value();
                return nullptr;
            }

            void Insert(Turnout turnout)
            {
                m_TurnoutCache.insert(turnout);
            }

            void RemoveTurnoutById(int Id)
            {
                auto& indexById = m_TurnoutCache.get<IndexById>();
                auto iter = indexById.find(Id);
                if (iter != indexById.end()) 
                    indexById.erase(iter);
            }

            // Status: 1: Close 0: Throw
            void SetStatusById(int Id, bool Status)
            {
                auto& indexById = m_TurnoutCache.get<IndexById>();
                auto iter = indexById.find(Id);
                if (iter != indexById.end())
                {
                    if (Status)
                        iter.get_node()->value().Status = StatusTurnout::Close;
                    else
                        iter.get_node()->value().Status = StatusTurnout::Throw;
                }
            }

            // Bool Status: 1: Close 0: Throw
            const std::unordered_map<int, bool> getStatus()
            {
                std::unordered_map<int, bool> result_map;
                for(auto first=m_TurnoutCache.begin(), last=m_TurnoutCache.end(); first!=last;)
                {
                    auto turnout = first.get_node()->value();
                    if(turnout.Status != StatusTurnout::StatusTurnout_None)
                    {
                        if(turnout.Status == StatusTurnout::Close)
                            result_map.emplace(turnout.Id, true);
                        else
                            result_map.emplace(turnout.Id, false);
                    }
                }
                return result_map;
            }

            // Status: 1: Close 0: Throw
            void SetStatusByPin(int Pin, bool Status)
            {
                for(auto first=m_TurnoutCache.begin(), last=m_TurnoutCache.end(); first!=last;)
                {
                    auto& turnout = first.get_node()->value();
                    // this is the normal case, it is not configured
                    if(turnout.Pin == 0)
                        continue;

                    if(turnout.Pin == Pin)
                    {
                        if (Status)
                            turnout.Status = StatusTurnout::Close;
                        else
                            turnout.Status = StatusTurnout::Throw;
                    }
                }
            }

            const std::vector<Turnout> TurnoutVector()
            {
                std::vector<Turnout> turnout_vector;
                for(auto first=m_TurnoutCache.begin(), last=m_TurnoutCache.end(); first!=last;)
                    turnout_vector.push_back(first.get_node()->value());
                return turnout_vector;
            }
    };
}

#endif
