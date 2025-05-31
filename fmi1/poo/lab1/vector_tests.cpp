#include "vector.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdexcept>

namespace {
	void print_ok(const std::string& what) {
		std::cout << "Ok! " << what << " work(s)" << std::endl;
	}

	void print_error(const std::string& what, const std::string& error) {
		std::cout << "!!! " << what << " error: " << error << std::endl;
	}
}

namespace vector_tests {
	//void base(const std::string& name, void(* test)()) {
	template<typename Func>
	void base(const std::string& name, Func test) {
		bool ok = true;
		try {
			test();
		} catch (std::exception& e) {
			ok = false;
			print_error(name, e.what());
		} if (ok) {
			print_ok(name);
		}
	}

	void default_allocator() {
		base("Default allocator", []() {
			vector<int> v;
		});
	}

	void sized_allocator() {
		base("Sized allocator", []() {
			for (int i = 1; i < 50; i++) {
				vector<int> v(i);
				if (v.size() != i) {
					throw std::runtime_error("Incorrect size after allocation");
				}
				for (int j = 0; j < i; j++) {
					if (v[j] != 0) {
						throw std::runtime_error("Incorrect default value");
					}
				}
			}
		});
	}

	void sized_value_allocator() {
		base("Sized + value allocator", []() {
			for (int i = 1; i < 50; i++) {
				vector<int> v(i, 25 - i);
				if (v.size() != i) {
					throw std::runtime_error("Incorrect size after allocation");
				}
				for (int j = 0; j < i; j++) {
					if (v[j] != 25 - i) {
						throw std::runtime_error("Incorrect value set");
					}
				}
			}
		});	
	}

	void random_access() {
		base("Random access []", []() {
			vector<int> v(4);
			v[0] = 3;
			v[1] = 4;
			v[2] = 2;
			v[3] = 1;

			if (v[0] != 3 || v[1] != 4 || v[2] != 2 || v[3] != 1) {
				throw std::runtime_error("Incorrect value (set / get)");
			}
		});
	}

	void front_back() {
		base("Front and back access", []() {
			vector<int> v(5);

			v[0] = 3;
			if (v.front() != 3) {
				throw std::runtime_error("Incorrect get on front");
			}

			v.front() = 7;
			if (v[0] != 7) {
				throw std::runtime_error("Incorrect set on front");	
			}

			v[v.size() - 1] = 5;
			if (v.back() != 5) {
				throw std::runtime_error("Incorrect get on back");
			}

			v.back() = 4;
			if (v[v.size() - 1] != 4) {
				throw std::runtime_error("Incorrect set on back");
			}
		});
	}

	void front_back_const() {
		base("Const front and back access", []() {
			const vector<int> v(5, 3);

			if (v.front() != 3) {
				throw std::runtime_error("Incorrect get on const front");
			}

			if (v.back() != 3) {
				throw std::runtime_error("Incorrect get on const back");
			}
		});
	}

	void begin_end() {
		base("Begin and end iterators", []() {
			vector<int> v(100);
			int cnt = 0;
			for (int* it = v.begin(); it != v.end(); it++) {
				cnt++;
				if (cnt > 100) { break; }
			}
			if (cnt != 100) {
				throw std::runtime_error("Incorrect number of steps");	
			}
		});
	}

	void push_back() {
		base("push_back function", []() {
			vector<int> v;
			for (int i = 0; i < 15; i++) {
				v.push_back(3 * i - 5);
				if (v.size() != i + 1) {
					throw std::runtime_error("Incorrect size after push_back");	
				}
			}

			for (int i = 0; i < v.size(); i++) {
				if (v[i] != 3 * i - 5) {
					throw std::runtime_error("Incorrect value after push_back");	
				}
			}
		});
	}

	void pop_back() {
		base("pop_back function", []() {
			vector<int> v(50);
			for (int i = 0; i < 15; i++) {
				v.pop_back();
				if (v.size() != (50 - i - 1)) {
					throw std::runtime_error("Incorrect size after pop_back");	
				}
			}
		});
	}

	void clear() {
		base("clear function", []() {
			vector<int> v(50);
			v.clear();
			if (!v.empty()) {
				throw std::runtime_error("Vector not empty after clear");	
			}
		});		
	}

