template< typename Key, typename Data, typename KeyComparator >
bool DSAL<Key, Data, KeyComparator>::remove(const Key & k_, Data & d_){
	int result = this->_search(k_); 

	d_ = DSAL::mpt_Data[result].info;

	if( result == -1 || this->DSAL::empty() ) return false;
	
	for(unsigned int i(result); i < DSAL::mi_Length-1; ++i)	
		DSAL<Key, Data, KeyComparator>::mpt_Data[i] = DSAL<Key, Data, KeyComparator>::mpt_Data[i+1];

	--DSAL::mi_Length;
	
	return true;
}

template< typename Key, typename Data, typename KeyComparator >
bool DSAL<Key, Data, KeyComparator>::insert(const Key & k_, const Data & d_){
	if( this->_search(k_) != -1 || this->fullSize() ) return false;

	if( this->empty() ){
		DSAL::mpt_Data[0].id = k_;
		DSAL::mpt_Data[0].info = d_;
		++DSAL::mi_Length;
		return true;
	}
	auto i(0u);

	while( KeyComparator()(DSAL::mpt_Data[i].id, k_) and i < DSAL::mi_Length ) ++i;
	

	for(auto ii(DSAL::mi_Length); ii > i; --ii){
		DSAL::mpt_Data[ii] = DSAL::mpt_Data[ii-1];
	}

	DSAL::mpt_Data[i].id = k_;
	DSAL::mpt_Data[i].info = d_;
	++DSAL::mi_Length;
	return true;	
}

template< typename Key, typename Data, typename KeyComparator >
Key DSAL<Key, Data, KeyComparator>::min(void) const{
	if( this->empty() ){
		throw std::out_of_range("empty");
	} 
	return DSAL::mpt_Data[0].id;
}

template< typename Key, typename Data, typename KeyComparator >
Key DSAL<Key, Data, KeyComparator>::max(void) const{
	if( this->empty() ){
		throw std::out_of_range("empty");
	} 
	return DSAL::mpt_Data[DSAL::mi_Length-1].id;
}

template< typename Key, typename Data, typename KeyComparator > 
bool DSAL<Key,Data,KeyComparator>::search(const Key & k_, Data & d_){
	int result = this->_search(k_); 
	if( result == -1 ) return false;
	d_ = DSAL::mpt_Data[result].info;
	return true;
}

template< typename Key, typename Data, typename KeyComparator >
int DSAL<Key, Data, KeyComparator>::_search(const Key & _x) const{

	if(this->empty()) return -1;
	int first = 0;
	int last =  DSAL::mi_Length - 1;

	while ( first <= last )
	{
		int mid = (first + last)/2;
		Key key_test = DSAL::mpt_Data[ mid ].id;

		if( ! KeyComparator()( _x, key_test )  and  ! KeyComparator()( key_test, _x )  )
			return mid;
		else if( KeyComparator()( _x, key_test ) )
			last = mid-1;
		else
			first = mid+1;
	}
	return -1;
}