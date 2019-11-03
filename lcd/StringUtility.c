// StringUtility.c
// Created by Robert Leonard on 2019-07-04.
//

#include "StringUtility.h"

#include <stdio.h>

void StringUtility_fixed_float(char *str, float number) {
	int n = (int) (number);
	int n1 = n / 10;
	int n2 = n - n1 * 10;

	float f = number - n;
	int f1 = (int) (f * 10);
//	int f2 = (int)(f * 100 - f1 * 10);

	if (n1 == 0) {
		sprintf(str, " %d.%d", n2, f1);
	} else {
		sprintf(str, "%d%d.%d", n1, n2, f1);
	}
}
