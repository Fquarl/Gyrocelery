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
public:
    /**
     *  \fn     Vector
     *  \brief  The constructor initializes an empty list
     */
    Vector(void)
    {

    }

    /**
     *  \fn     ~Vector 
     *  \brief  The destructor avoids memory leaks 
    */
    ~Vector(void)
    {
        VectorContainer::~VectorContainer();
    }

    /**
     *  \fn     Vector
     *  \brief  The constructor initializes an list with the passed parameter
     */
    Vector(T initializationParameter)
    {
        VectorContainer<T>::append(initializationParameter);
    }

    /**
     *  \fn         []
     *  \brief      The operator returns the value at the passed index
     *  \param[in]  index passes the index of the target value
     *  \return     The value at the given index
     *  \see        at
     */
    T& operator [](const uint8_t &index)
    {
        return VectorContainer<T>::at(index);
    }

    /**
     *  \fn         <<
     *  \brief      The operator adds a new element to the top of the linked list
     *  \param[in]  value passes the instance of template type to store
     *  \tparam     The template parameter specifies the passed type
     */
    void operator <<(const T value)
    {
        VectorContainer<T>::append(value);
    }

    /**
     *  \fn         <<
     *  \brief      The operator addds a C string to a vector of chars
     *  \param[in]  string passes the C string to append
     */
    void operator <<(const char* string)
    {
        uint8_t iterator = 0x00;
        char currentChar = 0xff;

        while (currentChar != 0x00)
        {
            VectorContainer<T>::append(string[iterator]);
            currentChar = string[iterator];
            iterator++;
        }
    }
};

#endif //__VECTOR_HPP__
