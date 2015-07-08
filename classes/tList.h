#ifndef TLIST_H_
#define TLIST_H_

#include <malloc.h>

#define minFunc(a, b) (((a) < (b)) ? (a) : (b))
#define maxFunc(a, b) (((a) > (b)) ? (a) : (b))

template <class T> class tList
{
private:
    int nItems,maxItems;
    void checkMem(int newItems);
    T **list;

public:
    tList();
    tList(const tList<T>& rhs);

    ~tList();

    T at(int index) const;
    void setAt(int index,T value);
    T last(void) const;
    int count(void) const;
    bool isEmpty(void) const;

    void prepend(T item);
    void append(T item);
    void append(const tList<T>& item);
    void insert(int index, T item);
    void move(int from, int to);
    int firstIndexOf(T item) const;
    int lastIndexOf(T item) const;
    void removeAll(T item);
    void removeFirst(T item);
    void removeLast(T item);
    void removeAt(int index);
    void removeDublicates(void);
    void reverse(void);
    void clear(void);
    int contains(T item) const;
    void copyList(const tList<T> *l);
    bool isEqualTo(const tList<T>& l) const;

    tList<T>& operator = (const tList<T>& b);
    bool operator == (const tList<T>& other) const;

};


template <class T> tList<T>::tList()
{
	nItems = 0;
	maxItems = 0;
	list = NULL;
}

template <class T> tList<T>::tList(const tList<T>& rhs){
  nItems = 0;
  maxItems = 0;
  list = NULL;
  copyList(&rhs);
}

//-----------------------------------------------------------------------------

template <class T> tList<T>::~tList()
{
  clear();
};

//-----------------------------------------------------------------------------

template <class T> void tList<T>::checkMem(int newItems)
{
	int i;
	T **newList;
	if (nItems+newItems >= maxItems && nItems+newItems > 0 ){
		maxItems = (int)((float)(nItems+newItems) *1.1);
	  newList = (T**)malloc(maxItems*sizeof(T*));
		for (i=0;i<nItems;i++){
			newList[i] = list[i];
		}
		free(list);
		list = newList;
	} else if (newItems <= 0 && (float)(nItems+1*newItems)*1.1 < (float)maxItems ){
		maxItems = maxFunc(nItems+newItems,1);
		list = (T**)realloc(list,maxItems*sizeof(T*));
	}
}
//-----------------------------------------------------------------------------

template <class T> T tList<T>::at(int index) const
{
	if (index >= 0 &&index < nItems){
 		return *list[index];
	} else {
		// Hier hat wohl jemand auf ein nicht vorhandenes Element zugegriffen;
		return *list[0];
	}
}
//-----------------------------------------------------------------------------

template <class T> void tList<T>::setAt(int index,T value)
{
	*list[index] = value;
}
//-----------------------------------------------------------------------------

template <class T> T tList<T>::last(void) const
{
	return *list[nItems-1];
}
//-----------------------------------------------------------------------------

template <class T> int tList<T>::count(void) const
{
	return nItems;
}
//-----------------------------------------------------------------------------

