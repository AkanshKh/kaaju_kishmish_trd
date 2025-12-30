mask &= ~(1LL << i); // Clear i-th bit
mask &= (mask - 1); // Turn off lowest set bit
bool is_pow2 = (mask > 0 && (mask & (mask - 1)) == 0); // Is power of two
int leading_zeros = __builtin_clzll(mask); // Count leading zeros
int trailing_zeros = __builtin_ctzll(mask); // Count trailing zeros
int lsb = mask & (-mask); // Isolate least significant bit
mask &= (mask - 1); // Turn off least significant bit
// Iterate over all subsets of a bitmask
for(int sub = mask; sub; sub = (sub - 1) & mask){
    // sub is a non-empty subset
}