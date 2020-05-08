//
// Created by convez on 05/05/2020.
//

#ifndef SIMPLESNAKE_BASEENUMFIELD_H
#define SIMPLESNAKE_BASEENUMFIELD_H

#include <tiff.h>
#include <map>
#include "BaseField.h"

namespace convez::lib::fields::base{
// Requires class T to have defined: typedef enum {k_Unknown, k_LastValue} Labels;
// Requires class T to have defined: static LabelToStringMap_t _LabelToStringMap;
template <class T>
class BaseEnumField: public BaseField<uint64>{
private:
    typedef uint64 LabelsType_t;
public:
    typedef std::map<LabelsType_t, std::string> LabelToStringMap_t;

    BaseEnumField(): BaseField<LabelsType_t>() {}
    explicit BaseEnumField(const LabelsType_t &iValue) : BaseField<LabelsType_t>(iValue) {}
    BaseEnumField(const BaseEnumField<T> &iOther) : BaseField<LabelsType_t>(iOther) {}

    std::string getAsString();
    void setFromString(const std::string& iStringValue);
};

template<class T>
std::string BaseEnumField<T>::getAsString() {
    LabelsType_t aLabel = BaseField<LabelsType_t>::get();
    typename LabelToStringMap_t::const_iterator aValueIter = T::_LabelToStringMap.find(aLabel);
    if(aValueIter == T::_LabelToStringMap.end())
    {
        std::stringstream aSs;
        aSs << typeid(BaseEnumField<T>).name() << "::getAsString Label "<< aLabel <<" not found in _LabelToStringMap" << std::endl;
        throw std::runtime_error(aSs.str());
    }
    return aValueIter->second;
}

template<class T>
void BaseEnumField<T>::setFromString(const std::string &iStringValue) {
    BaseField<LabelsType_t>::invalidate();
    for(typename LabelToStringMap_t::value_type& aLabelStringValue : T::_LabelToStringMap){
        if(aLabelStringValue.second == iStringValue)
        {
            BaseField<LabelsType_t>::set(aLabelStringValue.first);
            break;
        }
    }
    if(!BaseField<LabelsType_t>::isValid()){
        std::stringstream aSs;
        aSs << typeid(BaseEnumField<T>).name() << "::setFromString Label for string "<< iStringValue <<" not found in _LabelToStringMap" << std::endl;
        throw std::runtime_error(aSs.str());
    }
}
}


#endif //SIMPLESNAKE_BASEENUMFIELD_H
