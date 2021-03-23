#include <string>
#include <vector>

class Document {
   private:
    std::vector<std::string> body;
    int currentline, direction, multi_values;

   public:
    Document();
    ~Document();
    void def_a();
    void def_i();
    void def_c();
    void def_d();
    void def_j(int value);
    void def_search_text(std::string line);
    void def_replace(std::string line);
    void text_parser(std::string line);
    void set_EOF();
    void open_file(std::string);
    void set_multi_values(int num);
    void write_to_file(std::string line);
    void set_currentline(int num);
    int get_direction();
    int get_currentline();
    void print();
};
