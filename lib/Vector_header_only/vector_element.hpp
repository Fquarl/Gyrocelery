/**
 *  \file vector_element.hpp
 *  \note Do not include this file directly!
 */

#ifndef __VECTOR_ELEMENT_HPP__
#define __VECTOR_ELEMENT_HPP__

/**
 *  \class  VectorElement
 *  \brief  Element of the linked list
 *  \tparam The typename of the instance to store
 *  \see    VectorContainer
 *  \note   Do not asccess this class directly!
 */
template <typename ContentType>
class VectorElement
{
public:
    /**
     *  \fn         VectorElement
     *  \brief      Intializes the instance of type VectorElement
     *  \param[in]  content passes the instance to store
     *  \param[in]  nextElement passes the next element to store
     */
    VectorElement(const ContentType content, const VectorElement *nextElement) : _content(content), _nextElement(nextElement)
    {
    }

    /**
     *  \fn     getContent
     *  \brief  Getter method for the instance stored
     *  \return Reference to the stored instance
     */
    ContentType &getContent(void) const
    {
        return _content;
    }

    /**
     *  \fn     getNextElement
     *  \brief  Getter method for the next element in linked list
     *  \return Pointer to the next VectorElement
     */
    VectorElement *getNextElement(void) const
    {
        return _nextElement;
    }

private:
    /**
     *  \var    _content
     *  \brief  The member stores the target instance
     */
    ContentType _content;

    /**
     *  \var    _nextElement
     *  \brief  The member stores a pointer to the next element of linked list
     */
    VectorElement *_nextElement;
};

#endif //__VECTOR_ELEMENT_HPP__