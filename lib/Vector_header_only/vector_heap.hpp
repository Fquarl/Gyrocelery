/**
 *  \file vector_heap.hpp
 *  \note Do not include this file directly!
 *  \see  https://onlinedocs.microchip.com/pr/GUID-317042D4-BCCE-4065-BB05-AC4312DBC2C4-en-US-2/index.html?GUID-27757112-8BE1-49C2-B023-CD94AD06C5E2
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
    constexpr uint16_t totalLenghtOfSRAM = 0x800;

    /**
     *  \var        maxHeapSize
     *  \brief      The constant specifies the maximum size of the heap on the SRAM
     *  \value      0x100
     */
    constexpr uint16_t maxHeapSize = 0x100;

    /**
     *  \var        mallocMargin
     *  \brief      The constant references __malloc_margin to define the minimum margin to the stack 
     *  \value      Default value is 0x20
     *  \note       The value is set in the linking process.
     */
     constexpr inline size_t& mallocMargin = __malloc_margin;

    /**
     *  \var        mallocHeapStart
     *  \brief      The constant references __malloc_heap_start to point to the heap's start byte
     *  \note       The value is set in the linking process.
     */
     constexpr inline char*& mallocHeapStart = __malloc_heap_start;

    /**
     *  \var        mallocHeapEnd
     *  \brief      The constant references __malloc_heap_end to point to the heap's maximum byte position
     *  \note       The value is set in the linking process.
     */
     constexpr inline char*& mallocHeapEnd = __malloc_heap_end;
}

/**
 *  \fn         new
 *  \brief      The function creates a new instance on the heap
 *  \param[in]  size passes the size of the new instance in bytes
 *  \note       The function might return nullptr to avoid heap and stack colliding!
 */
inline void* operator new(size_t size)
{
    return malloc(size);
}
    
/**
 *  \fn         delete
 *  \brief      The function deletes a existing instance from the heap
 *  \param[in]  prt passes the pointer to the instance to delete from the heap
 */
inline void operator delete(void* ptr)
{        
    free(ptr);
}

#endif //__VECTOR_HEAP_HPP__
