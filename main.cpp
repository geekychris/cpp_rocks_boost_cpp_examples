#include <iostream>


#include <iostream>
#include <array>

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//https://www.jetbrains.com/help/clion/boost-test-support.html

#include "dat.h"
#include <ctime>
#include <limits>

#include <utility>

#include "rocks.h"


#include <boost/locale.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>


#include <ctime>
#include <limits>

#include <utility>
#include <folly/Format.h>
#include <folly/futures/Future.h>
#include <folly/executors/ThreadedExecutor.h>
#include <folly/Uri.h>
#include <folly/FBString.h>
#include <folly/portability/GTest.h>


//////////////// FUNCTIONS /////////////////////////////////////////
bool isEven(int number) {           // function declaration
    auto res = (number % 2) == 0;     // function body
    return res;                       // function return
}

#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

/*
 *
 * http://thisthread.blogspot.com/2010/05/ipc-with-boost-filemapping.html
 */
int
memTest(char * fileName, off_t offset, size_t length)
{
    char *addr;
    int fd;
    struct stat sb;
    off_t pa_offset;
    ssize_t s;


    fd = open(fileName, O_RDONLY);
    if (fd == -1)
        handle_error("open");

    if (fstat(fd, &sb) == -1)           /* To obtain file size */
        handle_error("fstat");

    pa_offset = offset & ~(sysconf(_SC_PAGE_SIZE) - 1);
    /* offset for mmap() must be page aligned */

    if (offset >= sb.st_size) {
        fprintf(stderr, "offset is past end of file\n");
        exit(EXIT_FAILURE);
    }


    if (offset + length > sb.st_size)
        length = sb.st_size - offset;
    /* Can't display bytes past end of file */

    addr = (char *)mmap(NULL, length + offset - pa_offset, PROT_READ,
                        MAP_PRIVATE, fd, pa_offset);
    if (addr == MAP_FAILED)
        handle_error("mmap");

    s = write(STDOUT_FILENO, addr + offset - pa_offset, length);
    if (s != length) {
        if (s == -1)
            handle_error("write");

        fprintf(stderr, "partial write");
        exit(EXIT_FAILURE);
    }

    munmap(addr, length + offset - pa_offset);
    close(fd);
}

//////////////// BASIC TYPES //////////////////////////////////////
void cpp_BasicTypes() {
    int messageId = 1234567;            // usually 32-bit signed
    std::string name = "Pusheen";       // 8-bit character std::string (see later)
    bool isViewer = true;               // true or false
    char middleInitial;                 // 8-bit signed
    short editCount = 9;                // usually 16-bit signed
    double createdTime = 234.23;        // 64-bit signed
    long double deleteTime = 9;         // 128-bit signed
    unsigned flags = 0x0;               // usually 32-bit signed
    const unsigned MaxFriends = 20;     // compile time constant
    std::array<std::string, MaxFriends> friends;  // array (see later)
}

void chris ()
{
    std::string s = "hello";
    auto t = s + "bla";
    std::cout << t << std::endl;


}

///////////////// STANDARD CONSTANTS ///////////////////////////////////////
void cpp_StandardConstants() {
    auto saved = true;                  // type inferred to be bool by compiler
    auto dirty = false;                 // type inferred to be bool by compiler
    std::shared_ptr<char> buffer = nullptr;  // null pointer value (see later)
}
///////////////////// ARITHMETIC OPERATIONS ///////////////////////////////////////
void cpp_Arithmetic() {
    std::cout << 9 + 30 << std::endl;         // addition (39)
    std::cout << 9 - 30 << std::endl;         // subtraction (-21)
    std::cout << -(9 *2) << std::endl;        // unary negation (-18)
    std::cout << 8 / 2 << std::endl;          // division (4)
    std::cout << 8 / 0 << std::endl;          // division by 0 (infinity or nan)
    std::cout << 9 % 4 << std::endl;          // remainder / modulus (1)
    auto a = 9;
    ++a;
    std::cout << a << std::endl;              // pre increment (10)
    a++;
    std::cout << a << std::endl;              // post increment (11)
    --a;
    std::cout << a << std::endl;              // pre decrement  (10)
    a--;
    std::cout << a << std::endl;              // post decrement (9)
}
//////////////////// COMPARISION OPERATIONS ////////////////////////////////
void cpp_Comparison() {
    std::cout << (9 == 8) << std::endl;       // equality comparison (false)
    std::cout << (9 != 8) << std::endl;       // inequality comparison (true)
    std::cout << !true << std::endl;          // negation (false)
    std::cout << (7 < 8) << std::endl;        // less than (true)
    std::cout << (7 <= 8) << std::endl;       // less than or equal (true)
    std::cout << (7 > 8) << std::endl;        // greater than (false)
    std::cout << (2 >= 2) << std::endl;       // greater than or equal (true)
}
/////////////////// LOGICAL OPERATIONS ///////////////////////////////////
void cpp_Logical() {
    std::cout << (true && false)  << std::endl;  // logical and (false)
    std::cout << (true || false) << std::endl;  // logical or (true)
}
/////////////////// BITWISE OPERATIONS //////////////////////////////////////

