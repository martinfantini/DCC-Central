#ifndef __COMMON_LOCO_CACHE_HPP__
#define __COMMON_LOCO_CACHE_HPP__

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>

#include "Loco.hpp"

namespace Common::LocoInformation
{
    struct IndexById {};
    struct IndexByAddress {};

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

            void insert(Loco Loco)
            {
                m_LocoMap.insert(Loco);
            }
    };
}

#endif
