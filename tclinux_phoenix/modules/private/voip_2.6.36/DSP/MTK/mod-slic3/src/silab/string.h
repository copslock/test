/****************************************************************************/
/**
*  @defgroup   crtString.h   C run-time string wrapper
*
*  @brief      Wrapper for the string.h include file
*
****************************************************************************/

#if !defined( CRT_STRING_H )
#define CRT_STRING_H            /**< Include Guard                           */

/* ---- Include Files ---------------------------------------------------- */

#include <linux/string.h>
#include <linux/slab.h>     /* for kmalloc and and kfree */

#define malloc(arg)        kmalloc(arg, GFP_KERNEL)
#define mallocAtomic(arg)  kmalloc(arg, GFP_ATOMIC)
#define calloc(num, size)  kmalloc((num)*(size), GFP_KERNEL)
#define free(arg)          kfree(arg)

#endif /* CRT_STRING_H */
