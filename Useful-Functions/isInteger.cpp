bool isInteger(const char* characters) {
    for(int i = 0; characters[i] != 0; i++) {
        if(characters[i] < 48 || characters[i] > 57)
            return false;
    }
    return true;
}
