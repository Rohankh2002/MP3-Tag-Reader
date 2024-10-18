#ifndef RETURN_H
#define RETURN_H

/* User defined types */
typedef unsigned int uint;

/* Status will be used in fn. return type */
typedef enum
{
    success,
    failure
} Status;

typedef enum
{
    edit,
    view,
    help,
    invalid
} OperationType;

#endif
