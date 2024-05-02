#ifndef LOG_HPP
#define LOG_HPP

#define log(...) (printf("[%s:%d] ", __FILE__, __LINE__), printf(__VA_ARGS__), printf("\n"))

#endif // LOG_HPP