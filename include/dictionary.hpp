/**!
* @file dictionary.hpp
* @author Israel Fontes
* @brief Implementação da estrutura de dados Dicionario (Dictionary).
*/


#ifndef _DICTIONARY_HPP_
#define _DICTIONARY_HPP_

#include <functional>
#include <string>
#include <algorithm>

template< typename Key, typename Data, typename KeyComparator = std::less<int> > 
class DAL{

	protected:
		struct NodeAL{
			Key id;
			Data info;
			NodeAL(Key _id, Data _d): id(_id), info(_d){/* Empty */}
			NodeAL(){}
		};

		static const unsigned int SIZE=50;
		unsigned int mi_Length;
		unsigned int mi_Capacity;
		NodeAL * mpt_Data;

		int _search(const Key & _x) const;

	public:

		DAL( unsigned int _MaxSz = SIZE );
		virtual ~DAL(){ delete [] mpt_Data; };
		bool remove( const Key & k_, Data & d_ );
		bool search( const Key & k_, Data & d_ );
		bool insert( const Key & k_, const Data & d_ );
		Key min( void ) const;
		Key max( void ) const;
		bool successor( const Key & k_, Key & n_k ) const;
		bool predecessor( const Key & k_, Key & n_k ) const;
		bool empty(void) const{ return mi_Length == 0; }
		bool fullSize(void) { return mi_Length == mi_Capacity; }
		unsigned int capacity(void){ return mi_Capacity; }
		
			friend std::ostream &operator<<(std::ostream &_o, const DAL& _oList){
			_o << "[ ";
			for(auto i(0u); i < _oList.mi_Length; ++i){
				_o 	<< "{id: " << _oList.mpt_Data[i].id << ", info: "
					<< _oList.mpt_Data[i].info << "} ";
			}
			_o << "]";
			return _o;		
		}
};

template< typename Key, typename Data, typename KeyComparator = std::less<int> > 
class DSAL : public DAL<Key, Data, KeyComparator> {
	
	public:
		DSAL(unsigned int _MaxSz = DAL<Key, Data, KeyComparator>::SIZE): DAL<Key, Data, KeyComparator>(_MaxSz){ }
		virtual ~DSAL(){}
		bool remove(const Key & k_, Data & d_);
		bool insert(const Key & k_, const Data & d_);
		bool search( const Key & k_, Data & d_ );
		Key min(void) const;
		Key max(void) const;
	private:
		int _search(const Key & _x) const;


};

#include "dal.inl"
#include "dsal.inl"

#endif