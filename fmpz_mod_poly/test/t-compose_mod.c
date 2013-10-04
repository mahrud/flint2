/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2011 Fredrik Johansson
    Copyright (C) 2012 Lina Kulakova

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "flint.h"
#include "fmpz_mod_poly.h"
#include "ulong_extras.h"

int
main(void)
{
    int i;
    flint_rand_t state;
    flint_randinit(state);
    flint_printf("compose_mod....");
    fflush(stdout);

    for (i = 0; i < 1000; i++)
    {
        fmpz_mod_poly_t a, b, c, d, e;
        fmpz_t p;

        fmpz_init(p);
        fmpz_set_ui(p, n_randtest_prime(state, 0));

        fmpz_mod_poly_init(a, p);
        fmpz_mod_poly_init(b, p);
        fmpz_mod_poly_init(c, p);
        fmpz_mod_poly_init(d, p);
        fmpz_mod_poly_init(e, p);

        fmpz_mod_poly_randtest(a, state, n_randint(state, 20) + 1);
        fmpz_mod_poly_randtest(b, state, n_randint(state, 20) + 1);
        fmpz_mod_poly_randtest_not_zero(c, state, n_randint(state, 20) + 1);

        fmpz_mod_poly_compose_mod(d, a, b, c);
        fmpz_mod_poly_compose(e, a, b);
        fmpz_mod_poly_rem(e, e, c);

        if (!fmpz_mod_poly_equal(d, e))
        {
            flint_printf("FAIL (composition):\n");
            flint_printf("a:\n"); fmpz_mod_poly_print(a); flint_printf("\n");
            flint_printf("b:\n"); fmpz_mod_poly_print(b); flint_printf("\n");
            flint_printf("c:\n"); fmpz_mod_poly_print(c); flint_printf("\n");
            flint_printf("d:\n"); fmpz_mod_poly_print(d); flint_printf("\n");
            flint_printf("e:\n"); fmpz_mod_poly_print(e); flint_printf("\n");
            abort();
        }

        fmpz_clear(p);
        fmpz_mod_poly_clear(a);
        fmpz_mod_poly_clear(b);
        fmpz_mod_poly_clear(c);
        fmpz_mod_poly_clear(d);
        fmpz_mod_poly_clear(e);
    }

    /* Test aliasing of res and a */
    for (i = 0; i < 1000; i++)
    {
        fmpz_mod_poly_t a, b, c, d;
        fmpz_t p;

        fmpz_init(p);
        fmpz_set_ui(p, n_randtest_prime(state, 0));

        fmpz_mod_poly_init(a, p);
        fmpz_mod_poly_init(b, p);
        fmpz_mod_poly_init(c, p);
        fmpz_mod_poly_init(d, p);

        fmpz_mod_poly_randtest(a, state, n_randint(state, 20) + 1);
        fmpz_mod_poly_randtest(b, state, n_randint(state, 20) + 1);
        fmpz_mod_poly_randtest_not_zero(c, state, n_randint(state, 20) + 1);

        fmpz_mod_poly_compose_mod(d, a, b, c);
        fmpz_mod_poly_compose_mod(a, a, b, c);

        if (!fmpz_mod_poly_equal(d, a))
        {
            flint_printf("FAIL (aliasing a):\n");
            flint_printf("a:\n"); fmpz_mod_poly_print(a); flint_printf("\n");
            flint_printf("b:\n"); fmpz_mod_poly_print(b); flint_printf("\n");
            flint_printf("c:\n"); fmpz_mod_poly_print(c); flint_printf("\n");
            flint_printf("d:\n"); fmpz_mod_poly_print(d); flint_printf("\n");
            abort();
        }

        fmpz_clear(p);
        fmpz_mod_poly_clear(a);
        fmpz_mod_poly_clear(b);
        fmpz_mod_poly_clear(c);
        fmpz_mod_poly_clear(d);
    }

    /* Test aliasing of res and b */
    for (i = 0; i < 1000; i++)
    {
        fmpz_mod_poly_t a, b, c, d;
        fmpz_t p;

        fmpz_init(p);
        fmpz_set_ui(p, n_randtest_prime(state, 0));

        fmpz_mod_poly_init(a, p);
        fmpz_mod_poly_init(b, p);
        fmpz_mod_poly_init(c, p);
        fmpz_mod_poly_init(d, p);

        fmpz_mod_poly_randtest(a, state, n_randint(state, 20) + 1);
        fmpz_mod_poly_randtest(b, state, n_randint(state, 20) + 1);
        fmpz_mod_poly_randtest_not_zero(c, state, n_randint(state, 20) + 1);

        fmpz_mod_poly_compose_mod(d, a, b, c);
        fmpz_mod_poly_compose_mod(b, a, b, c);

        if (!fmpz_mod_poly_equal(d, b))
        {
            flint_printf("FAIL (aliasing b)\n");
            flint_printf("a:\n"); fmpz_mod_poly_print(a); flint_printf("\n");
            flint_printf("b:\n"); fmpz_mod_poly_print(b); flint_printf("\n");
            flint_printf("c:\n"); fmpz_mod_poly_print(c); flint_printf("\n");
            flint_printf("d:\n"); fmpz_mod_poly_print(d); flint_printf("\n");
            abort();
        }

        fmpz_clear(p);
        fmpz_mod_poly_clear(a);
        fmpz_mod_poly_clear(b);
        fmpz_mod_poly_clear(c);
        fmpz_mod_poly_clear(d);
    }

    /* Test aliasing of res and c */
    for (i = 0; i < 1000; i++)
    {
        fmpz_mod_poly_t a, b, c, d;
        fmpz_t p;

        fmpz_init(p);
        fmpz_set_ui(p, n_randtest_prime(state, 0));

        fmpz_mod_poly_init(a, p);
        fmpz_mod_poly_init(b, p);
        fmpz_mod_poly_init(c, p);
        fmpz_mod_poly_init(d, p);

        fmpz_mod_poly_randtest(a, state, n_randint(state, 20) + 1);
        fmpz_mod_poly_randtest(b, state, n_randint(state, 20) + 1);
        fmpz_mod_poly_randtest_not_zero(c, state, n_randint(state, 20) + 1);

        fmpz_mod_poly_compose_mod(d, a, b, c);
        fmpz_mod_poly_compose_mod(c, a, b, c);

        if (!fmpz_mod_poly_equal(d, c))
        {
            flint_printf("FAIL (aliasing c)\n");
            flint_printf("a:\n"); fmpz_mod_poly_print(a); flint_printf("\n");
            flint_printf("b:\n"); fmpz_mod_poly_print(b); flint_printf("\n");
            flint_printf("c:\n"); fmpz_mod_poly_print(c); flint_printf("\n");
            flint_printf("d:\n"); fmpz_mod_poly_print(d); flint_printf("\n");
            abort();
        }

        fmpz_clear(p);
        fmpz_mod_poly_clear(a);
        fmpz_mod_poly_clear(b);
        fmpz_mod_poly_clear(c);
        fmpz_mod_poly_clear(d);
    }

    flint_randclear(state);
    flint_cleanup();
    flint_printf("PASS\n");
    return 0;
}
