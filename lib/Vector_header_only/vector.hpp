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

#endif //__VECTOR_HPP__
