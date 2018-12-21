#include <vector>
#include <algorithm>

/////////////////////////////////////

template <typename RET_CONT, typename IN_CONT, typename OPERATION>
RET_CONT map(IT col, OPERATION op) {
  RET_CONT ret;
  std::transform(col.begin(), col.end(), back_inserter(ret), op);
  return ret;
}

////////////////////////////////////

template <typename IN_CONT, typename Predicate>
Collection filter(Collection col,Predicate predicate) {
   auto fnCol = filterNot(col,[predicate](typename Collection::value_type i) { return !predicate(i);});
    return fnCol; 
}

////////////////////////////////////

template <typename IN_CONT,typename Predicate>
IN_CONT reduce(Collection col,Predicate predicate) {
   auto fnCol = filterNot(col,[predicate](typename Collection::value_type i) { return !predicate(i);});
    return fnCol; 
}

////////////////////////////////////

template <typename IT,typename Condition>
bool exists(IT col, Condition con) {
     auto exist = std::find_if(col.begin(),col.end(),con);
        return exist != col.end();
}

/////////////////////////////////////

template <typename RET_CONT, typename IP_CONT, typename OPERATION>
void forEach(IP_CONT col, OPERATION op){
    std::for_each(col.begin(), col.end(), op);
}

////////////////////////////////////