void cpp_Bitwise() {
    std::cout << std::hex << (0xf1 & 0x01) << std::endl;  // bitwise and (0x01)
    std::cout << std::hex << (0xf0 | 0x01) << std::endl;  // bitwise or (0xf1)
    std::cout << std::hex << (0xf0 ^ 0x0f) << std::endl;  // bitwise xor (0xff)
    std::cout << std::hex << ~0xf0f0f0 << std::endl;      // bitwise complement (0xff0f0f0f)
}
//////////////////// VARIABLES & SCOPE ///////////////////////////////////////
void cpp_VariablesAndScope() {          // void function no return value
    auto initialized = true;            // compiler type inferred to be bool
    int readCount = 0;                  // explicit type declaration
    int likeCount;                      // declared but uninitialized

    if (initialized) {
        auto readCount = 9;             // block variable shadows local readCount
        std::cout << readCount << std::endl;      // 9
    }
    std::cout << readCount << std::endl;          // 0
}
///////////////////////// REFERENCES ///////////////////////////////////////////
void cpp_ReferenceGood(int& r) {   // reference to an integer
    r = 40;                       // modify the referenced object
}

/*
void cpp_ReferencesBad(const int& r) {   // constant reference to message
  r = 20;                     // !!!compile error!!!
}
*/

void cpp_Refrences() {
    int x = 10;
    cpp_ReferenceGood(x);
    std::cout << std::dec << x << std::endl;     // ensure std::cout not still in std::hex mode
}
///////////////////// CONDITIONS & CONTROL FLOW //////////////////////////////////////
void cpp_ConditionsAndControlFlow() {
    int unreadCount = 20;                    // try changing to 0, 100
    if (unreadCount) {                       // single block if
        std::cout << "Has Unread" << std::endl;
    }

    if (unreadCount) {                       // if else
        std::cout << "Has Unread" << std::endl;
    } else {
        std::cout << "All Read" << std::endl;
    }

    if (unreadCount > 99) {             // multiple conditions
        std::cout << "Many Unread" << std::endl;
    } else if (unreadCount > 0) {
        std::cout << unreadCount << " Unread" << std::endl;
    } else {
        std::cout << "All Read" << std::endl;
    }
}
//////////////////// SWITCH STATEMENT ////////////////////////////////////////
void cpp_SwitchStatement() {
    const int TypeNormal = 0;
    const int TypeAdmin = 1;
    const int TypeOther = 2;
    int type = TypeAdmin;           // Try changing to other values

    switch(type) {
        case TypeNormal: {
            std::cout << "Normal" << std::endl;
        }
            break;

        case TypeAdmin: {
            std::cout << "Admin" << std::endl;
        }
            break;

        default: {
            std::cout << "Other" << std::endl;
        }
    }
}
/////////////////////// LOOPS ////////////////////////////////////////////
void cpp_Loops() {
    std::array<std::string, 4> messages = { "hello", "world", "foo", "bar" };

    for(int i = 0; i < messages.size(); i++) {
        std::string& m = messages[i];

        if (m == "foo") {
            std::cout << "found foo will break" << std::endl;
            break;                          // exit entire loop
        }

        if (m == "hello") {
            std::cout << "found hello will continue" << std::endl;
            continue;                       // continue loop
        }

        std::cout << "message: " << m << std::endl;
    }
}
/////////////////////// STRUCTS ///////////////////////////////////////
struct Person {
    std::string name;
    int age;
};

void cpp_StructConstruct() {
    Person jon{"jon snow", 30};
    std::cout << jon.name << " is " << jon.age << " old" << std::endl;
}

void makeOlder(Person& p) {
    p.age += 1;
}

void cpp_StructByRef() {
    Person jon{"jon snow", 30};
    makeOlder(jon);
    std::cout << jon.name << " is " << jon.age << " old" << std::endl;
}

Person makePerson(std::string first, std::string last, int age) {
    std::string name = first + " " + last;
    return Person{name, age};
}

void cpp_StructRetAsValue() {
    Person jon = makePerson("jon", "snow", 30);
    std::cout << jon.name << " is " << jon.age << " old" << std::endl;
}
///////////////////// CLASSES ///////////////////////////////////////
#pragma once

class Message {
public:                                          // public members
    Message(std::string from, std::string to, std::string subj);  // constructor method
private:                                         // private members
    std::string from_;                                  // field member
    std::string to_;                                    // field member
    std::string subj_;                                  // field member
};

