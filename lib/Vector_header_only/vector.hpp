/**
 *  \file vector.hpp
 */

#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include "vector_container.hpp"

/**
 *  \class  Vector
 *  \brief  Container for various elements of same type
 *  \tparam The typename of the instance to store
 */
template <typename T>
class Vector : public VectorContainer<T>
{
    /**
     *  \fn         []
     *  \brief      The operator returns the value at the passed index
     *  \param[in]  index passes the index of the target value
     *  \return     The value at the given index
     *  \see        at
     */
    T& operator [](const uint8_t &index)
    {
        return at(index);
    }

    /**
     *  \fn         <<
     *  \brief      The operator adds a new element to the top of the linked list
     *  \param[in]  value passes the instance of template type to store
     */
    void operator <<(const T value)
    {
        append(value);
    }
};

#endif //__VECTOR_HPP__
