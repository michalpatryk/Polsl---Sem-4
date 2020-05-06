#include <iostream>
#include <string>
#include <regex>


bool isLoginValid(std::string login) {

	std::regex loginRegex("^\\w{3,}$");
	return std::regex_match(login, loginRegex);
}
bool isEmailValid(std::string email) {
	std::regex emailRegex("^([a-zA-Z]+[a-zA-Z0-9_\\-\\.]{0,20})@([a-zA-Z0-9_\\-\\.]{1,10})\\.([a-zA-Z]{2,5})$");
	return std::regex_match(email, emailRegex);
}
//void showMatches(std::string s, std::regex r) {		//doesnt work
//	std::smatch match;
//	std::regex_search(s, match, r);
//	while (std::regex_search(s, match, r)) {
//		std::cout << match.str(1) << std::endl;
//		s = match.suffix().str();
//	}
//}
void showMatches(std::string s, std::regex r) {

	std::sregex_iterator it = std::sregex_iterator(s.begin(), s.end(), r);
	std::sregex_iterator last;

	while (it != last) {
		std::smatch match = *it;
		std::cout << match.str() << std::endl;
		it++;
	}
}

std::string replacer(std::string s) {
	std::string goodWords = std::regex_replace(s, std::regex("[a-zA-Z]\\*+ing"), "quacking");
	goodWords = std::regex_replace(goodWords, std::regex("[a-zA-Z]\\*+[a-z]*"), "duck");
	return goodWords;
}


int main() {

	//Ex1
	std::string login1 = "SuperKoksu420";
	std::string login2 = "the_best_gamer";
	std::string login3 = ";DROP TABLE USERS;";
	std::string login4 = "Rick&Morty";
	std::string login5 = "ilikegames";

	std::cout << login1 << " returns " << isLoginValid(login1) << std::endl;
	std::cout << login2 << " returns " << isLoginValid(login2) << std::endl;
	std::cout << login3 << " returns " << isLoginValid(login3) << std::endl;
	std::cout << login4 << " returns " << isLoginValid(login4) << std::endl;
	std::cout << login5 << " returns " << isLoginValid(login5) << std::endl;
	std::cout << std::endl << std::endl << std::endl;
	//Ex2
	std::string email1 = "adamsmith@gmail.com";
	std::string email2 = "Adam-Smith@ex1am_ple.pl";
	std::string email3 = "-Adam-Smith@example.eu";
	std::string email4 = "ThePresident45@mail.gov.com";
	std::string email5 = "_lol_mail@lolmail.gov.com";

	std::cout << email1 << " returns " << isEmailValid(email1) << std::endl;
	std::cout << email2 << " returns " << isEmailValid(email2) << std::endl;
	std::cout << email3 << " returns " << isEmailValid(email3) << std::endl;
	std::cout << email4 << " returns " << isEmailValid(email4) << std::endl;
	std::cout << email5 << " returns " << isEmailValid(email5) << std::endl;
	std::cout << std::endl << std::endl << std::endl;
	//Ex3
	//a
	showMatches("A kiwi tastes like a kiwi - kiwilicious!", std::regex("kiwi[\\s]"));
	std::cout << std::endl;
	//b
	showMatches("How much wood would a woodchuck chuck if a woodchuck could chuck wood? Would Woodie who chucked that driftwood know?",
		std::regex("([a-zA-Z]*[wW]ood[a-zA-Z]*)|([a-zA-Z]*[cC]huck[a-zA-Z]*)"));
	std::cout << std::endl << std::endl << std::endl;
	//Ex4
	std::string uglyString = "To be     fair, you have    to have a\n\n very high     IQ tounderstand   Rick and Morty.\n\n\nAnd    yes, by   the way, I\n DO have a Rick & Morty tattoo.";
	std::cout << uglyString << std::endl;
	std::string niceString = std::regex_replace(uglyString, std::regex("(\\\n){2,}"), "\n");
	niceString = std::regex_replace(niceString, std::regex("( ){2,}"), " ");
	niceString = std::regex_replace(niceString, std::regex("( a\\n)"), " \na");
	niceString = std::regex_replace(niceString, std::regex("( I\\n)"), " \nI");
	std::cout << niceString << std::endl;
	std::cout << std::endl << std::endl << std::endl;
	//Ex5
	std::string badWords = "You are a f***ing m********ker";
	std::string goodWords = replacer(badWords);
	std::cout << badWords << " changed to " << goodWords << std::endl;

	std::string badWords2 = "I'll f***ing kill your sorry f***ing ass you m********ker";
	std::string goodWords2 = replacer(badWords2);
	std::cout << badWords2 << " changed to " << goodWords2 << std::endl;
}