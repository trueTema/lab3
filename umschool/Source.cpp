#include <windows.h>
#include <iostream>
#include <glut.h>
#include <cstdlib>
#include <cmath>
#include "Tree.h"
#include "AVLTree.h"
#include "Set.h"
#include "Person.h"
#include "menu.h"

using namespace std;



int main(int argc, char** argv) {
    srand(time(0));
    glutInit(&argc, argv);
    init();
	set<complex> st;
	st.push(complex(1, 1));
	st.push(complex(1, 2));
	st.push(complex(17, -5));
	st.push(complex(1, 1));
	st.push(complex(4, 4));
	st.push(complex(0, 12));
	st.push(complex(0, 0));
	st.erase(complex(0, 0));
	cout << st.size();
	cout << (st.size() == 6) && (st.find(complex(0, 0)) == false);
    //menu();
    //timing();
}