Message::Message(std::string f, std::string t, std::string s)  // Method impl
        : from_{f}, to_{t}, subj_{s} {                     // Member initializer
    std::cout << "Message created" << std::endl;          // Method body
}
//////////////////////// ENUMERATIONS ////////////////////////////////////
void cpp_EnumClass() {
    enum class ValType { Number, Bool, String };
    auto t = ValType::String;

    switch (t) {
        case ValType::Number:
            std::cout << "number" << std::endl;
            break;
        case ValType::Bool:
            std::cout << "boolean" << std::endl;
            break;
        case ValType::String:
            std::cout << "std::string" << std::endl;
            break;
    }
}
//////////////////////// NAMESPACES ////////////////////////////////////////
// People/Friend.h
#pragma once
namespace People {
    class Friend {
    public:
        Friend(std::string name) : name_(name) { }
    private:
        std::string name_;
    };
}

// #include "People/Friend"
void cpp_NamespaceExplicit() {
    People::Friend bruce{"bruce wayne"};
}

void cpp_NamespaceImplicit() {
    using namespace People;
    Friend ww{"wonder woman"};
}
/////////////////// EXCEPTIONS ////////////////////////////////////////////
#include <stdexcept>
void cpp_ExceptionsThrow() {
    auto x = 200;
    if (x > 20) {
        throw std::out_of_range("a too large");
    }
}

void cpp_ExceptionsTryCatch() {
    try {
        cpp_ExceptionsThrow();
    } catch(std::out_of_range a) {
        std::cout << "exception out of range" << std::endl;
    }
}

void cpp_ExceptionsRethrow() {
    try {
        cpp_ExceptionsThrow();
    } catch(std::out_of_range) {
        std::cout << "exception out of range" << std::endl;
        throw;
    }
}
//////////////////////// METHODS ///////////////////////////////////////////
class Animal {
public:
    Animal(std::string name, float weight): name_{name}, weight_{weight} {}
    std::string getName() const { return name_; }
    std::string getWeight() const { return std::to_string(weight_) + "lbs"; }
private:
    std::string name_;
    float weight_;
};

void cpp_Methods() {
    Animal duck("donald", 8.6);
    std::cout << duck.getName() << " is " << duck.getWeight() << std::endl;
}
/////////////////// STATIC METHODS ////////////////////////////////
class Entity {
public:
    Entity(std::string name): name_{name} {}
    static Entity MakeAnEntity(std::string name);
    std::string name_;
};

Entity Entity::MakeAnEntity(std::string name) {
    return Entity{"Static " + name};
}

void cpp_StaticMethods() {
    auto ent = Entity::MakeAnEntity("gizmo");
    std::cout << ent.name_ << std::endl;
}
//////////////////// CLASS CONTAINMENT ///////////////////////////////////////
struct Attachment {
    std::string content;
};

struct ModularMessage {
    std::string from;
    std::string to;
    Attachment attachment;
    ModularMessage(std::string f, std::string t, std::string c) : from{f}, to{t}, attachment{c} {}
};

void cpp_ClassContainment() {
    ModularMessage mm{"john", "jane", "hello"};
    std::cout << mm.from << " send " << mm.attachment.content << " to " << mm.to << std::endl;
}
//////////////////////// DESTRUCTORS //////////////////////////////////////////
#include <stdio.h>
class File {
public:
    File(std::string name) {
        file_ = fopen(name.c_str(),"w");
        std::cout << "opened " << name << std::endl;
    }
    ~File() {
        fclose(file_);
        std::cout << "closed file" << std::endl;
    }
private:
    FILE* file_;
};

void cpp_Destructors() {
    { // block scoped but typically function scoped
        File f{"foo"};
    }
    std::cout << "the file should be closed now" << std::endl;
}
///////////////////////// INHERITANCE ///////////////////////////////////////////
struct Contact {
    Contact(std::string n) : name{n} {}
    virtual bool canVideoCall() { return false; };
    virtual bool canBeInGroups() = 0;
    std::string name;
};

struct PersonContact : public Contact {
    PersonContact(std::string n, std::string p) : Contact{n}, phone{p} {}
    virtual bool canVideoCall() override { return true; }
    virtual bool canBeInGroups() override { return true; }
    std::string phone;
};

struct PageContact : public Contact {
    PageContact(std::string n) : Contact(n) {}
    virtual bool canBeInGroups() override { return false; }
};

void cpp_Inheritance() {
    PersonContact sandy{"sandy", "555-1212"};
    PageContact soccer{"soccer"};
    std::cout << sandy.name << "call:" << sandy.canVideoCall() << " group:" << sandy.canBeInGroups() << std::endl;
    std::cout << soccer.name << "call:" << soccer.canVideoCall() << " group:" << soccer.canBeInGroups() << std::endl;
}
////////////////////// std::stringS ////////////////////////////////////////////
std::string to_lower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}
std::string to_upper(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), ::toupper);
    return s;
}

void cpp_Strings() {
    std::string s = "Hello";                       // initialize with literal
    s += ", World";                           // std::strings are mutable, append
    std::cout << s << std::endl;                        // Hello, World
    std::cout << s.substr(1) << std::endl;              // ello, World
    std::cout << s.substr(1,4) << std::endl;            // ello

    std::cout << to_lower(s) << std::endl;              // hello, world
    std::cout << to_upper(s) << std::endl;              // HELLO, WORLD
    std::cout << (s == "Hello") << std::endl;           // false
    std::cout << (s == "Hello, World") << std::endl;    // true
}
///////////////////////// VECTORS /////////////////////////////////////////
#include <vector>