template <class T> bool tList<T>::isEmpty(void) const
{
	if (nItems == 0){
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

template<class T>	int tList<T>::contains(T item) const
{
    int i, count = 0;
	for (i=0;i<nItems;i++){
		if (*list[i] == item){
            count++;
		}
	}
    return count;
}
//-----------------------------------------------------------------------------

template <class T> void tList<T>::prepend(T item)
{
	int i;
	checkMem(1);
	nItems ++;
	for (i=nItems-1;i>0;i--){
	  list[i] = list[i-1];
	}
  T* itemPtr = new T(item);
	list[0] = itemPtr;
}
//-----------------------------------------------------------------------------

template <class T> void tList<T>::append(T item)
{
	checkMem(1);
	T* itemPtr = new T(item);
	list[nItems] = itemPtr;
  nItems ++;
}
//-----------------------------------------------------------------------------

template <class T> void tList<T>::append(const tList<T>& l)
{
  checkMem(l.count());
  for (int i=0; i<l.count(); i++){
    T item = l.at(i);
    T* itemPtr = new T(item);
    list[nItems] = itemPtr;
    nItems ++;
  }
}
//-----------------------------------------------------------------------------

template <class T> void tList<T>::insert(int index, T item)
{
	int i;
	checkMem(1);
	index = minFunc(index,nItems);
	index = maxFunc(index,0);
	nItems ++;
	for (i=nItems-1;i>index;i--){
	  list[i] = list[i-1];
	}
  T* itemPtr = new T(item);
	list[index] = itemPtr;
}
//-----------------------------------------------------------------------------

template <class T> void tList<T>::move(int from, int to)
{
	T* help;
	int i;
	if (from >=0 && from < nItems && to>=0 && to < nItems){
		if (from > to){
			help = list[from];
			for (i=from;i>to;i--){
				list[i]=list[i-1];
			}
			list[to] = help;
		} else if (from < to){
			help = list[from];
			for (i=from;i<to;i++){
				list[i]=list[i+1];
			}
			list[to]=help;
		}
	}
}
//-----------------------------------------------------------------------------

template <class T> int tList<T>::firstIndexOf(T item) const
{
	int i;
	for (i=0;i<nItems;i++){
		if (*list[i] == item){
			return i;
		}
	}
	return -1;
}
//-----------------------------------------------------------------------------

template <class T> int tList<T>::lastIndexOf(T item) const
{
	int i;
	for (i=nItems-1;i>=0;i--){
		if (*list[i] == item){
			return i;
		}
	}
	return -1;
}
//-----------------------------------------------------------------------------

template <class T> void tList<T>::removeAll(T item)
{
	int i, found=0;
	for (i=0;i<nItems-1;i++){
		if (*list[i] == item){
	    delete list[i];
			found++;
		}
		list[i] = list[i+found];
	}
	if (nItems>0 && *list[i] == item){
		found++;
	}
	nItems -= found;
	checkMem(0);
}
//-----------------------------------------------------------------------------

template <class T> void tList<T>::removeFirst(T item)
{
  removeAt(firstIndexOf(item));
	checkMem(0);
}
//-----------------------------------------------------------------------------

template <class T> void tList<T>::removeLast(T item)
{
  removeAt(lastIndexOf(item));
	checkMem(0);
}
//-----------------------------------------------------------------------------

template <class T> void tList<T>::removeAt(int index)
{
	int i;
  if (index >= 0 && index < nItems){
    delete list[index];
    for (i=index;i<nItems-1;i++){
      list[i] = list[i+1];
    }
    nItems--;
    checkMem(0);
  }
}
//-----------------------------------------------------------------------------
template <class T> void tList<T>::removeDublicates(void)
{
    tList orig;
    orig = *this;
    clear();
    for (int i=0; i<orig.count(); i++) {
        if (!contains( orig.at(i)) ) {
            append(orig.at(i));
        }
    }
}
//-----------------------------------------------------------------------------

template <class T> void tList<T>::reverse(void)
{
	T **newList;
	int i;

  newList = (T**)malloc(maxItems*sizeof(T*));
  for (i=0;i<nItems;i++){
    newList[i] = list[nItems-i-1];
  }
  free(list);
  list = newList;
}
//-----------------------------------------------------------------------------

template <class T> void tList<T>::clear(void)
{
  if (list){
    for (int i=0;i<nItems;i++){
      delete list[i];
    }
    free(list);
    list = NULL;
  }
  nItems = 0;
  maxItems = 0;
}
//-----------------------------------------------------------------------------

template <class T> void tList<T>::copyList(const tList<T> *l)
{
  int i;
  clear();
  checkMem(l->count());
  for (i=0;i<l->count();i++){
    T* itemPtr = new T(l->at(i));
    list[i] = itemPtr;
    nItems++;
  }
}
//-----------------------------------------------------------------------------

template <class T> tList<T>& tList<T>::operator= (const tList<T>& b)
{
  int i;
  clear();
  for (i=0;i<b.count();i++){
    T item = b.at(i);
    append(item);
  }
  return *this;
}

template <class T> bool tList<T>::operator == (const tList<T>& other) const
{
  return isEqualTo(other);
}

//-----------------------------------------------------------------------------

template <class T> bool tList<T>::isEqualTo(const tList<T>& l) const
{
  if (l.count() != this->count()){
    return false;
  }
  for (int i=0;i<l.count();i++){
    if (at(i) != l.at(i)){
      return false;
    }
  }
  return true;
}

//-----------------------------------------------------------------------------

#endif /*TLIST_H_*/
