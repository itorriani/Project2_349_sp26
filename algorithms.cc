#include "algorithms.h"

// -----------------------------------------------------------------------------
// Helper: determine whether a portion of the sequence contains duplicates
//
// Pseudocode idea:
// 1. Look through the selected portion of the sequence from left to right.
// 2. Compare each value with the one immediately before it.
// 3. If two neighboring values are the same, then this portion is not distinct.
// 4. Otherwise, this portion is distinct.
// -----------------------------------------------------------------------------
bool all_distinct(const std::vector<int>& A, int left, int right) {
    // TODO: move through the subarray from left to right

    int curr = left+1; // set curr to left+1

    for (int i = left; i <= right; i++)
    {
        // TODO: compare each value to the previous one
        if (A[curr] == A[curr-1])
        { 
            // TODO: return false if a duplicate is found
            return false; 
        }

    }    
    // TODO: return true if no duplicates are found
    return true; 
}

// -----------------------------------------------------------------------------
// Part 1: Linear search
//
// Pseudocode idea:
// 1. Start at the beginning of the sequence.
// 2. Compare each value with the next value in the sequence.
// 3. When the difference is larger than expected, the missing value lies there.
// 4. Return that missing value.
// -----------------------------------------------------------------------------
int find_missing_linear(const std::vector<int>& A) {
    // TODO: examine each adjacent pair of values
    for (int i = 0; i+1 < A.size(); i++)
    {
        // TODO: detect where the sorted consecutive pattern breaks
        int diff = A[i+1]-A[i];

        // TODO: return the missing value between those two elements
        if (diff > 1) { return A[i] + 1; }
    }

    return -1; // return -1 if no such missing consecutive value is found. 
    
}

// ------------------------------- ----------------------------------------------
// Part 2 helper: binary-search-based search on a distinct subarray
//
// Pseudocode idea:
// 1. Work with the current left and right boundaries.
// 2. Repeatedly look at the middle position.
// 3. Decide whether the left side still matches the expected consecutive pattern.
// 4. If it does, continue searching in the right half.
// 5. Otherwise, continue searching in the left half.
// 6. When only one position remains, determine the missing value from that spot.



// -----------------------------------------------------------------------------
int binary_missing_distinct(const std::vector<int>& A, int left, int right) {
    // TODO: prepare any information needed to tell whether the pattern is still correct

    // TODO: repeat while more than one position remains

    // TODO: compute the middle position

    // TODO: compare the middle value against what should appear there

    // TODO: keep only the half that could still contain the missing value

    // TODO: return the missing value once the search range is narrowed down

    while (left < right)
    {
        int mid = left + (right - left) / 2; //compute midpoint

        int base = A[left] - left;

        if (A[mid] == base + mid) { 

            left = mid + 1; // if pattern is still correct, missing value is on the right

        } else {

            right = mid; //otherwise, pattern is missing on the left side
        }
    }

    return A[0] + left;

}

// -----------------------------------------------------------------------------
// Part 3 helper: divide-and-conquer search for the general case
//
// Pseudocode idea:
// 1. First handle the smallest subproblems directly.
// 2. If the current portion happens to have all distinct values, use the faster
//    binary-search-based method.
// 3. Otherwise, split the current portion into two smaller parts.
// 4. Recursively search the left part.
// 5. If the answer was not found there, check the gap between the two parts.
// 6. If needed, recursively search the right part.
// -----------------------------------------------------------------------------
int general_missing_recursive(const std::vector<int>& A, int left, int right) {

    // TODO: handle an empty or invalid subproblem
    if (left >= right) { return -1; }

    // TODO: handle a very small subproblem directly
    if (right - left == 1) {
        if (A[right] - A[left] > 1) {
            return A[left] + 1;
        }
        return -1;
    }

    // TODO: switch to the binary-search-based method if this portion is distinct
    if (all_distinct(A, left, right)) {
        return binary_missing_distinct(A, left, right);
    }

    // TODO: split the current portion around the middle
    int mid = (left + right) / 2;

    // TODO: recursively search the left half
    int left_result = general_missing_recursive(A, left, mid);

    if (left_result != -1) {
        return left_result;
    }

    // TODO: check whether the missing value lies between the two halves
    if (A[mid + 1] - A[mid] > 1) {
        return A[mid] + 1;
    }

    // TODO: recursively search the right half if necessary
    return general_missing_recursive(A, mid + 1, right);
}

// -----------------------------------------------------------------------------
// Public wrapper for Part 2
//
// Pseudocode idea:
// 1. Run the distinct-elements algorithm on the entire sequence.
// -----------------------------------------------------------------------------
int find_missing_distinct(const std::vector<int>& A) {
    // TODO: call the binary-search-based helper on the full array
    return binary_missing_distinct(A, 0, A.size() - 1); 
}

// -----------------------------------------------------------------------------
// Public wrapper for Part 3
//
// Pseudocode idea:
// 1. Run the general divide-and-conquer algorithm on the entire sequence.
// -----------------------------------------------------------------------------
int find_missing_general(const std::vector<int>& A) {
    // TODO: call the general recursive helper on the full array
    return general_missing_recursive(A, 0, A.size() - 1);
}

// -----------------------------------------------------------------------------
// Final combined algorithm
//
// Pseudocode idea:
// 1. Check whether the full sequence is distinct.
// 2. If it is, use the binary-search-based algorithm.
// 3. Otherwise, use the general divide-and-conquer algorithm.
// -----------------------------------------------------------------------------
int find_missing_element(const std::vector<int>& A) {
    
     // TODO: use the distinct-elements algorithm when it is safe
    if (all_distinct(A, 0, A.size() - 1)) {
           
        return find_missing_distinct(A);
        // TODO: otherwise use the general divide-and-conquer algorithm
    } else {
        return find_missing_general(A);
    }
}