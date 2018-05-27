/*прогр. ищет все URL-адреса, введенные из консоли или переданные в программу из файла
$ ./urls < access.log здесь ./urls - исполнняемый файл, а access.log лог-файл http сервера apache
Программа использует контейнеры, алгоритмы string-объекты и тд */

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

#include "urls.h"

using std::cout;
using std::cin;
using std::endl;
using std::find_if;
using std::getline;
using std::string;
using std::vector;


int main() {
        string s;
        while (getline(cin, s)) {
                vector<string> v = find_urls(s);
#ifdef _MSC_VER
                for (std::vector<string>::const_iterator i = v.begin();
#else
                for (vector<string>::const_iterator i = v.begin();
#endif
                        i != v.end(); ++i)
                        cout << *i << endl;
        }
        return 0;
}
