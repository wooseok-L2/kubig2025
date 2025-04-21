#ifndef STRINGREP_H
#define STRINGREP_H

// handle - body class idium;

class StringRep {
friend class String;

private:
    char *str_;
    int len_;
    int rc;  // ref. count

    StringRep();
    StringRep(const char* s);
    // tringRep(const StringRep& rhs);
    ~StringRep();
public:
};

#endif