	void resize() {
		base("resize function", []() {
			vector<int> v;
			v.resize(5, 3);
			if (v.size() != 5) {
				throw std::runtime_error("Incorrect size after resize");
			}
			for (int i = 0; i < v.size(); i++) {
				if (v[i] != 3) {
					throw std::runtime_error("Incorrect value after resize");
				}
			}

			v.resize(10, 2);
			if (v.size() != 10) {
				throw std::runtime_error("Incorrect size after resize");
			}
			for (int i = 0; i < v.size(); i++) {
				if (v[i] != 3 - i / 5) {
					throw std::runtime_error("Incorrect value after resize");	
				}
			}

			v.resize(7, 9);
			if (v.size() != 7) {
				throw std::runtime_error("Incorrect size after resize");
			}
			for (int i = 0; i < v.size(); i++) {
				if (v[i] != 3 - i / 5) {
					throw std::runtime_error("Incorrect value after resize");
				}
			}
		});
	}

	void reserve() {
		base("reserve function", []() {
			vector<int> v(5);
			for (int i = 0; i < v.size(); i++) {
				v[i] = -i - 1;
			}

			int old_cap = v.capacity();
			v.reserve(3);
			if (old_cap != v.capacity()) {
				throw std::runtime_error("Capacity decreased in reserve");
			}

			v.reserve(17);
			if (v.capacity() != 17) {
				throw std::runtime_error("Incorrect capacity after reserve");
			}
			if (v.size() != 5) {
				throw std::runtime_error("Incorrect size after reserve");
			}

			for (int i = 0; i < v.size(); i++) {
				if (v[i] != -i - 1) {
					throw std::runtime_error("Incorrect value after reserve");
				}
			}
		});
	}

	void shrink_to_fit() {
		base("shrink_to_fit function", []() {
			vector<int> v;
			v.push_back(5);
			v.reserve(14);
			v.shrink_to_fit();
			if (v.size() != v.capacity()) {
				throw std::runtime_error("Incorrect size after shrink_to_fit");
			} else if (v.capacity() != v.size()) {
				throw std::runtime_error("Incorrect capacity after shrink_to_fit");
			}
		});
	}

	void to_print() {
		base("to_print function", []() {
			vector<int> v(5);
			std::cout<<"should be: ";
			for ( int i = 0 ; i < 5; i++) {
				v[i] = 3*i+1;
				std::cout<<v[i]<<" ";
			}
			std::cout<<" and was: ";
			std::cout <<  v << "\n";
		});
	}


	void swap() {
		base("swap function", []() {
			vector<int> v1(3, 10); // v1 = {10, 10, 10}
			vector<int> v2(2, 5);  // v2 = {5, 5}

			v1.push_back(20); // v1 = {10, 10, 10, 20}
			v2.push_back(15); // v2 = {5, 5, 15}

			// Perform swap
			v1.swap(v2);

			// Check if swap happened correctly
			if (v1.size() != 3 || v2.size() != 4) {
				throw std::runtime_error("swap() did not swap sizes correctly");
			}

			if (v1[0] != 5 || v1[1] != 5 || v1[2] != 15) {
				throw std::runtime_error("swap() did not swap contents correctly for v1");
			}

			if (v2[0] != 10 || v2[1] != 10 || v2[2] != 10 || v2[3] != 20) {
				throw std::runtime_error("swap() did not swap contents correctly for v2");
			}
		});
	}


	void at() {
		base("at function", []() {
			vector<int> v(5);
			v[0] = 3;
			v[1] = 4;
			v[2] = 2;
			v[3] = 1;
			v[4] = 8;

			// Check if at(2) returns the correct value
			if (*v.at(2) != 2) {
				throw std::runtime_error("at(2) did not return expected value");
			}

			// Check out-of-bounds behavior
			if (v.at(5) != nullptr) {
				throw std::runtime_error("at(5) should return nullptr for out-of-bounds access");
			}
		});
	}

	void assignment_operator() {
		base("operator=", []() {
			vector<int> v1(3, 10); // v1 = {10, 10, 10}
			vector<int> v2(5, 5);  // v2 = {5, 5, 5, 5, 5}
			
			// Test assignment
			v1 = v2;
			
			// Check if assignment worked correctly
			if (v1.size() != v2.size()) {
				throw std::runtime_error("operator= did not copy size correctly");
			}
			
			for (unsigned int i = 0; i < v1.size(); i++) {
				if (v1[i] != v2[i]) {
					throw std::runtime_error("operator= did not copy contents correctly");
				}
			}
			
			// Test self-assignment
			v1 = v1;
			if (v1.size() != 5) {
				throw std::runtime_error("Self-assignment changed the size");
			}
			
			for (unsigned int i = 0; i < v1.size(); i++) {
				if (v1[i] != 5) {
					throw std::runtime_error("Self-assignment changed the contents");
				}
			}
		});
	}

}