void cpp_Vectors() {
    std::vector<Person> contacts = {
            { "Sandy", 27 },
            { "Sam", 31 },
            { "Kay", 51 }
    };

    std::cout << contacts.size() << std::endl;                 // 3
    contacts.reserve(90);                            // capacity 90, size 3
    contacts.push_back({"Jay", 52 });                // size 4
    std::cout << contacts.size() << std::endl;                 // 4
    std::cout << contacts[0].name << std::endl;                // Sandy
    // std::cout << contacts[9].name  << std::endl;            // crash no range check
    try {
        std::cout << contacts.at(9).name  << std::endl;          // std::out_of_range exception
    } catch(std::exception e) {
        std::cout << "exception" << std::endl;
    }
    contacts.erase(contacts.begin()+2);              // remove "Kay" contact
    std::cout << contacts.size() << std::endl;                 // 3
    contacts.erase(contacts.begin(),contacts.end()); // contacts is empty
    std::cout << contacts.size() << std::endl;                 // 0
}
//////////////////////// ITERATORS ////////////////////////////////////////
void cpp_Iterators() {
    std::vector<Person> contacts = {
            { "Sandy", 27 },
            { "Sam", 31 },
            { "Kay", 51 }
    };
    for(const auto& c : contacts) {
        std::cout << c.name << ", " << c.age << std::endl;   // print contact
    }
}
/////////////////////// ARRAYS ///////////////////////////////////
#include <array>

struct Node {
    std::array<float,3> translation;
    std::array<float,3> rotation;
    std::array<float,3> scaling;

    std::vector<Node> children;
};

void cpp_Arrays() {
    Node n{ { 1,2,3 }, {4, 5, 6}, {1, 1, 1}, {} };
    std::cout << "x0: " << n.translation[0] << ", r1: " << n.rotation[1] << std::endl;
}
/////////////////////// LAMBDAS /////////////////////////////////////////
void cpp_Lambdas() {
    auto d = 90;
    auto c = 100;

    auto no_capture = [](int z) {
        // d = z * 3;      // compile error => can't change d
        return z * 3;
    };

    auto capture_all_by_ref = [&](int z) {
        d = z; c = z;
    };

    auto capture_one_by_ref = [&d](int z) {
        d = z * d;
    };

    auto capture_all_by_copy = [=](int z) {
        // d = z * 3;      // compile error => can't change d
    };

    no_capture(10);
    std::cout << "no_capture: d = " << d << ", c = " << c << std::endl;

    capture_all_by_ref(20);
    std::cout << "capture_all_by_ref: d = " << d << ", c = " << c << std::endl;

    capture_one_by_ref(30);
    std::cout << "capture_all_by_ref: d = " << d << ", c = " << c << std::endl;

    capture_all_by_copy(40);
    std::cout << "capture_all_by_copy: d = " << d << ", c = " << c << std::endl;
}
///////////////////// FIND //////////////////////////////////
void cpp_FindWithIterators() {
    std::vector<Person> contacts = {
            { "Sandy", 27 },
            { "Sam", 31 },
            { "Kay", 51 }
    };
    auto start = contacts.begin();
    auto end = contacts.end();
    std::string lookFor = "Sam";
    auto p = find_if(start, end, [=](const Person& o) -> bool {
        return o.name == lookFor;
    });

    if (p == end) {
        std::cout << "not found" << std::endl;
    }
    std::cout << "found " << lookFor << " age " << p->age << std::endl;
}
//////////////////// INITIALIZER LISTS ////////////////////////////////////
class MultiTargetMessage {
public:
    MultiTargetMessage(std::string f, std::initializer_list<std::string> t) : from_{f}, to_{t} {}
    std::string from_;
    std::vector<std::string> to_;
};

void cpp_InitializerLists() {
    MultiTargetMessage m{"admin", {"jack", "jill", "sam"} };
    std::cout << "second to is " << m.to_[1] << std::endl;
}
///////////////// OPERATOR OVERLOADING /////////////////////////////////
struct Complex {
    Complex& operator+=(Complex o) {
        re += o.re;
        im += o.im;
        return *this;
    }
    Complex operator+(Complex y) {
        return { re + y.re, im + y.im };
    }
    double re;
    double im;
};

void cpp_OperatorOverloading() {
    Complex a{3,1};
    Complex b{1,6};
    auto c = a + b;
    std::cout << c.re << ", " << c.im << std::endl;

    a += { 9, 10 };
    std::cout << a.re << ", " << a.im << std::endl;
}
//////////////////// EXPLICIT CONSTRUCTORS ////////////////////////////////////////
struct AllowsImplicit {
    AllowsImplicit(int x) : data_{x} {}
    std::vector<int>data_;
};

