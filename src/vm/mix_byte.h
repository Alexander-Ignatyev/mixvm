/*
 *  mix_byte.h
 *  mixvm
 *
 *  Created by Alexander Ignatyev on 19.06.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MIX_BYTE_H
#define MIX_BYTE_H

namespace mix {
typedef signed char byte;
const int VALUES_IN_BYTE = 64;
typedef int value_type;
typedef long long int long_value_type;
const bool POS_SIGN = false;
const bool NEG_SIGN = true;
} // namespace mix
#endif // MIX_BYTE_H
