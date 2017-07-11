
//
// CS251 Data Structures
// Hash Table
//

#include <assert.h>
#include <stdlib.h>
#include <string.h>

// Each hash entry stores a key, object pair
template <typename Data>
struct HashTableTemplateEntry {
  const char * _key;
  Data _data;
  HashTableTemplateEntry * _next;
};

// This is a Hash table that maps string keys to objects of type Data
template <typename Data>
class HashTableTemplate {
 public:
  // Number of buckets
  enum { TableSize = 2039};
  
  // Array of the hash buckets.
  HashTableTemplateEntry<Data> **_buckets;
  
  // Obtain the hash code of a key
  int hash(const char * key);
  
 public:
  HashTableTemplate();
  ~HashTableTemplate();
  // Add a record to the hash table. Returns true if key already exists.
  // Substitute content if key already exists.
  bool insertItem( const char * key, Data data);

  // Find a key in the dictionary and place in "data" the corresponding record
  // Returns false if key is does not exist
  bool find( const char * key, Data * data);

  // Removes an element in the hash table. Return false if key does not exist.
  bool removeElement(const char * key);

  // Returns the data that corresponds to this index.
  // Data is initialized to 0s if the entry does not exist
  Data operator[] (const char * &key);
};

template <typename Data>
int HashTableTemplate<Data>::hash(const char * key)
{
  int h = 0;
  const char * p = key;
  while (*p) {
    h += *p;
    p++;
  }
  return h % TableSize;
}

template <typename Data>
HashTableTemplate<Data>::HashTableTemplate()
{
	_buckets = new HashTableTemplateEntry <Data> * [TableSize];

  for(int i=0;i<TableSize;i++){

    _buckets[i] = NULL;

  }

  // Add implementation here
}

template <typename Data>
HashTableTemplate<Data>::~HashTableTemplate()
{
  for(int i=0;i<TableSize;i++){
		HashTableTemplateEntry <Data> * ent = _buckets[i];
		HashTableTemplateEntry <Data> * temp = ent;
		while(ent!=NULL){
			free((char * )ent->_key);
			temp = ent->_next;
			delete ent;
			ent = temp;
		}
	}
  delete [] _buckets;
  // Add implementation here
}



template <typename Data>
bool HashTableTemplate<Data>::insertItem( const char * key, Data data)
{
  // Add implementation here
  int h = hash(key);

  HashTableTemplateEntry <Data> * node = _buckets[h];

  if(node==NULL){
    HashTableTemplateEntry <Data> * ent = new HashTableTemplateEntry<Data>();
    ent->_key = strdup(key);
    ent->_data = data;
    ent->_next = NULL;
    _buckets[h] = ent;
    return false;
  }else{
    while(node!=NULL){
      if(strcmp(node->_key,key)==0){
        node->_data = data;
        return true;
      }
      node = node->_next;
    }

    HashTableTemplateEntry <Data> * temp = new  HashTableTemplateEntry<Data>();
    temp->_data = data;
    temp->_key = strdup(key);
    temp->_next = _buckets[h];
    _buckets[h] = temp;
    return false;
  }

}

template <typename Data>
bool HashTableTemplate<Data>::find( const char * key, Data * data)
{
  // Add implementation here
  int h = hash(key);
  HashTableTemplateEntry<Data> * ent = _buckets[h];

  if(ent==NULL){
    return false;
  }else{
    while(ent!=NULL){
      if(strcmp(ent->_key,key)==0){
       * data = ent->_data;
        return true;
      }
      ent = ent->_next;
    }
    return false;
  }
}

template <typename Data>
Data HashTableTemplate<Data>::operator[] (const char * &key) {
  Data d;
  bool flag = find(key,&d);
  return d;
}

template <typename Data>
bool HashTableTemplate<Data>::removeElement(const char * key)
{
  // Add implementation here
  int h = hash(key);
  HashTableTemplateEntry<Data> * node = _buckets[h];
  HashTableTemplateEntry<Data> * prev = NULL;
  while(node!=NULL){
	  if(strcmp(node->_key,key)==0){
		  break;
	  }
	  prev = node;
	  node = node->_next;
  }

  if(node==NULL)
  	return false;
  if(prev==NULL){
	  _buckets[h] = node->_next;
  }else{
	  prev->_next = node->_next;
  }
  //free(node);
  delete node;
  return true;
}

template <typename Data>
class HashTableTemplateIterator {
  int _currentBucket;
  HashTableTemplateEntry<Data> *_currentEntry;
  HashTableTemplate<Data> * _hashTable;
 public:
  HashTableTemplateIterator(HashTableTemplate<Data> * hashTable);
  bool next(const char * & key, Data & data);
};

template <typename Data>
HashTableTemplateIterator<Data>::HashTableTemplateIterator(HashTableTemplate<Data> * hashTable)
{
  // Add implementation here
  _currentBucket = 0;
  this->_hashTable = hashTable;

  _currentEntry = hashTable->_buckets[_currentBucket];
}

template <typename Data>
bool HashTableTemplateIterator<Data>::next(const char * & key, Data & data)
{
  // Add implementation here
  while(_currentEntry==NULL){
   if(_currentBucket==_hashTable->TableSize){
    return false;
   }
   _currentEntry = _hashTable->_buckets[_currentBucket];
   _currentBucket++;

  }
  char * tempkey = strdup(_currentEntry->_key);
  data = _currentEntry->_data;
  key = tempkey;
  _currentEntry = _currentEntry->_next;
  delete tempkey;
  // Add implementation her
  return true;
}
