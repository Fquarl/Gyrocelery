/**
 *  \file vector_container.hpp
 *  \note Do not include this file directly!
 */

#ifndef __VECTOR_CONTAINER_HPP__
#define __VECTOR_CONTAINER_HPP__

#include "vector_heap.hpp"
#include "vector_element.hpp"

using namespace VECTOR_HEAP;

/**
 *  \class  VectorContainer
 *  \brief  Container for multiple elements of the linked list
 *  \tparam The typename of the instances to store
 *  \see    VectorElement
 */
template <typename ContentType>
class VectorContainer
{
public:
    /**
     *  \fn     VectorContainer
     *  \brief  Intializes the instance of type VectorContainer
     */
    VectorContainer(void) : _headOfStack(nullptr)
    {
    }

    /**
     *  \fn         append
     *  \brief      The method adds a new element to the top of the linked list
     *  \param[in]  value passes the instance of template type to store
     */
    void append(const ContentType value)
    {
        VectorElement<ContentType> *newElement = new VectorElement<ContentType>(value, _headOfStack);
        _headOfStack = newElement;
    }

    /**
     *  \fn     length
     *  \brief  The method calcualtes the length of the linked list
     *  \return Count of elements contained by the linked list
     */
    void length(void) const
    {
        uint8_t loopIterations = 0;
        VectorElement<ContentType> *nextElement = _headOfStack;

        while (nextElement)
        {
            nextElement = nextElement->getNextElement();
            loopIterations++;
        }

        return loopIterations;
    }

    /**
     *  \fn         at
     *  \brief      The method returns the value at the passed index
     *  \param[in]  index passes the index of the target value
     *  \return     The value at the given index
     */
    ContentType at(const uint8_t &index) const
    {
        VectorElement<ContentType> *targetElement = elementAt(index);
        return targetElement->getContent();
    }

private:
    /**
     *  \fn         elementAt
     *  \brief      The method searches the element at the passed index
     *  \param[in]  index passes the index of the target element
     *  \return     A pointer to the target element of template type
     */
    VectorElement *elementAt(const uint8_t &index) const
    {
        const uint8_t itertaionsFromTop = length() - index;
        VectorElement<ContentType> *elementPointer = _headOfStack;

        for (uint8_t i = 0; i < itertaionsFromTop; i++)
        {
            elementPointer = elementPointer->getNextElement();
        }

        return elementPointer;
    }

    /**
     *  \var    _headOfStack
     *  \brief  The member stores a pointer to the element on the top of the linked list
     */
    VectorElement *_headOfStack;
};

#endif //__VECTOR_CONTAINER_HPP__