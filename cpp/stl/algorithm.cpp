#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <list>
#include <random>
#include <cmath>
#include <utility>
#include <numeric>
#include <deque>
#include <iterator>

using namespace std;

void counting();
void finding();
void sorting();
void comparing();
void accumulating();
void generating_manipulating_collection();
void iterator_usage();
void misc();

int main() {
	cout << boolalpha;
	counting();
	finding();
	sorting();
	comparing();
	accumulating();
	iterator_usage();
	misc();
    return 0;
}
/**
 * back_inserter, front_inserter, change the container capacity
 * begin, end, change in place, won't change container capacity
 * reverse iterator
 * const iterator
 */
void iterator_usage(){
	deque<int> q;
	fill_n(front_inserter(q), 3, 2);
	generate_n(front_inserter(q), 3, [n = 0]() mutable { return n++; } );

	vector<int> v, v1;
	fill_n(back_inserter(v), 6, 2);
	generate_n(back_inserter(v), 6, [n = 0]() mutable { return n++; } );
	transform(begin(v), end(v), back_inserter(v1), [](int e) { return e * 2; } );
	copy_if(begin(v), end(v), back_inserter(v1), [](int e) { return e % 2 == 0; } );
	unique_copy(begin(v), end(v), back_inserter(v1), [](int e) { return e % 2 == 0; } );
	reverse_copy(begin(v), end(v), back_inserter(v1));

	// reverse iterator
	copy(rbegin(v), rend(v), back_inserter(v1));
	auto rFind = find(rbegin(v), rend(v), 2);

	// const iterator
	for(auto i = crbegin(v); i != crend(v); ++i)
		cout << *i << endl;
}
/**
 * copy, move objects, move ranges, remove, create and fill, replace, transform, unique, reverse, swap
 * rotate, move within collection
 * partition, gather
 * partial_sort, top n
 */
void generating_manipulating_collection(){
	vector<int> v { 1, 2, 3, 4, 5, 6, 7, 7, 8, 9, 5, 6, 7, 8 };
	vector<int> moved, removed, replaced, transformed, uniqued, reversed, swaped, v1;

	// copy
	vector<int> copied = v;
	copy(begin(v), end(v), begin(copied));
	copy_if(begin(v), end(v), begin(copied), [](int e) { return e % 2 == 0; } );
	copy_n(begin(v), 3, begin(copied));
	copy(begin(v) + 1, end(v), begin(v));						        // shift left
	copy_backward(begin(v), end(v) - 1, end(v));				        // shift right, avoid overlap copy

	// rotate [first, middle, last) => middle become the first element
	rotate(begin(v), end(v) - 1, end(v));						        // shift right
	rotate(begin(v), begin(v) + 1, end(v));						        // shift left
	rotate(rbegin(v), rend(v) - 1, rend(v));					        // shift left

	// move objects, source will be empty
	moved = move(v);

	// move ranges, source is undefined, could be empty, could be un-touched
	move(begin(moved), end(moved), begin(v));
	
	// remove, doesn't shrink container, old value still there, erase will shrink container
	auto newEndIter = remove(begin(v), end(v), 3);
	int logicalSize = newEndIter - begin(v);
	v.erase(newEndIter, end(v));

	v.erase(remove(begin(v), end(v), 3), end(v));			            // one line to clean elements not needed

	remove_if(begin(v), end(v), [](int e) { return e == 3; } );
	remove_copy(begin(v), end(v), begin(removed), 3);
	remove_copy_if(begin(v), end(v), begin(removed), [](int e) { return e == 3; } );

	// create and fill
	v1.resize(10);
	fill(begin(v1), end(v1), 1);
	fill_n(begin(v1), 5, 2);
	iota(begin(v1), end(v1), 1);

	int index = 10;
	generate(begin(v), end(v), [&index]() { return --index; } );
	generate_n(begin(v), 5, [&index]() { return ++index; } );

	// replace
	replace(begin(v), end(v), 3, 2);
	replace_if(begin(v), end(v), [](int e) { return e == 3; }, 2 );
	replace_copy(begin(v), end(v), begin(replaced), 3, 2);
	replace_copy_if(begin(v), end(v), begin(replaced), [](int e) { return e == 3; }, 2 );

	// transform, source could be one container or two containers, use UnaryOperation or BinaryOperation  respectively
	transform(begin(v), end(v), begin(v), [](int e) { return e + 1; } );
	transform(begin(v), end(v) - 1, begin(v) + 1, begin(v), [](int e1, int e2) { return e1 - e2; } );

	// unique, eliminate duplicates, must work on sorted array
	sort(begin(v), end(v));
	v.erase(unique(begin(v), end(v)), end(v));
	unique_copy(begin(v), end(v), begin(uniqued));

	// reverse
	reverse(begin(v), end(v));
	reverse_copy(begin(v), end(v), begin(reversed));

	// swap
	iter_swap(begin(v), end(v) - 1);
	swap(v[0], v[1]);
	swap_ranges(begin(v), end(v), begin(swaped));

	// partition, return partition point
	stable_partition(begin(v), end(v), [](int e) { return e % 2 == 0; } );		    // move even to the top, return first odd iter
}
/**
 * equal, returns true if all of the elements in both ranges match
 * mismatch, find the first element of both sequences that does not match
 */
