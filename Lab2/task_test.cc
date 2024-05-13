#include <iostream>
#include <string>
#include "main.cc"

int main() {
	MyUnorderedMap<size_t, std::string> map;

	std::string text = "hello";
	size_t savedHash = map.hashString(text);
	std::cout << "Hash for the string 'hello': " << savedHash << std::endl;

	std::string newText = "world";
	bool result = map.compareHashes(savedHash, newText);
	std::cout << "Do the hashes match for the strings 'hello' and 'world': " << std::boolalpha << result << std::endl;

	newText = "hello";
	result = map.compareHashes(savedHash, newText);
	std::cout << "Do the hashes match for the strings 'hello' and 'hello': " << std::boolalpha << result << std::endl;

	return 0;
}
