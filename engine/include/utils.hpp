#define LOG_ERROR(__CALL__) \
	std::cout << std::endl << __FILE__ << ":" << __LINE__ << std::endl;\
	std::cout << "[*] " << #__CALL__ << std::endl \
	<< "before call: " << glGetError() << std::endl; \
	__CALL__; \
	std::cout << "after call: " << glGetError() << std::endl;
