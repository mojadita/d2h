/* d2h.h -- definitions for d2h program.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Fri Nov  8 08:37:26 EET 2019
 * Copyright: (C) 2019 LUIS COLORADO.  All rights reserved.
 * License: BSD.
 */
#ifndef _D2H_H
#define _D2H_H

#define F(_fmt) __FILE__":%d:%s: " _fmt, __LINE__, __func__

#define EXIT_USAGE		(1)
#define EXIT_FOPEN		(2)

#define FLAG_VERBOSE	(1 << 0)
#define FLAG_FLOAT		(1 << 1) /* beware this is never
								  * == sizeof(float)
								  * or sizeof(double) */

#define FMT_DBL			"%.17lg\n"
#define FMT_FLT			"%.6g\n"

#define MODE_DOUBLE_LE  "dbl-le"
#define MODE_FLOAT_LE   "flt-le"
#define MODE_DOUBLE_BE  "dbl-be"
#define MODE_FLOAT_BE   "flt_be"

#define DEFAULT_MODE    MODE_FLOAT_BE

#endif /* _D2H_H */
