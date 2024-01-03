/**
 *  \file vector_heap.hpp
 *  \note Do not include this file directly!
 */

#ifndef __VECTOR_HEAP_HPP__
#define __VECTOR_HEAP_HPP__

#include <stdlib.h>

/**
 *  \namespace  HEAP_SETTINGS
 *  \brief      The namespace contains constants for use of the AVR's heap
 */
namespace HEAP_SETTINGS
{
     /**
      *  \var        totalLenghtOfSRAM
      *  \brief      The constant specifies the total count of bytes on the SRAM
      *  \value      0x800
      */
    constexpr uin16_t totalLenghtOfSRAM = 0x800;

    /**
     *  \var        maxHeapSize
     *  \brief      The constant specifies the maximum size of the heap on the SRAM
     *  \value      0x100
     */
    constexpr uint16_t maxHeapSize = 0x100;
}

/**
 *  \fn         new
 *  \brief      The function creates a new instance on the heap
 *  \param[in]  size passes the size of the new instance in bytes
 *  \note       The function might return nullptr to avoid heap and stack colliding!
 */
void* operator new(size_t size)
{
    return malloc(size);
}
    
/**
 *  \fn         delete
 *  \brief      The function deletes a existing instance from the heap
 *  \param[in]  prt passes the pointer to the instance to delete from the heap
 */
void operator delete(void* ptr)
{        
    free(ptr);
}

#endif //__VECTOR_HEAP_HPP__
