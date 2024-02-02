#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <algorithm>

struct comp
{
    bool operator()(const std::string &str1, const std::string str2)
    {
        if (str1.size() == str2.size())
        {
            for (size_t i = 0; i < str1.size(); ++i)
            {
                if (str1[i] == str2[i])
                    continue;
                return str1[i] < str2[i];
            }
        }
        return str1.size() < str2.size();
    }
};

void sorting(std::vector<std::string> &group)
{
    std::sort(group.begin(), group.end(), comp());
}

int main()
{
    std::vector<std::string> numbers = {"7", "1", "12", "2", "1234", "1234567890", "98765", "321", "322", "17"};
    std::vector<std::vector<std::string>> groups(10);

    for (auto &n : numbers)
    {
        groups[n.size() / 2].push_back(n);
    }

    std::vector<std::thread> threads;
    for (size_t i = 0; i < groups.size(); ++i)
    {
        std::thread t(sorting, std::ref(groups[i]));
        threads.push_back(std::move(t));
    }

    for (auto &th : threads)
    {
        if (th.joinable())
            th.join();
    }

    for (auto &group : groups)
    {
        for (auto &numb : group)
        {
            std::cout << numb << std::endl;
        }
    }
}