void comparing(){
	vector<int> v { 1, 2, 3, 4, 5, 6, 7, 7, 8, 9, 5, 6, 7, 8 };
	vector<int> sequences { 1, 6, 7 };

	cout << "equal : " << equal(begin(v), end(v), begin(sequences), end(sequences)) << endl;

	auto diff = mismatch(begin(v), end(v), begin(sequences), end(sequences));
	cout << "mismatch : " << *(diff.first) << " " << *(diff.second) << " distance : "<< (diff.first - begin(v)) << endl;
}
void accumulating(){
	vector<int> v { 1, 2, 3, 4, 5, 6, 7, 7, 8, 9, 5, 6, 7, 8 };
	cout << "accumulate : " << accumulate(begin(v), end(v), 0) << endl;
	cout << "accumulate even : " << accumulate(begin(v), end(v), 0,
		[](int total, int i){ if(i % 2 == 0) return total + i; else return total; } ) << endl;
	cout << "accumulate multiply : " << accumulate(begin(v), end(v), 1,
		[](int total, int i){ return total * i; } ) << endl;

	vector<string> words { "hello", "world" };
	cout << "accumulate : " << accumulate(begin(words), end(words), string {} ) << endl;
	cout << "accumulate : " << accumulate(begin(words), end(words), string {},
		[](string& total, string i){ return total + " " + i; }) << endl;
}
/**
 * sort is default to unstable sort, if stable wanted, use stable_sort
 * upper_bound, > val.
 * lower_bound, >= val.
 * equal_range, return pair of iterator of (lower_bound, upper_bound)
 * binary_search, check if val is in sorted range [first,last)
 * shuffle, shuffle with random generator
 * partial_sort, for pagination, sort top N elements, [first, middle) is sorted, [middle, end) is unsorted
 * nth_element, give a rough partition, the element at the nth position is the element that would be in that position in a sorted sequence.
 */
