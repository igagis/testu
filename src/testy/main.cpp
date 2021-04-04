#include <clargs/parser.hpp>

#include "tester.hpp"
#include "init.hpp"

namespace testy{

int main(utki::span<const char*> args){
	bool help = false;

	testy::tester t;

	t.cli.add("help", "display help information", [&help](){help = true;});

	testy::init(t);

	t.cli.parse(
			args,
			t.non_key_cli_handler
		);

	if(help){
		if(t.description.empty()){
			std::cout << "unit tests" << std::endl;
		}else{
			std::cout << t.description << std::endl;
		}
		std::cout << std::endl;
		std::cout << "options:" << std::endl;
		std::cout << t.cli.description();
		return 0;
	}

	std::cout << "\e[1;33;4mrunning\e[0m " << t.size() << " test(s)" << std::endl;

	t.run();

	std::cout << "\e[1;32m" << t.num_passed << "\e[0m test(s) passed" << std::endl;

	if(t.num_disabled != 0){
		std::cout << "\e[0;33m" << t.num_disabled  << "\e[0m test(s) disabled" << std::endl;
	}

	if(t.num_failed != 0){
		std::cout << "\e[1;31m" << t.num_failed  << "\e[0m test(s) failed" << std::endl;
		std::cout << "\t\e[1;31mFAILED\e[0m" << std::endl;
		return 1;
	}else{
		std::cout << "\t\e[1;32mPASSED\e[0m" << std::endl;
		return 0;
	}
}

}

int main(int argc, const char** argv){
	return testy::main(utki::make_span(argv, argc));
}