struct OnlyExplicit {
    explicit OnlyExplicit(int x) : data_{x} {}
    std::vector<int> data_;
};

void cpp_ExplicitConstructors() {
    AllowsImplicit constructAllowsImplicit(10);
    AllowsImplicit assignAllowsImplicit = 20;
    OnlyExplicit constructAllowsExplicit(30);
    // OnlyExplicit assignOnlyExplicit = 40; <<<< Will not compile
}
//////////////// TYPE ALIAS AND USING ////////////////////////////////////////
void cpp_Using() {
    using stringIntVector = std::vector<std::pair<std::string, int>>;
    stringIntVector div = { { "hi", 1 }, { "world", 2 } };
    std::cout << div[0].first << "," << div[0].second << std::endl;
}
//////////////////// UNIQUE POINTERS ///////////////////////////////////////
using UniqueAttachment = std::unique_ptr<Attachment>;

struct MessageWithDynamicAttachment {
    UniqueAttachment attachment;
    void makeAttachment() {
        attachment = UniqueAttachment{new Attachment()};
    }
};

void cpp_UniquePointers() {
    MessageWithDynamicAttachment m;
    std::cout << "has attachment " << (m.attachment != nullptr) << std::endl;
    m.makeAttachment();
    std::cout << "has attachment " << (m.attachment != nullptr) << std::endl;
}
///////////////////// DYNAMIC CAST ////////////////////////////////
struct Base {
    virtual void something() { }        // to allow polymorphism
};
struct Derived1 : public Base {
};

struct Derived2 : public Base {
};

void cpp_DynamicCast() {
    using UniqueBase = std::unique_ptr<Base>;

    UniqueBase b1 = UniqueBase{ new Derived1 };
    UniqueBase b2 = UniqueBase{ new Derived2 };

    std::cout << "b1 " << dynamic_cast<Derived1*>(b1.get()) << std::endl;
    std::cout << "b1 " << dynamic_cast<Derived2*>(b1.get()) << std::endl;
    std::cout << "b2 " << dynamic_cast<Derived1*>(b2.get()) << std::endl;
    std::cout << "b2 " << dynamic_cast<Derived2*>(b2.get()) << std::endl;
}
///////////////////////// SHARED POINTERS //////////////////////////////
using Bytes = std::vector<char>;
using SharedBytes = std::shared_ptr<Bytes>;

struct Buffer {
    void takeData(SharedBytes d) { data_ = d; }
    void clearData() { data_ = nullptr; }
    SharedBytes data_;
};

void cpp_SharedPointers() {
    auto d1 = SharedBytes{ new Bytes(2000) };

    std::cout << "d1 has " << d1.use_count() << " references" << std::endl;
    Buffer b1;
    b1.takeData(d1);                             // d1 has 2 references
    std::cout << "d1 has " << d1.use_count() << " references" << std::endl;
    Buffer b2;
    b2.takeData(d1);                             // d1 has 3 references
    std::cout << "d1 has " << d1.use_count() << " references" << std::endl;
    b1.clearData();                              // d1 has 2 references
    std::cout << "d1 has " << d1.use_count() << " references" << std::endl;
    b2.clearData();                              // d1 has 1 references
    std::cout << "d1 has " << d1.use_count() << " references" << std::endl;
    d1 = nullptr;                                // d1 has 0 refs -> destructed
}
///////////////////////// REGULAR EXPRESSIONS //////////////////////////////
#include <regex>
void cpp_Regex() {
    auto matchZipCode = [](std::string zip) {
        std::regex pattern{R"((\w{2}\s)*\d{5}(-\d{4})?)"};
        std::smatch matches ;
        return regex_search(zip, matches, pattern);
    };
    std::cout << matchZipCode("96816") << std::endl;                // true
    std::cout << matchZipCode("H234") << std::endl;                 // false
    std::cout << matchZipCode("CA 55434-1234") << std::endl;        // true
}
///////////////////////// REGULAR EXPRESSIONS ITERATORS /////////////////////
void cpp_RegexIterators() {
    std::string inp = "11 a; a123 999";
    auto end = std::sregex_iterator{};
    std::regex pat{R"(\d+[\s|$])"};
    for(std::sregex_iterator p(inp.begin(),inp.end(),pat); p!=end; p++) {
        std::cout << (*p)[0] << ' ';                              // 11 123 999
    }
    std::cout << std::endl;
}

