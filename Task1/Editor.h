#include "Document.h"

class Editor {
   private:
    Document document;
    std::vector<std::string> split(std::string line, char token);
    bool dot_typed;

   public:
    Editor();
    ~Editor();
    void loop();
    void editor(std::string line);
    void row_jump(std::string line);
    void set_dot_flag(bool v);
    void print_body();
    void print(std::string line);
    bool is_search(std::string line);
    bool is_replace_old_new(std::string line);
    bool is_row_jump(std::string line);
    bool is_digit(std::string line);
    bool is_write_file(std::string line);
    bool is_editor(std::string);
};
