#ifndef __COMMON_SENSOR_CACHE_HPP__
#define __COMMON_SENSOR_CACHE_HPP__

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/member.hpp>

#include "Sensor.hpp"
#include "IndexHelper.hpp"

namespace Common
{
    typedef 
        boost::multi_index_container<
            Sensor,
                boost::multi_index::indexed_by<
                    boost::multi_index::hashed_unique<
                        boost::multi_index::tag<IndexById>,
                        boost::multi_index::member<Sensor, int, &Sensor::Id>
                    >,
                    boost::multi_index::hashed_unique<
                        boost::multi_index::tag<IndexByPin>,
                        boost::multi_index::member<Sensor, int, &Sensor::Pin>
                    >
                >
        > SensorMap;

    class SensorCache
    {
        private:
            SensorMap m_SensorMap;

        public:
            SensorCache() {}
            ~SensorCache() {}

            bool IsEmpty() const
            {
                return m_SensorMap.empty();
            }

            Sensor* GetSensorById(const int Id) const
            {
                auto& indexById = m_SensorMap.get<IndexById>();
                auto iter = indexById.find(Id);
                if (iter != indexById.end()) return &iter.get_node()->value();

                return nullptr;
            }

            Sensor* GetSensorByPin(const int Pin) const
            {
                auto& indexByPin = m_SensorMap.get<IndexByPin>();
                auto iter = indexByPin.find(Pin);
                if (iter != indexByPin.end()) return &iter.get_node()->value();

                return nullptr;
            }

            void Insert(Sensor Sensor)
            {
                m_SensorMap.insert(Sensor);
            }

            int size()
            {
                return m_SensorMap.size();
            }

            void RemoveById(int id)
            {
                auto& indexById = m_SensorMap.get<IndexById>();
                auto iter = indexById.find(id);
                if (iter != indexById.end())
                {
                    indexById.erase(iter);
                }
            }

            const std::vector<Sensor> SensorVector()
            {
                std::vector<Sensor> sensor_vector;
                for(auto first=m_SensorMap.begin(), last=m_SensorMap.end(); first!=last;)
                    sensor_vector.push_back(first.get_node()->value());
                return sensor_vector;
            }
            
    };
}

#endif
