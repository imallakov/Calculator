// Calculator.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <map>
#include <vector>

bool func(int a = 0, char c = '#', int b = 0)
{
    if (c == '~')
    {
        return b == 1 ? 0 : 1;
    }
    if (c == '&')
        return a && b;

    if (c == 'v')
        return a || b;
    if (c == '|')
        return a || b;

    if (c == '+')
        return a ^ b;

    if (c == '=')
        return a == b;

    if (c == '>')
        return !a || b;

    if (c == '<')
        return a || !b;

    if (c == '!')
        return !a && !b;

    if (c == '@')
        return !a || !b;

    throw "Unknown operator : " + c;
}
int ob(std::string& s)
{
    int k = -1;
    for (int i = 0; i < s.length(); ++i)
    {
        if (s[i] == '(') k = i;
    }
    return k;
}
int cb(std::string& s)
{
    int k = s.length();
    for (int i = 0; i < s.length(); ++i)
    {
        if (s[i] == ')')
        {
            k = i;
            break;
        }
    }
    return k;
}
int main()
{
    try
    {
        std::string s = "";
        std::map<char, bool>mp;
        std::vector<char>v = { '&' , '|' , 'v' , '>' , '<' , '=' , '@' , '!' };
        std::cout << "!Please use only lower case English to name the variables!\n";
        std::cout << "~ - negation\n& - and\n| - or\nv - or\n> - implication\n< - reversed implication\n= - equal\n@ - Sheffer stroke\n! - Peirce's arrow/NOR\n";

        std::cout << "Enter a expression: ";
        std::getline(std::cin, s);
        for (int i = 0; i < s.length(); ++i)
        {
            if (s[i] == ' ') s.erase(s.begin() + i), --i;
        }
        for (int i = 0; i < s.length(); ++i)
        {
            if (s[i] != '(' && s[i] != ')' && s[i] != '~' && s[i] != '&' && s[i] != '|' && s[i] != 'v' && s[i] != '>' && s[i] != '<' && s[i] != '+' && s[i] != '=' && s[i] != '!' && s[i] != '@')
            {
                int a = 0;
                do
                {
                    std::cout << "Please enter the value of " << s[i] << "(0 or 1): ";
                    std::cin >> a;
                } while (a != 0 && a != 1);
                mp[s[i]] = a;
            }
        }
        for (int i = 0; i < s.length(); ++i)
        {
            if (s[i] == '~')
            {
                mp[s[i + 1]] = func(1, s[i], mp[s[i + 1]]);
                s.erase(s.begin() + i);
            }
        }
        while (s.length() > 1)
        {
            for (int i = 0; i < v.size(); ++i)
            {
                int l = ob(s);
                int r = cb(s);
                for (int j = l + 1; j < r; ++j)
                {
                    if (s[j] == v[i])
                    {
                        bool bl;
                        if (isdigit(s[j + 1]))
                            bl = func(mp[s[j - 1]], s[j], s[j + 1] - 48);
                        else
                            bl = func(mp[s[j - 1]], s[j], mp[s[j + 1]]);
                        s[j - 1] = bl + 48;
                        s.erase(s.begin() + j);
                        s.erase(s.begin() + j);
                        j -= 1;
                        r -= 2;
                    }
                }
            }
            for (int i = 1; i < s.length() - 1; ++i)
            {
                if (s[i - 1] == '(' && s[i + 1] == ')')
                {
                    s.erase(s.begin() + i + 1);
                    s.erase(s.begin() + i - 1);
                }
            }
            //            std::cout << s << std::endl;
        }
        /*std::cout << s << std::endl;
        for (int i = 0; i < s.length(); ++i)
            if (mp[s[i]] != -1)    std::cout << s[i] << " = " << mp[s[i]] << std::endl;
        */
        std::cout << "Answer: ";
        if (isdigit(s[0])) std::cout << s[0] << std::endl;
        else std::cout << mp[s[0]] << std::endl;
    }
    catch (const char* str)
    {
        std::cout << "Error: " << str << std::endl;
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
