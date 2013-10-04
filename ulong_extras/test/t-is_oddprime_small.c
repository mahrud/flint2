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

    Copyright (C) 2009 William Hart

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "flint.h"
#include "ulong_extras.h"

int main(void)
{
   int i, result;
   flint_rand_t state;
   
   flint_printf("is_oddprime_small....");
   fflush(stdout);
   
   flint_randinit(state);

   for (i = 0; i < 10000 * flint_test_multiplier(); i++) /* Test that primes pass the test */
   {
      mp_limb_t d;
      mpz_t d_m;
      
      mpz_init(d_m);

      do
      {
         d = n_randint(state, FLINT_ODDPRIME_SMALL_CUTOFF) | 1;
         mpz_set_ui(d_m, d);
         mpz_nextprime(d_m, d_m);
         d = mpz_get_ui(d_m);
      } while (d > FLINT_ODDPRIME_SMALL_CUTOFF);

      result = n_is_oddprime_small(d);
      if (!result)
      {
         flint_printf("FAIL:\n");
         flint_printf("d = %wu is declared composite\n", d); 
         abort();
      }

      mpz_clear(d_m);
   }
         
   for (i = 0; i < 10000 * flint_test_multiplier(); i++) /* Test that not too many composites pass */
   {
      mp_limb_t d;
      mpz_t d_m;
      
      mpz_init(d_m);

      do
      {
         d = n_randint(state, FLINT_ODDPRIME_SMALL_CUTOFF) | 1;
         mpz_set_ui(d_m, d);
      } while ((mpz_probab_prime_p(d_m, 12)) || (d > FLINT_ODDPRIME_SMALL_CUTOFF));

      result = !n_is_oddprime_small(d);
      if (!result)
      {
         flint_printf("FAIL:\n");
         flint_printf("d = %wu is declared prime\n", d); 
         abort();
      }

      mpz_clear(d_m);
   }

   flint_randclear(state);

   flint_printf("PASS\n");
   return 0;
}
