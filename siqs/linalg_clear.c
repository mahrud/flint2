/*
    Copyright (C) 2006, 2011, 2016 William Hart
    Copyright (C) 2015 Nitin Kumar

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include <gmp.h>
#include "flint.h"
#include "ulong_extras.h"
#include "siqs.h"
#include "fmpz.h"

void qsieve_linalg_clear(qs_t qs_inf)
{
    slong i;

    flint_free(qs_inf->small);
    flint_free(qs_inf->factor);
    flint_free(qs_inf->relation);
    flint_free(qs_inf->qsort_arr);
    flint_free(qs_inf->hash_table);
    flint_free(qs_inf->table);

    if (qs_inf->matrix != NULL)
    {
        for (i = 0; i < qs_inf->buffer_size + qs_inf->num_unmerged; i++)
        {
            la_col_t * col = qs_inf->matrix + i;

            if (col->weight)
                flint_free(col->data);
        }

        flint_free(qs_inf->matrix);
    }

    if (qs_inf->Y_arr != NULL)
    {
        for (i = 0; i < qs_inf->buffer_size; i++)
            fmpz_clear(qs_inf->Y_arr + i);
        flint_free(qs_inf->Y_arr);
    }

    flint_free(qs_inf->prime_count);

    qs_inf->small = NULL;
    qs_inf->factor = NULL;
    qs_inf->relation = NULL;
    qs_inf->qsort_arr = NULL;
    qs_inf->matrix = NULL;
    qs_inf->Y_arr = NULL;
    qs_inf->prime_count = NULL;
    qs_inf->hash_table = NULL;
    qs_inf->table = NULL;
}