#include <algorithm>
#include <numeric>
#include <iostream>

namespace ELI {
  template <template <typename...> class CONTAINER, typename TYPE, typename... TS, typename OPERATION>
    auto map(const CONTAINER<TYPE, TS...> &col, const OPERATION &op){
      CONTAINER<decltype(op((*col.begin())))> ret;
      std::transform(col.begin(), col.end(), std::back_inserter(ret), op);
      return ret;
    };
  template <template <typename...> class CONTAINER, typename TYPE, typename... TS, typename OPERATION>
    auto filter(const CONTAINER<TYPE, TS...> &col, const OPERATION &predicate){
      CONTAINER<TYPE> ret;
      std::copy_if(col.begin(), col.end(), std::back_inserter(ret),predicate);
      return ret;
    };
  template <template <typename...> class CONTAINER, typename TYPE, typename ACC_TYPE, typename... TS,  typename OPERATION>
    auto reduce(const CONTAINER<TYPE, TS...> &col, const OPERATION &reducer, ACC_TYPE acc){
      return std::accumulate(col.begin(), col.end(), acc, reducer);  
    };
}


