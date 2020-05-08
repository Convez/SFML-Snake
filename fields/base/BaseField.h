//
// Created by convez on 05/05/2020.
//

#ifndef SIMPLESNAKE_BASEFIELD_H
#define SIMPLESNAKE_BASEFIELD_H

#include <stdexcept>
#include <sstream>

namespace convez::lib::fields::base {

template<class T>
class BaseField {
public:
    BaseField();

    explicit BaseField(const T& iValue);

    BaseField(const BaseField& iOther);

    bool isValid();

    void set(const T& iValue);

    T get() const;

    void invalidate();

    bool operator==(const BaseField<T>& iOther) const;

    bool operator<(const BaseField<T>& iOther) const;

private:
    bool _isValid;
    T _value;
};

template<class T>
BaseField<T>::BaseField():
        _isValid(false) {
}

template<class T>
BaseField<T>::BaseField(const T& iValue):
        _isValid(true),
        _value(iValue) {
}

template<class T>
BaseField<T>::BaseField(const BaseField& iOther):
        _isValid(iOther._isValid),
        _value(iOther._value) {
}

template<class T>
bool BaseField<T>::isValid() {
    return _isValid;
}

template<class T>
void BaseField<T>::set(const T& iValue) {
    _isValid = true;
    _value = iValue;
}

template<class T>
T BaseField<T>::get() const {
    if (!isValid()) {
        std::stringstream aSs;
        aSs << typeid(BaseField<T>).name() << ": Value is not set" << std::endl;
        throw std::runtime_error(aSs.str());
    }
    return _value;
}

template<class T>
void BaseField<T>::invalidate() {
    _isValid = false;
}

template<class T>
bool BaseField<T>::operator==(const BaseField<T>& iOther) const {
    return _isValid == iOther._isValid && _value == iOther._value;
}

template<class T>
bool BaseField<T>::operator<(const BaseField<T>& iOther) const {
    if (_isValid < iOther._isValid)
        return true;
    else if (_isValid > iOther._isValid)
        return false;
    return _value < iOther._value;
}

}

#endif //SIMPLESNAKE_BASEFIELD_H
