#include "../include/urlencoder.h"
#include <cctype>
#include <iomanip>
#include <sstream>

std::string urlEncode(const std::string &value) {
  std::ostringstream escaped;
  escaped.fill('0');
  escaped << std::hex;

  for (char c : value) {
    if (std::isalnum(static_cast<unsigned char>(c)) || c == '-' || c == '_' ||
        c == '.' || c == '~') {
      escaped << c;
    } else if (c == ' ') {
      escaped << '+';
    } else {
      escaped << '%' << std::setw(2)
              << static_cast<unsigned int>(static_cast<unsigned char>(c));
    }
  }

  return escaped.str();
}
