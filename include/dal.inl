template< typename Key, typename Data, typename KeyComparator > 
DAL<Key,Data,KeyComparator>::DAL(unsigned int _MaxSz){
	mpt_Data = new NodeAL[_MaxSz];
	mi_Capacity = _MaxSz;
	mi_Length = 0;
}

template< typename Key, typename Data, typename KeyComparator > 
bool DAL<Key,Data,KeyComparator>::remove(const Key & k_, Data & d_){
	int result = this->_search(k_); 
	if( result == -1 ) return false;
	
	if( mi_Length <= 0 ){
		d_ = mpt_Data[result-1].info;
		--mi_Length; 
		return false;
	}
	
	d_ = mpt_Data[result].info;
	
	int tmp(mi_Length-1);
	mpt_Data[result] = mpt_Data[tmp];
	--mi_Length;
	return true;
}

template< typename Key, typename Data, typename KeyComparator > 
bool DAL<Key,Data,KeyComparator>::search(const Key & k_, Data & d_){
	int result = this->_search(k_); 
	if( result == -1 ) return false;
	d_ = mpt_Data[result].info;
	return true;
}

template< typename Key, typename Data, typename KeyComparator > 
int DAL<Key,Data,KeyComparator>::_search(const Key & _x) const{
	for( auto i(0u); i < mi_Length; ++i ){
		if( mpt_Data[i].id == _x ) return i;
	}

	return -1;
}

template< typename Key, typename Data, typename KeyComparator > 
bool DAL<Key,Data,KeyComparator>::insert(const Key & k_, const Data & d_){
	auto result(this->_search(k_));
	if( result != -1 || this->fullSize() ) return false;

	mpt_Data[mi_Length++] = NodeAL(k_, d_);

	return true;
}

template< typename Key, typename Data, typename KeyComparator > 
Key DAL<Key,Data,KeyComparator>::min(void) const{
	if( this->empty() ){
		throw std::out_of_range("empty");
	} 

	Key work = mpt_Data[0].id;

	for(auto i(0u); i < mi_Length; ++i){
		if( KeyComparator()(mpt_Data[i].id, work) ) 
			work = mpt_Data[i].id;
	}

	return work;
}	

template< typename Key, typename Data, typename KeyComparator > 
Key DAL<Key,Data,KeyComparator>::max(void) const{
	if( this->empty() ){
		throw std::out_of_range("empty");
	} 

	Key work = mpt_Data[0].id;

	for(auto i(0u); i < mi_Length; ++i){
		if( not KeyComparator()(mpt_Data[i].id, work) ) 
			work = mpt_Data[i].id;
	}
	return work;
}

template< typename Key, typename Data, typename KeyComparator > 
bool DAL<Key,Data,KeyComparator>::successor( const Key & k_, Key & n_k) const{

	int result = this->_search(k_);

	if( result == -1 || (unsigned int)result == mi_Length || this->empty() ) return false;
	n_k = mpt_Data[result+1].id;

	return true;
}

template< typename Key, typename Data, typename KeyComparator > 
bool DAL<Key,Data,KeyComparator>::predecessor( const Key & k_, Key & n_k) const{
	int result = this->_search(k_);
	if( result == -1 || result-1 < 0 ) return false;
	n_k = mpt_Data[result-1].id;
	return true;
}