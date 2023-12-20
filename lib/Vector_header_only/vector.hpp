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
};

/**
 *  \class  VectorContainer
 *  \brief  Container for multiple characters representing a string
 */
class String : public Vector<char>
{
};

/**
 *  \class  StringList
 *  \brief  Container for multiple strings forming a list of strings
 */
class StringList : public Vector<String>
{
};

#endif //__VECTOR_HPP__