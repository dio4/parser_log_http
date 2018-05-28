#include <algorithm>
#include <cctype>
#include <string>
#include <vector>
#include "urls.h"

using std::find;
using std::find_if;

#ifndef _MSC_VER
using std::isalnum;
using std::isalpha;
using std::isdigit;
#endif

using std::search;
using std::string;
using std::vector;

bool not_url_char(char);

string::const_iterator
url_end(string::const_iterator, string::const_iterator);

string::const_iterator
url_beg(string::const_iterator, string::const_iterator);

vector<string> find_urls(const string& s)
{
	vector<string> ret;
	typedef string::const_iterator iter;
	iter b = s.begin(), e = s.end();

	// смотрим все содержимое входных данных
	while (b != e) {

		// поиск одной или нескольких букв, стоящих за `://'
		b = url_beg(b, e);

		// если нали
		if (b != e) {
			// получаем остальную часть адреса 
			iter after = url_end(b, e);

			// запоминаем адрес \s-1URL\s0
			ret.push_back(string(b, after));

			// передвигаем  `b' для попытки отыскать адрес  в этой строке
			b = after;
		}
	}
	return ret;
}

string::const_iterator
url_end(string::const_iterator b, string::const_iterator e)
{
	return find_if(b, e, not_url_char);
}

bool not_url_char(char c)
{
	// символы кроме букв и цифр, которые мб включены в URL 
	static const string url_ch = "~;/?:@=&$-_.+!*'(),";

	// смотрим, может ли символ `c' быть частью URL адреса и возвр.отрицание значения ответа
	return !(isalnum(c) ||
	         find(url_ch.begin(), url_ch.end(), c) != url_ch.end());
}

string::const_iterator
url_beg(string::const_iterator b, string::const_iterator e)
{
	static const string sep = "://";

	typedef string::const_iterator iter;

	// `i' помечает, где был найден разделитель
	iter i = b;

	while ((i = search(i, e, sep.begin(), sep.end())) != e) {

		// убеждаемся, что разделителя нет в начале или конце строки
		if (i != b && i + sep.size() != e) {

			// `beg' помечает начало имени протокола
			iter beg = i;
			while (beg != b && isalpha(beg[-1]))
				--beg;
			if (beg != i && !not_url_char(i[sep.size()]))
				return beg;
		}

		i += sep.size();
	}
	return e;
}

