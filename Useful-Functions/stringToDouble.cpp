#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;

/* Returns true if the array of characters is a valid double type.
 * Will return false otherwise. */
bool isDouble(const char* characters) {
   /* Keep track of the number of decimal places */
   int decimals = 0;
   /* Iterate through each character until the end of the array
    * is reached (denoted by the null character). */
   for(int i = 0; characters[i] != 0; i++) {
      if(characters[i] == '.') {
         decimals++;
      }
      else if(characters[i] < '0' || characters[i] > '9') {
         return false;
      }
   }
   /* Make sure no more than 1 decimal was found */
   return (decimals < 2);
}

/* Convert the argument string to a double and return this value.
 * Note that there is a check to make sure that the string can be
 * converted to a valid double type. */
double stringToDouble(string number) {
   /* Check to make sure that string is a valid double */
   if( !isDouble(number.c_str()) ) {
      throw invalid_argument("Argument string is not a valid double type.");
   }
   /* Convert the string to a double */
   double result;
   stringstream ss(number);
   ss >> result;
   return result;
}

int main() {

   return 0;
}
