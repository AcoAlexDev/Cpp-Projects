#include <iostream>
#include <vector>
#include <string>
#include <random>

std::string pick_letter(std::random_device& rng, const std::string& set) {
    std::uniform_int_distribution<size_t> dist(0, set.size() - 1);
    return std::string(1, set[dist(rng)]);
}

int main(){
    std::string letters = "ABCDEFGHJKLMNPQRSTUVWXYZabcdefghjkmnpqrstuvwxyz";
    std::string numbers = "1023456789";
    std::string symbols = "!#$&*-_=+?.,";

    std::random_device rng;
    std::string password;

    for (size_t i = 0; i < 12; ++i)
    {
        int dist = std::uniform_int_distribution<size_t>(0, 10)(rng);
        if (dist <= 6)
        {
            password += pick_letter(rng, letters);
            continue;
        }
        if (dist <= 9)
        {
            password += pick_letter(rng, numbers);
            continue;
        }
        else
        {
            password += pick_letter(rng, symbols);
            continue;
        }
    }

    std::cout << "Generated Password: \n" << password << std::endl;

    return 0;
}