/////////////////////////////// LIST ///////////////////////////////////
#include <list>
void cpp_List() {
    auto print = [](std::list<int> l) {
        for(const auto& i : l) {
            std::cout << i << " ";                  // 9 3 1
        }
        std::cout << std::endl;
    };
    std::list<int> l = { 9, 3, 1 };
    print(l);
    l.insert(l.begin(), 2);                // 2 9 3 1
    print(l);
    auto e = l.end();
    e--;
    l.erase(e);                            // 2 9 3
    print(l);
}
////////////////////////// MAP /////////////////////////////////////////////
#include <map>
void cpp_Map() {
    std::map<std::string,int> m = {{"Jane", 9}, {"Joe", 12}, {"Kay", 1}};
    std::cout << m["Jane"] << std::endl;                      // 9
    std::cout << m["Kim"] << std::endl;                       // Dangerous 0 is default
    m["Kim"] = 17;
    std::cout << m["Kim"] << std::endl;                       // 17
}
///////////////////// UNORDERED MAP ////////////////////////////////////////
#include <unordered_map>
void cpp_UnorderedMap() {
    std::unordered_map<std::string,int> m = {{"Jane", 9}, {"Joe", 12}, {"Kay", 1}};
    std::cout << m["Jane"] << std::endl;                      // 9
    std::cout << m["Kim"] << std::endl;                       // Dangerous 0 is default
    m["Kim"] = 17;
    auto p = m.find("Kim");
    std::cout << p->second << std::endl;                      // 17
}

//////////////////////// ALGORITHMS ////////////////////////////////////////
void cpp_Algorithms() {
    std::vector<int> v = { 9, 3, 7, 9 };

    sort(v.begin(), v.end());               // sort
    for(const auto& i : v) {
        std::cout << std::to_string(i) << " ";
    }
    std::cout << std::endl;

    std::list<int> l;
    unique_copy(v.begin(), v.end(), back_inserter(l));     // remove duplicates
    for(const auto& i : l) {
        std::cout << std::to_string(i) << " ";
    }
    std::cout << std::endl;

    std::map<std::string, int> m = {{"Abc",1}, {"Work",90}};
    auto pred = [](const std::pair<std::string,int>& r) {
        return r.second>10;
    };
    auto r = find_if(m.begin(), m.end(), pred);
    std::cout << r->first << std::endl;                   // Work
}
//////////////////////// STREAMS ////////////////////////////////////////
struct SerializablePerson {
    std::string name;
    int phone;

    // serialize to stream
    friend std::ostream& operator<<(std::ostream& os, const SerializablePerson& p) {
        return os << p.name << ": " << p.phone;
    }

