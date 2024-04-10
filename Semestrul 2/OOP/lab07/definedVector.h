//
// Created by raulo on 4/9/2024.
//

#ifndef LAB06_DEFINEDVECTOR_H
#define LAB06_DEFINEDVECTOR_H

#include "domain.h"

#define INITIAL_CAPACITY 8

template <typename ElementType>
class VectorDinamic {
private:
    int nr_elemente{};
    int capacitate_maxima{};
    ElementType* lista;

    void alloc_more_memory();
public:
    // constructor
    // aloca memorie pentru 8 de elemente
    VectorDinamic();

    // constructor de copiere
    VectorDinamic(const VectorDinamic& oldTemplate);

    // eliberarea memoriei
    ~VectorDinamic();

    // operator assignment
    VectorDinamic& operator=(const VectorDinamic& oldTemplate);

    /**
	 Move constructor
	 Apelat daca construim un nou vector dintr-un r-value (ex temporary, expresie de la return)
	 Obiectul ot nu se mai foloseste astfel se poate refolosi interiorul lui
	*/
    VectorDinamic(VectorDinamic&& oldTemplate) noexcept ;

    /**
	Move assignment
	Similar cu move constructor
	Folosit la assignment
	*/
    VectorDinamic& operator=(VectorDinamic&& oldTemplate) noexcept ;

    /**
     * add function
     */
    void adauga_element(const ElementType& element);

    const int get_last_id_vd() const;

    const ElementType & get_element(int position) const;

    const void set_element(int position, const ElementType& element);

    void modifica_element(int position, int new_price, const string& new_subst);

    void sterge_element(int position);
};

template<typename ElementType>
void VectorDinamic<ElementType>::alloc_more_memory() {
    this->capacitate_maxima = this->capacitate_maxima + 128;
    auto* new_list = new ElementType[this->capacitate_maxima];
    for(int i = 0; i < this->nr_elemente; i++) {
        new_list[i] = this->lista[i];
    }
    delete[] this->lista;
    this->lista = new_list;
}

template<typename ElementType>
VectorDinamic<ElementType>::VectorDinamic() {
    this->lista = new ElementType[INITIAL_CAPACITY];
    this->capacitate_maxima = INITIAL_CAPACITY;
    this->nr_elemente = 0;
}

template<typename ElementType>
VectorDinamic<ElementType>::VectorDinamic(const VectorDinamic &oldTemplate) {
    // initializam si copiem lista de elemente
    this->lista = new ElementType[oldTemplate.capacitate_maxima];
    for(int i = 0; i < oldTemplate.nr_elemente; i++) {
        this->lista[i] = oldTemplate.lista[i];
    }
    // copiere date despre lista
    this->nr_elemente = oldTemplate.nr_elemente;
    this->capacitate_maxima = oldTemplate.capacitate_maxima;
}

template<typename ElementType>
VectorDinamic<ElementType>::~VectorDinamic() {
    delete[] this->lista;
}

template<typename ElementType>
VectorDinamic<ElementType> &VectorDinamic<ElementType>::operator=(const VectorDinamic<ElementType> &oldTemplate) {
    if (this == &oldTemplate) {
        return *this;
    }
    delete[] this->lista;
    // Copy the data pointer from other
    this->lista = oldTemplate.lista;
    this->nr_elemente = oldTemplate.nr_elemente;
    this->capacitate_maxima = oldTemplate.capacitate_maxima;

    // Release the data pointer from the source object so that
    // the destructor does not free the memory multiple times.
    oldTemplate.lista = nullptr;
    oldTemplate.nr_elemente = 0;
    oldTemplate.capacitate_maxima = 0;
    return *this;
}

template <typename ElementType>
VectorDinamic<ElementType>::VectorDinamic(VectorDinamic&& oldTemplate) noexcept {
    // Copy the data pointer from other
    this->lista = oldTemplate.lista;
    this->nr_elemente = oldTemplate.nr_elemente;
    this->capacitate_maxima = oldTemplate.capacitate_maxima;

    // Release the data pointer from the source object so that
    // the destructor does not free the memory multiple times.
    oldTemplate.lista = nullptr;
    oldTemplate.nr_elemente = 0;
    oldTemplate.capacitate_maxima = 0;
}

/*
Move assignment
Similar cu move constructor
Folosit la assignment
Elibereaza ce continea obiectul curent (this)
"fura" interiorul lui ot
pregateste ot pentru distrugere
*/
template <typename ElementType>
VectorDinamic<ElementType>& VectorDinamic<ElementType>::operator=(VectorDinamic&& oldTemplate) noexcept {
    if (this == &oldTemplate) {
        return *this;
    }
    delete[] this->lista;
    // Copy the data pointer from other
    this->lista = oldTemplate.lista;
    this->nr_elemente = oldTemplate.nr_elemente;
    this->capacitate_maxima = oldTemplate.capacitate_maxima;

    // Release the data pointer from the source object so that
    // the destructor does not free the memory multiple times.
    oldTemplate.lista = nullptr;
    oldTemplate.nr_elemente = 0;
    oldTemplate.capacitate_maxima = 0;
    return *this;
}

template<typename ElementType>
void VectorDinamic<ElementType>::adauga_element(const ElementType& element) {
    if(this->nr_elemente == this->capacitate_maxima)
        this->alloc_more_memory();
    this->lista[this->nr_elemente] = element;
    this->nr_elemente++;
}

template<typename ElementType>
const int VectorDinamic<ElementType>::get_last_id_vd() const {
    return this->nr_elemente;
}

template<typename ElementType>
const ElementType & VectorDinamic<ElementType>::get_element(int position) const {
    return this->lista[position];
}

template<typename ElementType>
const void VectorDinamic<ElementType>::set_element(int position, const ElementType &element) {
    this->lista[position] = element;
}

template<typename ElementType>
void VectorDinamic<ElementType>::modifica_element(const int position, const int new_price, const string &new_subst) {
    this->lista[position].set_pret(new_price);
    this->lista[position].set_subst_activa(new_subst);
}

template<typename ElementType>
void VectorDinamic<ElementType>::sterge_element(int position) {
    for(int i = position; i < this->nr_elemente; i++) {
        this->lista[i] = this->lista[i + 1];
        this->lista[i].set_id(i);
    }
    this->nr_elemente--;

}

#endif //LAB06_DEFINEDVECTOR_H
