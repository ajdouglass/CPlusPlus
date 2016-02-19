#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;

/* Returns true if the array of characters represents a valid
 * integer type. Will return false otherwise */
bool isInteger(const char* characters) {
   /* iterate through each character in the array until the
    * null character is hit */
   for(int i = 0; characters[i] != 0; i++) {
      if(characters[i] < 48 || characters[i] > 57) {
         return false;
      }
   }
   return true;
}

/* Convert the string number to an integer. This value is then
 * returned. Note that an error will be thrown if the strig
 * cannot be converted to an integer type */
int stringToInt(string number) {
   /* Check to make sure it is a valid string */
   if( !isInteger(number.c_str()) ) {
      throw invalid_argument("Argument string is not a valid integer type.");
   }
   /* Convert string to an int using a stringstream */
   int result;
   stringstream ss(number);
   ss >> result;
   return result;
}

int main() {

   return 0;
}
