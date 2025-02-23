#ifndef __COMMON_LOCO_CACHE_HPP__
#define __COMMON_LOCO_CACHE_HPP__

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/member.hpp>

#include "Loco.hpp"
#include "IndexHelper.hpp"

namespace Common
{
    typedef 
        boost::multi_index_container<
            Loco, //The data type stored
                boost::multi_index::indexed_by<
                    boost::multi_index::hashed_unique<
                        boost::multi_index::tag<IndexById>,
                        boost::multi_index::member<Loco, int, &Loco::Id>
                >,
                    boost::multi_index::hashed_unique<
                        boost::multi_index::tag<IndexByAddress>,
                        boost::multi_index::member<Loco, int, &Loco::Address>
                >,
                    boost::multi_index::hashed_unique<
                        boost::multi_index::tag<IndexByIdAndAddress>,
                        boost::multi_index::composite_key<
                            Loco,
                            boost::multi_index::member<Loco, int, &Loco::Id>,
                            boost::multi_index::member<Loco, int, &Loco::Address>
                        >
                >
            >
        > LocoMap;

    class LocoCache
    {
        private:
            LocoMap m_LocoMap;

        public:
            LocoCache() {}
            ~LocoCache() {}

            bool IsEmpty() const
            {
                return m_LocoMap.empty();
            }

            Loco* GetLocoByAddress(int Address) const
            {
                auto& indexByAddress = m_LocoMap.get<IndexByAddress>();
                auto iter = indexByAddress.find(Address);
                if (iter != indexByAddress.end()) return &iter.get_node()->value();
                return nullptr;
            }

            Loco* GetLocoById(const int id) const
            {
                auto& indexById = m_LocoMap.get<IndexById>();
                auto iter = indexById.find(id);
                if (iter != indexById.end()) return &iter.get_node()->value();
                return nullptr;
            }

            Loco* GetLocoByIdAddress(int Id, int Address) const
            {
                auto& indexByIdAddress = m_LocoMap.get<IndexByIdAndAddress>();
                auto iter = indexByIdAddress.find(std::make_tuple(Id, Address));
                if (iter != indexByIdAddress.end()) return &iter.get_node()->value();
                return nullptr;
            }

            void EmergencyStop()
            {
                for(Loco& loco : m_LocoMap)
                    loco.SpeedSteps = 1;
            }

            void EmergencyStopById(int Id)
            {
                auto& indexById = m_LocoMap.get<IndexById>();
                auto iter = indexById.find(id);
                if (iter != indexById.end()) 
                    return iter.get_node()->value().SpeedSteps = 1;
            }

            void Insert(Loco Loco)
            {
                m_LocoMap.insert(Loco);
            }

            void RemoveLocoById(int locoId)
            {
                auto& indexById = m_LocoMap.get<IndexById>();
                auto iter = indexById.find(id);
                if (iter != indexById.end())
                {
                    indexById.erase(iter);
                }
            }

            void ClearCache()
            {
                m_LocoMap.clear();
            }

            const std::vector<Loco> LocoVector()
            {
                std::vector<Loco> loco_vector;
                for(Loco& loco : m_LocoMap)
                    loco_vector.push_back(loco);
                return loco_vector;
            }
    };
}

#endif
