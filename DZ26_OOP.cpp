#include <iostream>
#include <windows.h>
#include <string>
#include <cstring>


using namespace std;


class String
{
private:
	char* arrChars;
public:
	String()
	{
		cout << "Default constructor called. Object address: " << this << endl;
		arrChars = new char[80 + 1];
		arrChars[0] = '\0';
	}

	explicit String(int size)
	{
		cout << "Size constructor called. Object address: " << this << endl;
		if (size < 0)
			size = 0;
		
		arrChars = new char[size + 1];
		arrChars[0] = '\0';


	}

	String(const char* arrChars):arrChars(nullptr)
	{
		cout << "Parameterized constructor called. Object address: " << this << endl;

		if (arrChars == nullptr)
		{
			this->arrChars = new char[1];
			this->arrChars[0] = '\0';
		}
		else
		{
			size_t length = strlen(arrChars);
			this->arrChars = new char[length + 1];
			strcpy_s(this->arrChars, length + 1, arrChars);
		}
	}
	
	String(const String& other)
	{
		cout << "Copy constructor called. Object address: " << this << endl;

		size_t length = strlen(other.arrChars);
		arrChars = new char[length + 1];
		strcpy_s(arrChars, length + 1, other.arrChars);
	}

	String& operator=(const String& other)
	{
		cout << "Assignment operator called. Object address: " << this << endl;

		if (this == &other)
			return *this;

		size_t length = strlen(other.arrChars);
		char* newChars = new char[length + 1];
		strcpy_s(newChars, length + 1, other.arrChars);

		delete[] arrChars;
		arrChars = newChars;

		return *this;
	}

	String operator+(const String& other) const
	{
		cout << "Addition operator called. Object address: " << this << endl;

		size_t length1 = strlen(arrChars);
		size_t length2 = strlen(other.arrChars);

		char* allChars = new char[length1 + length2 + 1];

		strcpy_s(allChars, length1 + length2 + 1, arrChars);
		strcat_s(allChars, length1 + length2 + 1, other.arrChars);

		String result(allChars);

		delete[] allChars;

		return result;
	}

	String operator*(const String& other) const
	{
		cout << "Intersection operator called. Object address: " << this << endl;

		size_t length1 = strlen(arrChars);
		size_t length2 = strlen(other.arrChars);

		char* result = new char[length1 + 1];
		int similarity = 0;

		for (size_t i = 0; i < length1; i++)
		{
			for (size_t j = 0; j < length2; j++)
			{
				if (arrChars[i] == other.arrChars[j])
				{
					result[similarity] = arrChars[i];
					similarity++;
					break;
				}
			}
		}

		result[similarity] = '\0';
		String intersection = result;
		delete[] result;

		return intersection;
	}

	String operator/(const String& other) const
	{
		cout << "Difference operator called. Object address: " << this << endl;

		size_t length1 = strlen(arrChars);
		size_t length2 = strlen(other.arrChars);

		char* result = new char[length1 + 1];
		int similarity = 0;
	

		for (size_t i = 0; i < length1; i++)
		{
			bool check = false;
			
			for (size_t j = 0; j < length2; j++)
			{
				if (arrChars[i] == other.arrChars[j])
				{
					check = true;
					break;
				}
			}
			if (!check)
			{
					result[similarity] = arrChars[i];
					similarity++;
			}
		
		}
		
		result[similarity] = '\0';
		String difference = result;
		delete[] result;

		return difference;

	}


	void show()
	{
		cout << "show() method called. Object address: " << this << endl;

		cout << arrChars;
	}

	
	~String()
	{
		cout << "Destructor called. Object address: " << this << endl;

		delete[] arrChars;
	}


	friend istream& operator>>(istream& is, String& str);
	friend ostream& operator<<(ostream& os, const String& str);
	
};

istream& operator>>(istream& is, String& str)
{
	cout << "Input operator called. Object address: " << &str << endl;

	char buffer[1024];

	is >> buffer;

	if (is)
	{
		size_t length = strlen(buffer);
		char* newChars = new char[length + 1];

		strcpy_s(newChars, length + 1, buffer);

		delete[] str.arrChars;
		str.arrChars = newChars;
	}

	return is;
}
 
ostream& operator<<(ostream& os, const String& str)
{
	cout << "Output operator called. Object address: " << &str << endl;

	os << str.arrChars;
	return os;
}



int main()
{
	
	String str1;                 
	String str2("hello");        
	String str3(50);             

	cout << "\n--- Constructors ---\n";
	cout << "str1: " << str1 << endl;
	cout << "str2: " << str2 << endl;
	cout << "str3: " << str3 << endl;

	str1 = "hello";
	str3 = str2;

	cout << "\n--- Assignment ---\n";
	cout << "str1: " << str1 << endl;
	cout << "str3: " << str3 << endl;

	String str4(str2);

	cout << "\n--- Copy constructor ---\n";
	cout << "str4: " << str4 << endl;

	String str5;

	cout << "\nEnter a string: ";
	cin >> str5;

	cout << "You entered: " << str5 << endl;

	String a("hello");
	String b(" world");

	String sum = a + b;

	cout << "\n--- Operator + ---\n";
	cout << sum << endl;

	String c("hello");
	String d("world");

	String intersection = c * d;

	cout << "\n--- Operator * (intersection) ---\n";
	cout << intersection << endl;

	String difference = c / d;

	cout << "\n--- Operator / (difference) ---\n";
	cout << difference << endl;

	str1 = str1;

	cout << "\n--- Self-assignment ---\n";
	cout << str1 << endl;

	cout << "\n--- End of main ---\n";

	return 0;
}
