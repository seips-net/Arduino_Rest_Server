#include "Message.h"

Message::Message () {
	for (int i = 0; i < REQUEST_MAX_LENGTH; i++) { msg[i] = '\0'; }
	length = 0;
}

void Message::add (char _new_char) {
	if (length == REQUEST_MAX_LENGTH) return;
	msg[length] = _new_char;
	length += 1;
}

/* slice(char*, int, int)
 *	accepts a string (char array) and a start index and an end index. 
 *	it changes the existing array to only contain the information 
 *  within the start and end index. 
 */
void Message::slice (int _start_index, int _end_index) {
	if (_end_index > length) 
		{ _end_index = length; } 
	if (_start_index > _end_index || _start_index < 0 || _end_index < 0) 
		{ return; }

    for (int i = 0; i < length; i++) {
        int shift_start_index = _start_index + i;
        if (shift_start_index < _end_index) 
			{ msg[i] = msg[shift_start_index]; } 
		else 
			{ msg[i] = '\0'; }
    }
	length = strlen(msg);
}

/* Message::clear()
 *	clears the full Message::msg array and resets the Message::msg_index to 0.
 */
void Message::clear(){
    for (int i = 0; i < REQUEST_MAX_LENGTH; i++) { msg[i] = '\0'; } 
    length = 0;   
}

/* Message::find(char, char*, int)
 *	accepts a search character, a source string and a start index.
 *	returns the index of next occurence of a char after the start 
 *	index. If the char does not exist then it returns a -1.
 */
int Message::find(char _char_search,  int _start_index) {
    if (length <= _start_index) return -1;
    for (int i = _start_index; i < length; i++) {       
      if (_char_search == msg[i]) return i;
    }
	return -1;
}

/* Message::match_string(char*, char*, int)
 *	accepts a search string, a source string and a start index. 
 *	searches the source string for a match with the search string
 *	starting at the start index location only. 
 *	if match is found it returns the index number of the last 
 *	matching element. Otherwise, it returns -1.
 */
int Message::match_string(char* _char_search, int _start_index) {
    int length_search = strlen(_char_search);
    int location = -1;

    if (length < length_search + _start_index) return -1;
    for (int i = 0; i < length_search; i++) {       
      if (_char_search[i] == msg[i+_start_index]) {
           location = i + _start_index;
        } else {
            return -1;
        }
    }
    return location;  
}

/* Message::to_i(char*, int, int)
 *	accepts a msg string, a start and an end index. Then it attempts 
 *	to convert the character string into digits. If any of the 
 *	characters are not numbers then the method returns a -1.
 *	otherwise the method returns the number as an int.
 */
int Message::to_i(int _start_index, int end_index) {
  int return_num = 0;  
  int reverse_counter = (end_index - _start_index);

  for(int i = 0; i <= (end_index - _start_index); i++) {
      char cur_char = msg[i+_start_index];      
      if (int(cur_char) < 48 || int(cur_char) > 57) { return -1; }
      int mult = 1;
      for(int j = 0; j < reverse_counter; j++) { mult = mult * 10; }
      return_num += (int(cur_char)-48) * mult; 
      reverse_counter--;
  }
  return return_num;
}