void sorting(){
	vector<int> v { 1, 5, 2, 8, 3, -5, 9, 7, 7, 8, 6 };

	cout << "max : " << *(max_element(begin(v), end(v))) << endl;
	cout << "min : " << *(min_element(begin(v), end(v))) << endl;

	cout << "lower_bound : " << *(lower_bound(begin(v), end(v), -3)) << endl;		// 1
	cout << "upper_bound : " << *(upper_bound(begin(v), end(v), -3)) << endl;		// 1

	sort(begin(v), end(v));	
	sort(begin(v), end(v), greater<int>());
	sort(begin(v), end(v), [](int l, int r) { return abs(l) < abs(r); } );

	cout << "is sorted : " << is_sorted(begin(v), end(v)) << endl;
	cout << "is sorted : " << is_sorted(begin(v), end(v), [](int l, int r) { return abs(l) < abs(r); } ) << endl;

	stable_sort(begin(v), end(v));

	cout << "-3 not existed in sorted vector : " << binary_search(begin(v), end(v), -3) << endl;

	random_device rDevice;
	mt19937 generator(rDevice());
	shuffle(begin(v), end(v), generator);

	partial_sort(begin(v), begin(v) + 2, end(v));
	vector<int> result(2);
	partial_sort_copy(begin(v), end(v), begin(result), end(result));
	cout << "sorted until : " << *(is_sorted_until(begin(v), end(v))) << endl;

	nth_element(begin(v), begin(v) + 5, end(v));
	cout << "nth element : " << *(begin(v) + 5) << endl;
}
void counting(){
	vector<int> v { 1, 2, 3, 4, 5, 6, 7, 7, 8, 9 };

	cout << "count number 7 : " << count(begin(v), end(v), 7) << endl;
	cout << "count odd : " << count_if(begin(v), end(v), [](auto elem) { return elem % 2 != 0; } ) << endl;

	cout << "all of is odd : " << all_of(begin(v), end(v), [](auto elem) { return elem % 2 != 0; } ) << endl;
	cout << "none of is odd : " << none_of(begin(v), end(v), [](auto elem) { return elem % 2 != 0; } ) << endl;
	cout << "any of is odd : " << any_of(begin(v), end(v), [](auto elem) { return elem % 2 != 0; } ) << endl;
}
/**
 * find_if_not, the first element in the range [first,last) for which pred returns false
 * find_first_of, the first element in the range [first1,last1) that matches any of the elements in [first2,last2)
 * search, searches the range [first1,last1) for the first occurrence of the sequence defined by [first2,last2)
 * find_end, searches the range [first1,last1) for the last occurrence of the sequence defined by [first2,last2)
 * search_n, searches the range [first,last) for a sequence of count elements, each comparing equal to val
 * adjacent_find, searches the range [first,last) for the first occurrence of two consecutive elements that match
 */
void finding(){
	vector<int> v { 1, 2, 3, 4, 5, 6, 7, 7, 8, 9, 5, 6, 7, 8 };
	vector<int> targets { 1, 3, 5, 7, 9 };
	vector<int> sequences { 5, 6, 7 };

	auto result = find(begin(v), end(v), 7);
	cout << "first number 7 : " << *result << endl;
	result = find(result + 1, end(v), 7);
	cout << "next number 7 : " << *result << endl;
	result = find(result + 1, end(v), 7);
	cout << "no number 7 found next : " << result == end(v) << endl;

	cout << "first odd : " << *(find_if(begin(v), end(v), [](auto elem) { return elem % 2 != 0; })) << endl;
	cout << "first even : " << *(find_if_not(begin(v), end(v), [](auto elem) { return elem % 2 != 0; })) << endl;
	cout << "first element in targets : " << *(find_first_of(begin(v), end(v), begin(targets), end(targets))) << endl;
	cout << "first sequence occurrence : " << *(search(begin(v), end(v), begin(sequences), end(sequences))) << endl;
	cout << "last sequence occurrence : " << *(find_end(begin(v), end(v), begin(sequences), end(sequences))) << endl;
	cout << "2 consective occurrence of 7 : " << *(search_n(begin(v), end(v), 2, 7)) << endl;
	cout << "2 consective occurrence of 7 : " << *(adjacent_find(begin(v), end(v), 7)) << endl;
}
/**
 * for_each, usually change partial range data based iterator
 */
void misc(){
	vector<int> v { 1, 2, 3, 4, 5, 6, 7, 7, 8, 9, 5, 6, 7, 8 };

	for(auto& i : v) 
		i += 2;
	for_each(begin(v) + 5, end(v), [](int& e) { e += 1;} );
}
