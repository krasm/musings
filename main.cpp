
#include <number.hpp>

typedef number_t<10> decimal_t;

int main(int argc, char * argv[]) {
    if(argc > 2) {
        decimal_t l(argv[1], strlen(argv[1]));
        decimal_t r(argv[2], strlen(argv[2]));
        int pow = (argc > 3) ? atoi(argv[3]) : 0;
        decimal_t s = l + r;


        std::cout << l << " + " << r << " == " << s  << std::endl;
        std::cout << l << " - " << r << " == " << (l - r) << std::endl;
        std::cout << l << " * " << r << " == " << (l * r)  << std::endl;
    

        std::cout << "lower half of " << l << " is " << l.lowerHalf(l.size() / 2) << std::endl; 
        std::cout << "upper half of " << l << " is " << l.upperHalf(l.size() / 2) << std::endl; 
        std::cout << "lower half of " << r << " is " << r.lowerHalf(r.size() / 2) << std::endl; 
        std::cout << "upper half of " << r << " is " << r.upperHalf(r.size() / 2) << std::endl; 

        std::cout << l << " ** 10^" << pow << " == " << l.multByPowerOfBase(pow) << std::endl;
        std::cout << r << " ** 10^" << pow << " == " << r.multByPowerOfBase(pow) << std::endl;
    }

    return 0;
}
