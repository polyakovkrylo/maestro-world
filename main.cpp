#include <iostream>

#include "transform.h"

using namespace std;
using glm::vec3;

int main()
{
    Transform t;
    Transform t1;
    t1.translate(vec3(1.0f, 0.0f, 0.0f));
    t.rotate(vec3(0.0f, 0.0f, 1.0f), glm::radians(270.0f), t1);

    return 0;
}
