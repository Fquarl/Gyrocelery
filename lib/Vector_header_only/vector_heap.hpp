/**
 *  \file vector_heap.hpp
 *  \note Do not include this file directly!
 */

#ifndef __VECTOR_HEAP_HPP__
#define __VECTOR_HEAP_HPP__

#include <stdlib.h>

/**
 *  \namespace  VECT_HEAP
 *  \brief      The namespace contains functions for use of the AVR's heap
 */
namespace VECTOR_HEAP
{
    /**
     *  \fn         new
     *  \brief      The function creates a new instance on the heap
     *  \param[in]  size passes the size of the new instance in bytes
     */
    void *operator new(size_t size)
    {
        return malloc(size);
    }

    /**
     *  \fn         delete
     *  \brief      The function deletes a existing instance from the heap
     *  \param[in]  prt passes the pointer to the instance to delete from the heap
     */
    void operator delete(void *ptr)
    {
        free(ptr);
    }
}

#endif //__VECTOR_HEAP_HPP__