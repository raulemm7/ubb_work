//
// Created by raulo on 4/10/2024.
//

#ifndef LAB06_ITERATORVECTOR_H
#define LAB06_ITERATORVECTOR_H

#include "definedVector.h"

template <typename ElementType>
class IteratorVectorDinamic{
private:
    const VectorDinamic<ElementType>& vectorDinamic;
    int pozitie;
public:
    explicit IteratorVectorDinamic(const VectorDinamic<ElementType>& vectorDinamic) : vectorDinamic{vectorDinamic}, pozitie{0}{};

    bool valid() const noexcept;

    ElementType element() const noexcept;

    void prim() noexcept;

    void next() noexcept;
};

template<typename ElementType>
bool IteratorVectorDinamic<ElementType>::valid() const noexcept {
    return pozitie < this->vectorDinamic.get_last_id_vd();
}

template<typename ElementType>
ElementType IteratorVectorDinamic<ElementType>::element() const noexcept {
    return this->vectorDinamic.get_element(this->pozitie);
}

template<typename ElementType>
void IteratorVectorDinamic<ElementType>::prim() noexcept {
    this->pozitie = 0;
}

template<typename ElementType>
void IteratorVectorDinamic<ElementType>::next() noexcept {
    this->pozitie++;
}

#endif //LAB06_ITERATORVECTOR_H
