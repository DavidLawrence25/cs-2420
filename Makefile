all: lab01 lab02 lab03 lab04 lab05 lab06 lab07 lab08 lab09 lab10 lab11 nb01 nb02 nb03 nb04 nb05 nb06 nb07 nb08 nb09 nb10 nb11

clean:
	rm -f ./labs/*/*.o
	rm -f ./labs/*/main.exe
	rm -f ./labs/*/log.txt
	rm -f ./labs/*/log.json
	rm -f ./no_brainers/*/*.o
	rm -f ./no_brainers/*/main.exe
	rm -f ./no_brainers/*/log.txt
	rm -f ./no_brainers/*/log.json

log_all:
	find -type f -name main.exe -execdir ./main.exe -t -j \;

lab01:
	g++ -std=c++23 -I . -o ./labs/01_date/main.exe ./labs/01_date/main.cc ./labs/01_date/date.cc

lab02:
	g++ -std=c++23 -I . -o ./labs/02_range/main.exe ./labs/02_range/main.cc

lab03:
	g++ -std=c++23 -I . -o ./labs/03_sorted_collection/main.exe ./labs/03_sorted_collection/main.cc

lab04:
	g++ -std=c++23 -I . -o ./labs/04_bracket_matching/main.exe ./labs/04_bracket_matching/main.cc ./labs/04_bracket_matching/bracket_check.cc

lab05:
	g++ -std=c++23 -I . -o ./labs/05_fifth_element/main.exe ./labs/05_fifth_element/main.cc

lab06:
	g++ -std=c++23 -I . -o ./labs/06_recursion/main.exe ./labs/06_recursion/main.cc ./labs/06_recursion/subsequence.cc

lab07:
	g++ -std=c++23 -I . -o ./labs/07_gumball_guess/main.exe ./labs/07_gumball_guess/main.cc ./labs/07_gumball_guess/person.cc

lab08:
	g++ -std=c++23 -I . -o ./labs/08_dynamic_hash_table/main.exe ./labs/08_dynamic_hash_table/main.cc

lab09:
	g++ -std=c++23 -I . -o ./labs/09_merge_sort/main.exe ./labs/09_merge_sort/main.cc

lab10:
	g++ -std=c++23 -I . -o ./labs/10_bst_remove/main.exe ./labs/10_bst_remove/main.cc

lab11:
	g++ -std=c++23 -I . -o ./labs/11_missionaries_cannibals/main.exe ./labs/11_missionaries_cannibals/main.cc ./labs/11_missionaries_cannibals/state.cc ./labs/11_missionaries_cannibals/missionaries_cannibals.cc

nb01:
	g++ -std=c++23 -I . -o ./no_brainers/01_overloaded_operators/main.exe ./no_brainers/01_overloaded_operators/main.cc ./no_brainers/01_overloaded_operators/point.cc

nb02:
	g++ -std=c++23 -I . -o ./no_brainers/02_point_revisited/main.exe ./no_brainers/02_point_revisited/main.cc

nb03:
	g++ -std=c++23 -I . -o ./no_brainers/03_collection/main.exe ./no_brainers/03_collection/main.cc

nb04:
	g++ -std=c++23 -I . -o ./no_brainers/04_palindrome/main.exe ./no_brainers/04_palindrome/main.cc ./no_brainers/04_palindrome/palindrome.cc

nb05:
	g++ -std=c++23 -I . -o ./no_brainers/05_linked_list/main.exe ./no_brainers/05_linked_list/main.cc

nb06:
	g++ -std=c++23 -I . -o ./no_brainers/06_recursion_maze/main.exe ./no_brainers/06_recursion_maze/main.cc ./no_brainers/06_recursion_maze/maze.cc

nb07:
	g++ -std=c++23 -I . -o ./no_brainers/07_stack/main.exe ./no_brainers/07_stack/main.cc

nb08:
	g++ -std=c++23 -I . -o ./no_brainers/08_lp_hash_table/main.exe ./no_brainers/08_lp_hash_table/main.cc

nb09:
	g++ -std=c++23 -I . -o ./no_brainers/09_quadratic_sorts/main.exe ./no_brainers/09_quadratic_sorts/main.cc

nb10:
	g++ -std=c++23 -I . -o ./no_brainers/10_bst/main.exe ./no_brainers/10_bst/main.cc

nb11:
	g++ -std=c++23 -I . -o ./no_brainers/11_graph/main.exe ./no_brainers/11_graph/main.cc