    // deserialize from stream
    friend std::istream& operator>>(std::istream& is, SerializablePerson& p) {
        char cr1, cr2;
        std::string name;
        int phone;
        is >> name >> phone;

        if (name.size() && phone > 0) {
            p = {name, phone};
            return is;
        }
        is.setstate(std::ios_base::failbit);
        return is;
    }
};
#include <sstream>
void cpp_Streams() {
    SerializablePerson han{"Han Solo", 5551212};
    std::cout << han << std::endl;
    std::string text = "Leia\n1212555\n";
    std::stringstream ss;
    ss << text;
    SerializablePerson leia;
    ss >> leia;
    std::cout << leia << std::endl;
}
//////////////////////// STREAM ITERATORS ////////////////////////////////////////
void cpp_StreamIterators() {
    std::stringstream str("1 2 1 3 4");
    copy(std::istream_iterator<int>(str), std::istream_iterator<int>(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}
/////////////////////////// TIME /////////////////////////////////////
#include <chrono>
#include <thread>
void cpp_Time() {
    using namespace std::chrono;
    auto t1 = high_resolution_clock::now();
    std::this_thread::sleep_for(milliseconds{250});
    auto t2 = high_resolution_clock::now();
    std::cout << duration_cast<milliseconds>(t2 - t1).count() << "ms\n";
}
//////////////////////////// MATH //////////////////////////////////////
#include <cerrno>
//#include <cmath>                                // float, double, long double
void cpp_Math() {
    std::cout << abs(-1)     << ", "     <<  ceil(3.1)   << "\n";
    std::cout << floor(3.1)  << ", "     <<  sqrt(4)     << "\n";
    std::cout << cos(3.14)   << ", "     <<  sin(3.14)   << "\n";
    std::cout << tan(0.1)    << ", "     <<  acos(0)     << "\n";
    std::cout << asin(1)     << ", "     <<  atan(0)     << "\n";
    std::cout << sinh(0.1)   << ", "     <<  cosh(0.1)   << "\n";
    std::cout << tanh(0.1)   << ", "     <<  exp(2)      << "\n";
    std::cout << log(3)      << ", "     <<  log10(3)    << "\n";

    auto i = sqrt(-1);                              // bad real math
    std::cout  << isnan(i) << std::endl;               // true
    auto max = std::numeric_limits<double>::max();
    auto j = pow(max,2);
    std::cout << isinf(j) << std::endl;              // true
}
/////////////////////////// NUMERIC /////////////////////////////////////
#include <numeric>
void cpp_Numeric() {
    std::array<int,3> a = {1, 2, 3};
    auto sum = std::accumulate(a.begin(), a.end(), 0);
    std::cout << sum << "\n";                                // 6
}
/////////////////////////// RANDOM /////////////////////////////////////
#include <random>
void cpp_Random() {
    auto engine = std::default_random_engine{0};
    for(auto i = 0; i < 5; i++) {
        auto dist = std::uniform_int_distribution<int>{1,6};
        auto dice = dist(engine);
        std::cout << dice << std::endl;
    }
}
/////////////////////////// LIMITS /////////////////////////////////////
#include <limits>
void cpp_Limits() {
    int maxChar = std::numeric_limits<char>::max();
    std::cout << maxChar << std::endl;
    std::cout << std::numeric_limits<char>::is_signed << std::endl;
    std::cout << std::numeric_limits<int>::max() << std::endl;
}
/////////////////////////// ASYNC /////////////////////////////////////
#include <future>
void cpp_Async() {
    auto sum = [](std::vector<int> array, int start, int end) {
        auto result = 0;
        for(auto i = start; i < end; i++) {
            result += array[i];
        }
        return result;
    };

    std::vector<int> data = { 1, 2, 3, 4, 5, 6, 7, 8 };  // imagine this is very large
    auto t1 = async(sum, data, 0, 4);               // t1 & t2 running parallel
    auto t2 = async(sum, data, 4, 8);               // t1 & t2 running parallel
    auto sum1 = t1.get();                           // wait for t1 to complete
    auto sum2 = t2.get();                           // wait for t2 to complete
    std::cout << "total: " << sum1+sum2 << std::endl;         // results 36
}
/////////////////////////// THREADS /////////////////////////////////////
#include <thread>
void cpp_Threads() {
    std::mutex m;

    int total = 0;
    auto sum =[&](std::vector<int> array, int start, int end) {
        for(int i=start; i < end; i++) {
            std::unique_lock<std::mutex> lock{m};                 // alternative manual m.lock()
            // and m.unlock() calls
            total += array[i];
        }
    };
    std::vector<int> data = { 1, 2, 3, 4, 5, 6, 7, 8 };  // imagine this is very large
    std::thread t1([&]() { sum(data, 0, 4); });          // run t1
    std::thread t2([&]() { sum(data, 4, 8); });          // run t2
    t1.join();                                      // wait for t1
    t2.join();                                      // wait for t2
    std::cout << "total: " << total << std::endl;             // results 36
}
/////////////////////////// EVENTS /////////////////////////////////////
#include <queue>
#include <chrono>
void cpp_Events() {
    std::queue<std::string> messages;
    std::condition_variable cond;
    std::mutex m;

    auto consumer= [&]() {
        while(true) {
            std::unique_lock<std::mutex> lock{m};
            cond.wait(lock);
            auto msg = messages.front();
            messages.pop();
            lock.unlock();
            std::cout << "received: " << msg << std::endl;
            if (msg == "quit") {
                break;
            }
        }
    };

    auto producer = [&]() {
        using namespace std::chrono;
        std::vector<std::string> list = { "hello", "world", "quit" };
        for(const auto& msg : list) {
            std::unique_lock<std::mutex> lock{m};
            messages.push(msg);
            cond.notify_one();
            m.unlock();
            std::this_thread::sleep_for(milliseconds{250});
        }
    };

    std::thread prod([&]() { consumer(); });
    std::thread cons([&]() { producer(); });
    prod.join();
    cons.join();
}
/////////////////////////// UNIONS /////////////////////////////////////
union VarUnion {                    // numVal OR bVal can be used
    int numVal;
    bool bVal;
};

struct VarValue {                   // Can be have both numVal and bVal used
    int numVal;
    bool bVal;
};

enum class ValType { Number, String, Bool };

class Variant {
public:
    Variant(int i) : type{ValType::Number} { value.numVal = i; }
    Variant(bool b) : type{ValType::Bool} { value.bVal = b; }
    int iVal() const { return value.numVal; }
    int bVal() const { return value.bVal; }
private:
    ValType type;
    VarUnion unionValue;           // Will use 4 bytes (sizeof int)
    VarValue value;                // Uses use 8 bytes (sizeof int and bool)
};

void cpp_Unions() {
    Variant v1(20);
    std::cout << v1.iVal() << std::endl;
    Variant v2(true);
    std::cout << v1.bVal() << std::endl;
}


void b ()
{
    using namespace boost::locale;
    using namespace std;
    generator gen;
    locale loc=gen("");
    // Create system default locale

    locale::global(loc);
    // Make it system global

    cout.imbue(loc);
    // Set as default locale for output

    cout <<format("Today {1,date} at {1,time} we had run our first localization example") % time(0)
         <<endl;

    cout<<"This is how we show numbers in this locale "<<as::number << 103.34 <<endl;
    cout<<"This is how we show currency in this locale "<<as::currency << 103.34 <<endl;
    cout<<"This is typical date in the locale "<<as::date << std::time(0) <<endl;
    cout<<"This is typical time in the locale "<<as::time << std::time(0) <<endl;
    cout<<"This is upper case "<<to_upper("Hello World!")<<endl;
    cout<<"This is lower case "<<to_lower("Hello World!")<<endl;
    cout<<"This is title case "<<to_title("Hello World!")<<endl;
    cout<<"This is fold case "<<fold_case("Hello World!")<<endl;
}




static void print_uri(const folly::fbstring& address) {
    const folly::Uri uri(address);
    const auto authority = folly::format("The authority from {} is {}", uri.fbstr(), uri.authority());
    std::cout << authority << std::endl;
}

int fb() {
    folly::ThreadedExecutor executor;
    folly::Promise<folly::fbstring> promise;
    folly::Future<folly::fbstring> future = promise.getSemiFuture().via(&executor);
    folly::Future<folly::Unit> unit = std::move(future).thenValue(print_uri);
    promise.setValue("https://conan.io/");
    std::move(unit).get();
    return 0;
}


int foo ()
{

    std::cout << std::boolalpha;
    std::cout << "Minimum value for int: " << std::numeric_limits<int>::min() << '\n';
    std::cout << "Maximum value for int: " << std::numeric_limits<int>::max() << '\n';
    std::cout << "int is signed: " << std::numeric_limits<int>::is_signed << '\n';
    std::cout << "Non-sign bits in int: " << std::numeric_limits<int>::digits << '\n';
    std::cout << "int has infinity: " << std::numeric_limits<int>::has_infinity << '\n';


    std::cout << std::boolalpha;
    std::cout << "Minimum value for long: " << std::numeric_limits<long>::min() << '\n';
    std::cout << "Maximum value for long: " << std::numeric_limits<long>::max() << '\n';
    std::cout << "long is signed: " << std::numeric_limits<long>::is_signed << '\n';
    std::cout << "Non-sign bits in long: " << std::numeric_limits<long>::digits << '\n';
    std::cout << "long has infinity: " << std::numeric_limits<long>::has_infinity << '\n';

    std::cout << std::boolalpha;
    std::cout << "Minimum value for long long: " << std::numeric_limits<long long>::min() << '\n';
    std::cout << "Maximum value for long long: " << std::numeric_limits<long long>::max() << '\n';
    std::cout << "long long is signed: " << std::numeric_limits<long long>::is_signed << '\n';
    std::cout << "Non-sign bits in long long: " << std::numeric_limits<long long>::digits << '\n';
    std::cout << "long long has infinity: " << std::numeric_limits<long long>::has_infinity << '\n';
    return 0;
}
template <typename T>
void populate (T &data) {
    data.insert({"a", {1,4}});
    data.insert({"b", {3,1}});
    data.insert({"c", {2,3}});
}
template <typename T>
auto merge (T data, T upcoming_data) {
    auto result = data;
    for (auto it: upcoming_data) {
        result.insert(it);
    }
    return result;
}


int at () {
    std::map<std::string, std::pair<int,int>> data;
    populate(data);
    std::map<std::string, std::pair<int,int>> upcoming_data;
    upcoming_data.insert({"d", {5,3}});
    auto final_data = merge(data, upcoming_data);

    for (auto itr : final_data) {
        auto [v1, v2] = itr.second;
        std::cout << itr.first << " " << v1 << " " << v2 << std::endl;
    }
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, const char * argv[]) {
    at();
    t();
    fb();

    foo();
    std::cout << isEven(12) << std::endl;                 // will show 1
    memTest("/Users/i500845/dmoz/dmoz_domain_category.csv", 0, 1000);
    chris();
    cpp_BasicTypes();
    cpp_StandardConstants();
    cpp_Arithmetic();
    cpp_Comparison();
    cpp_Logical();
    cpp_Bitwise();
    cpp_VariablesAndScope();
    cpp_Refrences();
    cpp_ConditionsAndControlFlow();
    cpp_SwitchStatement();
    cpp_Loops();
    cpp_StructConstruct();
    cpp_StructByRef();
    cpp_StructRetAsValue();
    cpp_EnumClass();
//  cpp_ExceptionsThrow();
    cpp_ExceptionsTryCatch();
//  cpp_ExceptionsRethrow();
    cpp_Methods();
    cpp_StaticMethods();
    cpp_ClassContainment();
    cpp_Destructors();
    cpp_Inheritance();
    cpp_Strings();
    cpp_Vectors();
    cpp_Iterators();
    cpp_Arrays();
    cpp_Lambdas();
    cpp_FindWithIterators();
    cpp_InitializerLists();
    cpp_OperatorOverloading();
    cpp_Using();
    cpp_UniquePointers();
    cpp_DynamicCast();
    cpp_SharedPointers();
    cpp_Regex();
    cpp_RegexIterators();
    cpp_List();
    cpp_Map();
    cpp_UnorderedMap();
    cpp_Algorithms();
    cpp_Streams();
    cpp_StreamIterators();
    cpp_Time();
    cpp_Math();
    cpp_Numeric();
    cpp_Random();
    cpp_Limits();
    cpp_Async();
    cpp_Threads();
    cpp_Events();
    cpp_Unions();
    return 0;
}


/*


 */