#include <iostream>


#include "/home/nardi/repos/Sun_Fields/src/lib/heliostato.h"
/* #include "~/repos/Sun_Fields/src/lib/bare_functions.h" */

int main(){


Heliostato h1; //criando objeto
Heliostato result;

h1.set_point_inside_mirror_region(0.2,0.5);

result.pick_point_inside_mirror_region();
//std::cout<<result;

	return 0;
}
