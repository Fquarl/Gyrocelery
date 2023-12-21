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
     *  \defgroup   HeapSettings
     *  \brief      This group contains basic settings for the ATmega32's memory
     */

    /**
     *  \var        totalLenghtOfSRAM
     *  \brief      The constant specifies the total count of bytes in the SRAM
     *  \value      0x800
     */
    constexpr uin16_t totalLenghtOfSRAM = 0x800;

    /**
     *  \var        mallocMargin
     *  \brief      The constant specifies the minimum margin between stack and heap
     *  \note       The margin can be undercut if the stack grows after heap expansion!
     *  \ingroup    HeapSettings
     *  \value      The default value is set to 64 byte.
     */
    constexpr size_t &mallocMargin = __malloc_margin;
    mallocMargin = 64;

    /**
     *  \var        mallocHeapStart
     *  \brief      The constant specifies the start of the heap
     *  \ingroup    HeapSettings
     */
    constexpr char *&mallocHeapStart = __malloc_heap_start;

    /**
     *  \var        mallocHeapEnd
     *  \brief      The constant specifies the end of the heap
     *  \ingroup    HeapSettings
     */
    constexpr char *&mallocHeapEnd = __malloc_heap_end;

    /**
     *  \fn         new
     *  \brief      The function creates a new instance on the heap
     *  \param[in]  size passes the size of the new instance in bytes
     *  \return     A pointer to the created instance on the heap.
     *  \return     nullptr if the memory allocation fails!
     *  \note       The function might return nullptr to avoid heap and stack colliding!
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
